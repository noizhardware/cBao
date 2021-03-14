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
/* 2021c14-2328 */

#include <stdint.h>

#define B00000000 0
#define B00000001 1
#define B00000010 2
#define B00000011 3
#define B00000100 4
#define B00000101 5
#define B00000110 6
#define B00000111 7
#define B00001000 8
#define B00001001 9
#define B00001010 10
#define B00001011 11
#define B00001100 12
#define B00001101 13
#define B00001110 14
#define B00001111 15
#define B00010000 16
#define B00010001 17
#define B00010010 18
#define B00010011 19
#define B00010100 20
#define B00010101 21
#define B00010110 22
#define B00010111 23
#define B00011000 24
#define B00011001 25
#define B00011010 26
#define B00011011 27
#define B00011100 28
#define B00011101 29
#define B00011110 30
#define B00011111 31
#define B00100000 32
#define B00100001 33
#define B00100010 34
#define B00100011 35
#define B00100100 36
#define B00100101 37
#define B00100110 38
#define B00100111 39
#define B00101000 40
#define B00101001 41
#define B00101010 42
#define B00101011 43
#define B00101100 44
#define B00101101 45
#define B00101110 46
#define B00101111 47
#define B00110000 48
#define B00110001 49
#define B00110010 50
#define B00110011 51
#define B00110100 52
#define B00110101 53
#define B00110110 54
#define B00110111 55
#define B00111000 56
#define B00111001 57
#define B00111010 58
#define B00111011 59
#define B00111100 60
#define B00111101 61
#define B00111110 62
#define B00111111 63
#define B01000000 64
#define B01000001 65
#define B01000010 66
#define B01000011 67
#define B01000100 68
#define B01000101 69
#define B01000110 70
#define B01000111 71
#define B01001000 72
#define B01001001 73
#define B01001010 74
#define B01001011 75
#define B01001100 76
#define B01001101 77
#define B01001110 78
#define B01001111 79
#define B01010000 80
#define B01010001 81
#define B01010010 82
#define B01010011 83
#define B01010100 84
#define B01010101 85
#define B01010110 86
#define B01010111 87
#define B01011000 88
#define B01011001 89
#define B01011010 90
#define B01011011 91
#define B01011100 92
#define B01011101 93
#define B01011110 94
#define B01011111 95
#define B01100000 96
#define B01100001 97
#define B01100010 98
#define B01100011 99
#define B01100100 100
#define B01100101 101
#define B01100110 102
#define B01100111 103
#define B01101000 104
#define B01101001 105
#define B01101010 106
#define B01101011 107
#define B01101100 108
#define B01101101 109
#define B01101110 110
#define B01101111 111
#define B01110000 112
#define B01110001 113
#define B01110010 114
#define B01110011 115
#define B01110100 116
#define B01110101 117
#define B01110110 118
#define B01110111 119
#define B01111000 120
#define B01111001 121
#define B01111010 122
#define B01111011 123
#define B01111100 124
#define B01111101 125
#define B01111110 126
#define B01111111 127
#define B10000000 128
#define B10000001 129
#define B10000010 130
#define B10000011 131
#define B10000100 132
#define B10000101 133
#define B10000110 134
#define B10000111 135
#define B10001000 136
#define B10001001 137
#define B10001010 138
#define B10001011 139
#define B10001100 140
#define B10001101 141
#define B10001110 142
#define B10001111 143
#define B10010000 144
#define B10010001 145
#define B10010010 146
#define B10010011 147
#define B10010100 148
#define B10010101 149
#define B10010110 150
#define B10010111 151
#define B10011000 152
#define B10011001 153
#define B10011010 154
#define B10011011 155
#define B10011100 156
#define B10011101 157
#define B10011110 158
#define B10011111 159
#define B10100000 160
#define B10100001 161
#define B10100010 162
#define B10100011 163
#define B10100100 164
#define B10100101 165
#define B10100110 166
#define B10100111 167
#define B10101000 168
#define B10101001 169
#define B10101010 170
#define B10101011 171
#define B10101100 172
#define B10101101 173
#define B10101110 174
#define B10101111 175
#define B10110000 176
#define B10110001 177
#define B10110010 178
#define B10110011 179
#define B10110100 180
#define B10110101 181
#define B10110110 182
#define B10110111 183
#define B10111000 184
#define B10111001 185
#define B10111010 186
#define B10111011 187
#define B10111100 188
#define B10111101 189
#define B10111110 190
#define B10111111 191
#define B11000000 192
#define B11000001 193
#define B11000010 194
#define B11000011 195
#define B11000100 196
#define B11000101 197
#define B11000110 198
#define B11000111 199
#define B11001000 200
#define B11001001 201
#define B11001010 202
#define B11001011 203
#define B11001100 204
#define B11001101 205
#define B11001110 206
#define B11001111 207
#define B11010000 208
#define B11010001 209
#define B11010010 210
#define B11010011 211
#define B11010100 212
#define B11010101 213
#define B11010110 214
#define B11010111 215
#define B11011000 216
#define B11011001 217
#define B11011010 218
#define B11011011 219
#define B11011100 220
#define B11011101 221
#define B11011110 222
#define B11011111 223
#define B11100000 224
#define B11100001 225
#define B11100010 226
#define B11100011 227
#define B11100100 228
#define B11100101 229
#define B11100110 230
#define B11100111 231
#define B11101000 232
#define B11101001 233
#define B11101010 234
#define B11101011 235
#define B11101100 236
#define B11101101 237
#define B11101110 238
#define B11101111 239
#define B11110000 240
#define B11110001 241
#define B11110010 242
#define B11110011 243
#define B11110100 244
#define B11110101 245
#define B11110110 246
#define B11110111 247
#define B11111000 248
#define B11111001 249
#define B11111010 250
#define B11111011 251
#define B11111100 252
#define B11111101 253
#define B11111110 254
#define B11111111 255

static __inline__ uint8_t oneCount (const uint8_t source){ /* counts the number of single 1's in the byte */
     uint8_t ones = 0;
     uint8_t i;
     for(i=0; i<8; i++){
          ones += ((source & (1 << i)) >> i)!=0;}
     return ones;}

/*// temporaneamente eliminata perchè usa "pint" di baobasic.h
// static __inline__ uint8_t printBits (const uint8_t c){
//   for (int i = 7; i >= 0; i--){
//     pint((c >> i) & 1 ? true : false); // il numero dopo il ">>" è di quanti bit shifta!
//   }
//   NEWLINE;
//   return true;
// }

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

static __inline__ uint8_t getBit (const uint8_t source, const uint8_t bitno){ /* bitno=[0..7] [LSB..MSB] */
  return ((source & (1 << bitno)) >> bitno)!=0;}

static __inline__ uint8_t setBit (const uint8_t source, const uint8_t bitno, const uint8_t bittoset){ /* bitno=[0..7] [LSB..MSB] */
  return (bittoset) ? (source | (1 << bitno)) : (source & ~(1 << bitno));}

static __inline__ uint8_t flipBit (const uint8_t source, const uint8_t bitno){ /* bitno=[0..7] [LSB..MSB] */
  return source ^ (1 << bitno);}

static __inline__ uint8_t onehot8Valid (const uint8_t source){
  return ((source==B00000001)|(source==B00000010)|(source==B00000100)|(source==B00001000)|(source==B00010000)|(source==B00100000)|(source==B01000000)|(source==B10000000)) ? true : false;}

static __inline__ uint8_t onehot8Set (const uint8_t elem){ /* elem [0..7], (returns a 00000000 byte if "elem" is out of range (hint: it won't pass the "onehot8Valid" test)) */
  return ((elem <= 7)) ? (1 << elem) : 0;} /* not checking for (elem >= 0), it's always true */

static __inline__ uint8_t BIT8clip (const intmax_t in){ /* clips a value in the range [0..255] */
  return (in <= 255) ? (in >= 0) ? in : 0 : 255;}

#endif /* _BITTY_H_ */