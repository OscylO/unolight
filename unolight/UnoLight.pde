/*
 * UnoLight - Atmolight Arduino Client for ATmega 328p versions (Tested with ATmega 328p on Arduino UNO R2)
 * Copyright 2011 by Oskar Wicha
 */

/*
  Color |  Arduino Uno Pins for
        | LED1  LED2  LED3  LED4
  BLUE    2     5     8     11 
  GREEN   3     6     9     12 
  RED     4     7     10    13 
 */
#ifndef __AVR_ATmega328P__
#error Code created for ATmega 328p and Arduino UNO. To compile for another Arduino boards you will need to change register names in source code.
#endif

#define NUM_LEDS 6 // max number of RGB LEDs (ATmega 328p in Arduino UNO or NANO 3.0 sypports only up to 4 RGB LEDs on 12 output pins)
#define IDLE_TIME_LIMIT 30 // time (in seconds) without data transmision after which LEDs will by turn off  

#include <avr/io.h>
#include "ledPorts.h"
#include "macros.h"
#include "gammaTable.h"

uint16_t ledChannels[NUM_LEDS][3] = {0};
boolean ledsOff = false; //flag indicating if LEDs ar OFF or ON
uint8_t incomingAtmo[16]; //buffer array for incomming data over serial

//order is reversed, first uint8_t is last module in the chain
//0=sum,1=left,2=right,3=top,4=bottom
const uint8_t channelOrder[NUM_LEDS] = {1,2,3,4,0,0};
uint32_t timeOfLastTransmition = millis(); //stores time of last serial transmition

void setup() 
{
  cli();
  DDRD |= 0xFC;      // direction variable for port D - make all pins outputs except serial pins 0 & 1
  DDRB |= 0xFF;      // direction variable for port B - all outputs

  //----------------Initialize Interupts------------------
  initTimer2();

  //----------------Initialize serial connection ---------
  Serial.begin(38400); // Setting serial speed correct for Atmolight
  sei(); // Enable global interrupts
}

void loop()
{
  getAtmoCommand();
}

// TIMER2 Overflow interrupt
ISR(TIMER2_OVF_vect)
{
  static uint16_t pwmCounter;

  uint16_t *ledValPtr = &(ledChannels[0][0]);

  cli();
  //LED 1
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTD,LED1_RED_PIN)   : LEDOFF(PORTD,LED1_RED_PIN);
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTD,LED1_GREEN_PIN) : LEDOFF(PORTD,LED1_GREEN_PIN);
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTD,LED1_BLUE_PIN)  : LEDOFF(PORTD,LED1_BLUE_PIN);

  //LED 2
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTD,LED2_RED_PIN)   : LEDOFF(PORTD,LED2_RED_PIN);
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTD,LED2_GREEN_PIN) : LEDOFF(PORTD,LED2_GREEN_PIN);
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTD,LED2_BLUE_PIN)  : LEDOFF(PORTD,LED2_BLUE_PIN);

  //LED 3
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTB,LED3_RED_PIN)   : LEDOFF(PORTB,LED3_RED_PIN);
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTB,LED3_GREEN_PIN) : LEDOFF(PORTB,LED3_GREEN_PIN);
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTB,LED3_BLUE_PIN)  : LEDOFF(PORTB,LED3_BLUE_PIN);

  //LED 4
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTB,LED4_RED_PIN)   : LEDOFF(PORTB,LED4_RED_PIN);
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTB,LED4_GREEN_PIN) : LEDOFF(PORTB,LED4_GREEN_PIN);
  (*ledValPtr++ >= pwmCounter) ? LEDON(PORTB,LED4_BLUE_PIN)  : LEDOFF(PORTB,LED4_BLUE_PIN);

  (pwmCounter < 1023) ? pwmCounter++ : pwmCounter = 0;

  TCNT2 = 0xff;// necessery for not triggering commperator ISR also sets frequency
  sei();
}

//---------------ADDITIONAL FUNCTIONS----------------------------

inline void initTimer2()
{
  // Initialize TIMER2
  TCCR2B &= ~_BV(WGM22);
  TCCR2A |= _BV(WGM21);
  TCCR2A &= ~_BV(WGM20); // Fast PWM

  TCCR2B |= _BV(CS22);
  TCCR2B &= ~_BV(CS21);
  TCCR2B &= ~_BV(CS20); // Timer Prescaler 64

  TIMSK2 |= _BV(TOIE2);  //Enable Overflow Interrupt
  TCNT2 = 0;

  TIMSK1 &= ~_BV(TOIE1); // turn off Timer1 (not used interrupt)
}

void turnOffLEDArray()
{
  //Turn off all LEDs an Timer2 interrupt
  TIMSK2 &= ~_BV(TOIE2);	
  PORTD = 0x00;
  PORTC = 0x00;  
  ledsOff = true;
}

//get LED values sent over serial (Atmolight protocol)
inline void getAtmoCommand()
{
  if( Serial.available() > 18 && Serial.read() == 0xff && Serial.read() == 0x00 && Serial.read() == 0x00 )
  {
    timeOfLastTransmition = millis();

    uint8_t i = 0; 
    while( i < 16 )
      *(incomingAtmo + i++) = Serial.read();

    uint16_t *ledChannelAndColorPointer = &ledChannels[0][0]; 

    uint8_t channel = 0;
    while( channel < NUM_LEDS )
    {  
      uint8_t *incomingValuePointer = incomingAtmo + *(channelOrder + channel++) * 3 + 1; 

      *ledChannelAndColorPointer++ = *(gammaTable + *incomingValuePointer++); //red
      *ledChannelAndColorPointer++ = *(gammaTable + *incomingValuePointer++); //green
      *ledChannelAndColorPointer++ = *(gammaTable + *incomingValuePointer);   //blue              
    }

    if(ledsOff)
      TIMSK2 |= _BV(TOIE2); // LEDs ON

  }
  else
  {
    //turn off leds iff nod data for defined period of time 
    if( millis() - timeOfLastTransmition > IDLE_TIME_LIMIT * 1000 )
      turnOffLEDArray();
  }
}


