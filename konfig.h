#ifndef _KONFIG_H_
#define _KONFIG_H_

#define KONFIG_CREATED "2025b21-1332"
#define KONFIG_VERSION "2025c01-2058s"

/*** TODO

*/
/*** DOCU
	- usage:
		kfgVal_t myValue;
		kfgGet("myFileName.kfg", "myKey", myValue);
*/

/*** INCLUDES */
	#include "helpers.h"
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
	#define KFG_MAX_LINE_LEN 128
	#define KFG_GLYPH ':'
	#define KFG_SEPARATOR ' '
/* DEFINES end. */

/*** TYPEDEFS */
	typedef char kfgVal_t[KFG_MAX_LINE_LEN];
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
	void kfgGet(char* konfigFileName, char* key, kfgVal_t value); /* will fill `value` string, NULL if not found */
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
	void kfgGet(char* konfigFileName, char* key, kfgVal_t value){
		FILE* konfigFile;
		char line[KFG_MAX_LINE_LEN];
		char temp[KFG_MAX_LINE_LEN];

		value[0] = '\0'; /* sanitize string */
		konfigFile = fopen(konfigFileName, "r");
		if(konfigFile){
			while(fgets(line, KFG_MAX_LINE_LEN, konfigFile)){ /* line by line */
				strTrim((char*)line);
				if(line[0] == KFG_GLYPH){
					strUntilChar(line, KFG_SEPARATOR, temp);
					if(strEqu(temp+1, key)){
						strCopy(value, line+strLen(temp)+1);
						return;
					}
				}
			}
		}
		fclose(konfigFile);
		value = NULL; /* key not found */
		return;
	}
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _KONFIG_H_ */
