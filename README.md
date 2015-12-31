# TenTecRebel
Custom firmware for TenTec Rebel 506

## Purpose
This project is designed to replace the factory firmware to add features to the radio. The primary goal is to control as many features as possible through commands sent over the serial port, with the end result being a touch-screen graphical interface while leaving the original hardware controls with their original functionality.

## Features
Some features in the original firmware have been removed or changed because they were unnecessary or unsuitable for the purpose of this project. Many other features have been added to increase the flexibility and functionality of the radio.

### Removed and Changed Features
 * Removed all LCD functionality
 * Removed human-readable data over the serial port
 * Cleaned an organized code for greatly reduced size and improved efficiency
 * Removed tuning step indicator; tuning will be done on the computer now

### Added features
 * Binary serial communications protocol (see below) that includes several different kinds of data and implements a wide range of commands
 * Iambic keyer, or straight key
 * Morse code encoder
 * Morse code decoder

## Computer Interface
Currently the only computer interface available is for testing and debugging. In the future there will be a cross-platform application to act as a front-end for the radio.

## Default Settings
The following are the default values for each setting:

Setting | Value
--------|------
Frequency | 7.03MHZ for 40 meters or 14.06MHz for 20 meters
Filter Bandwidth | 2.5KHz
Tuning Step Size | 100Hz
Iambic Keyer | Enabled
Morse Decoder | Enabled
Keyer/Decoder Speed | 20WPM
Decode Threshhold | 700
User Mode | 1 (not used)

# Serial Protocol
Two-way communication between the radio and a computer is achieved over the USB virtual serial port using a custom protocol.

## Message Format
Each message contains a header byte (0xee), a data type byte, an optional argument, and a footer byte (0xff). At this time, no checksum is utilized. Messages may be either an immediate command or status with no data, may contain a numeric data portion of four bytes, or a variable-length string.

## Output Messages
These message are sent from the radio to the computer:

Message | Number | Data Type | Description
--------|--------|-----------|------------
Text | 0x00 | Variable-length string | Text to display to the user
Transmit Start | 0x01 | None | Radio transmitting
Transmit End | 0x02 | None | Transmission ended (radio receiving)
Voltage In | 0x03 | Integer | 0 to 1023 (raw ADC reading, multiply by 0.01611328125 for actual volts)
Transmit Frequency | 0x04 | Integer | Transmitting frequency in Hz
Receive Frequency | 0x05 | Integer |Receiving (RIT-adjusted) frequency in Hz
Output Power | 0x06 | Integer | RF voltage reading for output power (0 to 1023, meaningful-value calculation forthcoming)
Signal Strength | 0x07 | Integer | Relative signal strength (0 to 1023, meaningful-value calculation forthcoming)
Keyer/Decoder Speed | 0x08 | Integer | Morse code keyer and decoder speed in Words Per Minute (WPM)
Received Character | 0x09 | ASCII Character |Single character received by Morse decoder
Character Sent | 0x0a | None | Character sent by Morse encoder has finished sending
Filter Bandwidth | 0x0b | Integer | Current filter bandwidth selection (0=2.5KHz, 1=1.5KHz, 2=800Hz)
Tuning Step Size | 0x0c | Integer | Current tuning step size selection (0=100Hz, 1=1KHz, 2=10KHz)
User Mode | 0x0d | Integer | Current user mode selected (0, 1, or 2); not used
Keyer Enabled | 0x0e | Boolean | Keyer enabled or disabled (0=straight key, 1=iambic keyer)
Initialization Finished | 0x0f | None | Radio initialization has finished and commands may now be sent
Decoder Enable | 0x10 | Boolean | Morse code decoder enabled or disabled (0=off, 1=on)
Decode Threshhold | 0x11 | Integer | Audio level required for a signal to be considered for decoding (0 to 1023)

## Input Messages
These messages are sent from the computer to control the radio:

Message | Number | Data Type | Description
--------|--------|-----------|------------
Set Frequency | 0x80 | Integer | New frequency in Hz (must be valid for the selected band)
Tune Up | 0x81 | None | Tune up a step (based on currently selected tuning step)
Tune Down | 0x82 | None | Tune down a step (based on currently selected tuning step)
Set Keyer/Decoder Speed | 0x83 | Integer | Set keyer and decoder speed in WPM
Send Character | 0x84 | ASCII Character | Send a character using the Morse encoder (only available when the iambic keyer is enabled)
Set Filter Bandwidth | 0x85 | Integer | Set filter width (0=2.5KHz, 1=1.5KHz, 2=800Hz)
Set Tuning Step Size | 0x86 | Integer | Set tuning step size (0=100Hz, 1=1KHz, 2=10KHz)
Set User Mode | 0x87 | Integer | Set user mode (0, 1, or 2); not used
Set Keyer Mode | 0x88 | Boolean | Enable or diable the iambic keyer (0=straight key, 1=iambic keyer)
Set Morse Decoder | 0x89 | Boolean | Enable or disable the Morse decoder (0=disabled, 1=enabled)
Set Morse Decoding Threshhold | 0x8a | Integer | Set audio level required for a signal to be considered for decoding (0 to 1023)
