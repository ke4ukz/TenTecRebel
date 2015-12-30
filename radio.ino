#include "radio.h"

int getCurrentBand() {
  if (digitalRead(PIN_BAND_SELECT) == HIGH) {
    return BAND_20METERS;
  } else {
    return BAND_40METERS;
  }
}

void Band_Set_40_20M() {
  if ( getCurrentBand() == BAND_20METERS ) { 
    frequency_default = DEFAULT_20METERS;
  } else { 
    frequency_default = DEFAULT_40METERS; 
    IF *= -1;               //  HI side injection
  }
  Default_frequency();
}

void Frequency_up() { 
  currentFrequency = bandLimit(currentFrequency + frequency_step);
}

void Frequency_down() { 
  currentFrequency = bandLimit(currentFrequency - frequency_step);
}

void setFrequency(long freq) {
  long freq1;
//  some of this code affects the way to Rit responds to being turned
  if (LastFreqWriteTime != 0) {
    if ((millis() - LastFreqWriteTime) < 100) return;
  }
  LastFreqWriteTime = millis();
  if(freq == frequency_old) return;
  //Serial.print("Freq: ");
  //Serial.println(freq);
  program_freq0( freq  );
  bsm = digitalRead(PIN_BAND_SELECT); 
  freq1 = freq - RitFreqOffset;  //  to get the TX freq
  program_freq1( freq1 + IF  );
  frequency_old = freq;
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

void readRITValue() {
  int RitReadValueNew =0 ;
  RitReadValueNew = analogRead(PIN_RIT);
  RitReadValue = (RitReadValueNew + (7 * RitReadValue))/8;//Lowpass filter
  if(RitReadValue < 500) {
      RitFreqOffset = RitReadValue-500;
  } else if(RitReadValue < 523) {
      RitFreqOffset = 0;//Deadband in middle of pot
  } else {
      RitFreqOffset = RitReadValue - 523;
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

void Default_frequency() {
  currentFrequency = frequency_default;
  setFrequency(currentFrequency);
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
