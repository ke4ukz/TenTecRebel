#include "bandscan.h"

void performBandscan() {
  long bsWidth;
  switch (bandscanMode) {
    case BANDSCAN_OFF:
      return;
      break;
    case BANDSCAN_FULLBAND:
      bandscanBottom = (getCurrentBand() == BAND_20METERS ? BANDLIMIT_20_BOTTOM : BANDLIMIT_40_BOTTOM);
      bandscanTop = (getCurrentBand() == BAND_20METERS ? BANDLIMIT_20_TOP : BANDLIMIT_40_TOP);
      break;
    case BANDSCAN_CENTERED:
      bsWidth = bandscanWidth / 2;
      bandscanBottom = (currentFrequency - bsWidth);
      bandscanTop = (currentFrequency + bsWidth);
      break;
    case BANDSCAN_CUSTOM:
      //bandscanTop and bandscanBottom are already set
      break;
    default:
      return;
  }
  
  long startingFrequency = currentFrequency;
  long scanStep = (bandscanBottom - bandscanTop) / BANDSCAN_SIZE;
  long f = bandscanBottom;
  isBandscanning = true;
  for (int i=0; i<BANDSCAN_SIZE; i++) {
    setFrequency(f);
    delay(3);
    bandscanData[i] = (byte)((analogRead(PIN_SMETER) & 0x3fc) >> 2); //discard two least-significant bytes
    f += scanStep;
  }
  setFrequency(startingFrequency);
  isBandscanning = false;
}

void setBandscanMode(int bsMode) {
  bandscanMode = bsMode;
  serialSend(SERIAL_BANDSCAN, bsMode);
}

void setBandscanWidth(long bsWidth) {
  bandscanWidth = bsWidth;
  serialSend(SERIAL_BANDSCAN_WIDTH, bsWidth);
}

void setBandscanTop(long bsTop) {
  bandscanTop = bandLimit(bsTop);
  serialSend(SERIAL_BANDSCAN_TOP, bandscanTop+IF);
}

void setBandscanBottom(long bsBottom) {
  bandscanBottom = bandLimit(bsBottom);
  serialSend(SERIAL_BANDSCAN_BOTTOM, bandscanBottom+IF);
}

void setBandscanInterval(unsigned long bsInterval) {
  bandscanInterval = bsInterval;
  serialSend(SERIAL_BANDSCAN_INTERVAL, bsInterval);
}

