#include "radio.h"

void Band_Set_40_20M() {
  bsm = digitalRead(PIN_BAND_SELECT); 
  //  select 40 or 20 meters 1 for 20 0 for 40
  if ( bsm == 1 ) { 
    frequency_default = meter_20;
  } else { 
    frequency_default = meter_40; 
    IF *= -1;               //  HI side injection
  }
  Default_frequency();
}

void Frequency_up() { 
  frequency = frequency + frequency_step;
  bsm = digitalRead(PIN_BAND_SELECT); 
   if ( bsm == 1 ) {
     Band_20_Limit_High();
   } else if ( bsm == 0 ) {
     Band_40_Limit_High();
   }
}

void Frequency_down() { 
  frequency = frequency - frequency_step;
  bsm = digitalRead(PIN_BAND_SELECT); 
  if ( bsm == 1 ) {
    Band_20_Limit_Low();
  } else if ( bsm == 0 ) {
    Band_40_Limit_Low();
  }
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

void TX_routine() {
  TX_key = digitalRead(PIN_KEY_DIT);
  if ( TX_key == LOW) {       // was high   
    //   (FREQ_REGISTER_BIT, HIGH) is selected      
    do {
      digitalWrite(FREQ_REGISTER_BIT, HIGH);
      digitalWrite(PIN_TRANSMIT, HIGH);
      digitalWrite(PIN_SIDETONE, HIGH);
      TX_key = digitalRead(PIN_KEY_DIT);
    } while (TX_key == LOW);   // was high 

    digitalWrite(PIN_TRANSMIT, LOW);  // trun off TX
    for (int i=0; i <= 10e3; i++); // delay for maybe some decay on key release

    digitalWrite(FREQ_REGISTER_BIT, LOW);
    digitalWrite(PIN_SIDETONE, LOW);
  }
}

void readRITValue() {
  int RitReadValueNew =0 ;
  RitReadValueNew = analogRead(RitReadPin);
  RitReadValue = (RitReadValueNew + (7 * RitReadValue))/8;//Lowpass filter
  if(RitReadValue < 500) {
      RitFreqOffset = RitReadValue-500;
  } else if(RitReadValue < 523) {
      RitFreqOffset = 0;//Deadband in middle of pot
  } else {
      RitFreqOffset = RitReadValue - 523;
  }
}

void Band_40_Limit_High() { //  Ham band limits
  if ( frequency < 16.3e6 ) { 
    stop_led_off();
  } else if ( frequency >= 16.3e6 ) { 
    frequency = 16.3e6;
    stop_led_on();    
  }
}

void Band_40_Limit_Low() {  //  Ham band limits
  if ( frequency <= 16.0e6 ) { 
    frequency = 16.0e6;
    stop_led_on();
  } else if ( frequency > 16.0e6 ) { 
    stop_led_off();
  } 
}

void Band_20_Limit_High() {    //  Ham band limits
  if ( frequency < 5.35e6 ) {
    stop_led_off();
  } else if ( frequency >= 5.35e6 ) {
    frequency = 5.35e6;
    stop_led_on();    
  }
}

void Band_20_Limit_Low() {    //  Ham band limits
  if ( frequency <= 5.0e6 ) { 
    frequency = 5.0e6;
    stop_led_on();
  } else if ( frequency > 5.0e6 ) { 
    stop_led_off();
  } 
}

void Default_frequency() {
  frequency = frequency_default;
  setFrequency(frequency);
}   //  end   Default_frequency

