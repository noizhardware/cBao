#ifndef _BAOCPU_H_
#define _BAOCPU_H_

/* detects the current CPU and defines easy names */

#if defined(__AVR_ATmega32U4__)
     #define ARDUMICRO
#elif defined (__AVR_ATtiny85__)
     #define ATTINY85
#else
     #define BHO
#endif

#endif /* _BAOCPU_H_ */