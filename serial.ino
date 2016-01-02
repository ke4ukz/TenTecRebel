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
//  static int lastPowerIn = -1; //Set to -1 to ensure that it gets sent on the first run of serialDump()
//  static int lastPowerOut = -1;
//  static int lastSMeter = -1;
//  static int lastCWRead = -1;
  int powerIn = getPowerIn();
  int powerOut = getPowerOut();
  int sMeter = getSignalStrength();
  int cwRead = getCWRead();
  
//  if (powerIn != lastPowerIn) {
    serialSend(SERIAL_VOLTMETER, powerIn);
//    lastPowerIn = powerIn;
//  }
//  if (powerOut != lastPowerOut) {
    serialSend(SERIAL_OUTPUTPOWER, powerOut);
//    lastPowerOut = powerOut;
//  }
//  if (sMeter != lastSMeter) {
    serialSend(SERIAL_SMETER, sMeter);
//    lastSMeter = sMeter;
//  }
//  if (cwRead != lastCWRead) {
    serialSend(SERIAL_CWREAD, cwRead);
//    lastCWRead = cwRead;
//  }
} //end serialDump()

void processSerialCommand() {
  switch (incomingDataType) {
    case SERIAL_SET_FREQUENCY:
      setFrequency(bandLimit(incomingData - IF));
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
      sendCharacter((char)(incomingData & 0xff));
      break;
    case SERIAL_SET_BANDWIDTH:
      Step_Multi_Function_Button = MULTIFUNCTION_1;
      setMultifunction(Step_Multi_Function_Button);
      Step_Select_Button = (int)(incomingData & 0xff);
      setFunction(Step_Select_Button);
      break;
    case SERIAL_SET_STEPSIZE:
      Step_Multi_Function_Button = MULTIFUNCTION_2;
      setMultifunction(Step_Multi_Function_Button);
      Step_Select_Button = (int)(incomingData & 0xff);
      setFunction(Step_Select_Button);
      break;
    case SERIAL_SET_USER:
      Step_Multi_Function_Button = MULTIFUNCTION_3;
      setMultifunction(Step_Multi_Function_Button);
      Step_Select_Button = (int)(incomingData & 0xff);
      setFunction(Step_Select_Button);
      break;
    case SERIAL_SET_KEYER:
      setKeyerMode(incomingData);
      break;
    case SERIAL_SET_DECODER:
      setDecoder(incomingData == 0 ? false : true);
      break;
    case SERIAL_SET_DECODETHRESHHOLD:
      setDecodeThreshhold(incomingData);
      break;
    case SERIAL_SET_BANDSCAN:
      setBandscanMode(incomingData);
      break;
    case SERIAL_SET_BANDSCAN_WIDTH:
      setBandscanWidth(incomingData);
      break;
    case SERIAL_SET_BANDSCAN_TOP:
      setBandscanTop(incomingData-IF);
      break;
    case SERIAL_SET_BANDSCAN_BOTTOM:
      setBandscanBottom(incomingData-IF);
      break;
    case SERIAL_SET_BANDSCAN_INTERVAL:
      setBandscanInterval(incomingData);
      break;
    case SERIAL_SET_WRAPAROUND:
      setWraparoundTuning( (incomingData==0 ? false : true) );
      break;
    case SERIAL_UPDATE:
      sendUpdate();
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
           (incomingDataType == SERIAL_TUNE_DOWN) || 
           (incomingDataType == SERIAL_UPDATE) ) {
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

void serialSendBandscan() {
  Serial.write((byte)SERIAL_HEADER);
  Serial.write((byte)SERIAL_BANDSCAN_DATA);
  for (int i=0; i<BANDSCAN_SIZE; i++) {
    Serial.write((byte)bandscanData[i]);
  }
  Serial.write((byte)SERIAL_FOOTER);
}
