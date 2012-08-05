//-------------------------------------------------------------------------------------------------------
static inline void initSerialCommunication()
{
  Serial.begin(SERIAL_BAUD_RATE);  // Setting serial speed correct for used protocol
  
  // Calculate channels values positions in received packets
  for(byte i = 0; i < NUM_OF_LEDS; i++)
	  channelOrder[i] *= 3;
}

static inline boolean sendInfo()
{
  Serial.write((byte)0xFF);
  Serial.write((byte)0x00);
  Serial.write((byte)0xAA);
  Serial.write((byte)UNOLIGHT_VERSION);
  
  for(byte i = 0; i < NUMBER_OF_SETTINGS; i++)
    Serial.write((byte)*(settings + i)); 

  return true;
}
//-------------------------------------------------------------------------------------------------------
static inline boolean getCommand()
{
  byte valueToReturn = false;

#if (COMMUNICATION_PROTOCOL == ATMOLIGHT_PROTOCOL)
  if( Serial.available() >= 4 &&  // 4 bytes of header
	  Serial.read() == 0xFF &&
	  Serial.read() == 0x00 )
  {
    switch ( Serial.read() )
    {
      case 0x00:                                     // Atmolight Packet (max 5-ch)
        valueToReturn = getAtmolightCommand();
        break;
      case 0xcc:                                     // UnoLight Settings Update Packet
        valueToReturn = getUpdateSettingsCommand();
        break;
      case 0xaa:                                     // UnoLightConfig version request packet
        valueToReturn = sendInfo();
        break;
    }
  }

#elif (COMMUNICATION_PROTOCOL == AMBLONE_PROTOCOL)  
  if (Serial.available() != 0)
  {
	  if (!(IS_WAITING_FOR_SF && Serial.peek() == 0xFF))
	  {
		  valueToReturn = getAmbloneCommand();
	  } 
	  else // custom packet (Not part of Amblone protocol)
	  {
		  if( Serial.available() >= 19 &&
			  Serial.read() == 0xFF &&
			  Serial.read() == 0x00 )
		  {
			  switch ( Serial.read() )
			  {
				  case 0xCC:                                     // UnoLight Settings Update Packet
					  valueToReturn = getUpdateSettingsCommand();
					  break;
				  case 0xAA:                                     // UnoLightConfig version request packet
					  valueToReturn = sendInfo();
					  break;
			  }
		  }
	  }
  }
#endif

  if( valueToReturn )          // if correct command received
    timeOfLastTransmition = millis();
  
  return valueToReturn;
}
//-------------------------------------------------------------------------------------------------------
static inline word timeElapsedSinceLastCmd() __attribute__((always_inline));
static inline word timeElapsedSinceLastCmd()
{
  return (word)((millis() - timeOfLastTransmition) / 1000);
}
//-------------------------------------------------------------------------------------------------------
