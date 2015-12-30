#include "globals.h"
#include "defines.h"
#ifndef RADIO_H
#define RADIO_H
int getCurrentBand();
void Band_Set_40_20M();
void Frequency_up();
void Frequency_down();
void setFrequency(long);
void setTransmit(bool);
void readRITValue();
long bandLimit(long);
void Default_frequency();
#endif
