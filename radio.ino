#include "radio.h"

int getCurrentBand() {
  if (digitalRead(PIN_BAND_SELECT) == HIGH) {
    return BAND_20METERS;
  } else {
    return BAND_40METERS;
  }
}

void setBand() {
  if ( getCurrentBand() == BAND_20METERS ) { 
    frequency_default = DEFAULT_20METERS;
  } else { 
    frequency_default = DEFAULT_40METERS; 
    IF *= -1;               //  HI side injection
  }
  defaultFrequency();
}

void setFrequency(long txFreq) {
  long rxFreq;
  //if(txFreq == currentFrequency) return;
  dssSetRXFreq( rxFreq  );
  rxFreq = txFreq + RitFrequencyOffset;  //  to get the TX freq
  dssSetTXFreq( txFreq + IF  );
  currentFrequency = txFreq;
#ifdef BINARYOUTPUT
  serialSend(SERIAL_TXFREQUENCY, txFreq + IF);
  serialSend(SERIAL_RXFREQUENCY, rxFreq + IF);
#endif
}

void setTransmit(bool tx) {
  if (!isTransmitting && tx) {
#ifdef BINARYOUTPUT
    serialSend(SERIAL_TXSTART);
#endif
    digitalWrite(FREQ_REGISTER_BIT, HIGH);
    digitalWrite(PIN_TRANSMIT, HIGH);
    digitalWrite(PIN_SIDETONE, HIGH);
    isTransmitting = true;
  } else if (isTransmitting && !tx) {
    digitalWrite(PIN_TRANSMIT, LOW);
    digitalWrite(FREQ_REGISTER_BIT, LOW);
    digitalWrite(PIN_SIDETONE, LOW);
    isTransmitting = false;
#ifdef BINARYOUTPUT
    serialSend(SERIAL_TXEND);
#endif
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
}   //  end   Default_frequency

int getPowerIn() {
  return analogRead(PIN_POWERIN);
}

int getPowerOut() {
  return analogRead(PIN_POWEROUT);
}

int getSignalStrength() {
  return analogRead(PIN_SMETER);
}
