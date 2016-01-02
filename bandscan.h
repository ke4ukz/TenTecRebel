#ifndef BANDSCAN_H
#define BANDSCAN_H
#include "globals.h"
#include "defines.h"

void performBandscan();
void setBandscanMode(int);
void setBandscanWidth(long);
void setBandscanTop(long);
void setBandscanBottom(long);
void setBandscanInterval(unsigned long);

#endif
