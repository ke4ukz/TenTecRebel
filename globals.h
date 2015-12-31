#ifndef GLOBALS_H
#define GLOBALS_H
#include <inttypes.h>
#include "defines.h"

extern int RitReadValue;
extern int RitFrequencyOffset;
extern int Step_Select_Button;
extern int Step_Multi_Function_Button;
extern int Selected_BW;
extern int Selected_Step;
extern int Selected_Other;
extern unsigned long serialReportInterval;
extern unsigned long ditDuration;

extern int encoder0PinALast;

extern bool isTransmitting;
extern unsigned long transmitUntil;
extern unsigned long transmitInhibitUntil;

extern long frequency_step;
extern long currentFrequency;
extern long frequency_default;
extern long IF;

extern uint8_t currentSerialStep;
extern uint8_t incomingDataType;
extern uint32_t incomingData;

extern bool morseSending;
extern const int morseTreetop;
extern const int morseTableLength;
extern const int morseTreeLevels;
extern char morseTable[];
extern char morseSignal[];
extern int morseSignalPos;
extern int morseSignals;
extern bool keyerOn;
extern bool decoderOn;
extern int decodeThreshhold;
#endif
