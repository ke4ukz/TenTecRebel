#include "globals.h"
#include "defines.h"


int RitReadValue = 0;
int RitFrequencyOffset = 0;
int Step_Select_Button = 0;
int Step_Multi_Function_Button = 0;
int Selected_BW = 0; // BANDWIDTH_*
int Selected_Step = 0; // STEP_*
int Selected_Other = 0; // USER_*
unsigned long serialReportInterval = 50; //Milliseconds between serial dumps
unsigned long ditDuration = 100; //Number of milliseconds in a dit

int encoder0PinALast = LOW;

bool isTransmitting = false;
unsigned long transmitUntil = 0;
unsigned long transmitInhibitUntil = 0;
unsigned long lastSerialDump = 0;

long frequency_step;
long currentFrequency = 0;
long frequency_default = 0;
long IF = 9.00e6; // I.F. Frequency

byte currentSerialStep = SERIALSTEP_IDLE;
byte incomingDataType = 0;
uint32_t incomingData = 0;

