#ifndef _HELPERS_H_
#define _HELPERS_H_

#define HELPERS_VERSION "2022c20-1851"
/**** quick embeddable functions, no deps */

/*** TODO
	- nice ideas: https://wiki.xxiivv.com/site/defunct.html
*/

/*** INCLUDES */
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
	#define ERROR_BLOC printf("%c%c",219, 219)
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
	long int slen(char* s);
	char* scpy(char* dest, char* src);
	char ctri(char c); /* char is trimmable */
	char* stri(char* s); /* string trim */
	char sequ(char* a, char* b); /* string is equal */
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
	long int slen(char* s){
		long int i = 0;
		while(s[i]!='\0'){
			i++;
		}
		return i;
	}

	char* scpy(char* dest, char* src){
		int i = 0;
		while((dest[i] = src[i]) != '\0'){
			i++;
		}
		return dest;
	}
	
	char ctri(char c){ /* char is trimmable */
		return c == ' ' || c == '\t' || c == '\n' || c == '\r';
	}
	
	char* stri(char* s){ /* string trim */
		char* end;
		long int len = 0;
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
	
	char sequ(char* a, char* b){ /* string is equal */
		long int i;
		long int lena = 0;
		long int lenb = 0;

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