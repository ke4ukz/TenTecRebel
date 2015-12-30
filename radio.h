#include "globals.h"
#include "defines.h"
#ifndef RADIO_H
#define RADIO_H
void Band_Set_40_20M();
void Frequency_up();
void Frequency_down();
void setFrequency(long);
void setTransmit(bool);
void readRITValue();
void Band_40_Limit_High();
void Band_40_Limit_Low();
void Band_20_Limit_High();
void Band_20_Limit_Low();
void Default_frequency();
#endif