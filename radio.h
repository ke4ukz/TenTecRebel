#include "globals.h"
#include "defines.h"
#ifndef RADIO_H
#define RADIO_H
int getCurrentBand();
void setBand(int);
void setFrequency(long);
void setTransmit(bool);
long bandLimit(long);
void defaultFrequency();
int getPowerIn();
int getPowerOut();
int getSignalStrength();
void setBandwidth(int);
void setStepSize(int);

#endif
