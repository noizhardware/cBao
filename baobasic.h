#ifndef __BAOBASIC_H__
#define __BAOBASIC_H__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <stdbool.h>
// stdbool uses ad-hoc, platform-dependent implementations
// #define bool        _Bool
// #define true        1
// #define false       0

#include <stdint.h> // for platform-adaptive integer bit-sizes

//#define string char* // can cause problems
#define NIL 0

#define rnd_init srand(time(NULL))   // Initialization, should only be called once.
#define rnd(min, max) (min + (rand() % (max - min + 1)))

#define NEWLINE print("\n")

#define LOOP(n, func) for(uint8_t counter = 0; counter < n; counter++) func;
#define FOREVER(func) while(1) {func}
#define defn(name, styp, dtyp, fun) styp name(dtyp in){fun;} // usage: defn(dbl, int, int, return in+in); -> int dbl(int in){return in+in;}

#define print_type_name(expr) \
    printf("%s", (_Generic((expr), \
              char: "char", unsigned char: "unsigned char", signed char: "signed char", \
              short: "short", unsigned short: "unsigned short", \
              int: "int", unsigned int: "unsigned int", \
              long: "long", unsigned long: "unsigned long", \
              long long: "long long", unsigned long long: "unsigned long long", \
              float: "float", \
              double: "double", \
              long double: "long double", \
              void*: "void*", \
              _Bool: "boolean", \
              default: "?")))

#define BIT8 const uint8_t
#define vBIT8 uint8_t
#define BIT16 const uint16_t
#define vBIT16 uint16_t

bool print(const char* toPrint){
  printf("%s", toPrint);
  return true;
}

bool pint (const int num){
  printf("%d", num);
  return true;
}

bool puint (BIT8 num){
  printf("%u", num);
  return true;
}

bool pflo(const float numba){
  printf("%f",numba);
  return true;
}

// int main(void) {
//   print("porcodio");
//   return 0;
// }

#endif // __BAOBASIC_H__