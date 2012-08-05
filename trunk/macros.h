// Bit manipulation macros
#define BIT_CLR(reg,bit)                 reg &= ~_BV(bit)
#define BIT_SET(reg,bit)                 reg |= _BV(bit)

#define BITMASK_CLR(reg,bitmask)         reg &= ~bitmask
#define BITMASK_SET(reg,bitmask)         reg |= bitmask
#define BITMASK_TOGGLE(reg,bitmask)      reg ^= bitmask
#define BITMASK_TST(reg,bitmask)         (bool)(reg & bitmask)

#if !defined (LEDS_UNDEFINED)  // if LEDS ports and bit masks are defined for this Arduino board in arduinoPins2Ports.h

#if INVERT_OUTPUT == false

#define LEDON(led)               BITMASK_SET led
#define LEDOFF(led)              BITMASK_CLR led
#define LEDTOGGLE(led)           BITMASK_TOGGLE led
#define IS_LEDON(led)            BITMASK_TST led

#else

#define LEDON(led)               BITMASK_CLR led
#define LEDOFF(led)              BITMASK_SET led
#define LEDTOGGLE(led)           BITMASK_TOGGLE led
#define IS_LEDON(led)            ~(BITMASK_TST led)

#endif

#endif
