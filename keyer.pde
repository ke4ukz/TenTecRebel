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
