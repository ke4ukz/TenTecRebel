#include "globals.h"




int RitReadValue = 0;
int RitFrequencyOffset = 0;
int Step_Select_Button = 0;
int Step_Multi_Function_Button = 0;
int Selected_BW = 0; // BANDWIDTH_*
int Selected_Step = 0; // STEP_*
int Selected_Other = 0; // USER_*
unsigned long serialReportInterval = 50; //Milliseconds between serial dumps
unsigned long ditDuration = 100; //Number of milliseconds in a dit

//int encoder0PinALast = LOW;

bool isTransmitting = false;
unsigned long transmitUntil = 0;
unsigned long transmitInhibitUntil = 0;

long frequency_step;
long currentFrequency = 0;
long frequency_default = 0;
long IF = 9.00e6; // I.F. Frequency

byte currentSerialStep = SERIALSTEP_IDLE;
byte incomingDataType = 0;
uint32_t incomingData = 0;

bool morseSending = false;
const int morseTreetop = 63;   // This is for ITU with puncutation, but without non-english extensions
const int morseTableLength = (morseTreetop*2)+1;
const int morseTreeLevels = log(morseTreetop+1)/log(2);
char morseTable[] = "*5*H*4*S***V*3*I***F***U?*_**2*E***L\"**R*+.****A***P@**W***J'1* *6-B*=*D*/" "*X***N***C;*!K*()Y***T*7*Z**,G***Q***M:8*****O*9***0*";
char morseSignal[] = "......";
int morseSignalPos = 0;
int morseSignals = 0;
int keyerMode = true;
bool decoderOn = true;
int decodeThreshhold = 700;
bool wraparoundTuning = false;

uint8_t bandscanData[BANDSCAN_SIZE] = {0};
long bandscanTop;
long bandscanBottom;
int bandscanMode;
long bandscanWidth;
unsigned long bandscanInterval;
bool isBandscanning = false;
