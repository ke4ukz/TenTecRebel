#include "keyer.h"

void sendDit() {
  transmitUntil = (millis() + ditDuration);
  setTransmit(true);
}

void sendDah() {
  transmitUntil = (millis() + 3 * ditDuration);
  setTransmit(true);
}

bool getDitKey() {
  return (digitalRead(PIN_KEY_DIT) == LOW);
}

bool getDahKey() {
  return (digitalRead(PIN_KEY_DAH) == LOW);
}

void setKeyerWPM(int wpm) {
  ditDuration = 1200 / wpm;
  serialSend(SERIAL_WPM, wpm);
}

void sendCharacter(char toSend) {
  if (!morseSending) {
    if (toSend == ' ') {
      transmitInhibitUntil = (millis() + 7 * ditDuration);
      morseSignal[0] = '\0';
      morseSignalPos = 0;
      morseSending = true;
    } else {
      int i, test, morseTablePos, startLevel, add;
      
      for (i=0; i<morseTableLength; i++) if (morseTable[i] == toSend) break;
      morseTablePos = i+1;  // 1-based position
      
      // Reverse dichotomic / binary tree path tracing
      // Find out what level in the binary tree the character is
      for (i=0; i<morseTreeLevels; i++) {
        test = (morseTablePos + (0x0001 << i)) % (0x0002 << i);
        if (test == 0) break;
      }
      startLevel = i;
      morseSignals = morseTreeLevels - i; // = the number of dots and/or dashes
      morseSignalPos = 0;
      
      // Travel the reverse path to the top of the morse table
      if (morseSignals > 0) {
        // build the morse signal (backwards from last signal to first)
        for (i = startLevel; i<morseTreeLevels; i++) {
          add = (0x0001 << i);
          test = (morseTablePos + add) / (0x0002 << i);
          if (test & 0x0001 == 1) {
            morseTablePos += add;
            // Add a dot to the temporary morse signal string
            morseSignal[morseSignals-1 - morseSignalPos++] = '.';
          } else {
            morseTablePos -= add;
            // Add a dash to the temporary morse signal string
            morseSignal[morseSignals-1 - morseSignalPos++] = '-';
          }
        }
      } else {  // unless it was on the top to begin with (A space character)
        morseSignal[0] = ' ';
        morseSignalPos = 1;
        morseSignals = 1; // cheating a little; a wordspace for a "morse signal"
      }
      morseSignal[morseSignalPos] = '\0';
      
      if (morseSignalPos > 0) {
        morseSignalPos = 0;
        morseSending = true;
      }
    }
  }
}

void sendNextSignal() {
  char curSignal = morseSignal[morseSignalPos];
  if (curSignal == '.') {
    sendDit();
  } else if (curSignal == '-') {
    sendDah();
  } else if (curSignal == ' ') {
    transmitInhibitUntil = millis() + ditDuration;
  } else if ( (curSignal == '\0') || (morseSignalPos == morseSignals) ) {
    morseSending = false;
    serialSend(SERIAL_CHAR_SENT);
  }
  morseSignalPos++;
}

void setKeyer(bool turnon) {
  keyerOn = turnon;
  serialSend(SERIAL_KEYER, (keyerOn == true ? 1 : 0) );
}

void setDecoder(bool turnon) {
  decoderOn = turnon;
  serialSend(SERIAL_DECODER, (decoderOn == true ? 1 : 0) );
}

void setDecodeThreshhold(int thresh) {
  decodeThreshhold = thresh;
  serialSend(SERIAL_DECODETHRESHHOLD, thresh);
}

void decodeRoutine() {
  static unsigned long markTime = 0;    // timers for mark and space in morse signal
  static unsigned long spaceTime = 0;   // E=MC^2 ;p
  static unsigned long lastDebounceTime = 0;
  static int morseTableJumper = (morseTreetop+1)/2;
  static int morseTablePointer = morseTreetop;
  static boolean morseSignalState = false;
  static boolean morseSpace = false;    // Flag to prevent multiple received spaces
  static boolean gotLastSig = true;     // Flag that the last received morse signal is decoded as dot or dash

  int audioMorse = analogRead(PIN_CWREAD);
  unsigned long currentTime = millis();
  // Check for an audio signal...
  if (audioMorse > decodeThreshhold) {
    // If this is a new morse signal, reset morse signal timer
    if (currentTime - lastDebounceTime > ditDuration/2) {
      markTime = currentTime;
      morseSignalState = true; // there is currently a signal
    }
    lastDebounceTime = currentTime;
  } else {
    // if this is a new pause, reset space time
    if (currentTime - lastDebounceTime > ditDuration/2 && morseSignalState == true) {
      spaceTime = lastDebounceTime; // not too far off from last received audio
      morseSignalState = false;        // No more signal
    }
  }

  if (!morseSignalState) {
    if (!gotLastSig) {
      if (morseTableJumper > 0) {
        // if pause for more than half a dot, get what kind of signal pulse (dot/dash) received last
        if (millis() - spaceTime > ditDuration/2) {
          // if signal for more than 1/4 dotTime, take it as a valid morse pulse
          if (spaceTime-markTime > ditDuration/4) {
            // if signal for less than half a dash, take it as a dot, else if not, take it as a dash
            // (dashes can be really really long...)
            if (spaceTime-markTime < (ditDuration*3)/2) {
              morseTablePointer -= morseTableJumper;
            } else {
              morseTablePointer += morseTableJumper;
            }
            morseTableJumper /= 2;
            gotLastSig = true;
          }
        }
      } else { // error if too many pulses in one morse character
        //Serial.println("<ERROR: unrecognized signal!>");
        serialSend(SERIAL_RECEIVE_CHAR, '~');
        gotLastSig = true;
        morseTableJumper = (morseTreetop+1)/2;
        morseTablePointer = morseTreetop;
      }
    }
    // Write out the character if pause is longer than 2/3 dash time (2 dots) and a character received
    if ((millis()-spaceTime >= (ditDuration*2)) && (morseTableJumper < ((morseTreetop+1)/2))) {
      char morseChar = morseTable[morseTablePointer];
      //Serial.print(morseChar);
      serialSend(SERIAL_RECEIVE_CHAR, morseChar);
      morseTableJumper = (morseTreetop+1)/2;
      morseTablePointer = morseTreetop;
    }
    // Write a space if pause is longer than 2/3rd wordspace
    if (millis()-spaceTime > ((ditDuration*7)*2/3) && morseSpace == false) {
      serialSend(SERIAL_RECEIVE_CHAR, ' ');
      morseSpace = true ; // space written-flag
    }
    
  } else {
    // while there is a signal, reset some flags
    gotLastSig = false;
    morseSpace = false;
  }
}
