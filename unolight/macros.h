// Bit manipulation macros
#define BIT_CLR(reg,bit)                 reg &= (byte)~_BV(bit)
#define BIT_SET(reg,bit)                 reg |= (byte)_BV(bit)

#define BITMASK_CLR(reg,bitmask)         reg &= (byte)~bitmask
#define BITMASK_SET(reg,bitmask)         reg |= (byte)bitmask
#define BITMASK_TOGGLE(reg,bitmask)      reg ^= (byte)bitmask
#define BITMASK_TST(reg,bitmask)         (byte)(reg & bitmask)

#if !defined (LEDS_UNDEFINED)  // if LEDS ports and bitmasks are defined for this Arduino board in arduinoPins2Ports.h
#define LEDON(led)               BITMASK_SET led
#define LEDOFF(led)              BITMASK_CLR led
#define LEDTOGGLE(led)           BITMASK_TOGGLE led
#define IS_LEDON(led)            BITMASK_TST led
#endif

