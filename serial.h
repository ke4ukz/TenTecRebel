#ifndef SERIAL_H
#define SERIAL_H
#include "defines.h"
#include "globals.h"

void serialInit();
void serialDump();
void processSerialCommand();
void serialReceive(byte);
void serialSend(String);
void serialSend(byte);
void serialSend(byte, uint32_t);

#endif
