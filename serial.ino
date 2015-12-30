#include "serial.h"

void serialInit() {
  Serial.begin(115200);
  serialSend(__NAME__);
  serialSend(" version ");
  serialSend(__VERSION__);
  serialSend(" (");
  serialSend(__DATE__);
  serialSend(")\n");
}

void serialDump() {
  serialSend(SERIAL_VOLTMETER, getPowerIn() );
  serialSend(SERIAL_OUTPUTPOWER, getPowerOut() );
  serialSend(SERIAL_SMETER, getSignalStrength() );
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
