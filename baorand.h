#ifndef _BAORAND_H_
#define _BAORAND_H_

#define BAORAND_VERSION "2022w12-1701"

/*** TODO

*/
/*** DOCU

*/

/*** INCLUDES */
	#ifndef BAORAND_8BIT
		#include <stdlib.h>
	#endif
	#include <stdint.h>

	/* define BAORAND_NOTIME if your system doesn't have time (eg. an embedded device), and use rand_init_realtime to init the seed manually */
	#ifndef BAORAND_NOTIME
		#include <sys/time.h>
	#endif
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
	/* define BAORAND_8BIT if you're using only the 8bit implementation */
	#ifndef BAORAND_8BIT
		static uint32_t baorand_seed32;
		static uint16_t baorand_seed16;
	#endif
	static uint8_t baorand_seed8;
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
	#ifndef BAORAND_8BIT
		#ifndef BAORAND_NOTIME
			void rand_init();
		#endif
		static __inline__ void rand_init_realtime(unsigned int seed);
		static __inline__ unsigned long rand_(unsigned long min, unsigned long max);

		uint32_t xorshift32(uint32_t* state);
		uint64_t xorshift64(uint64_t* state);
		uint16_t xorshift16(uint16_t* state);
		static __inline__ void rand_xs32_init(uint32_t seed);
		static __inline__ void rand_xs32_init_time(void);
		static __inline__ uint32_t rand_xs32(uint32_t min, uint32_t max);
		static __inline__ uint32_t rand_xs32_seed(uint32_t* seed, uint32_t min, uint32_t max);
		static __inline__ void rand_xs16_init(uint16_t seed);
		static __inline__ uint16_t rand_xs16(uint16_t min, uint16_t max);
	#endif /* #ifndef BAORAND_8BIT */

	uint8_t xorshift8(uint8_t* state);
	static __inline__ void rand_xs8_init(uint8_t seed);
	static __inline__ uint8_t rand_xs8(uint8_t min, uint8_t max);
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
	#ifndef BAORAND_8BIT
		#ifndef BAORAND_NOTIME
			void rand_init(){
				struct timeval usec;
				gettimeofday(&usec, NULL);
				/* printf("microsec is: %lu\n", usec.tv_usec); */
				srand((unsigned)usec.tv_usec);
			}
		#endif

		static __inline__ void rand_init_realtime(unsigned int seed){
			srand((unsigned)seed);
		}

		static __inline__ unsigned long rand_(unsigned long min, unsigned long max){
			return (rand() % ((max - min) + 1)) + min;
		}

		static __inline__ unsigned long rand_simple(unsigned long seed, unsigned long min, unsigned long max){
			return (seed % ((max - min) + 1)) + min;
		}

		static __inline__ uint32_t rand_xs32_seed(uint32_t* seed, uint32_t min, uint32_t max){
			return (xorshift32(seed) % ((max - min) + 1)) + min;
		}

		static __inline__ void rand_xs32_init(uint32_t seed){
			baorand_seed32 = seed;
			return;
		}
		static __inline__ void rand_xs32_init_time(void){
			struct timeval usec;
			gettimeofday(&usec, NULL);
			baorand_seed32 = (uint32_t)usec.tv_usec;
			return;
		}
		static __inline__ uint32_t rand_xs32(uint32_t min, uint32_t max){
			return (xorshift32(&baorand_seed32) % ((max - min) + 1)) + min;
		}

		static __inline__ void rand_xs16_init(uint16_t seed){
			baorand_seed16 = seed;
			return;
		}
		static __inline__ uint16_t rand_xs16(uint16_t min, uint16_t max){
			return (xorshift16(&baorand_seed16) % ((max - min) + 1)) + min;
		}

		

		/* from https://en.wikipedia.org/wiki/Xorshift#Example_implementation */
		/* The state must be initialized to non-zero */
		uint32_t xorshift32(uint32_t* state){
			/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
			uint32_t x = *state;
			x ^= x << 13;
			x ^= x >> 17;
			x ^= x << 5;
			*state = x;
			return x;
		}
		uint64_t xorshift64(uint64_t* state){
			uint64_t x = *state;
			x ^= x << 13;
			x ^= x >> 7;
			x ^= x << 17;
			*state = x;
			return x;
		}

		/* from http://www.retroprogramming.com/2017/07/xorshift-pseudorandom-numbers-in-z80.html */
		/* The state must be initialized to non-zero */
		uint16_t xorshift16(uint16_t* state){
			uint16_t x = *state;
			x ^= x << 7;
			x ^= x >> 9;
			x ^= x << 8;
			*state = x;
			return x;
		}
	#endif /* #ifndef BAORAND_8BIT */

	/* from http://www.fractalforums.com/programming/8-bit-random-(unsigned)/ */
	/* returns values from 1 to 255 inclusive, period is 255 */
	/* The state must be initialized to non-zero */
	uint8_t xorshift8(uint8_t* state){
		uint8_t x = *state;
		x ^= x << 7;
		x ^= x >> 5;
		x ^= x << 3;
		*state = x;
		return x;
	}

	static __inline__ void rand_xs8_init(uint8_t seed){
		baorand_seed8 = seed;
		return;
	}
	static __inline__ uint8_t rand_xs8(uint8_t min, uint8_t max){
		return (xorshift8(&baorand_seed8) % ((max - min) + 1)) + min;
	}

/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _BAORAND_H_ */