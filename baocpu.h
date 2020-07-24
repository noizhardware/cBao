#ifndef __BAOCPU_H__
#define __BAOCPU_H__

#if defined(__AVR_ATmega32U4__)
     #define ARDUMICRO
#elif defined (__AVR_ATtiny85__)
     #define ATTINY85
#else
     #define BHO
#endif

#endif // __BAOCPU_H__