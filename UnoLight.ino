/*
 * UnoLight v0.2 Beta 2 - Atmolight and Amblone Arduino Client for ATmega328p,
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

/*
 * ____________________________________________
 * |  LED  |         Arduino Pins for         |
 * | Color | LED1 | LED2 | LED3 | LED4 | LED5 |
 * --------------------------------------------
 * |RED    |  2   |  5   |  8   |  11  |  A0  |
 * --------------------------------------------
 * |GREEN  |  3   |  6   |  9   |  12  |  A1  |
 * --------------------------------------------
 * |BLUE   |  4   |  7   |  10  |  13  |  A2  |
 * --------------------------------------------
 */
/**
 * Packets structures if COMMUNICATION_PROTOCOL == ATMOLIGHT_PROTOCOL :
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
 * Structure of packet send in response to received "info request packet" :
 * _______________________________________________________________________________________________________________________________________________________________________
 * |       HEADER       | VERSION |                                                       SETTINGS VALUES                                                                |
 * |____________________|_________|______________________________________________________________________________________________________________________________________|                                                                              
 * |Byte 1|Byte 2|Byte 3|  Byte 4 | Byte 5 | Byte 6 | Byte 7 | Byte 8 | Byte 9 | Byte 10| Byte 11| Byte 12| Byte 13| Byte 14| Byte 15| Byte 16| Byte 17| Byte 18| Byte 19|
 * |------------------------------|---------------------------------------------------------------------------------------------------------------------------------------
 * | 0xff | 0x00 | 0xaa |   0x02  |reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|reserved|
 * -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

/**
 * Packets structures if COMMUNICATION_PROTOCOL == AMBLONE_PROTOCOL :
 * 
 * Info about Amblone protocol can by downloaded from here : http://amblone.com/download/doc
 */

/**
 * Important info: Unolight was tested using Arduino 1.0 RC1 and should be compiled using this version or later.
 */

// Supported communication protocols :
#define ATMOLIGHT_PROTOCOL 1
#define AMBLONE_PROTOCOL   2 

/* 
* Select communication protocol: 
* ATMOLIGHT_PROTOCOL  http://www.vdr-wiki.de/wiki/index.php/Atmo-plugin 
* or 
* AMBLONE_PROTOCOL http://amblone.com , when using Amblone protocol settings can't be changed, it will be fixed in feature release
*
* P.S 
* In my opinion Amblone works better but is less popular so ATMOLIGHT_PROTOCOL is set as default but I suggest that you check Amblone
* you can download PC application processing screen image from here http://amblone.com/download/binaries1,2,1
*/
#define COMMUNICATION_PROTOCOL ATMOLIGHT_PROTOCOL

// Set this true if using PNP transistors to control LEDs and to false if NPN
#define INVERT_OUTPUT false
#define TEST_PERFORMANCE false
//-------------------------------------------------------------------------------------------------------
#include "UnoLight.h"
//-------------------------------------------------------------------------------------------------------
void setup() 
{
  noInterrupts();             // Disable global interrupts 
  initSettings();
  initSerialCommunication();
  initLeds(); 
  initSensors();
  disableUnusedFunctions();  
  interrupts();               // Enable global interrupts 
  //showTestingPattern();     // use it to test led configuration (all red -> all green -> all blue -> all off)
  //ledsOff = true;
 
  
  for(;;)
  {
	//if(!turnOffIfAmbientLightToBright())
	{
		if( getCommand() )
		{
			ledsOff = false;
		}
		else // Turn off LEDs if no valid data for defined period of time 
		{
			if ( !ledsOff )
			{
				if ( timeElapsedSinceLastCmd() > (*idleTimeLimit + 1) )
					turnOffLEDs();
			}
		}
	}
	//else
	//	Serial.flush();

//#if (COMMUNICATION_PROTOCOL == AMBLONE_PROTOCOL)
	if( *isSmoothEnabled  || (!*isSmoothEnabled && ledsOff) )
		smooth();//smooth(*smoothAmount); 
//#elif (COMMUNICATION_PROTOCOL == ATMOLIGHT_PROTOCOL)
	//if( !*isSmoothEnabled && ledsOff )
		//smooth();
//#endif

#if (TEST_PERFORMANCE == true)
	loopCounter++;

	if ((micros() - sendTime) >= 1000000)
	{
		temp = millis();
		Serial.print("fps = ");
		Serial.println(1000.0f / (float)((float)temp / framesCounter));

		Serial.print("main loop iterations per second = ");
		Serial.println(loopCounter);
		loopCounter = 0;
		sendTime = micros();
	}
#endif
  }
}
//-------------------------------------------------------------------------------------------------------
void loop()
{
	// Not used
}
//-------------------------------------------------------------------------------------------------------
static inline void disableUnusedFunctions()
{
   power_twi_disable();
   power_spi_disable();
   
   // don't turn off Timer0 because it is used by delay() and milis()
   power_timer2_disable();  // turn off interrupt for Timer1 (not used interrupt)
   
#if defined (__AVR_ATmega2560__) || defined (__AVR_ATmega1280__) 
   power_timer3_disable();  // turn off interrupt for Timer3 (not used interrupt)
   power_timer4_disable();  // turn off interrupt for Timer4 (not used interrupt)
   power_timer5_disable();  // turn off interrupt for Timer5 (not used interrupt)
#endif                          
}
//-------------------------------------------------------------------------------------------------------
