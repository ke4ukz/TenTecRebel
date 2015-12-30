#ifndef DEFINES_H
#define DEFINES_H

#define __NAME__                            "TenTec Rebel 506 (KE4UKZ)"
#define __VERSION__                         "1.0.3"

#define SDATA_BIT                           10          //  keep!
#define SCLK_BIT                            8           //  keep!
#define FSYNC_BIT                           9           //  keep!
#define RESET_BIT                           11          //  keep!
#define FREQ_REGISTER_BIT                   12          //  keep!
#define AD9834_FREQ0_REGISTER_SELECT_BIT    0x4000      //  keep!
#define AD9834_FREQ1_REGISTER_SELECT_BIT    0x8000      //  keep!
#define FREQ0_INIT_VALUE                    0x01320000  //  ?

#define PIN_SIDETONE                        3           // maybe to be changed to a logic control for a separate side tone gen
#define PIN_KEY_DAH                         33          // Physical pin attached to the "dah" input
#define PIN_KEY_DIT                         32          // Physical pin attached to the "dit" input
#define PIN_TRANSMIT                        38          // Physical pin attached to the transmitter key

#define PIN_TUNE_STEP_LED                   24          // ill flash every 100/1khz/10khz is tuned and when band end is reached
#define PIN_BAND_SELECT                     41          // if shorting block on only one pin 20m(1) on both pins 40m(0)
#define PIN_MULTIFUNCTION_BUTTON            2           // Multifunction button input pin
#define PIN_MULTIFUNCTION_GREEN             34          // For now assigned to BW (Band width)
#define PIN_MULTIFUNCTION_YELLOW            35          // For now assigned to STEP size
#define PIN_MULTIFUNCTION_RED               36          // For now assigned to USER

#define PIN_SELECT_BUTTON                   5           // Select button input pin
#define PIN_SELECT_GREEN                    37          // Wide/100/USER1
#define PIN_SELECT_YELLOW                   39          // Medium/1K/USER2
#define PIN_SELECT_RED                      40          // Narrow/10K/USER3

#define PIN_MEDIUM_A8                       22          // Hardware control of I.F. filter Bandwidth
#define PIN_NARROW_A9                       23          // Hardware control of I.F. filter Bandwidth

#define BANDWIDTH_WIDE                      0           // About 2.1 KHZ
#define BANDWIDTH_MEDIUM                    1           // About 1.7 KHZ
#define BANDWIDTH_NARROW                    2           // About 1 KHZ

#define STEP_100HZ                          0           // 100Hz tuning step
#define STEP_1000HZ                         1           // 1KHz tuning step
#define STEP_10000HZ                        2           // 10KHz tuning step

#define USER_1                              0           //User-defined mode 1
#define USER_2                              1           //User-defined mode 2
#define USER_3                              2           //User-defined mode 3

#endif
