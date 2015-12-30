#ifndef GLOBALS_H
#define GLOBALS_H
extern int RitReadValue;
extern int RitFrequencyOffset;
extern int SmeterReadValue;
extern int BatteryReadValue;
extern int PowerOutReadValue;
extern int CodeReadValue;
extern int CWSpeedReadValue;
extern int Step_Select_Button;
extern int Step_Select_Button1;
extern int Step_Multi_Function_Button;
extern int Step_Multi_Function_Button1;
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

//extern long RIT_frequency;
//extern long RX_frequency;
//extern long save_rec_frequency;
extern long frequency_step;
extern long currentFrequency;
extern long frequency_default;
extern long fcalc;
extern long IF;
extern unsigned long loopCount;
extern unsigned long lastLoopCount;
extern unsigned long loopsPerSecond;
extern unsigned int printCount;
extern unsigned long loopStartTime;
extern unsigned long loopElapsedTime;
extern float loopSpeed;
extern unsigned long LastFreqWriteTime;
#endif
