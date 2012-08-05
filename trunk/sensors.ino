/*
 * This code is not ready to be used, yet.
*/

#define LIGHT_SENSOR_PIN A6
//-------------------------------------------------------------------------------------------------------
static inline void initSensors()
{
  if( *useLightSensor )
  {
    pinMode(LIGHT_SENSOR_PIN, INPUT);  
    //analogReference(INTERNAL);

	// setup ADC
	ADMUX  = B11100110;  // default to AVCC INTERNAL, ADC Left Adjust, and ADC channel 6
	ADCSRB = B00000000; // Analog Input bank 1
	ADCSRA = B11001111; // ADC enable, ADC start, manual trigger mode, ADC interrupt enable, prescaler = 128
  }
}
//-------------------------------------------------------------------------------------------------------
static byte getSensorValue( byte pin )
{
     

  //return (byte)map(level, 0, 1023, 0, 255); 
  //return (levelSum - ( 32 * 4 )) / 4 / 32; // returns average value of light level (0 - 255)
}
//-------------------------------------------------------------------------------------------------------
volatile static int lightLevel = 0;
static boolean turnOffIfAmbientLightToBright()
{
  static unsigned long lastMesurementTime = 0;
  byte trashold = *lightSensorThreshold;

  if( *useLightSensor )
  {
	  if(millis() - lastMesurementTime > 300)
	  {
		lastMesurementTime = millis();

		if(!ledsOff)
			if ((*lightSensorThreshold) < 30)
				trashold = 30;
			//else
				//trashold += 30;
	   
		if( lightLevel > trashold)
		{
			if(!ledsOff) 
				turnOffLEDs();

			ledsOff = true;
			//Serial.print("LEDs: OFF ");
		} 
		else 
		{
			ledsOff = false;
			//Serial.print("LEDs: ON ");
		}

		//Serial.println(lightLevel);
	  }
  }
  else
	  ledsOff = false;

  return ledsOff;
}
//-------------------------------------------------------------------------------------------------------
static inline void updateSensorsValues()
{
  if( *useLightSensor )
    turnOffIfAmbientLightToBright();
}
//-------------------------------------------------------------------------------------------------------
ISR(ADC_vect) 
{ // Analog->Digital Conversion Complete
	char ADCch = ADMUX & B00000111;  // extract the channel of the ADC result
	if (ADCch == 6) 
	{
		int level = (int) ADCH;  // store ADC result (8-bit precision)
		// calc running average
		int temp = lightLevel * 99;
		temp += level;
		lightLevel = temp / 100;  
		ADCSRA |= B11000000;  // manually trigger the next ADC
	}
};