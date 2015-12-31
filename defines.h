#ifndef DEFINES_H
#define DEFINES_H

#define __NAME__                            "TenTec Rebel 506 (KE4UKZ)"
#define __VERSION__                         "1.0.12"

//PWM on pins 3, 5, 6, 9, & 10

#define SDATA_BIT                           10          //  keep!
#define SCLK_BIT                            8           //  keep!
#define FSYNC_BIT                           9           //  keep!
#define RESET_BIT                           11          //  keep!
#define FREQ_REGISTER_BIT                   12          //  keep!
#define AD9834_FREQ0_REGISTER_SELECT_BIT    0x4000      //  keep!
#define AD9834_FREQ1_REGISTER_SELECT_BIT    0x8000      //  keep!
#define FREQ0_INIT_VALUE                    0x01320000  //  ?

#define PIN_ENCODER0A                       7           // Rotary encoder A
#define PIN_ENCODER0B                       6           // PWM Rotary encoder B
#define PIN_SIDETONE                        3           // PWM maybe to be changed to a logic control for a separate side tone gen
#define PIN_KEY_DAH                         33          // Physical pin attached to the "dah" input
#define PIN_KEY_DIT                         32          // Physical pin attached to the "dit" input
#define PIN_TRANSMIT                        38          // Physical pin attached to the transmitter key
#define PIN_TT_LED                          24          //
#define PIN_BAND_SELECT                     41          // if shorting block on only one pin 20m(1) on both pins 40m(0)
#define PIN_MULTIFUNCTION_BUTTON            2           // Multifunction button input pin
#define PIN_MULTIFUNCTION_GREEN             34          // For now assigned to BW (Band width)
#define PIN_MULTIFUNCTION_YELLOW            35          // For now assigned to STEP size
#define PIN_MULTIFUNCTION_RED               36          // For now assigned to USER
#define PIN_SELECT_BUTTON                   5           // PWM Select button input pin
#define PIN_SELECT_GREEN                    37          // Wide/100/USER1
#define PIN_SELECT_YELLOW                   39          // Medium/1K/USER2
#define PIN_SELECT_RED                      40          // Narrow/10K/USER3
#define PIN_MEDIUM_A8                       22          // Hardware control of I.F. filter Bandwidth
#define PIN_NARROW_A9                       23          // Hardware control of I.F. filter Bandwidth
#define PIN_CWSPEED                         A7          // To adjust CW speed for user written keyer.
#define PIN_CWREAD                          A6          // Can be used to decode CW. 
#define PIN_POWEROUT                        A3          // Reads RF out voltage at Antenna.
#define PIN_POWERIN                         A2          // Reads 1/5 th or 0.20 of supply voltage.
#define PIN_SMETER                          A1          // To give a realitive signal strength based on AGC voltage.
#define PIN_RIT                             A0          // pin that the sensor is attached to used for a rit routine later.


#define MULTIFUNCTION_1                     0
#define MULTIFUNCTION_2                     1
#define MULTIFUNCTION_3                     2

#define FUNCTION_1                          0
#define FUNCTION_2                          1
#define FUNCTION_3                          2

#define BANDWIDTH_WIDE                      0           // About 2.1 KHZ
#define BANDWIDTH_MEDIUM                    1           // About 1.7 KHZ
#define BANDWIDTH_NARROW                    2           // About 1 KHZ

#define STEP_100HZ                          0           // 100Hz tuning step
#define STEP_1000HZ                         1           // 1KHz tuning step
#define STEP_10000HZ                        2           // 10KHz tuning step

#define USER_1                              0           //User-defined mode 1
#define USER_2                              1           //User-defined mode 2
#define USER_3                              2           //User-defined mode 3

#define KEYER_OFF                           0
#define KEYER_ON                            1

#define BAND_20METERS                       0
#define BAND_40METERS                       1
#define BANDLIMIT_20_TOP                    5.35e6
#define BANDLIMIT_20_BOTTOM                 5.0e6
#define BANDLIMIT_40_TOP                    16.3e6
#define BANDLIMIT_40_BOTTOM                 16.0e6
#define DEFAULT_40METERS                    16.03e6     // IF + Band frequency, HI side injection 40 meter range 16 > 16.3 mhz
#define DEFAULT_20METERS                    5.06e6      // Band frequency - IF, LOW side injection 20 meter range 5 > 5.35 mhz
#define REFERENCE                           49.99975e6  // for ad9834 this may be tweaked in software to fine tune the Radio

#define SERIAL_HEADER                       0xee
#define SERIAL_FOOTER                       0xff
#define SERIAL_STRING                       0x00
#define SERIAL_TXSTART                      0x01
#define SERIAL_TXEND                        0x02
#define SERIAL_VOLTMETER                    0x03
#define SERIAL_TXFREQUENCY                  0x04
#define SERIAL_RXFREQUENCY                  0x05
#define SERIAL_OUTPUTPOWER                  0x06
#define SERIAL_SMETER                       0x07
#define SERIAL_WPM                          0x08
#define SERIAL_RECEIVE_CHAR                 0x09
#define SERIAL_CHAR_SENT                    0x10
#define SERIAL_BANDWIDTH                    0x11
#define SERIAL_STEPSIZE                     0x12
#define SERIAL_USER                         0x13
#define SERIAL_KEYER                        0x14
#define SERIAL_INITDONE                     0x15

#define SERIAL_SET_FREQUENCY                0x80
#define SERIAL_TUNE_UP                      0x81
#define SERIAL_TUNE_DOWN                    0x82
#define SERIAL_SET_WPM                      0x83
#define SERIAL_SEND_CHAR                    0x84
#define SERIAL_SET_BANDWIDTH                0x85
#define SERIAL_SET_STEPSIZE                 0x86
#define SERIAL_SET_USER                     0x87
#define SERIAL_SET_KEYER                    0x88

#define SERIALSTEP_IDLE                     0
#define SERIALSTEP_EXPECT_TYPE              1
#define SERIALSTEP_EXPECT_4MORE             2
#define SERIALSTEP_EXPECT_3MORE             3
#define SERIALSTEP_EXPECT_2MORE             4
#define SERIALSTEP_EXPECT_1MORE             5
#define SERIALSTEP_EXPECT_FOOTER            6

#endif
