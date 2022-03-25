#ifndef _HELPERS_H_
#define _HELPERS_H_

#define HELPERS_VERSION "2022c22-1805"
/**** quick embeddable functions, no deps */

/*** TODO
	- nice ideas: https://wiki.xxiivv.com/site/defunct.html
*/

/*** INCLUDES */
#include <stdint.h>
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
	#define ERROR_BLOC printf("%c%c",219, 219)
	#define OK_BLOC printf("%c%c",176, 176)
/* DEFINES end. */

/*** TYPEDEFS */
	typedef uint8_t bool_t;
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
	uint32_t slen(char* s);
	char* scpy(char* dest, char* src);
	bool_t ctri(char c); /* char is trimmable */
	char* stri(char* s); /* string trim */
	bool_t sequ(char* a, char* b); /* string is equal */
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
	uint32_t slen(char* s){
		uint32_t i = 0;
		while(s[i]!='\0'){
			i++;
		}
		return i;
	}

	char* scpy(char* dest, char* src){
		uint32_t i = 0;
		while((dest[i] = src[i]) != '\0'){
			i++;
		}
		return dest;
	}
	
	bool_t ctri(char c){ /* char is trimmable */
		return c == ' ' || c == '\t' || c == '\n' || c == '\r';
	}
	
	char* stri(char* s){ /* string trim */
		char* end;
		uint32_t len = 0;
		char* temp = s;
		int i = 0;

		while((*s) == ' ' || (*s) == '\t' || (*s) == '\n' || (*s) == '\r'){ /* ctri */
			s++;
		}
		if(*s == '\0'){
			while((temp[i] = s[i]) != '\0'){ /* scpy */
				i++;
			}
			return s;
		}

		while(s[len]!='\0'){
			len++;
		}
		end = s + len - 1;
		while(end > s && ((*end) == ' ' || (*end) == '\t' || (*end) == '\n' || (*end) == '\r')){ /* ctri */
			end--;
		}
		end[1] = '\0';
		
		while((temp[i] = s[i]) != '\0'){ /* scpy */
			i++;
		}
		return s;
	}
	
	bool_t sequ(char* a, char* b){ /* string is equal */
		uint32_t i;
		uint32_t lena = 0;
		uint32_t lenb = 0;

		while(a[lena]!='\0'){ /* slen() */
			lena++;
		}
		while(b[lenb]!='\0'){ /* slen() */
			lenb++;
		}
		if(lena != lenb)
			return 0;
		for(i = 0; i < lena; ++i)
			if(a[i] != b[i])
				return 0;
		return 1;
	}
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _HELPERS_H_ */