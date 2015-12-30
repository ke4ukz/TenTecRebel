#include "serial.h"

void serialInit() {
  Serial.begin(115200);
  Serial.print(__NAME__);
  Serial.print(" version ");
  Serial.print(__VERSION__);
  Serial.print(" (");
  Serial.print(__DATE__);
  Serial.println(")");
}

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
