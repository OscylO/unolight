#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT)
#define TOGGLEBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT)
#define LEDON(ADDRESS,LED) (ADDRESS |= LED)
#define LEDOFF(ADDRESS,LED) (ADDRESS &= ~LED)

