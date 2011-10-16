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
//-------------------------------------------------------------------------------------------------------
 /** 
   LEDs pins initialization.
   It is not the fastest way 
   but it is easy to understand
   for everybody.
*/
static inline void initLeds()
{ 
#if (defined __AVR_ATmega168__ || defined __AVR_ATmega328P__) 
  byte i = 13;
#elif defined (__AVR_ATmega2560__) || defined (__AVR_ATmega1280__) 
  byte i = 53;
#endif

  while( i >= 2 )
    pinMode(i--, OUTPUT);
    
#if USE_ANALOG_PINS
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT); 
#endif

  initTimer2();             // Initialize Timer2
}
//-------------------------------------------------------------------------------------------------------
static inline void initTimer2()
{
#if (defined __AVR_ATmega168__ || defined __AVR_ATmega328P__) 
  // Initialize TIMER2
  BIT_CLR(TCCR2B,WGM22);
  BIT_SET(TCCR2A,WGM21);
  BIT_CLR(TCCR2A,WGM20);  // CTC PWM

  BIT_CLR(TCCR2B,CS22);
  BIT_SET(TCCR2B,CS21);
  BIT_SET(TCCR2B,CS20);   // Timer Prescaler 32, results in 488 Hz led frequency 

  BIT_SET(TIMSK2,TOIE2);  // Enable Overflow Interrupt
  TCNT2 = 0x00;

  BIT_CLR(TIMSK1,TOIE1);  // turn off interrupt for Timer1 (not used interrupt)
                          // don't turn off Timer0 because it is used by delay() and milis()

#elif defined (__AVR_ATmega2560__) || defined (__AVR_ATmega1280__) 
  // Based on http://www.atmel.com/dyn/resources/prod_documents/doc2549.pdf . Not tested
  // Initialize TIMER2
  BIT_CLR(TCCR2B,WGM22);
  BIT_SET(TCCR2A,WGM21);
  BIT_CLR(TCCR2A,WGM20);  // CTC PWM
  
  BIT_CLR(TCCR2B,CS22);
  BIT_SET(TCCR2B,CS21);
  BIT_SET(TCCR2B,CS20);   // Timer Prescaler 32, results in 488 Hz led frequency 
  
  BIT_SET(TIMSK2,TOIE2);  // Enable Overflow Interrupt
  TCNT2 = 0x00;

  BIT_CLR(TIMSK1,TOIE1);  // turn off interrupt for Timer1 (not used interrupt)
  BIT_CLR(TIMSK3,TOIE3);  // turn off interrupt for Timer3 (not used interrupt)
  BIT_CLR(TIMSK4,TOIE4);  // turn off interrupt for Timer4 (not used interrupt)
  BIT_CLR(TIMSK5,TOIE5);  // turn off interrupt for Timer5 (not used interrupt)
                          // don't turn off Timer0 because it is used by delay() and milis()
#else
#error : There is no timer initialization code for your version of ATmega. Only ATmega168, ATmega328p and AVR_ATmega2560 are supported.
#endif
}
//-------------------------------------------------------------------------------------------------------
//--------------- TIMER2 Overflow interrupt---------------
ISR(TIMER2_OVF_vect)
{
  static word pwmCounter = 1024;
  word * ledValPtr = &ledChannels[0][0];

  if( !( pwmCounter & 0xfc00) )  // works faster then (pwmCounter < 1024)
  {
#if !defined (LEDS_UNDEFINED)  // if LEDS are defined for this Arduino board in arduinoPins2Ports.h
    //LED 1
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED1_RED);
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED1_GREEN);
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED1_BLUE);

    //LED 2
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED2_RED);
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED2_GREEN);
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED2_BLUE);  

    //LED 3
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED3_RED);
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED3_GREEN);
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED3_BLUE);

    //LED 4
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED4_RED);
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED4_GREEN);
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED4_BLUE);

#if USE_ANALOG_PINS
    //LED 5
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED5_RED);
    if(*ledValPtr++ < pwmCounter)  LEDOFF(LED5_GREEN);
    if(*ledValPtr   < pwmCounter)  LEDOFF(LED5_BLUE);
#endif
  }
  else
  {
    pwmCounter = 0;

    //LED 1
    if(*ledValPtr++) LEDON(LED1_RED);
    if(*ledValPtr++) LEDON(LED1_GREEN);
    if(*ledValPtr++) LEDON(LED1_BLUE);

    //LED 2
    if(*ledValPtr++) LEDON(LED2_RED);
    if(*ledValPtr++) LEDON(LED2_GREEN);
    if(*ledValPtr++) LEDON(LED2_BLUE);

    //LED 3
    if(*ledValPtr++) LEDON(LED3_RED);
    if(*ledValPtr++) LEDON(LED3_GREEN);
    if(*ledValPtr++) LEDON(LED3_BLUE);

    //LED 4
    if(*ledValPtr++) LEDON(LED4_RED);
    if(*ledValPtr++) LEDON(LED4_GREEN);
    if(*ledValPtr++) LEDON(LED4_BLUE);

#if USE_ANALOG_PINS
    //LED 5
    if(*ledValPtr++) LEDON(LED5_RED);
    if(*ledValPtr++) LEDON(LED5_GREEN);
    if(*ledValPtr)   LEDON(LED5_BLUE);
#endif
#endif
  }
  
  pwmCounter++;
  TCNT2 = 0xff; // necessery for not triggering commperator ISR
}
//-------------------------------------------------------------------------------------------------------
static inline void fadeOutLEDs()
{
   word * const ledChannelsNewPtr = &ledChannelsNew[0][0];
   
   for(byte led = 0; led < NUM_OF_LEDS; led++)
     *(ledChannelsNewPtr + led ) = 0;
 
   ledsOff = true;
}
//-------------------------------------------------------------------------------------------------------
static inline void turnOffLedsIfNeeded()
{
   // Turn off LEDs if no data for defined period of time 
   if( (timeElapsedSinceLastCommand() > (*idleTimeLimit + 1)) && !ledsOff )
     fadeOutLEDs();
}
//-------------------------------------------------------------------------------------------------------
static inline void smooth(const byte smoothAmount) 
{  
   byte epsilon;
   word *ledChannelsPtr  = &ledChannels[0][0];
   word *ledChannelsNewPtr = &ledChannelsNew[0][0];
   byte i = NUM_OF_LEDS - 1;
   word difference;
   
   do
   {
     difference = abs((int)(*ledChannelsNewPtr - *ledChannelsPtr));
     
     if( difference )
     {
       epsilon = ( (*ledChannelsPtr > 128) && (difference > (smoothAmount * 2)) ) ? (byte)(difference / smoothAmount) : 1;
       
       if( (int)(*ledChannelsNewPtr++ - *ledChannelsPtr) < 0  ) 
         *ledChannelsPtr++ -= epsilon;
       else
         *ledChannelsPtr++ += epsilon;
     }
     else
     {   
        ledChannelsNewPtr++;
        ledChannelsPtr++;
     }
   }while(i--);
}
//-------------------------------------------------------------------------------------------------------

