#if (COMMUNICATION_PROTOCOL == ATMOLIGHT_PROTOCOL)

#define SERIAL_BAUD_RATE 38400
// Order is reversed, first byte is last module in the chain
// 0=sum (center), 1=left, 2=right, 3=top, 4=bottom           
static const byte channelOrder[NUM_OF_RGB_LEDS] = {1, 2, 3, 4, 0};

#elif (COMMUNICATION_PROTOCOL == AMBLONE_PROTOCOL) 

#define SERIAL_BAUD_RATE 256000
// 0=Chanel 1, 1=Chanel 2, 2=Chanel 3, 3=Chanel 4, 4=RGB LED will be off
static const byte channelOrder[NUM_OF_RGB_LEDS] = {0, 1, 2, 3, 4};

#endif

static byte incomingData[16]; // buffer array for incomming data over serial
static unsigned long timeOfLastTransmition = millis();

