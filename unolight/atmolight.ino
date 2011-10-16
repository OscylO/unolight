// More on : http://www.vdr-wiki.de/wiki/index.php/Atmo-plugin 

#if (COMMUNICATION_PROTOCOL == ATMOLIGHT_PROTOCOL)
//-------------------------------------------------------------------------------------------------------
// Gets LED values sent over serial (Atmolight protocol)
inline boolean getAtmolightCommand()
{
  Serial.read(); // not using this byte (informs of number of bytes left in this packet to be transmited == 15)

  byte i = 0; 
  while( i < NUM_OF_LEDS )
    *(incomingData + i++) = Serial.read();
    
  word *ledChannelAndColorPointer = (*isSmoothEnabled) ? &ledChannelsNew[0][0] : &ledChannels[0][0];
  byte channel = 0;
  
  cli();
  if( *useGammaTable )
  {
    while( channel < NUM_OF_RGB_LEDS )
    {  
      byte *incomingValuePointer = incomingData + *(channelOrder + channel++) * 3; 

      *ledChannelAndColorPointer++ = *(gammaTable + *incomingValuePointer++); // red
      *ledChannelAndColorPointer++ = *(gammaTable + *incomingValuePointer++); // green
      *ledChannelAndColorPointer++ = *(gammaTable + *incomingValuePointer);   // blue              
    }
  }
  else
  {
    while( channel < NUM_OF_RGB_LEDS )
    {  
      byte *incomingValuePointer = incomingData + *(channelOrder + channel++) * 3; 

      *ledChannelAndColorPointer++ = *incomingValuePointer++ * 4; // red
      *ledChannelAndColorPointer++ = *incomingValuePointer++ * 4; // green
      *ledChannelAndColorPointer++ = *incomingValuePointer * 4;   // blue              
    }
  }
  sei();
  return true;
}
//-------------------------------------------------------------------------------------------------------
#endif
