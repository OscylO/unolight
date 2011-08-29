/* Ports and Pins
 Direct port access is much faster than digitalWrite.
 You must match the correct port and pin as shown in the table below.
 
 Arduino Pin        Port        Pin
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
 1 (TX)             PORTD       1
 0 (RX)             PORTD       0
 A5 (Analog)        PORTC       5
 A4 (Analog)        PORTC       4
 A3 (Analog)        PORTC       3
 A2 (Analog)        PORTC       2
 A1 (Analog)        PORTC       1
 A0 (Analog)        PORTC       0
 */
/* 
 PORTB,5 = PIN 13 = LED4_RED_PIN
 PORTB,4 = PIN 12 = LED4_GREEN_PIN
 PORTB,3 = PIN 11 = LED4_BLUE_PIN
 
 PORTB,2 = PIN 10 = LED3_RED_PIN 
 PORTB,1 = PIN 9 = LED3_GREEN_PIN
 PORTB,0 = PIN 8 = LED3_BLUE_PIN
 
 PORTD,7 = PIN 7 = LED2_RED_PIN
 PORTD,6 = PIN 6 = LED2_GREEN_PIN
 PORTD,5 = PIN 5 = LED2_BLUE_PIN
 
 PORTD,4 = PIN 4 = LED1_RED_PIN
 PORTD,3 = PIN 3 = LED1_GREEN_PIN
 PORTD,2 = PIN 2 = LED1_BLUE_PIN
 */

//PINS 8 - 13 on PORTB
#define LED4_RED_PIN 0x20     //PIN 13
#define LED4_GREEN_PIN 0x10   //PIN 12
#define LED4_BLUE_PIN 0x08    // PIN 11

#define LED3_RED_PIN 0x04     // RED pin of the LED to PWM pin 10
#define LED3_GREEN_PIN 0x02   // GREEN pin of the LED to PWM pin 9
#define LED3_BLUE_PIN 0x01    // BLUE pin of the LED to PWM pin 8

//PINS 2 - 7 on PORTD
#define LED2_RED_PIN 0x80    // RED pin of the LED to PWM pin 7
#define LED2_GREEN_PIN 0x40  // GREEN pin of the LED to PWM pin 6
#define LED2_BLUE_PIN 0x20   // BLUE pin of the LED to PWM pin 5

#define LED1_RED_PIN 0x10    // RED pin of the LED to PWM pin 4
#define LED1_GREEN_PIN 0x08  // GREEN pin of the LED to PWM pin 3
#define LED1_BLUE_PIN 0x04   // BLUE pin of the LED to PWM pin 2

#define ALL_LED_PINS_PORTD (LED1_RED_PIN | LED1_GREEN_PIN | LED1_BLUE_PIN | LED2_RED_PIN | LED2_GREEN_PIN | LED2_BLUE_PIN); 
#define ALL_LED_PINS_PORTB (LED3_RED_PIN | LED3_GREEN_PIN | LED3_BLUE_PIN | LED4_RED_PIN | LED4_GREEN_PIN | LED4_BLUE_PIN);


