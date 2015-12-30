#ifndef GLOBALS_H
#define GLOBALS_H

extern int RitReadValue;
extern int RitFrequencyOffset;
extern int Step_Select_Button;
extern int Step_Multi_Function_Button;
extern int Selected_BW;
extern int Selected_Step;
extern int Selected_Other;
extern unsigned long serialReportInterval;
extern unsigned long ditDuration;

extern int val;
extern int encoder0Pos;
extern int encoder0PinALast;
extern int n;

extern bool isTransmitting;
extern unsigned long transmitUntil;
extern unsigned long transmitInhibitUntil;
extern unsigned long lastSerialDump;

extern long frequency_step;
extern long currentFrequency;
extern long frequency_default;
extern long IF;

#endif
