#include "dss.h"

//-----------------------------------------------------------------------------
// ****************  Dont bother the code below  ******************************
// \/  \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/
//-----------------------------------------------------------------------------
void dssSetRXFreq(long freq) {
//void program_freq0(long freq) {
  long fcalc;
  int flow,fhigh;
  AD9834_reset_high();  
  fcalc = freq*(268.435456e6 / REFERENCE );    // 2^28 =
  flow = fcalc&0x3fff;              //  49.99975mhz  
  fhigh = (fcalc>>14)&0x3fff;
  digitalWrite(PIN_AD9834_FSYNC, LOW);  //
  clock_data_to_ad9834(flow|AD9834_FREQ0_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(fhigh|AD9834_FREQ0_REGISTER_SELECT_BIT);
  digitalWrite(PIN_AD9834_FSYNC, HIGH);
  AD9834_reset_low();
} // end   program_freq0

void dssSetTXFreq(long freq) {
//void program_freq1(long freq) {
  long fcalc;
  int flow,fhigh;
  AD9834_reset_high(); 
  fcalc = freq*(268.435456e6 / REFERENCE );    // 2^28 =
  flow = fcalc&0x3fff;              //  use for 49.99975mhz   
  fhigh = (fcalc>>14)&0x3fff;
  digitalWrite(PIN_AD9834_FSYNC, LOW);  
  clock_data_to_ad9834(flow|AD9834_FREQ1_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(fhigh|AD9834_FREQ1_REGISTER_SELECT_BIT);
  digitalWrite(PIN_AD9834_FSYNC, HIGH);  
  AD9834_reset_low();
}

void clock_data_to_ad9834(unsigned int data_word) {
  char bcount;
  unsigned int iData;
  iData=data_word;
  digitalWrite(PIN_AD9834_SCLK, HIGH);  //portb.PIN_AD9834_SCLK = 1;  
  // make sure clock high - only chnage data when high
  for(bcount=0;bcount<16;bcount++) {
    if((iData & 0x8000)) {
      digitalWrite(PIN_AD9834_SDATA, HIGH);  //portb.PIN_AD9834_SDATA = 1; 
    // test and set data bits
    } else {
      digitalWrite(PIN_AD9834_SDATA, LOW);  
    }
    digitalWrite(PIN_AD9834_SCLK, LOW);  
    digitalWrite(PIN_AD9834_SCLK, HIGH);     
    // set clock high - only change data when high
    iData = iData<<1; // shift the word 1 bit to the left
  } // end for

} // end  clock_data_to_ad9834

void AD9834_init() {    // set up registers
  AD9834_reset_high(); 
  digitalWrite(PIN_AD9834_FSYNC, LOW);
  clock_data_to_ad9834(0x2300);  // Reset goes high to 0 the registers and enable the output to mid scale.
  clock_data_to_ad9834((FREQ0_INIT_VALUE&0x3fff)|AD9834_FREQ0_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(((FREQ0_INIT_VALUE>>14)&0x3fff)|AD9834_FREQ0_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(0x2200); // reset goes low to enable the output.
  AD9834_reset_low();
  digitalWrite(PIN_AD9834_FSYNC, HIGH);  
} //  end   init_AD9834()

void AD9834_reset() {
  digitalWrite(PIN_AD9834_RESET, HIGH);  // hardware connection
  for (int i=0; i <= 2048; i++);  // small delay
  digitalWrite(PIN_AD9834_RESET, LOW);   // hardware connection
}

void AD9834_reset_low() {
  digitalWrite(PIN_AD9834_RESET, LOW);
}

void AD9834_reset_high() {  
  digitalWrite(PIN_AD9834_RESET, HIGH);
}
//^^^^^^^^^^^^^^^^^^^^^^^^^  DON'T BOTHER CODE ABOVE  ^^^^^^^^^^^^^^^^^^^^^^^^^ 
//=============================================================================
