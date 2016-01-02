#ifndef KEYER_H
#define KEYER_H
#include "globals.h"
#include "defines.h"

void sendDit();
void sendDah();
bool getDitKey();
bool getDahKey();
void setKeyerWPM(int);
void sendCharacter(char);
void sendNextSignal();
void setKeyerMode(int);
void setDecoder(bool);
void setDecodeThreshhold(int);
void decodeRoutine();
int getCWRead();

#endif
