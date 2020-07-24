#ifndef __BAORAND_H__
#define __BAORAND_H__

/* 202007241410 */

#include <stdlib.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

//prototypes
static inline void rand_init();
static inline unsigned long rand_(unsigned long min, unsigned long max);
//////////////////////////////

static inline void rand_init(){
     struct timeval usec;
     gettimeofday(&usec, NULL);
     //printf("microsec is: %lu\n", usec.tv_usec);
     srand((unsigned)usec.tv_usec);}

static inline unsigned long rand_(unsigned long min, unsigned long max){
     return (rand() % ((max - min) + 1)) + min;}

#ifdef __cplusplus
}
#endif

#endif // __BAORAND_H__