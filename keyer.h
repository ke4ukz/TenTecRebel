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

#endif