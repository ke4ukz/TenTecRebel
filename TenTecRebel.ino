/*
 * Ten Tec Rebel 506 Radio Firmware
 * Copyright 2015, 2016 Jonathan Dean (ke4ukz@gmx.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "TenTecRebel.h"

void setup() {
  pinMode(PIN_AD9834_SCLK, OUTPUT);    // clock
  pinMode(PIN_AD9834_FSYNC, OUTPUT);    // fsync
  pinMode(PIN_AD9834_SDATA, OUTPUT);    // data
  pinMode(PIN_AD9834_RESET, OUTPUT);    // reset
  pinMode(PIN_AD9834_FREQ_REGISTER, OUTPUT);    // freq register select
  pinMode(PIN_TRANSMIT, OUTPUT);
  pinMode(PIN_TT_LED, OUTPUT);
  pinMode(PIN_MULTIFUNCTION_GREEN, OUTPUT);    // Band width
  pinMode(PIN_MULTIFUNCTION_YELLOW, OUTPUT);    // Step size
  pinMode(PIN_MULTIFUNCTION_RED, OUTPUT);    // Other
  pinMode(PIN_MULTIFUNCTION_BUTTON, INPUT);     // Choose from Band width, Step size, Other
  pinMode(PIN_SELECT_GREEN, OUTPUT);    //  BW wide, 100 hz step, other1
  pinMode(PIN_SELECT_YELLOW, OUTPUT);    //  BW medium, 1 khz step, other2
  pinMode(PIN_SELECT_RED, OUTPUT);    //  BW narrow, 10 khz step, other3
  pinMode(PIN_MEDIUM_A8, OUTPUT);    // Hardware control of I.F. filter Bandwidth
  pinMode(PIN_NARROW_A9, OUTPUT);    // Hardware control of I.F. filter Bandwidth
  pinMode(PIN_SIDETONE, OUTPUT);    // sidetone enable
  pinMode(PIN_ENCODER0A, INPUT);     // using optical for now
  pinMode(PIN_ENCODER0B, INPUT);     // using optical for now 
  pinMode(PIN_KEY_DIT, INPUT);     // Dit Key line 
  pinMode(PIN_KEY_DAH, INPUT);     // Dah Key line
  pinMode(PIN_SELECT_BUTTON, INPUT);     //  Selection form the above
  pinMode(PIN_BAND_SELECT, INPUT);     // select
  
  //Turn the LEDs on
  digitalWrite(PIN_MULTIFUNCTION_RED, HIGH);
  digitalWrite(PIN_SELECT_RED, HIGH);
  digitalWrite(PIN_MULTIFUNCTION_YELLOW, HIGH);
  digitalWrite(PIN_SELECT_YELLOW, HIGH);
  digitalWrite(PIN_MULTIFUNCTION_GREEN, HIGH);
  digitalWrite(PIN_SELECT_GREEN, HIGH);
  digitalWrite(PIN_TT_LED, HIGH);
  delay(1000);
  
  serialInit();
  loadDefaultSettings();
  AD9834_init();
  AD9834_reset();
  serialSend(SERIAL_INITDONE);
} //end setup()

void loop() {
  static unsigned long lastSerialDump = 0;
  static unsigned long lastBandscan = 0;
  
  //digitalWrite(PIN_AD9834_FSYNC, HIGH);  // 
  //digitalWrite(PIN_AD9834_SCLK, HIGH);  //

  //Check for user input
  pollRIT();
  pollMultifunctionButton(); 
  pollSelectButton();
  pollRotaryEncoder();

  //Keyer/key stuff
  switch (keyerMode) {
    case KEYER_DISABLED:
      if (isTransmitting) setTransmit(false);
      break;
    case KEYER_IAMBIC:
      //If not transmitting and not pausing between dits or dahs, see if either the user has tapped the key or send a character
      if (!isTransmitting) {
        if (millis() >= transmitInhibitUntil) {
          if (!morseSending) {
            if (getDitKey()) {
              sendDit();
            } else if (getDahKey()) {
              sendDah();
            }
          } else {
            sendNextSignal();
          }
        }
      }
      //If we're transmitting, see if we should stop yet
      if ((millis() >= transmitUntil) && isTransmitting) {
        setTransmit(false);
        transmitInhibitUntil = (millis() + ditDuration);
      }
      break;
    case KEYER_STRAIGHT:
      //No keyer, treat it as a straight key
      setTransmit( getDitKey() );
      break;
    case KEYER_TUNE:
      if (!isTransmitting) setTransmit(true);
      break;
  }

  //Run the Morse decoder if it's turned on
  if (decoderOn) {
    decodeRoutine();
  }

  //Run a bandscan if necessary
  if ( !isTransmitting && (millis() - lastBandscan > bandscanInterval)  && (bandscanMode != BANDSCAN_OFF) ) {
    performBandscan();
    serialSendBandscan();
    lastBandscan = millis();
  }

  //Report data
  if((millis() - lastSerialDump) >= serialReportInterval) {
    serialDump();
    lastSerialDump = millis();
  }
  
  //Process incoming serial data
  while (Serial.available() > 0) {
    serialReceive((byte)Serial.read());
  }
} //end loop()

void loadDefaultSettings() {
  digitalWrite (PIN_TRANSMIT, LOW);
  digitalWrite (PIN_TT_LED, LOW);
  digitalWrite (PIN_SIDETONE, LOW);
  digitalWrite (PIN_AD9834_FREQ_REGISTER, LOW);

  setBand(getCurrentBand() );
  setStepSize(STEP_100HZ);
  setBandwidth(BANDWIDTH_WIDE);
  setMultifunction(MULTIFUNCTION_1);
  setFunction(FUNCTION_1);
  setBandscanMode(BANDSCAN_OFF);
  setBandscanWidth(5000);
  setBandscanInterval(1000);
  setDecoder(true);
  setDecodeThreshhold(700);
  setKeyerMode(KEYER_IAMBIC);
  setKeyerWPM(20);
  setWraparoundTuning(false);
} //end loadDefaultSettings()

void sendUpdate() {
  serialSend(SERIAL_VOLTMETER, getPowerIn() );
  serialSend(SERIAL_OUTPUTPOWER, getPowerOut() );
  serialSend(SERIAL_SMETER, getSignalStrength() );
  serialSend(SERIAL_BAND, getCurrentBand() );
  serialSend(SERIAL_STEPSIZE, frequency_step);
  serialSend(SERIAL_TXFREQUENCY, currentFrequency+IF);
  serialSend(SERIAL_RXFREQUENCY, currentFrequency + RitFrequencyOffset + IF);
  //More to come
}
