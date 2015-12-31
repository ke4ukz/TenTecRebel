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

void processSerialCommand() {
  switch (incomingDataType) {
    case SERIAL_SET_FREQUENCY:
      break;
    case SERIAL_TUNE_UP:
      tuneUp();
      break;
    case SERIAL_TUNE_DOWN:
      tuneDown();
      break;
    case SERIAL_SET_WPM:
      setKeyerWPM((int)(incomingData & 0x8fff));
      break;
    case SERIAL_SEND_CHAR:
      break;
  }
}

void serialReceive(byte incoming) {
  switch (currentSerialStep) {
    case SERIALSTEP_IDLE:
      if (incoming == SERIAL_HEADER) {
        currentSerialStep = SERIALSTEP_EXPECT_TYPE;
      }
      break;
    case SERIALSTEP_EXPECT_TYPE:
      incomingDataType = incoming;
      incomingData = 0;
      if ( (incomingDataType == SERIAL_TUNE_UP) ||
           (incomingDataType == SERIAL_TUNE_DOWN) ) {
        currentSerialStep = SERIALSTEP_EXPECT_FOOTER;
      } else {
        currentSerialStep = SERIALSTEP_EXPECT_4MORE;
      }
      break;
    case SERIALSTEP_EXPECT_4MORE:
      incomingData = (incomingData | (incoming << 24) );
      currentSerialStep = SERIALSTEP_EXPECT_3MORE;
      break;
    case SERIALSTEP_EXPECT_3MORE:
      incomingData = (incomingData | (incoming << 16) );
      currentSerialStep = SERIALSTEP_EXPECT_2MORE;
      break;
    case SERIALSTEP_EXPECT_2MORE:
      incomingData = (incomingData | (incoming << 8) );
      currentSerialStep = SERIALSTEP_EXPECT_1MORE;
      break;
    case SERIALSTEP_EXPECT_1MORE:
      incomingData = (incomingData | incoming);
      currentSerialStep = SERIALSTEP_EXPECT_FOOTER;
      break;
    case SERIALSTEP_EXPECT_FOOTER:
      if (incoming == SERIAL_FOOTER) {
        processSerialCommand();
      }
      currentSerialStep = SERIALSTEP_IDLE;
      break;
  }
}

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
