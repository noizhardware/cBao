#ifndef _RECAMAN_H_
#define _RECAMAN_H_

#define RECAMAN_VERSION "2022k13-1801"

/*** TODO

*/
/*** DOCU
	Recaman sequence
	http://oeis.org/A005132
	https://www.geeksforgeeks.org/recamans-sequence/
*/

/*** INCLUDES */
	#include <stdint.h>
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
	#define RECAMAN_MAX 100000
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
	uint32_t recaman(uint32_t n);
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
uint32_t recaman(uint32_t n){
	uint32_t arr[RECAMAN_MAX];
	uint32_t i;
	uint32_t out = 0;

	/*// First term of the sequence is always 0*/
		if(n==0){
			return 0;
		}

	/*// Fill remaining terms using recursive
	// formula.*/
	for (i=1; i< n; i++){
		int32_t curr = arr[i-1] - i;
		uint32_t j;
		for (j = 0; j < i; j++){
			/*// If arr[i-1] - i is negative or
			// already exists.*/
			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wsign-compare"
			if ((arr[j] == curr) || curr < 0){
			#pragma GCC diagnostic pop
				curr = arr[i-1] + i;
				break;
			}
		}

		arr[i] = curr;
		out = curr;
	}
	return out;
}
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _RECAMAN_H_ */
