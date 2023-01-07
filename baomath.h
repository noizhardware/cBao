#ifndef __BAOMATH_H__
#define __BAOMATH_H__

/* 2022w20-2219 */

/* ANSI C compliant <3 */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */
#define PHI ((1.+sqrt(5.))/2.)
#define MA_PHI 1.618033988749894848204586834

/* prototypes: */
static __inline__ float round_up(float num);
static __inline__ float roundDec(float num, unsigned char prec);
static __inline__ float roundDec_up(float num, unsigned char prec);
static __inline__ float fract(float x);

/*static __inline__ int minn(int a, int b);*/
static __inline__ int maxx(int a, int b);
static __inline__ bool inRange(unsigned char x, unsigned char low, unsigned char high);
/* prototypes END */

static __inline__ float fract(float x){
     return x - floor(x);}
     

static __inline__ float round_up(float num){
     return ((num - floor(num)) >= 0.5) ? ceil(num) : floor(num); }
                    
static __inline__ float roundDec(float num, unsigned char prec){
     return floor(pow(10, prec) * num) / pow(10, prec); }
     
static __inline__ float roundDec_up(float num, unsigned char prec){
     return floor(round_up(pow(10, prec) * num)) / pow(10, prec); }

/* TODO commented out minn() so it doesn't conflict with helpers.h 2022w12-1509 */
/*static __inline__ int minn(int a, int b){
     return a*(a<b) + b*(b<a) + a*(a==b);}*/
static __inline__ int maxx(int a, int b){
     return a*(a>b) + b*(b>a) + a*(a==b);}

static __inline__ bool inRange(unsigned char x, unsigned char low, unsigned char high) { 
     return  ((x-low) <= (high-low));}


/* from: https://github.com/FHowington/CPUEngine/blob/d1c6f4abeff330ba4ab6b4a6098ae460e7bb4ffc/src/rasterize.cpp#L19 */

     int fast_max(int a, int b) {
  int diff = a - b;
  int dsgn = diff >> 31;
  return a - (diff & dsgn);
}

int fast_min(int a, int b) {
  int diff = a - b;
  int dsgn = diff >> 31;
  return b + (diff & dsgn);
}

uint8_t isPrimeFast32(uint32_t n) {
	if(n < 2){
		return 0;
	}
	else if(n == 2 || n == 3){
		return 1;
	}
	else if(n % 2 == 0 || n % 3 == 0){
		return 0;
	}
	else{
		uint32_t limit = sqrt(n) + 1;
		uint32_t i = 5;
		uint32_t w = 2;
		while (i <= limit) {
			if (n % i == 0){
				return 0;
			}
			i += w;
			w = 6 - w;
		}
		return 1;
	}
}
long double ldMod(long double x, long double y) {
    return x - (long int)(x/y) * y;
}

long double powLD(long double x, long double y) {
    return pow((long int)x, (long int)y);
}
uint8_t isPrimeFastLD(long double n) {
	if(n < 2){
		return 0;
	}
	else if(n == 2 || n == 3){
		return 1;
	}
	else if(ldMod(n, 2) == 0 || ldMod(n, 3) == 0){
		return 0;
	}
	else{
		long double limit = sqrt(n) + 1;
		long double i = 5;
		long double w = 2;
		while (i <= limit) {
			if (ldMod(n, i) == 0){
				return 0;
			}
			i += w;
			w = 6 - w;
		}
		return 1;
	}
}

#ifdef __cplusplus
}
#endif

#endif /* __BAOMATH_H__ */