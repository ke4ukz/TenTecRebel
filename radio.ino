#include "radio.h"

int getCurrentBand() {
  if (digitalRead(PIN_BAND_SELECT) == HIGH) {
    return BAND_20METERS;
  } else {
    return BAND_40METERS;
  }
}

void setBand(int band) {
  if ( band == BAND_20METERS ) { 
    frequency_default = DEFAULT_20METERS;
  } else { 
    frequency_default = DEFAULT_40METERS; 
    IF *= -1;               //  HI side injection
  }
  defaultFrequency();
}

void tuneUp() {
  setFrequency(bandLimit(currentFrequency + frequency_step));
}

void tuneDown() {
  setFrequency(bandLimit(currentFrequency - frequency_step));
}

void setFrequency(long txFreq) {
  if (!isTransmitting) {
    long rxFreq;
    dssSetRXFreq( rxFreq  );
    rxFreq = txFreq + RitFrequencyOffset;
    dssSetTXFreq( txFreq + IF  );
    currentFrequency = txFreq;
    serialSend(SERIAL_TXFREQUENCY, txFreq + IF);
    serialSend(SERIAL_RXFREQUENCY, rxFreq + IF);
  }
}

void setTransmit(bool tx) {
  if (!isTransmitting && tx) {
    serialSend(SERIAL_TXSTART);
    digitalWrite(FREQ_REGISTER_BIT, HIGH);
    digitalWrite(PIN_TRANSMIT, HIGH);
    digitalWrite(PIN_SIDETONE, HIGH);
    isTransmitting = true;
  } else if (isTransmitting && !tx) {
    digitalWrite(PIN_TRANSMIT, LOW);
    digitalWrite(FREQ_REGISTER_BIT, LOW);
    digitalWrite(PIN_SIDETONE, LOW);
    isTransmitting = false;
    serialSend(SERIAL_TXEND);
  }
}

long bandLimit(long freq) {
  if (getCurrentBand() == BAND_20METERS) {
    if (freq > BANDLIMIT_20_TOP) {
      return BANDLIMIT_20_TOP;
    } else if (freq < BANDLIMIT_20_BOTTOM) {
      return BANDLIMIT_20_BOTTOM;
    } else {
      return freq;
    }
  } else {
    if (freq > BANDLIMIT_40_TOP) {
      return BANDLIMIT_40_TOP;
    } else if (freq < BANDLIMIT_40_BOTTOM) {
      return BANDLIMIT_40_BOTTOM;
    } else {
      return freq;
    }
  }
}

void defaultFrequency() {
  setFrequency(frequency_default);
}

int getPowerIn() {
  return analogRead(PIN_POWERIN);
}

int getPowerOut() {
  return analogRead(PIN_POWEROUT);
}

int getSignalStrength() {
  return analogRead(PIN_SMETER);
}

void setBandwidth(int bwWidth) {
  switch (bwWidth) {
    case BANDWIDTH_WIDE:
      digitalWrite( PIN_MEDIUM_A8, LOW);   // Hardware control of I.F. filter shape
      digitalWrite( PIN_NARROW_A9, LOW);   // Hardware control of I.F. filter shape
      break;
    case BANDWIDTH_MEDIUM:
      digitalWrite( PIN_MEDIUM_A8, HIGH);  // Hardware control of I.F. filter shape
      digitalWrite( PIN_NARROW_A9, LOW);   // Hardware control of I.F. filter shape
      break;
    case BANDWIDTH_NARROW:
      digitalWrite( PIN_MEDIUM_A8, LOW);   // Hardware control of I.F. filter shape
      digitalWrite( PIN_NARROW_A9, HIGH);  // Hardware control of I.F. filter shape
      break;
    default:
      return;
  }
  Selected_BW = bwWidth;
}

void setStepSize(int stepSize) {
  switch (stepSize) {
    case STEP_100HZ:
      frequency_step = 100;
      break;
    case STEP_1000HZ:
      frequency_step = 1e3;
      break;
    case STEP_10000HZ:
      frequency_step = 10e3;
      break;
    default:
      return;
  }
  Selected_Step = stepSize;
}

