#include "TenTecRebel.h"

void setup() {
  // these pins are for the AD9834 control
  pinMode(SCLK_BIT, OUTPUT);    // clock
  pinMode(FSYNC_BIT, OUTPUT);    // fsync
  pinMode(SDATA_BIT, OUTPUT);    // data
  pinMode(RESET_BIT, OUTPUT);    // reset
  pinMode(FREQ_REGISTER_BIT, OUTPUT);    // freq register select
  pinMode(PIN_TRANSMIT, OUTPUT);
  pinMode(PIN_TUNE_STEP_LED, OUTPUT);
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
  
  serialInit();
  loadDefaultSettings();
  AD9834_init();
  AD9834_reset();                             // low to high
  for (int i=0; i <= 5e4; i++);  // small delay
  AD9834_init();
  AD9834_reset();
  attachCoreTimerService(TimerOverFlow);//See function at the bottom of the file.
} //end setup()

void loop() {
  digitalWrite(FSYNC_BIT, HIGH);  // 
  digitalWrite(SCLK_BIT, HIGH);  //

  readRITValue();

  pollMultifunctionButton(); 

  pollRotaryEncoder();

  if (!isTransmitting) {
    frequency_tune  = frequency + RitFreqOffset;
    setFrequency(frequency_tune);
    if (millis() >= transmitInhibitUntil) {
      if (getDitKey()) {
        transmitUntil = (millis() + ditDuration);
        setTransmit(true);
      } else if (getDahKey()) {
        transmitUntil = (millis() + 3 * ditDuration);
        setTransmit(true);
      }
    }
  }

  if ((millis() >= transmitUntil) && isTransmitting) {
    setTransmit(false);
    transmitInhibitUntil = (millis() + ditDuration);
  }

  loopCount++;
  loopElapsedTime    = millis() - loopStartTime;

  if(loopElapsedTime >= serialReportInterval) {
    serialDump();
  }

} //end loop()

void loadDefaultSettings() {
  digitalWrite(PIN_MULTIFUNCTION_GREEN, HIGH); 
  digitalWrite(PIN_MULTIFUNCTION_YELLOW, LOW);
  digitalWrite(PIN_MULTIFUNCTION_RED, LOW);

  digitalWrite(PIN_SELECT_GREEN, HIGH);
  digitalWrite(PIN_SELECT_YELLOW, LOW);
  digitalWrite(PIN_SELECT_GREEN, LOW);

  digitalWrite (PIN_TRANSMIT, LOW);
  digitalWrite (PIN_TUNE_STEP_LED, LOW);
  digitalWrite (PIN_SIDETONE, LOW);
  digitalWrite (FREQ_REGISTER_BIT, LOW);

  Band_Width_W();
  Band_Set_40_20M();
  Step_Size_100();
} //end loadDefaultSettings()

uint32_t TimerOverFlow(uint32_t currentTime) {
  return (currentTime + CORE_TICK_RATE*(1));//the Core Tick Rate is 1ms
} //end TimerOverFlow()
