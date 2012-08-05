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

  initTimer2();             // Initialize Timer2 and disable others except Timer0
}
//-------------------------------------------------------------------------------------------------------
static inline void initTimer2()
{
	// Initialize TIMER2
#if (defined __AVR_ATmega168__ || defined __AVR_ATmega328P__) 

//  BIT_CLR(TCCR2B,WGM22);
//  BIT_SET(TCCR2A,WGM21);
//  BIT_SET(TCCR2A,WGM20);  // if BIT_SET == FAST PWM, if BIT_CLR == CTC PWM

  /*
   * CS22 = 0 and CS21 == 1 and CS20 == 1 : Timer Prescaler 32 
   * CS22 = 1 and CS21 == 0 and CS20 == 0 : Timer Prescaler 64
   */
 //// BIT_SET(TCCR2B,CS22);
//  BIT_CLR(TCCR2B,CS21);
 // BIT_CLR(TCCR2B,CS20);

//  BIT_SET(TIMSK2,TOIE2);  // Enable Overflow Interrupt
 // TCNT2 = 0xff;
  
  // Timer 1 setup
  TCCR1A = 0x00;    // timer control registers set for
  TCCR1B = 0x00;    // normal operation, timer disabled
  BIT_SET(TCCR1B,WGM12);
  // Setting prescaler
  BIT_CLR(TCCR1B,CS12);
  BIT_SET(TCCR1B,CS11);
  BIT_SET(TCCR1B,CS10);  
  // Setting comparator value
  OCR1A = 9;			 // Controls led refresh rate (smaller number means faster refresh rate),
						 // 9 corresponds to 100Hz for 8bit led brightness values
  BIT_SET(TIMSK1,OCIE1A);

 // BIT_SET(TIMSK1,TOIE1);  // Enable Overflow Interrupt
 // TCNT1 = 0xff;

#elif defined (__AVR_ATmega2560__) || defined (__AVR_ATmega1280__) 

  // Based on http://www.atmel.com/dyn/resources/prod_documents/doc2549.pdf . Not tested
  BIT_CLR(TCCR2B,WGM22);
  BIT_SET(TCCR2A,WGM21);
  BIT_SET(TCCR2A,WGM20);  // if BIT_SET == FAST PWM, if BIT_CLR == CTC PWM
  
  /*
   * CS22 = 0 and CS21 == 1 and CS20 == 1 : Timer Prescaler 32, results in 488 Hz led frequency 
   * CS22 = 1 and CS21 == 0 and CS20 == 0 : Timer Prescaler 64, results in 244 Hz led frequency 
   */
  BIT_SET(TCCR2B,CS22);
  BIT_CLR(TCCR2B,CS21);
  BIT_CLR(TCCR2B,CS20);   // Timer Prescaler 64, results in 244 Hz led frequency 
  
  BIT_SET(TIMSK2,TOIE2);  // Enable Overflow Interrupt
  TCNT2 = 0x00;

  // Timer 1 setup
  TCCR1A = 0x00;    //timer control registers set for
  TCCR1B = 0x00;    //normal operation, timer disabled
  TCCR1B  = (1<<WGM12);
  BIT_CLR(TCCR1B,CS12);
  BIT_SET(TCCR1B,CS11);
  BIT_SET(TCCR1B,CS10); //prescaler 64
  OCR1A = 9;
  BIT_SET(TIMSK1,OCIE1A);
#else
#error : "There is no timer initialization code for your version of ATmega. Only ATmega168, ATmega328p, ATmega1280 and ATmega2560 are supported."
#endif
}

//-------------------------------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)
{
	static byte pwmCounter = 0x00;
	volatile byte * ledValPtr = ledChannelsPtr;
	
	if( ++pwmCounter )
	{
#if !defined (LEDS_UNDEFINED)  // if LEDs are defined for this Arduino board in arduinoPins2Ports.h
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
#endif
	}
	else
	{
#if !defined (LEDS_UNDEFINED)  // if LEDs are defined for this Arduino board in arduinoPins2Ports.h
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

#if (TEST_PERFORMANCE == true)	
		framesCounter++;
#endif
	}	
}
//-------------------------------------------------------------------------------------------------------
static inline void turnOffLEDs()
{  
   for(byte led = 0; led < NUM_OF_LEDS; led++)
     *(ledChannelsNewPtr + led++) = 0;
 
   ledsOff = true;
}
//--------------------------------------------------------------------------------------------------------
/*static inline void smooth(const byte smoothAmount) 
{ 
   word *ledChannelPtr = ledChannelsPtr;
   word *ledChannelNewPtr = ledChannelsNewPtr;
   byte i = NUM_OF_LEDS;
   int difference;

   do
   {
     difference = (int)(*ledChannelNewPtr - *ledChannelPtr);
  
     if( difference )
     {
       if(*ledChannelPtr > 128)
         *ledChannelPtr += difference / smoothAmount;
       else
         *ledChannelPtr += (difference < 0) ? -1 : 1;
     }
  
     ++ledChannelNewPtr;
     ++ledChannelPtr;
   }while( --i );
}*/
//------------------------------------------------------------------------------------------------------
static inline void smooth()
{
	
	byte *ledChannelPtr = ledChannelsPtr;
    byte *ledChannelNewPtr = ledChannelsNewPtr;

	//*ledChannelPtr = (byte)(((((unsigned long)(*ledChannelPtr++)) << 7) + (((unsigned long)(*ledChannelNewPtr++)) << 7)) >> 8);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);

	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);

	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);

	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);

#if USE_ANALOG_PINS == true
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
	*ledChannelPtr = (byte)(((*ledChannelNewPtr++) + (*ledChannelPtr++ * 9)) / 10);
#endif
}
//-------------------------------------------------------------------------------------------------------
static inline void showTestingPattern()
{
	byte *ledChannelPtr;
	const byte maxLedVal = gammaTable[255];

	for(byte colorNum = 0; colorNum < 3; colorNum++)
	{
		// Setting color to 255
		ledChannelPtr = ledChannelsPtr + colorNum;
		for (byte rgbLedNum = 0; rgbLedNum < NUM_OF_RGB_LEDS; rgbLedNum++)
		{
			*ledChannelPtr = maxLedVal;
			ledChannelPtr += 3; // 3 == number of colors
		}

		delay(200);

		// Reseting to 0
		ledChannelPtr = ledChannelsPtr + colorNum;
		for (byte rgbLedNum = 0; rgbLedNum < NUM_OF_RGB_LEDS; rgbLedNum++)
		{
			*ledChannelPtr = 0;
			ledChannelPtr += 3; // 3 == number of colors
		}
	}
}
//-------------------------------------------------------------------------------------------------------
