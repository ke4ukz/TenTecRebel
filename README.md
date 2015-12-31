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

# Serial Protocol
Two-way communication between the radio and a computer is achieved over the USB virtual serial port using a custom protocol.

## Message Format
Each message contains a header byte (0xee), a data type byte, an optional argument, and a footer byte (0xff). At this time, no checksum is utilized. Messages may be either an immediate command or status with no data, may contain a numeric data portion of four bytes, or a variable-length string.

## Messages

Message | Number | Data Type | Description
--------|--------|-----------|------------
Text | 0x00 | Variable-length string
Transmit Start | 0x01 | None | Radio transmitting
Transmit End | 0x02 | None | Transmission ended (radio receiving)
Voltage In | 0x03 | Integer | 0 to 1023 (raw ADC reading, multiply by 0.01611328125 for actual volts)
Transmit Frequency | 0x04 | Integer | Transmitting frequency in Hz
Receive Frequency | 0x05 | Integer |Receiving (RIT-adjusted) frequency in Hz
Output Power | 0x06 | Integer | RF voltage reading for output power (0 to 1023, meaningful-value calculation forthcoming)
Signal Strength | 0x07 | Integer | Relative signal strength (0 to 1023, meaningful-value calculation forthcoming)
Keyer Speed | 0x08 | Integer | Morse code keyer speed in Words Per Minute (WPM)
Received Character | 0x09 | ASCI Character |Single character received by Morse decoder
Character Sent | 0x0a | None | Character sent by Morse encoder has finished sending
Filter Bandwidth | 0x0b | Integer | Filter bandwidth selection (0=2.5KHz, 1=1.5KHz, 2=800Hz)
Tuning Step Size | 0x0c | Integer | Tuning step size selection (0=100Hz, 1=1KHz, 2=10KHz)
User Mode | 0x0d | Integer | User mode selected (0, 1, or 2); not used
Keyer Enabled | 0x0e | Boolean | Enable or disable the keyer (0=straight key, 1=iambic keyer)
Initialization Finished | 0x0f | None | Radio initialization has finished and commands may now be sent
Decoder Enable | 0x10 | Boolean | Enable or disable Morse code decoder (0=off, 1=on)
Decode Threshhold | 0x11 | Integer | Audio level required for a signal to be considered for decoding (0 to 1023)
