#ifndef __BAOMATH_H__
#define __BAOMATH_H__

/* 202007241410 */

#ifdef _WIN32
#include <Math.h>
////////// non-win ///////////
#else
#include <math.h>
#endif // OS switch

#ifdef __cplusplus
extern "C" {
#endif

// prototypes:
static inline float round_up(float num);
static inline float roundDec(float num, unsigned char prec);
static inline float roundDec_up(float num, unsigned char prec);


static inline float round_up(float num){
     return ((num - floor(num)) >= 0.5) ? ceil(num) : floor(num); }
                    
static inline float roundDec(float num, unsigned char prec){
     return floor(pow(10, prec) * num) / pow(10, prec); }
     
static inline float roundDec_up(float num, unsigned char prec){
     return floor(round_up(pow(10, prec) * num)) / pow(10, prec); }

#ifdef __cplusplus
}
#endif

#endif // __BAOMATH_H__