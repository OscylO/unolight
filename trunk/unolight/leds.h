/*
  Important: If you want to use other pins then Digital Pins 2-13 and Analog A0-A2 than you have to change function initLeds() in leds.ino.
*/
/*
 ____________________________________________
 |  LED  |      Arduino Uno Pins for        |
 | Color | LED1 | LED2 | LED3 | LED4 | LED5 |
 --------------------------------------------
 |BLUE   |  2   |  5   |  8   |  11  |  A0  |
 --------------------------------------------
 |GREEN  |  3   |  6   |  9   |  12  |  A1  |
 --------------------------------------------
 |RED    |  4   |  7   |  10  |  13  |  A2  |
 --------------------------------------------
 */
 
#define LEDS_ON_A_FOURTH_OF_THEIR_POWER false  // useful if you have weak power supply and many of Power LEDs
#define USE_ANALOG_PINS true   // If "true" Arduinos A0 to A2 pins will be use as 
                               // PWM pins for RGB LED 5 if "false" they won't be used

#define NUM_OF_RGB_LEDS 5      // Number of RGB LEDs values transmited using Serial by Atmolight ( UnoLight on Arduino UNO or NANO
                               // supports only up to 4 RGB LEDs on 12 output pins using "Digital Pins" or 5 RGB LEDs if using also 
                               // "Analog Pins"). Pins A3-A5 will be used for something different like for example light sensor.
                               // Don't change this value.
                               
#define NUM_OF_LEDS (NUM_OF_RGB_LEDS * 3)
                               
#if !defined (PINS_UNDEFINED)  // if pins are defined for this Arduino board in arduinoPins2Ports.h

#if USE_ANALOG_PINS
//PINS A0 - A2 on PORTC
#define LED5_RED    PIN_A2  
#define LED5_GREEN  PIN_A1  
#define LED5_BLUE   PIN_A0  
#endif

//PINS 8 - 13 on PORTB
#define LED4_RED    PIN_D13 
#define LED4_GREEN  PIN_D12 
#define LED4_BLUE   PIN_D11 

#define LED3_RED    PIN_D10 
#define LED3_GREEN  PIN_D9  
#define LED3_BLUE   PIN_D8  

//PINS 2 - 7 on PORTD
#define LED2_RED    PIN_D7  
#define LED2_GREEN  PIN_D6  
#define LED2_BLUE   PIN_D5  

#define LED1_RED    PIN_D4  
#define LED1_GREEN  PIN_D3  
#define LED1_BLUE   PIN_D2 

// Compilation error tests
#if (!defined LED1_RED || !defined LED1_GREEN || !defined LED1_BLUE || !defined LED2_RED || !defined LED2_GREEN || !defined LED2_BLUE || !defined LED3_RED || !defined LED3_GREEN || !defined LED3_BLUE || !defined LED4_RED || !defined LED4_GREEN || !defined LED4_BLUE)
#define LEDS_UNDEFINED
#error : Some of pins for at least one of LEDs nr 1 to 4 are not defined in leds.h
#endif

#if (USE_ANALOG_PINS && (!defined LED5_RED || !defined LED5_GREEN || !defined LED5_BLUE))
#define LEDS_UNDEFINED
#error : LED nr 5 using analog pins is not defined in leds.h
#endif

#else                                            // equal to "defined (PINS_UNDEFINED)"
#define LEDS_UNDEFINED
#error : LEDs are not defined in leds.h because pins are not defined in arduinoPins2Ports.h
#endif

// Variables and constants
static word ledChannels[NUM_OF_RGB_LEDS][3];
static word ledChannelsNew[NUM_OF_RGB_LEDS][3];
static boolean ledsOff = true;                  // flag indicating if LEDs are OFF or ON


