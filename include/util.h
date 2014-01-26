#ifndef UTIL_H
#define UTIL_H

#define MIN(X,Y) ((X) > (Y) ? (Y) : (X))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define ABS(X) ((X) < 0 ? (-(X)) : (X))
#define TRUNCMOD(X,Y) ((((X) % (Y)) == 0) ? (X) : (X) - ((X) % (Y)))

extern bool IsDigits(char* str);

#endif /*UTIL_H*/
