//-------------------------------------------------------------------------------------------------------
static inline void initSerialCommunication()
{
  Serial.begin(SERIAL_BAUD_RATE);  // Setting serial speed correct for used protocol
}

static inline boolean sendInfo()
{
  Serial.write((byte)0xff);
  Serial.write((byte)0x00);
  Serial.write((byte)0xaa);
  Serial.write((byte)UNOLIGHT_VERSION);
  
  for(byte i = 0; i<NUMBER_OF_SETTINGS; i++)
    Serial.write((byte)*(settings + i)); 

  return true;
}
//-------------------------------------------------------------------------------------------------------
inline boolean getCommand()
{
  byte valueToReturn;

#if (COMMUNICATION_PROTOCOL == ATMOLIGHT_PROTOCOL)
  if( Serial.available() >= 19 && Serial.read() == 0xff && Serial.read() == 0x00 )
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
      default:
          valueToReturn = false;
    }
  }
  else
  {
    valueToReturn = false;
  }
#elif (COMMUNICATION_PROTOCOL == AMBLONE_PROTOCOL)  
  // AMBLONE Packet (max 4-ch)
  if( (Serial.available() > 0)  && isWaitingForFirstCommandByte() && (Serial.peek() == 0xff) )
  {
    if( Serial.available() >= 19 && Serial.read() == 0xff && Serial.read() == 0x00 )
    {
      switch ( Serial.read() )
      {
        case 0xcc:                                     // UnoLight Settings Update Packet
          valueToReturn = getUpdateSettingsCommand();
          break;
        case 0xaa:                                     // UnoLightConfig version request packet
          valueToReturn = sendInfo();
          break;
        default:
          valueToReturn = false;
      }
    }
    else
      valueToReturn = false;
  }
  else
  {
     valueToReturn = ( Serial.available() > 0 ) ? getAmbloneCommand() : false;
  }
#else
#error : You need to define COMMUNICATION_PROTOCOL as equal to AMBLONE_PROTOCOL or ATMOLIGHT_PROTOCOL
#endif

  if( valueToReturn == true )          // if correct command recived
    timeOfLastTransmition = millis();
  
  return valueToReturn;
}
//-------------------------------------------------------------------------------------------------------
static inline word timeElapsedSinceLastCommand()
{
  return ((millis() - timeOfLastTransmition) / 1000);
}
//-------------------------------------------------------------------------------------------------------
