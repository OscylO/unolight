// More on : http://www.vdr-wiki.de/wiki/index.php/Atmo-plugin

#if (COMMUNICATION_PROTOCOL == ATMOLIGHT_PROTOCOL)
//-------------------------------------------------------------------------------------------------------
// Gets LED values sent over serial (Atmolight protocol)
static inline boolean getAtmolightCommand()
{
  register byte i = 0;
  byte *ledChannelAndColorPtr = (*isSmoothEnabled) ? ledChannelsNew : ledChannels;
  byte *incomingValuePtr = incomingData;
  const byte *channelOrderPtr = channelOrder;
  const byte numOfValuesInPacket = Serial.read(); // informs of number of bytes left in this packet to be transmitted
  const byte numOfUsableValues =  (numOfValuesInPacket >= NUM_OF_LEDS) ? NUM_OF_LEDS : numOfValuesInPacket;
  byte  numOfUnusableValues = numOfValuesInPacket - numOfUsableValues; 

  const unsigned long startTime = millis();
  while ( Serial.available() <= numOfValuesInPacket ) // waiting for all bytes in packet + 
  {													  // starting flag of next packet to be received 
	  if ((millis() - startTime) > 500)
		  return false;
  } 

  // Loop is faster replacement for Serial.readBytes((char*)incomingData, NUM_OF_LEDS);
  while( i < numOfUsableValues )
  {
	  *incomingValuePtr++ = Serial.read();
	  *incomingValuePtr++ = Serial.read();
	  *incomingValuePtr++ = Serial.read();
	  i += 3;
  }

  while( numOfUnusableValues-- )
	  Serial.read();
  
  if( Serial.peek() != 0xFF ) // if not reached starting flag of next packet
	  return false;

  while ( i++ < NUM_OF_LEDS)
	  *incomingValuePtr++ = 0;

  i = 0;

  if( *useGammaTable )
  {
    while( i++ < NUM_OF_RGB_LEDS )
    {  
      incomingValuePtr = incomingData + *channelOrderPtr++; 

      *ledChannelAndColorPtr++ = *(gammaTable + *incomingValuePtr++); // red
      *ledChannelAndColorPtr++ = *(gammaTable + *incomingValuePtr++); // green
      *ledChannelAndColorPtr++ = *(gammaTable + *incomingValuePtr);   // blue              
    }
  }
  else
  {
    while( i++ < NUM_OF_RGB_LEDS )
    {  
      incomingValuePtr = incomingData + *channelOrderPtr++; 

      *ledChannelAndColorPtr++ = *incomingValuePtr++; // red
      *ledChannelAndColorPtr++ = *incomingValuePtr++; // green
      *ledChannelAndColorPtr++ = *incomingValuePtr;   // blue              
    }
  }

  return true;
}
//-------------------------------------------------------------------------------------------------------
#endif
