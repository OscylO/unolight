// More on http://amblone.com

#if (COMMUNICATION_PROTOCOL == AMBLONE_PROTOCOL) 
// Flags for the serial communication protocol
#define C_SF1 0xF1 // Start flag for 1-channel mode (1 RGB channel)
#define C_SF2 0xF2 // Start flag for 2-channel mode (2 RGB channels)
#define C_SF3 0xF3 // Start flag for 3-channel mode (3 RGB channels)
#define C_SF4 0xF4 // Start flag for 4-channel mode (4 RGB channels)
#define C_END 0x33 // End flag
#define C_ESC 0x99 // Escape character

// states for receiving the information, see the flow chart for more info
#define S_WAIT_FOR_SF  0
#define S_RECV_RGB     1
#define S_RECV_RGB_ESC 2

#define IS_WAITING_FOR_SF ((state == S_WAIT_FOR_SF) ? true : false)

// state we are in: one of the S_* defines
static byte state =  S_WAIT_FOR_SF;
// The payload of a received message
static byte payload[32];
// The amount of RGB values we have received
static byte byteCount = 0;
// The character we received
static byte recv;
// The amount of RGB channels we are using
static byte channelMode;
//-------------------------------------------------------------------------------------------------------
static boolean inline getAmbloneCommand() 
{
  recv = Serial.read();
  
  switch (state) 
  {
    case S_WAIT_FOR_SF:
      // =============================== Wait for start flag state
      switch (recv) 
      {
        case C_SF1:
          // Start flag for 1-channel mode
          channelMode = 1;
          state = S_RECV_RGB;
          byteCount = 0;
          return false;
        case C_SF2:
          // Start flag for 2-channel mode
          channelMode = 2;
          state = S_RECV_RGB;
          byteCount = 0;
          return false;
        case C_SF3:
          // Start flag for 3-channel mode
          channelMode = 3;
          state = S_RECV_RGB;
          byteCount = 0;
          return false;
        case C_SF4:
          // Start flag for 4-channel mode
          channelMode = 4;
          state = S_RECV_RGB;
          byteCount = 0;
          return false;
        default:
          // No action for all other characters
          return false;
      }
      break;
    case S_RECV_RGB:
      // =============================== RGB Data reception state
      switch (recv) 
      {
        case C_SF1:
          // Start flag for 1-channel mode
          channelMode = 1;
          state = S_RECV_RGB;
          byteCount = 0;
          return false;
        case C_SF2:
          // Start flag for 2-channel mode
          channelMode = 2;
          state = S_RECV_RGB;
          byteCount = 0;
          return false;
        case C_SF3:
          // Start flag for 3-channel mode
          channelMode = 3;
          state = S_RECV_RGB;
          byteCount = 0;
          return false;
        case C_SF4:
          // Start flag for 4-channel mode
          channelMode = 4;
          state = S_RECV_RGB;
          byteCount = 0;
          return false;
        case C_END:
          // End Flag
          // For each channel, we should have received 3 values. If so, we have received a valid packet
          if (byteCount == channelMode * 3) 
          {
            loadNewLedValues(byteCount);
            state = S_WAIT_FOR_SF;
            byteCount = 0;
            return true; // <------------------------ TRUE IS RETURNED
          }
          else 
          {
            // Some thing's gone wrong: restart
            state = S_WAIT_FOR_SF;
            byteCount = 0;
            return false;
          }
        case C_ESC:
          // Escape character
          state = S_RECV_RGB_ESC;
          return false;
        default:
          // The character received wasn't a flag, so store it as an RGB value        
          *(payload + byteCount++) = recv;
          return false;
      }
      case S_RECV_RGB_ESC:
        // =============================== RGB Escaped data reception state
        // Store the value in the payload, no matter what it is
        *(payload + byteCount++) = recv;
        state = S_RECV_RGB;
        return false;
  }
  
  return false;
}
//-------------------------------------------------------------------------------------------------------
static inline void loadNewLedValues(byte numOfValues) 
{
  byte i = 0; 
  while( i < NUM_OF_LEDS )
  {
    *(incomingData + i++) = (i < numOfValues) ? *(payload + i) : 0;
	*(incomingData + i++) = (i < numOfValues) ? *(payload + i) : 0;
	*(incomingData + i++) = (i < numOfValues) ? *(payload + i) : 0;
  }
    
  byte *ledChannelAndColorPtr = (*isSmoothEnabled) ? ledChannelsNewPtr : ledChannelsPtr;
  byte channel = 0;

  noInterrupts();
  if( *useGammaTable )
  {
    while( channel < NUM_OF_RGB_LEDS )
    {  
      byte *incomingValuePtr = incomingData + *(channelOrder + channel++) * 3; 

      *ledChannelAndColorPtr++ = *(gammaTable + *incomingValuePtr++); // red
      *ledChannelAndColorPtr++ = *(gammaTable + *incomingValuePtr++); // green
      *ledChannelAndColorPtr++ = *(gammaTable + *incomingValuePtr);   // blue              
    }
  }
  else
  {
    while( channel < NUM_OF_RGB_LEDS )
    {  
      byte *incomingValuePtr = incomingData + *(channelOrder + channel++) * 3; 

      *ledChannelAndColorPtr++ = *incomingValuePtr++ << 2; // red
      *ledChannelAndColorPtr++ = *incomingValuePtr++ << 2; // green
      *ledChannelAndColorPtr++ = *incomingValuePtr << 2;   // blue              
    }
  }
  interrupts();
}
//-------------------------------------------------------------------------------------------------------
static inline void resetAmblone()
{
  state =  S_WAIT_FOR_SF;
  byteCount = 0;
}
//-------------------------------------------------------------------------------------------------------
#endif
