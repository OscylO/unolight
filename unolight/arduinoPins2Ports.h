/*
 http://arduino.cc/en/uploads/Main/arduino-uno-schematic.pdf
 
 Ports and Pins of Arduino Uno and Duemilanove :  
 __________________________________
 Arduino Uno Pin    Port        Pin
 13 (SCK)           PORTB       5
 12 (MISO)          PORTB       4
 11 (MOSI)          PORTB       3
 10 (SS)            PORTB       2
 9                  PORTB       1
 8                  PORTB       0
 7                  PORTD       7
 6                  PORTD       6
 5                  PORTD       5
 4                  PORTD       4
 3                  PORTD       3
 2                  PORTD       2
 1 (TX)             PORTD       1 // NOT USED BY LEDs
 0 (RX)             PORTD       0 // NOT USED BY LEDs
 A5 (Analog)        PORTC       5 // NOT USED BY LEDs
 A4 (Analog)        PORTC       4 // NOT USED BY LEDs
 A3 (Analog)        PORTC       3 // NOT USED BY LEDs
 A2 (Analog)        PORTC       2
 A1 (Analog)        PORTC       1
 A0 (Analog)        PORTC       0
 _________________________________
 
 Arduino Nano has additionaly (not used by UnoLight):
 A7 (Analog)        PORTC       7 
 A6 (Analog)        PORTC       6
 */

#if (defined __AVR_ATmega168__ || defined __AVR_ATmega328P__) // Arduino : Uno, Nano, Nano 3.0, Duemilanove

//PINS A0 - A7 on PORTC
#if (NUM_ANALOG_INPUTS > 6)      // if Arduino Nano

#define PIN_A7  (PORTC, _BV(5))  // NOT USED BY LED
#define PIN_A6  (PORTC, _BV(4))  // NOT USED BY LED

#if (!defined PIN_A6 || !defined PIN_A7)
#define PINS_UNDEFINED
#error : This version of Arduino board has more than 6 analog pins and some of their pin definitions are missing from arduinoPins2Ports.h file.
#endif

#endif

#define PIN_A5  (PORTC, _BV(5))  // NOT USED BY LED
#define PIN_A4  (PORTC, _BV(4))  // NOT USED BY LED
#define PIN_A3  (PORTC, _BV(3))  // NOT USED BY LED

#define PIN_A2  (PORTC, _BV(2))  
#define PIN_A1  (PORTC, _BV(1))  
#define PIN_A0  (PORTC, _BV(0))  

//PINS 8 - 13 on PORTB
#define PIN_D13 (PORTB, _BV(5))  
#define PIN_D12 (PORTB, _BV(4)) 
#define PIN_D11 (PORTB, _BV(3)) 

#define PIN_D10 (PORTB, _BV(2))  
#define PIN_D9  (PORTB, _BV(1)) 
#define PIN_D8  (PORTB, _BV(0)) 

//PINS 2 - 7 on PORTD
#define PIN_D7  (PORTD, _BV(7)) 
#define PIN_D6  (PORTD, _BV(6))  
#define PIN_D5  (PORTD, _BV(5)) 

#define PIN_D4  (PORTD, _BV(4)) 
#define PIN_D3  (PORTD, _BV(3)) 
#define PIN_D2  (PORTD, _BV(2))  

#define PIN_D1  (PORTD, _BV(1))  // TX
#define PIN_D0  (PORTD, _BV(0))  // RX

#if (!defined PIN_D0 || !defined PIN_D1 || !defined PIN_D2 || !defined PIN_D3 || !defined PIN_D4 || !defined PIN_D5 || !defined PIN_D6 || !defined PIN_D7 || !defined PIN_D8 || !defined PIN_D9 || !defined PIN_D10 || !defined PIN_D11 || !defined PIN_D12 || !defined PIN_D13 || !defined PIN_A0 || !defined PIN_A1 || !defined PIN_A2 || !defined PIN_A3 || !defined PIN_A4  || !defined PIN_A5)
#define PINS_UNDEFINED
#error : Some of pins definitions for this version of Arduino board are missing in arduinoPins2Ports.h file.
#endif

#elif defined (__AVR_ATmega2560__) || defined (__AVR_ATmega1280__)
// Arduino Mega 2560 http://arduino.cc/en/uploads/Main/arduino-mega2560-schematic.pdf
// Arduino Mega 1280 http://www.arduino.cc/en/uploads/Main/arduino-mega-schematic.pdf
// UnoLight has not been tested with Arduino Mega if you have one let me know if it works.

#define PIN_A5  (PORTF, _BV(5))  // NOT USED BY LED
#define PIN_A4  (PORTF, _BV(4))  // NOT USED BY LED
#define PIN_A3  (PORTF, _BV(3))  // NOT USED BY LED

#define PIN_A2  (PORTF, _BV(2))  
#define PIN_A1  (PORTF, _BV(1))  
#define PIN_A0  (PORTF, _BV(0))  

#define PIN_D13 (PORTB, _BV(7))  
#define PIN_D12 (PORTB, _BV(6))  
#define PIN_D11 (PORTB, _BV(5))  

#define PIN_D10 (PORTB, _BV(4))  
#define PIN_D9  (PORTH, _BV(6))  
#define PIN_D8  (PORTH, _BV(5))  

#define PIN_D7  (PORTH, _BV(4))  
#define PIN_D6  (PORTH, _BV(3))  
#define PIN_D5  (PORTE, _BV(3))  

#define PIN_D4  (PORTG, _BV(5))  
#define PIN_D3  (PORTE, _BV(5))  
#define PIN_D2  (PORTE, _BV(4))  

#define PIN_D1  (PORTE, _BV(1))  // TX
#define PIN_D0  (PORTE, _BV(0))  // RX

#if (!defined PIN_D0 || !defined PIN_D1 || !defined PIN_D2 || !defined PIN_D3 || !defined PIN_D4 || !defined PIN_D5 || !defined PIN_D6 || !defined PIN_D7 || !defined PIN_D8 || !defined PIN_D9 || !defined PIN_D10 || !defined PIN_D11 || !defined PIN_D12 || !defined PIN_D13 || !defined PIN_A0 || !defined PIN_A1 || !defined PIN_A2 || !defined PIN_A3 || !defined PIN_A4  || !defined PIN_A5)
#define PINS_UNDEFINED
#error : Some of pins definitions for this version of Arduino board are missing in arduinoPins2Ports.h file.
#endif

#else
#define PINS_UNDEFINED
#error : No pins definitions for this version of Arduino board in arduinoPins2Ports.h file.
#endif



