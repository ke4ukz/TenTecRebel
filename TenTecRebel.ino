#include "TenTecRebel.h"

void setup() {
  // these pins are for the AD9834 control
  pinMode(SCLK_BIT, OUTPUT);    // clock
  pinMode(FSYNC_BIT, OUTPUT);    // fsync
  pinMode(SDATA_BIT, OUTPUT);    // data
  pinMode(RESET_BIT, OUTPUT);    // reset
  pinMode(FREQ_REGISTER_BIT, OUTPUT);    // freq register select
  pinMode(encoder0PinA, INPUT);     // using optical for now
  pinMode(encoder0PinB, INPUT);     // using optical for now 
  pinMode(PIN_KEY_DIT, INPUT);     // Dit Key line 
  pinMode(PIN_KEY_DAH, INPUT);     // Dah Key line
  pinMode(PIN_TRANSMIT, OUTPUT);
  pinMode(PIN_TUNE_STEP_LED, OUTPUT);
  pinMode(PIN_MULTIFUNCTION_GREEN, OUTPUT);    // Band width
  pinMode(PIN_MULTIFUNCTION_YELLOW, OUTPUT);    // Step size
  pinMode(PIN_MULTIFUNCTION_RED, OUTPUT);    // Other
  pinMode(PIN_MULTIFUNCTION_BUTTON, INPUT);     // Choose from Band width, Step size, Other
  pinMode(PIN_SELECT_GREEN, OUTPUT);    //  BW wide, 100 hz step, other1
  pinMode(PIN_SELECT_YELLOW, OUTPUT);    //  BW medium, 1 khz step, other2
  pinMode(PIN_SELECT_RED, OUTPUT);    //  BW narrow, 10 khz step, other3
  pinMode(PIN_SELECT_BUTTON, INPUT);     //  Selection form the above
  pinMode(PIN_MEDIUM_A8, OUTPUT);    // Hardware control of I.F. filter Bandwidth
  pinMode(PIN_NARROW_A9, OUTPUT);    // Hardware control of I.F. filter Bandwidth
  pinMode(PIN_SIDETONE, OUTPUT);    // sidetone enable
  Default_Settings();
  pinMode (PIN_BAND_SELECT, INPUT);     // select
  AD9834_init();
  AD9834_reset();                             // low to high
  Band_Set_40_20M();
  //   Default_frequency();                   // what ever default is
  digitalWrite(PIN_TRANSMIT, LOW);       // turn off TX
  Step_Size_100();   // Change for other Step_Size default!
  for (int i=0; i <= 5e4; i++);  // small delay
  AD9834_init();
  AD9834_reset();
  attachCoreTimerService(TimerOverFlow);//See function at the bottom of the file.
  serialInit();
} //end setup()

void loop() {
  digitalWrite(FSYNC_BIT, HIGH);  // 
  digitalWrite(SCLK_BIT, HIGH);  //

  RIT_Read();

  Multi_Function(); 

  Encoder();

  frequency_tune  = frequency + RitFreqOffset;
  UpdateFreq(frequency_tune);

  TX_routine();

  loopCount++;
  loopElapsedTime    = millis() - loopStartTime;

  // has 1000 milliseconds elasped?
  if( 1000 <= loopElapsedTime ) {
      serialDump();    // comment this out to remove the one second tick
  }

} //end loop()

void Default_Settings() {
  digitalWrite(PIN_MULTIFUNCTION_GREEN, HIGH); 
  digitalWrite(PIN_MULTIFUNCTION_YELLOW, LOW);
  digitalWrite(PIN_MULTIFUNCTION_RED, LOW);
  digitalWrite(PIN_SELECT_GREEN, HIGH);
  Band_Width_W();
  digitalWrite(PIN_SELECT_YELLOW, LOW);
  digitalWrite(PIN_SELECT_GREEN, LOW);
  digitalWrite (PIN_TRANSMIT, LOW);
  digitalWrite (PIN_TUNE_STEP_LED, LOW);
  digitalWrite (PIN_SIDETONE, LOW);
  digitalWrite (FREQ_REGISTER_BIT, LOW);
} //end Default_Settings()

uint32_t TimerOverFlow(uint32_t currentTime) {
  return (currentTime + CORE_TICK_RATE*(1));//the Core Tick Rate is 1ms
} //end TimerOverFlow()
