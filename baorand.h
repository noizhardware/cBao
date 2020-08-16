#ifndef __BAORAND_H__
#define __BAORAND_H__

/* 202008152105 */

#include <stdlib.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* prototypes */
static __inline__ void rand_init();
static __inline__ unsigned long rand_(unsigned long min, unsigned long max);
/****************/

static __inline__ void rand_init(){
     struct timeval usec;
     gettimeofday(&usec, NULL);
     /* printf("microsec is: %lu\n", usec.tv_usec); */
     srand((unsigned)usec.tv_usec);}

static __inline__ unsigned long rand_(unsigned long min, unsigned long max){
     return (rand() % ((max - min) + 1)) + min;}

#ifdef __cplusplus
}
#endif

#endif /* __BAORAND_H__ */
