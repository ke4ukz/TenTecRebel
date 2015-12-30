#include "globals.h"
#include "defines.h"
#ifndef RADIO_H
#define RADIO_H
int getCurrentBand();
void setBand();
void setFrequency(long);
void setTransmit(bool);
long bandLimit(long);
void defaultFrequency();
#endif
