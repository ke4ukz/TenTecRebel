#include "serial.h"

void serialInit() {
  Serial.begin(115200);
  #ifdef TEXTOUTPUT
  Serial.print(__NAME__);
  Serial.print(" version ");
  Serial.print(__VERSION__);
  Serial.print(" (");
  Serial.print(__DATE__);
  Serial.println(")");
#endif

#ifdef BINARYOUTPUT
  serialSend(__NAME__);
  serialSend(" version ");
  serialSend(__VERSION__);
  serialSend(" (");
  serialSend(__DATE__);
  serialSend(")\n");
#endif

}

void serialDump() {
#ifdef TEXTOUTPUT
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
#endif

#ifdef BINARYOUTPUT
  serialSend(SERIAL_VOLTMETER, getPowerIn() );
  serialSend(SERIAL_OUTPUTPOWER, getPowerOut() );
#endif
} //end serialDump()

void serialSend(String toSend) {
  Serial.write((byte)SERIAL_HEADER);
  Serial.write((byte)SERIAL_STRING);
  Serial.print(toSend);
  Serial.write((byte)SERIAL_FOOTER);
}

void serialSend(byte toSend) {
  Serial.write((byte)SERIAL_HEADER);
  Serial.write(toSend);
  Serial.write((byte)SERIAL_FOOTER);
}

void serialSend(byte toSend, uint32_t value) {
  Serial.write((byte)SERIAL_HEADER);
  Serial.write(toSend);
  Serial.write((byte)((value & 0xff000000) >> 24));
  Serial.write((byte)((value & 0x00ff0000) >> 16));
  Serial.write((byte)((value & 0x0000ff00) >> 8));
  Serial.write((byte)( value & 0x000000ff));
  Serial.write((byte)SERIAL_FOOTER);  
}
