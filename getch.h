#ifndef _GETCH_H_
#define _GETCH_H_

#define GETCH_H_VERSION "2022f24-2234"

/*** TODO
	- define keys names, cross-platform
*/

/*** INCLUDES */
	#ifdef __linux__
	    /* linux code goes here */
			#include <unistd.h>
			#include <termios.h>
	#elif _WIN32
	    /*  windows code goes here */
		#include <conio.h>
	#else

	#endif
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
	#ifdef __linux__
		/* linux code goes here */
	#elif _WIN32
		/*  windows code goes here */
		#define GETCH_ENTER 13
		#define GETCH_BACKSPACE 8
		#define GETCH_SPECIAL (-32)
		#define GETCH_ARROW_LEFT 75
		#define GETCH_ARROW_RIGHT 77
		#define GETCH_ARROW_UP 72
		#define GETCH_ARROW_DOWN 80

	#else

	#endif
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
		
	#ifdef __linux__
		/* linux code goes here */
		char getch();
	#elif _WIN32
		/*  windows code goes here */
	#else

	#endif
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
#ifdef __linux__
/* linux code goes here */
	char getch(){
		char buf = 0;
		struct termios old = {0};
		fflush(stdout);
		if(tcgetattr(0, &old) < 0){
			perror("tcsetattr()");
		}
		old.c_lflag &= ~ICANON;
		old.c_lflag &= ~ECHO;
		old.c_cc[VMIN] = 1;
		old.c_cc[VTIME] = 0;
		if(tcsetattr(0, TCSANOW, &old) < 0){
			perror("tcsetattr ICANON");
		}
		if(read(0, &buf, 1) < 0){
			perror("read()");
		}
		old.c_lflag |= ICANON;
		old.c_lflag |= ECHO;
		if(tcsetattr(0, TCSADRAIN, &old) < 0){
			perror("tcsetattr ~ICANON");
		}
		/*printf("%c\n", buf);*/
		return buf;
	}
#elif _WIN32
	/*  windows code goes here */
#else

#endif
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _GETCH_H_ */








