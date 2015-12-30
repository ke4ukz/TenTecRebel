#include "globals.h"
#include "defines.h"

//void program_freq0(long freq);
//void program_freq1(long freq1); // added 1 to freq
void dssSetTXFreq(long);
void dssSetRXFreq(long);
void clock_data_to_ad9834(unsigned int data_word);
void AD9834_init();
void AD9834_reset();
void AD9834_reset_high();
void AD9834_reset_low();
