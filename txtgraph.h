#ifndef _TXTGRAPH_H_
#define _TXTGRAPH_H_

#define TXTGRAPH_VERSION "2023a23-0848"

/*** TODO

*/
/*** DOCU

*/

/*** INCLUDES */
	#include <stdio.h>
	#include <stdint.h>
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
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
		void txtBar(uint32_t data, uint32_t dataMax, uint16_t barMaxLength, char barChar){
			uint16_t displayBar = (float)data / (float)dataMax * barMaxLength;
			uint16_t bar;

			for(bar=0;bar<displayBar;bar++){
				putchar(barChar);
			}
			return;
		}
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _TXTGRAPH_H_ */
