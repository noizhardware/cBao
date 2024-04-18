#ifndef _FLOOW_H_
#define _FLOOW_H_

#define FLOOW_H_VERSION "2024d01-1544"

/*** TODO

*/
/*** DOCU

*/

/*** INCLUDES */
	#ifdef WIN32
		#include <windows.h>
	#endif
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
/* DEFINES end. */

/*** TYPEDEFS */
	typedef char floow_t[13];
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
unsigned char* getFloowDate();
void ctimeToFloow(floow_t floow, char* ctimeStr);
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
	#ifdef WIN32
		unsigned char* getFloowDate(){
			unsigned char* floowOut;
			floowOut = (char*) malloc(8); /* kak sooooooooooo WRONG LOL */
			/* *charpointer = '\0' */
			SYSTEMTIME local;
			GetLocalTime(&local);
			/* strcpy(floowOut, local.wYear) */
			itoa(local.wYear,floowOut,10); /* 10 means "base 10" LOL */
			unsigned char floowMonths[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'w'};
			unsigned char floowMonth = floowMonths[local.wMonth-1];
			*(floowOut+4) = floowMonth;
			if(local.wDay<10){
			itoa(0,floowOut+5,10);
			itoa(local.wDay,floowOut+6,10);}
			else{
			itoa(local.wDay,floowOut+5,10);}
			return floowOut;
		}
	#endif /* WIN32 */

	/* platform-neutral */
	void ctimeToFloow(floow_t floow, char* ctimeStr){
		/* year */
			floow[0] = ctimeStr[20];
			floow[1] = ctimeStr[21];
			floow[2] = ctimeStr[22];
			floow[3] = ctimeStr[23];
		/* month */
			if(ctimeStr[4]=='J' && ctimeStr[5]=='a' && ctimeStr[6]=='n'){ floow[4] = 'a'; }
			if(ctimeStr[4]=='F' && ctimeStr[5]=='e' && ctimeStr[6]=='b'){ floow[4] = 'b'; }
			if(ctimeStr[4]=='M' && ctimeStr[5]=='a' && ctimeStr[6]=='r'){ floow[4] = 'c'; }
			if(ctimeStr[4]=='A' && ctimeStr[5]=='p' && ctimeStr[6]=='r'){ floow[4] = 'd'; }
			if(ctimeStr[4]=='M' && ctimeStr[5]=='a' && ctimeStr[6]=='y'){ floow[4] = 'e'; }
			if(ctimeStr[4]=='J' && ctimeStr[5]=='u' && ctimeStr[6]=='n'){ floow[4] = 'f'; }
			if(ctimeStr[4]=='J' && ctimeStr[5]=='u' && ctimeStr[6]=='l'){ floow[4] = 'g'; }
			if(ctimeStr[4]=='A' && ctimeStr[5]=='u' && ctimeStr[6]=='g'){ floow[4] = 'h'; }
			if(ctimeStr[4]=='S' && ctimeStr[5]=='e' && ctimeStr[6]=='p'){ floow[4] = 'i'; }
			if(ctimeStr[4]=='O' && ctimeStr[5]=='c' && ctimeStr[6]=='t'){ floow[4] = 'j'; }
			if(ctimeStr[4]=='N' && ctimeStr[5]=='o' && ctimeStr[6]=='v'){ floow[4] = 'k'; }
			if(ctimeStr[4]=='D' && ctimeStr[5]=='e' && ctimeStr[6]=='c'){ floow[4] = 'w'; }
		/* day */
			floow[5] = ctimeStr[8];
			floow[6] = ctimeStr[9];
		/* time */
			floow[7] = '-';
			floow[8] = ctimeStr[11];
			floow[9] = ctimeStr[12];
			floow[10] = ctimeStr[14];
			floow[11] = ctimeStr[15];
		return;
	}
	/* platform-neutral END. */
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _FLOOW_H_ */
