#ifndef UTIL_H
#define UTIL_H

#include "itype.h"

#define MIN(X,Y) ((X) > (Y) ? (Y) : (X))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define ABS(X) ((X) < 0 ? (-(X)) : (X))
#define TRUNCMOD(X,Y) ((((X) % (Y)) == 0) ? (X) : (X) - ((X) % (Y)))
#define RANDONEIN(X) (!(rand() % (X)))
#define RANDBOOL (rand() & 1)

extern bool IsDigits(char* str);

extern u32 BinomialDistribution(u32 min, u32 max);

#endif /*UTIL_H*/
