#include "defines.h"
#include "globals.h"

void setup() {
  // these pins are for the AD9834 control
  pinMode(SCLK_BIT, OUTPUT);    // clock
  pinMode(FSYNC_BIT, OUTPUT);    // fsync
  pinMode(SDATA_BIT, OUTPUT);    // data
  pinMode(RESET_BIT, OUTPUT);    // reset
  pinMode(FREQ_REGISTER_BIT, OUTPUT);    // freq register select
  pinMode(encoder0PinA, INPUT);     // using optical for now
  pinMode(encoder0PinB, INPUT);     // using optical for now 
  pinMode(TX_Dit, INPUT);     // Dit Key line 
  pinMode(TX_Dah, INPUT);     // Dah Key line
  pinMode(TX_OUT, OUTPUT);
  pinMode(Band_End_Flash_led, OUTPUT);
  pinMode(Multi_function_Green, OUTPUT);    // Band width
  pinMode(Multi_function_Yellow, OUTPUT);    // Step size
  pinMode(Multi_function_Red, OUTPUT);    // Other
  pinMode(Multi_Function_Button, INPUT);     // Choose from Band width, Step size, Other
  pinMode(Select_Green, OUTPUT);    //  BW wide, 100 hz step, other1
  pinMode(Select_Yellow, OUTPUT);    //  BW medium, 1 khz step, other2
  pinMode(Select_Red, OUTPUT);    //  BW narrow, 10 khz step, other3
  pinMode(Select_Button, INPUT);     //  Selection form the above
  pinMode(Medium_A8, OUTPUT);    // Hardware control of I.F. filter Bandwidth
  pinMode(Narrow_A9, OUTPUT);    // Hardware control of I.F. filter Bandwidth
  pinMode(Side_Tone, OUTPUT);    // sidetone enable
  Default_Settings();
  pinMode (Band_Select, INPUT);     // select
  AD9834_init();
  AD9834_reset();                             // low to high
  Band_Set_40_20M();
  //   Default_frequency();                   // what ever default is
  digitalWrite(TX_OUT,            LOW);       // turn off TX
  Step_Size_100();   // Change for other Step_Size default!
  for (int i=0; i <= 5e4; i++);  // small delay
  AD9834_init();
  AD9834_reset();
  attachCoreTimerService(TimerOverFlow);//See function at the bottom of the file.
  Serial.begin(115200);
  Serial.print(__NAME__);
  Serial.print(" version ");
  Serial.print(__VERSION__);
  Serial.print(" (");
  Serial.print(__DATE__);
  Serial.println(")");
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

void serialDump() {
  loopStartTime   = millis();
  loopsPerSecond  = loopCount - lastLoopCount;
  loopSpeed       = (float)1e6 / loopsPerSecond;
  lastLoopCount   = loopCount;

  Serial.print    ( "uptime: " );
  Serial.print    ( ++printCount );
  Serial.println  ( " seconds" );

  Serial.print    ( "loops per second:    " );
  Serial.println  ( loopsPerSecond );
  Serial.print    ( "loop execution time: " );
  Serial.print    ( loopSpeed, 3 );
  Serial.println  ( " uS" );

  Serial.print    ( "Freq Rx: " );
  Serial.println  ( frequency_tune + IF );
  Serial.print    ( "Freq Tx: " );
  Serial.println  ( frequency + IF );
  Serial.println  ();
} //end serialDump()

void Default_Settings() {
  digitalWrite(Multi_function_Green, HIGH); 
  digitalWrite(Multi_function_Yellow, LOW);
  digitalWrite(Multi_function_Red, LOW);
  digitalWrite(Select_Green, HIGH);
  Band_Width_W();
  digitalWrite(Select_Yellow, LOW);
  digitalWrite(Select_Green, LOW);
  digitalWrite (TX_OUT, LOW);
  digitalWrite (Band_End_Flash_led, LOW);
  digitalWrite (Side_Tone, LOW);
  digitalWrite ( FREQ_REGISTER_BIT, LOW);
} //end Default_Settings()

uint32_t TimerOverFlow(uint32_t currentTime) {
  return (currentTime + CORE_TICK_RATE*(1));//the Core Tick Rate is 1ms
} //end TimerOverFlow()
