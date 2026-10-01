#ifndef _COLPRINT_H_
#define _COLPRINT_H_

#define COLPRINT_H_CREATED "2025j31-1741"
#define COLPRINT_H_VERSION "2025j31-1741"

/*** TODO
	- intergrate in helpers.h?
*/
/*** DOCU
	- usage; printf(ANSI_COLOR_RED "This text is RED!" ANSI_COLOR_RESET "\n");
*/

/*** INCLUDES */
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
	#define ANSI_COLOR_RED     "\x1b[31m"
	#define ANSI_COLOR_GREEN   "\x1b[32m"
	#define ANSI_COLOR_YELLOW  "\x1b[33m"
	#define ANSI_COLOR_BLUE    "\x1b[34m"
	#define ANSI_COLOR_MAGENTA "\x1b[35m"
	#define ANSI_COLOR_CYAN    "\x1b[36m"
	#define ANSI_COLOR_BHO    "\x1b[30m"
	#define ANSI_COLOR_BHO2    "\x1b[29m"
	
	#define ANSI_COLOR_RESET   "\x1b[0m"

	#define ANSI_COLOR_BOLD "\x1b[1m"
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _COLPRINT_H_ */
