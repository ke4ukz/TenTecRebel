#include "globals.h"
#include "defines.h"

int RitReadValue = 0;
int RitFrequencyOffset = 0;
int Step_Select_Button = 0;
int Step_Multi_Function_Button = 0;
int Selected_BW = 0; // current Band width 0= wide, 1 = medium, 2= narrow
int Selected_Step = 0; // Current Step
int Selected_Other = 0; // To be used for anything
unsigned long serialReportInterval = 50;
unsigned long ditDuration = 100;

int val; 
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

bool isTransmitting = false;
unsigned long transmitUntil = 0;
unsigned long transmitInhibitUntil = 0;
unsigned long lastSerialDump = 0;

long frequency_step;
long currentFrequency = 0;
long frequency_default = 0;
long IF = 9.00e6; // I.F. Frequency

