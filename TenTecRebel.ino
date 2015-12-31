#include "TenTecRebel.h"

void setup() {
  pinMode(SCLK_BIT, OUTPUT);    // clock
  pinMode(FSYNC_BIT, OUTPUT);    // fsync
  pinMode(SDATA_BIT, OUTPUT);    // data
  pinMode(RESET_BIT, OUTPUT);    // reset
  pinMode(FREQ_REGISTER_BIT, OUTPUT);    // freq register select
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
  
  digitalWrite(FSYNC_BIT, HIGH);  // 
  digitalWrite(SCLK_BIT, HIGH);  //

  //Check for user input
  pollRIT();
  pollMultifunctionButton(); 
  pollSelectButton();
  pollRotaryEncoder();

  if (keyerOn) {
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
  } else {
    //No keyer, treat it as a straight key
    setTransmit( getDitKey() );
  }

  //Run the decoder if it's turned on
  if (decoderOn) {
    decodeRoutine();
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
  digitalWrite (FREQ_REGISTER_BIT, LOW);

  setBandwidth(BANDWIDTH_WIDE);
  setBand(getCurrentBand() );
  setStepSize(STEP_100HZ);
  setMultifunction(MULTIFUNCTION_1);
  setFunction(FUNCTION_1);
  setDecoder(true);
  setDecodeThreshhold(700);
  setKeyer(true);
  setKeyerWPM(20);
} //end loadDefaultSettings()
