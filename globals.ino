#include "globals.h"
#include "defines.h"

int RitReadValue = 0;
int RitFreqOffset = 0;
int SmeterReadValue = 0;
int BatteryReadValue = 0;
int PowerOutReadValue = 0;
int CodeReadValue = 0;
int CWSpeedReadValue = 0; 
int TX_key;
int band_sel; // select band 40 or 20 meter
int band_set;
int bsm; 
int Step_Select_Button = 0;
int Step_Select_Button1 = 0;
int Step_Multi_Function_Button = 0;
int Step_Multi_Function_Button1 = 0;
int Selected_BW = 0; // current Band width 0= wide, 1 = medium, 2= narrow
int Selected_Step = 0; // Current Step
int Selected_Other = 0; // To be used for anything
unsigned long serialReportInterval = 50;
unsigned long ditDuration = 100;

//-Encoder Stuff------------------------------------------
int val; 
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

bool isTransmitting = false;
unsigned long transmitUntil = 0;
unsigned long transmitInhibitUntil = 0;

long RIT_frequency;
long RX_frequency; 
long save_rec_frequency;
long frequency_step;
long frequency = 0;
long frequency_old = 0;
long frequency_tune = 0;
long frequency_default = 0;
long fcalc;
long IF = 9.00e6; // I.F. Frequency

//-Debug Stuff------------------------------------------------
unsigned long loopCount = 0;
unsigned long lastLoopCount = 0;
unsigned long loopsPerSecond = 0;
unsigned int printCount = 0;
unsigned long loopStartTime = 0;
unsigned long loopElapsedTime = 0;
float loopSpeed = 0;
unsigned long LastFreqWriteTime = 0;
