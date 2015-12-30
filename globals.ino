#include "globals.h"
#include "defines.h"

const int RitReadPin = A0; // pin that the sensor is attached to used for a rit routine later.
int RitReadValue = 0;
int RitFreqOffset = 0;
const int SmeterReadPin = A1; // To give a realitive signal strength based on AGC voltage.
int SmeterReadValue = 0;
const int BatteryReadPin = A2; // Reads 1/5 th or 0.20 of supply voltage.
int BatteryReadValue = 0;
const int PowerOutReadPin = A3; // Reads RF out voltage at Antenna.
int PowerOutReadValue = 0;
const int CodeReadPin = A6; // Can be used to decode CW. 
int CodeReadValue = 0;
const int CWSpeedReadPin = A7; // To adjust CW speed for user written keyer.
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

//-Encoder Stuff------------------------------------------
const int encoder0PinA = 7;
const int encoder0PinB = 6;
int val; 
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

const long meter_40 = 16.03e6; // IF + Band frequency, HI side injection 40 meter range 16 > 16.3 mhz
const long meter_20 = 5.06e6; // Band frequency - IF, LOW side injection 20 meter range 5 > 5.35 mhz
const long Reference = 49.99975e6; // for ad9834 this may be tweaked in software to fine tune the Radio
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
