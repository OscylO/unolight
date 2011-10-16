/*
 * UnoLight v0.2 Beta 1 - Atmolight and Amblone Arduino Client for ATmega328p,
 *                        ATmega168, ATmega2560, ATmega1280 on Arduino boards.
 *
 * Author : Oskar Wicha (oscyloskop [at] gmail [dot] com)
 *
 * UnoLight site : http://code.google.com/p/unolight/
 * Authors blog  : http://www.oskarwicha.blogspot.com
 *
 * License :
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to anyone change, redistribute or copy parts of this code
 * as long as it is not for commercial purposes / monetary gain
 * Please be so kind to pay credit where due.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * ____________________________________________
 * |  LED  |   Arduino Uno or NANO Pins for   |
 * | Color | LED1 | LED2 | LED3 | LED4 | LED5 |
 * --------------------------------------------
 * |  BLUE |  2   |  5   |  8   |  11  |  A0  |
 * --------------------------------------------
 * | GREEN |  3   |  6   |  9   |  12  |  A1  |
 * --------------------------------------------
 * |  RED  |  4   |  7   |  10  |  13  |  A2  |
 * --------------------------------------------
 */
/**
 * Packets structures if COMMUNICATION_PROTOCOL == ATMOLITE_PROTOCOL :
 * 
 * Standard Atmolight packet structure :
 * ________________________________________________________________________________________________________________________________________________
 * |       HEADER       |                                                      COLOR VALUES FOR 5 RGB LED                                         |
 * |____________________|_________________________________________________________________________________________________________________________|
 * |Byte 1|Byte 2|Byte 3|Byte 4|Byte 5|Byte 6|Byte 7|Byte 8|Byte 9|Byte 10|Byte 11|Byte 12|Byte 13|Byte 14|Byte 15|Byte 16|Byte 17|Byte 18|Byte 19|
 * ------------------------------------------------------------------------------------------------------------------------------------------------
 * | 0xff | 0x00 | 0x00 | 0x0f |  RED | GREEN| BLUE |  RED | GREEN|  BLUE |  RED  | GREEN |  BLUE |  RED  | GREEN |  BLUE |   RED | GREEN |  BLUE |                                                                                     |
 * ------------------------------------------------------------------------------------------------------------------------------------------------
 */
/**
 * Settings packet structure :
 * _______________________________________________________________________________________________________________________________________________________________________
 * |       HEADER       | VERSION |                                                          SETTINGS VALUES                                                             |
 * |____________________|_________|______________________________________________________________________________________________________________________________________|
 * |Byte 1|Byte 2|Byte 3|  Byte 4 | Byte 5 | Byte 6 | Byte 7 | Byte 8 | Byte 9 | Byte 10| Byte 11| Byte 12| Byte 13| Byte 14| Byte 15| Byte 16| Byte 17| Byte 18| Byte 19|
 * ----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
 * | 0xff | 0x00 | 0xcc |   0x02  |reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|                                                                                     |
 * ----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
 */
/**
 * Info request packet structure:
 * ________________________________________________________________________________________________________________________________________________________________
 * |       HEADER       |                                               BITS USED TO KEEP PACKET SIZE CONSTANT                                                    |
 * |____________________|_________________________________________________________________________________________________________________________________________|
 * |Byte 1|Byte 2|Byte 3|Byte 4|Byte 5|Byte 6| Byte 7 | Byte 8 | Byte 9 | Byte 10| Byte 11| Byte 12| Byte 13| Byte 14| Byte 15| Byte 16| Byte 17| Byte 18| Byte 19|
 * |--------------------|------------------------------------------------------------------------------------------------------------------------------------------
 * | 0xff | 0x00 | 0xaa |   0  |   0  |   0  |    0   |    0   |    0   |    0   |    0   |    0   |    0   |    0   |    0   |    0   |    0   |    0   |    0   | 
 * ----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * 
 * Structure of packet send in response to recived "info request packet" :
 * ___________________________________________________________________________________________________________________________________________________________________
 * |       HEADER       | VERSION |                                                       SETTINGS VALUES                                                            |
 * |____________________|_________|__________________________________________________________________________________________________________________________________|                                                                              
 * |Byte 1|Byte 2|Byte 3|  Byte 4 |Byte 5|Byte 6| Byte 7 | Byte 8 | Byte 9 | Byte 10| Byte 11| Byte 12| Byte 13| Byte 14| Byte 15| Byte 16| Byte 17| Byte 18| Byte 19|
 * |------------------------------|-----------------------------------------------------------------------------------------------------------------------------------
 * | 0xff | 0x00 | 0xaa |   0x02  |0 or 1|0 or 1| 0- 255 |reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|
 * -------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

/**
 * Packets structures if COMMUNICATION_PROTOCOL == AMBLONE_PROTOCOL :
 * 
 * Info about Amblone protocol can by downloaded from here : http://amblone.com/download/doc
 * 
 * UnoLight settings can't be changed over serial connection when using this protocol.
 */

/**
 * Important info: Unolight was tested using Arduino 1.0 RC1 and should be compiled using this version or later.
 */

// Suported communication protocols :
#define ATMOLIGHT_PROTOCOL 1
#define AMBLONE_PROTOCOL   2 

/* 
* Select communication protocol: 
* ATMOLIGHT_PROTOCOL  http://www.vdr-wiki.de/wiki/index.php/Atmo-plugin 
* or 
* AMBLONE_PROTOCOL http://amblone.com , when using Amblone protocol settings can't be changed, it will be fixed in feature relase
*
* P.S In my opinion Amblone works better but is less popular so ATMOLIGHT_PROTOCOL is set as default but I sugest that you check Amblone
* you can download PC application processing screen image form here http://amblone.com/download/binaries1,2,1
*/
#define COMMUNICATION_PROTOCOL ATMOLIGHT_PROTOCOL
//-------------------------------------------------------------------------------------------------------
#include "UnoLight.h"
//-------------------------------------------------------------------------------------------------------
void setup() 
{
  noInterrupts();             // Disable global interrupts 
  initSettings();
  initSerialCommunication();
  initLeds();        
  interrupts();               // Enable global interrupts 
}
//-------------------------------------------------------------------------------------------------------
void loop()
{
  if( getCommand() )
  {
    if(ledsOff)
      ledsOff = false;
  }
  else
  {
    if( !ledsOff )
      turnOffLedsIfNeeded();
  }

  if( *isSmoothEnabled || (!*isSmoothEnabled && ledsOff) )
    smooth(*smoothAmount); 
}
//-------------------------------------------------------------------------------------------------------
