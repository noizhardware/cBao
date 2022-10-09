#ifndef _HELPERS_H_
#define _HELPERS_H_

#define HELPERS_VERSION "2022j09-1802"
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
	uint32_t strLen(const char* s);
	char* strCopy(char* dest, const char* src);

	bool_t charIsTrim(const char c); /* char is trimmable */
	char* strTrim(char* s); /* string trim */
	bool_t strEqu(const char* a, const char* b); /* string is equal */
	bool_t strStartWith(const char* str, const char* with); /* string starts with */
		
		uint16_t strUntilChar(const char* src, char unti, char* dest); /* cuts a string BEFORE the provided char, so it won't be included in the output string. returns len of output string */

	bool_t strIsInt(const char* s); /* string is int */
	bool_t charIsUint(const char c); /* char is uint */
	bool_t strIsFloat(const char* s);
	float strToFloat(char* s);
	uint16_t strToUint16(const char* s); /* string to uint16 */
	uint32_t strToUint32(char* s);
	uint32_t strHexToUint32(char* s);
	bool_t strIsHex(char* s);
	
	static __inline__ int minn(int a, int b);
	
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
	uint16_t strUntilChar(const char* src, char unti, char* dest){ /* string until char */
		uint16_t i = 0;
		while(src[i]!='\0' && src[i]!=unti){
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		if(src[i]!='\0'){
			i++;
		}
		return i;
	}
	
	static __inline__ int minn(int a, int b){
		return a*(a<b) + b*(b<a) + a*(a==b);
	}

	bool_t strStartWith(const char* str, const char* with){
		uint32_t i;
		size_t c = 0;
		for(i=0; i<((uint32_t)minn(strLen(with),strLen(str))); i++){
			c += str[i]==with[i];
		}
		return (c==strLen(with))&&(strLen(with)<=strLen(str)); /* "with" must be smaller OR EQUAL to the string! if they are the same, we will return true */
	}

	bool_t strIsInt(const char* s){ /* string is int */
		int ii = 0;
		char c;
		while((c = s[ii++])){
			if(!(c >= '0' && c <= '9')){
				return 0;}
		}
		return ii > 1;
	}

	bool_t strIsFloat(const char* s){
		int ii = 0;
		char c;
		while((c = s[ii++])){
			if(!((c >= '0' && c <= '9') || (c == '.') || (c == '-'))){
				return 0;}
		}
		return ii > 1;
	}

	bool_t strIsHex(char* s){
		int ii = 0;
		char c;
		while((c = s[ii++])){
			if(!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f')){
				return 0;
			}
		}
		return ii > 1;
	}
	
	bool_t charIsUint(const char c){ /* char is uint */
		return (c >= '0' && c <= '9');
	}
	
	uint16_t strToUint16(const char* s){ /* string to uint16 */
		uint16_t n = 0, ii = 0;
		char c;
		while((c = s[ii++])){
			n = n * 10 + (c - '0');
		}
		return n;
	}

	uint32_t strToUint32(char* s){
		uint32_t n = 0, ii = 0;
		char c;
		while((c = s[ii++])){
			n = n * 10 + (c - '0');
		}
		return n;
	}

	float strToFloat(char* s){
		float n = 0.f;
		uint32_t ii = 0;
		char c;
		bool_t neg = 0;
		bool_t afterPoint = 0;
		float ten = 10.f;
		float deci = 1.f;

		if(s[0] == '-'){
			neg = 1;
			ii++;
		}

		while((c = s[ii++])){
			if(c == '.'){
				ten = 1.f;
				deci = .1f;
				afterPoint = 1;
				continue;
			}
			n = n * ten + ((c - '0') * deci);
			if(afterPoint){
				deci /= 10.f;
			}
		}
		if(neg){
			n *= (-1.f);
		}
		return n;
	}


	uint32_t strHexToUint32(char* s){
		uint32_t n = 0, ii = 0;
		char c;
		while((c = s[ii++])){
			if(c >= '0' && c <= '9'){
				n = n * 16 + (c - '0');
			}
			else if(c >= 'a' && c <= 'f'){
				n = n * 16 + 10 + (c - 'a');
			}
		}
		return n;
	}

	uint32_t strLen(const char* s){
		uint32_t i = 0;
		while(s[i]!='\0'){
			i++;
		}
		return i;
	}

	char* strCopy(char* dest, const char* src){
		uint32_t i = 0;
		while((dest[i] = src[i]) != '\0'){
			i++;
		}
		return dest;
	}
	
	bool_t charIsTrim(const char c){ /* char is trimmable */
		return c == ' ' || c == '\t' || c == '\n' || c == '\r';
	}
	
	/*
	#include <stdint.h>
	char* strTrim(char* s);
	*/
	char* strTrim(char* s){ /* string trim */
		char* end;
		uint32_t len = 0;
		char* temp = s;
		int i = 0;

		while((*s) == ' ' || (*s) == '\t' || (*s) == '\n' || (*s) == '\r'){ /* charIsTrim */
			s++;
		}
		if(*s == '\0'){
			while((temp[i] = s[i]) != '\0'){ /* strCopy */
				i++;
			}
			return s;
		}

		while(s[len]!='\0'){
			len++;
		}
		end = s + len - 1;
		while(end > s && ((*end) == ' ' || (*end) == '\t' || (*end) == '\n' || (*end) == '\r')){ /* charIsTrim */
			end--;
		}
		end[1] = '\0';
		
		while((temp[i] = s[i]) != '\0'){ /* strCopy */
			i++;
		}
		return s;
	}
	
	/*
	#include <stdint.h>
	typedef uint8_t bool_t;
	bool_t strEqu(char* a, char* b);
	*/
	bool_t strEqu(const char* a, const char* b){ /* string is equal */
		uint32_t i;
		uint32_t lena = 0;
		uint32_t lenb = 0;

		while(a[lena]!='\0'){ /* strLen() */
			lena++;
		}
		while(b[lenb]!='\0'){ /* strLen() */
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