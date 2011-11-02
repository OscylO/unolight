#if defined(ARDUINO) && ARDUINO < 100
#error : "To compile UnoLight you need Arduino 1.0 RC1 or later"
#endif

#if defined (__AVR_ATmega2560__) || defined (__AVR_ATmega1280__)
#error : "Code should work on Arduino Mega 2560 and 1280 but was not tested fully. To compile comment this line. Please let me know if it works (oscyloskop [at] gmail [dot] com). Thanks in advance."
#elif !defined (__AVR_ATmega328P__) && !defined (__AVR_ATmega168__)
#error : "Code created for ATmega168 and ATmega328p, tested with Arduino UNO(ATmega328p) and NANO (ATmega168). To compile for another Arduino boards with different ATmega you will need to change register names in source code and define Arduino pins to ports mappings in arduinoPins2Ports.h." 
#endif

#if (!defined COMMUNICATION_PROTOCOL) || ((COMMUNICATION_PROTOCOL != ATMOLIGHT_PROTOCOL) && (COMMUNICATION_PROTOCOL != AMBLONE_PROTOCOL))
#error : "You need to define COMMUNICATION_PROTOCOL as equal to AMBLONE_PROTOCOL or ATMOLIGHT_PROTOCOL in UnoLight.ino."
#endif

#define UNOLIGHT_VERSION 0x02  // 0x02 = UnoLight v0.20
#define BETA_VERSION 0x1

#include <Arduino.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "arduinoPins2Ports.h"
#include "leds.h"
#include "macros.h"
#include "gammaTable.h"
#include "serialCommunication.h"
#include "settings.h"





