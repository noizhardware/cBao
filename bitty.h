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


#ifndef _BITTY_H_
#define _BITTY_H_
/* 202007241413 */

#include <stdint.h>

static inline uint8_t oneCount (const uint8_t source){ // counts the number of single 1's in the byte
     uint8_t ones = 0;
     for(uint8_t i=0; i<8; i++){
          ones += ((source & (1 << i)) >> i)!=0;}
     return ones;}

// temporaneamente eliminata perchè usa "pint" di baobasic.h
// static inline uint8_t printBits (const uint8_t c){
//   for (int i = 7; i >= 0; i--){
//     pint((c >> i) & 1 ? true : false); // il numero dopo il ">>" è di quanti bit shifta!
//   }
//   NEWLINE;
//   return true;
// }

// temporaneamente eliminata perchè usa "NEWLINE" di baobasic.h
// static inline char* stringBits (const uint8_t c){ // TODO: write correct pointer math
//   char* out;
//   for (int i = 7; i >= 0; i--){
//     out = (c >> i) & 1 ? true : false; // il numero dopo il ">>" è di quanti bit shifta!
//   }
//   NEWLINE;
//   return true;
// }

// temporaneamente eliminata perchè usa "pint" di baobasic.h
// static inline uint8_t printBits32 (int c){
//   for (int i = 31; i >= 0; i--){
//     pint((c >> i) & 1 ? true : false); // il numero dopo il ">>" è di quanti bit shifta!
//   }
//   return true;
// }

static inline uint8_t getBit (const uint8_t source, const uint8_t bitno){ // bitno=[0..7] [LSB..MSB]
  return ((source & (1 << bitno)) >> bitno)!=0;}

static inline uint8_t setBit (const uint8_t source, const uint8_t bitno, const uint8_t bittoset){ // bitno=[0..7] [LSB..MSB]
  return (bittoset) ? (source | (1 << bitno)) : (source & ~(1 << bitno));}

static inline uint8_t flipBit (const uint8_t source, const uint8_t bitno){ // bitno=[0..7] [LSB..MSB]
  return source ^ (1 << bitno);}

static inline uint8_t onehot8Valid (const uint8_t source){
  return ((source==0b00000001)|(source==0b00000010)|(source==0b00000100)|(source==0b00001000)|(source==0b00010000)|(source==0b00100000)|(source==0b01000000)|(source==0b10000000)) ? true : false;}

static inline uint8_t onehot8Set (const uint8_t elem){ // elem [0..7], (returns a 00000000 byte if "elem" is out of range (hint: it won't pass the "onehot8Valid" test))
  return ((elem <= 7) & (elem >= 0)) ? (1 << elem) : 0;}

static inline uint8_t BIT8clip (const intmax_t in){ // clips a value in the range [0..255]
  return (in <= 255) ? (in >= 0) ? in : 0 : 255;}

#endif // _BITTY_H_