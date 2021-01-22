#ifndef __BAOMATH_H__
#define __BAOMATH_H__

/* 2020i17-1011 */

/* ANSI C compliant <3 */

#ifdef _WIN32
#include <Math.h>
/********** non-win **********/
#else
#include <math.h>
#endif /* OS switch */

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

static __inline__ int minn(int a, int b);
static __inline__ int maxx(int a, int b);
static __inline__ bool inRange(unsigned char x, unsigned char low, unsigned char high);
/* prototypes END */


static __inline__ float round_up(float num){
     return ((num - floor(num)) >= 0.5) ? ceil(num) : floor(num); }
                    
static __inline__ float roundDec(float num, unsigned char prec){
     return floor(pow(10, prec) * num) / pow(10, prec); }
     
static __inline__ float roundDec_up(float num, unsigned char prec){
     return floor(round_up(pow(10, prec) * num)) / pow(10, prec); }
     
static __inline__ int minn(int a, int b){
     return a*(a<b) + b*(b<a) + a*(a==b);}
static __inline__ int maxx(int a, int b){
     return a*(a>b) + b*(b>a) + a*(a==b);}

static __inline__ bool inRange(unsigned char x, unsigned char low, unsigned char high) { 
     return  ((x-low) <= (high-low));} 

#ifdef __cplusplus
}
#endif

#endif /* __BAOMATH_H__ */