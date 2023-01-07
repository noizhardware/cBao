#ifndef _GETCH_H_
#define _GETCH_H_

#define GETCH_H_VERSION "2022i24-1753"

/*** TODO
	- define all keys names/codes, cross-platform
*/

/*** INCLUDES */
	#ifdef __linux__
	    /* linux code goes here */
			#include <unistd.h>
			#include <termios.h>

			#include <sys/select.h>
			#include <stropts.h>
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
	#else

	#endif
	/* common defines */
		#define GETCH_ENTER 13
		#define GETCH_SPACE 32
		#define GETCH_ESC 27
		#define GETCH_BACKSPACE 8
		#define GETCH_SPECIAL (-32)
		#define GETCH_ARROW_LEFT 75
		#define GETCH_ARROW_RIGHT 77
		#define GETCH_ARROW_UP 72
		#define GETCH_ARROW_DOWN 80

		#define GETCH_F1 59

		#define GETCH_1 49
		#define GETCH_2 50
		#define GETCH_3 51
		#define GETCH_4 52
		#define GETCH_5 53
		#define GETCH_6 54
		#define GETCH_7 55
		#define GETCH_8 56
		#define GETCH_9 57
		#define GETCH_0 48
		#define GETCH_MINUS 45
		#define GETCH_EQUAL 61


		#define GETCH_Q 113
		#define GETCH_W 119
		#define GETCH_E 101
		#define GETCH_R 114
		#define GETCH_T 116
		#define GETCH_Y 121
		#define GETCH_U 117
		#define GETCH_I 105
		#define GETCH_O 111
		#define GETCH_P 112
		#define GETCH_SQUAREL 91
		#define GETCH_SQUARER 93
		#define GETCH_CURLYL 123
		#define GETCH_CURLYR 125

		#define GETCH_A 97
		#define GETCH_S 115
		#define GETCH_D 100
		#define GETCH_F 102
		#define GETCH_G 103
		#define GETCH_H 104
		#define GETCH_J 106
		#define GETCH_K 107
		#define GETCH_L 108
		#define GETCH_SEMICOLON 59
		#define GETCH_QUOTE 39
		#define GETCH_COLON 58
		#define GETCH_QUOTEDOUBLE 34

		#define GETCH_Z 122
		#define GETCH_X 120
		#define GETCH_C 99
		#define GETCH_V 118
		#define GETCH_B 98
		#define GETCH_N 110
		#define GETCH_M 109
		#define GETCH_COMMA 44
		#define GETCH_PEDIOD 46
		#define GETCH_SLASHF 47
		#define GETCH_ANGLEL 60
		#define GETCH_ANGLER 62
		#define GETCH_QUESTION 63
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

	/**
	Linux (POSIX) implementation of _kbhit().
	Morgan McGuire, morgan@cs.brown.edu
	https://www.flipcode.com/archives/kbhit.txt
	*/
	int kbhit(){
	    static const int STDIN = 0;
	    static bool initialized = false;

	    if (! initialized) {
	        // Use termios to turn off line buffering
	        termios term;
	        tcgetattr(STDIN, &term);
	        term.c_lflag &= ~ICANON;
	        tcsetattr(STDIN, TCSANOW, &term);
	        setbuf(stdin, NULL);
	        initialized = true;
	    }

	    int bytesWaiting;
	    ioctl(STDIN, FIONREAD, &bytesWaiting);
	    return bytesWaiting;
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








