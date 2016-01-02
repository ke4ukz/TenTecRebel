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
  serialSend(SERIAL_BAND, band);
}

void tuneUp() {
  setFrequency(bandLimit(currentFrequency + frequency_step, wraparoundTuning));
}

void tuneDown() {
  setFrequency(bandLimit(currentFrequency - frequency_step, wraparoundTuning));
}

void setFrequency(long txFreq) {
  if (!isTransmitting) {
    long rxFreq;
    rxFreq = txFreq + RitFrequencyOffset;
    dssSetRXFreq( rxFreq  );
    dssSetTXFreq( txFreq + IF  );
    currentFrequency = txFreq;
    if (!isBandscanning) {
      serialSend(SERIAL_TXFREQUENCY, txFreq + IF);
      serialSend(SERIAL_RXFREQUENCY, rxFreq + IF);
    }
  }
}

void setTransmit(bool tx) {
  if (!isTransmitting && tx) {
    serialSend(SERIAL_TXSTART);
    digitalWrite(PIN_TT_LED, HIGH);
    digitalWrite(PIN_AD9834_FREQ_REGISTER, HIGH);
    digitalWrite(PIN_TRANSMIT, HIGH);
    digitalWrite(PIN_SIDETONE, HIGH);
    isTransmitting = true;
  } else if (isTransmitting && !tx) {
    digitalWrite(PIN_TRANSMIT, LOW);
    digitalWrite(PIN_AD9834_FREQ_REGISTER, LOW);
    digitalWrite(PIN_SIDETONE, LOW);
    digitalWrite(PIN_TT_LED, LOW);
    isTransmitting = false;
    serialSend(SERIAL_TXEND);
  }
}

long bandLimit(long freq) {
  return bandLimit(freq, false);
}

long bandLimit(long freq, bool wraparound) {
  if (getCurrentBand() == BAND_20METERS) {
    if (freq > BANDLIMIT_20_TOP) {
      if (wraparound) {
        return BANDLIMIT_20_BOTTOM;
      } else {
        return BANDLIMIT_20_TOP;
      }
    } else if (freq < BANDLIMIT_20_BOTTOM) {
      if (wraparound) {
        return BANDLIMIT_20_TOP;
      } else {
        return BANDLIMIT_20_BOTTOM;
      }
    } else {
      return freq;
    }
  } else {
    if (freq > BANDLIMIT_40_TOP) {
      if (wraparound) {
        return BANDLIMIT_40_BOTTOM;
      } else {
        return BANDLIMIT_40_TOP;
      }
    } else if (freq < BANDLIMIT_40_BOTTOM) {
      if (wraparound) {
        return BANDLIMIT_40_TOP;
      } else {
        return BANDLIMIT_40_BOTTOM;
      }        
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

void setWraparoundTuning(bool wraparound) {
  wraparoundTuning = wraparound;
  serialSend(SERIAL_WRAPAROUND, (wraparound ? 1 : 0) );
}
