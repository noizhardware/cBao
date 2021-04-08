#ifndef _BITTY_H_
#define _BITTY_H_

#define BITTY_VERSION "2021d08-1146"
/*
     ## setBit (source, bitnumber, bitvalue)
       * takes an 8-bit variable, and sets the (bitnumber)th bit (starting from Right = LSB), [0..7] to the bitvalue [true, false]
       * returns the changed 8-bit variable
       - BIT8 newvariable = setBit (8bitvariable, 2, false); // 11111111 -> 11111011

     ## getBit (source, bitnumber)
       * takes an 8-bit variable, and returns the (bitnumber)th bit (starting from Right = LSB), [0..7]
       - returns a uint8_t value [true, false]
       - uint8_t mybit = getBit(8bitvariable, 2); // 11100101 -> true

     ## printBits (source)
       * takes an 8-bit variable, and prints it to console in binary form
       * returns true if successful
       - printBits(12); // -> 00001100
*/

/*
// temporaneamente eliminata perchè usa "NEWLINE" di baobasic.h
// static __inline__ char* stringBits (const uint8_t c){ // TODO: write correct pointer math
//   char* out;
//   for (int i = 7; i >= 0; i--){
//     out = (c >> i) & 1 ? true : false; // il numero dopo il ">>" è di quanti bit shifta!
//   }
//   NEWLINE;
//   return true;
// }

// temporaneamente eliminata perchè usa "pint" di baobasic.h
// static __inline__ uint8_t printBits32 (int c){
//   for (int i = 31; i >= 0; i--){
//     pint((c >> i) & 1 ? true : false); // il numero dopo il ">>" è di quanti bit shifta!
//   }
//   return true;
// }*/


/*** INCLUDES */
     #include <stdint.h>
     #include <stdbool.h>
     
     #include "bitliterals.h"
/* INCLUDES end. */

#ifdef __cplusplus
     extern "C" {
#endif

/*** DEFINES */
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
     static __inline__ uint8_t getHiByte(const uint16_t in);
     static __inline__ uint8_t getLoByte(const uint16_t in);
     static __inline__ uint16_t makeUint16(const uint8_t hi, const uint8_t lo);

     static __inline__ uint8_t oneCount (const uint8_t source);
     static __inline__ uint8_t printBits(const uint8_t c);

     static __inline__ uint8_t getBit (const uint8_t source, const uint8_t bitno); /* bitno=[0..7] [LSB..MSB] */
     static __inline__ uint8_t setBit (const uint8_t source, const uint8_t bitno, const uint8_t bittoset); /* bitno=[0..7] [LSB..MSB] */
     static __inline__ uint8_t flipBit (const uint8_t source, const uint8_t bitno);

     static __inline__ uint8_t onehot8Valid (const uint8_t source);
     static __inline__ uint8_t onehot8Set (const uint8_t elem);

     static __inline__ uint8_t BIT8clip (const intmax_t in);
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
static __inline__ uint8_t getHiByte(const uint16_t in){
     /* I'm just shifting down, discarding the 8 LSBs and the return will cast to uint8_t */
     return (in>>8);
}
static __inline__ uint8_t getLoByte(const uint16_t in){
     /* the mask does select only the 8 LSBs */
  return in & 0xff;
}
static __inline__ uint16_t makeUint16(const uint8_t hi, const uint8_t lo){
  return lo | (hi<<8);
}

static __inline__ uint8_t oneCount (const uint8_t source){ /* counts the number of single 1's in the byte */
     uint8_t ones = 0;
     uint8_t i;
     for(i=0; i<8; i++){
          ones += ((source & (1 << i)) >> i)!=0;
     }
     return ones;
}

static __inline__ uint8_t printBits(const uint8_t c){
     int i;
     for (i = 7; i >= 0; i--){
          printf("%d", (c >> i) & 1 ? true : false);
     }
     printf("\n");
     return true;
}

static __inline__ uint8_t getBit (const uint8_t source, const uint8_t bitno){ /* bitno=[0..7] [LSB..MSB] */
     return ((source & (1 << bitno)) >> bitno)!=0;
}
static __inline__ uint8_t setBit (const uint8_t source, const uint8_t bitno, const uint8_t bittoset){ /* bitno=[0..7] [LSB..MSB] */
     return (bittoset) ? (source | (1 << bitno)) : (source & ~(1 << bitno));
}
static __inline__ uint8_t flipBit (const uint8_t source, const uint8_t bitno){ /* bitno=[0..7] [LSB..MSB] */
     return source ^ (1 << bitno);
}

static __inline__ uint8_t onehot8Valid (const uint8_t source){
     return (
          (source==B00000001)|
          (source==B00000010)|
          (source==B00000100)|
          (source==B00001000)|
          (source==B00010000)|
          (source==B00100000)|
          (source==B01000000)|
          (source==B10000000))
          ? true : false;
}

static __inline__ uint8_t onehot8Set (const uint8_t elem){ /* elem [0..7], (returns a 00000000 byte if "elem" is out of range (hint: it won't pass the "onehot8Valid" test)) */
     return ((elem <= 7)) ? (1 << elem) : 0; /* not checking for (elem >= 0), it's always true */
}

static __inline__ uint8_t BIT8clip (const intmax_t in){ /* clips a value in the range [0..255] */
     return (in <= 255) ? (in >= 0) ? in : 0 : 255;
}
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
     }
#endif
#endif /* _BITTY_H_ */