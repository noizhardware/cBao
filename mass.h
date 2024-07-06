#ifndef _MASS_H_
#define _MASS_H_

#define MASS_H_VERSION "2024e20-1631"

/*
POWERSHELL:
(Get-Content "alc.MASS") -replace "`r`n", "`n" | Set-Content "alc.MASS"
*/

/*#define DEBUG*/

/*** TODO:

- in generale, un migliore sanitizing dei .MASS con errori

- ereditarietà dei types dai PNAM (forse da mettere in grain.h)
	- soprattutto di `forw`

- clean preprocessor directives
- le funzioni che hanno a che fare con TOTT e quelle robe li, dovrebbero andare in grain.h

- MAX_BLOCKS_IN_ARCHIVE overflow error
- check buffer size overflows

* tutte le funzioni devono funzionare allo stesso modo: prendono un block e outputtano un block dentro un array

- olderThan
- newerThan
- dateInterval (riusa olderThan e newerThan)

- for config files:
  char** getVal(char* name) >> array di vals che hanno come nome "name"

- find and sanitize errors in the .MASS file

## WRITE to a .mass file:
  - vedi dentro grain.h se c'è qualcosa di usabile
  - create new
  - append

## file conversion
  - .csv to .MASS
  - .MASS to .csv
  
## extras
- rileva specs del file: (getFileSpecs)
  - MAX_NAME_LEN
  - MAX_VALUE_LEN
  - MAX_ELEMS_IN_BLOCK
  - MAX_BLOCKS_IN_ARCHIVE
  - MAX_LINE_LEN
e poi malloc la struct: https://stackoverflow.com/questions/14768230/malloc-for-struct-and-pointer-in-c

*/

/*
     ## MASS block structure:
          massElem_t.name  massElem_t.value --this is the element that acts as header of the block, to separate it form other blocks
            massElem_t.name  massElem_t.value
            massElem_t.name  massElem_t.value
            massElem_t.name  massElem_t.value
            .
            .
            .
          
     un insieme di blocks(ad esempio un file, o un array di blocks) è un "archive"  (massArchive_t)

*/

/*** INCLUDES */
#include <wchar.h>
#include "baostring.h"
#include "baotime.h"
#include "helpers.h"
/* INCLUDES end. */

#ifdef __cplusplus
extern "C" {
#endif

/*** DEFINES */

#define MAX_NAME_LEN 8 /* TODO questo deve essere modificabile dal .mass stesso */
#define MAX_VALUE_LEN 64 /* TODO questo deve essere modificabile dal .mass stesso */
#define MAX_ELEMS_IN_BLOCK 16 /* TODO questo deve essere modificabile dal .mass stesso */

#define MAX_BLOCKS_IN_ARCHIVE 16000
#define MAX_LINE_LEN 64

#define MASS_INLINE_COMMENT "--"

/* for blockPrint */
#define EXTRAS true
#define NO_EXTRAS false

#define UNINITIALIZED(x) x = x /* usage: int UNINITIALIZED(variableName); */

/* DEFINES end. */

/*** TYPEDEFS */
typedef struct massElem_t_{
     char name[MAX_NAME_LEN];
     char value[MAX_VALUE_LEN];
} massElem_t;

typedef struct massBlock_t_{
     unsigned int elemQty; /* number of elements actually contained in this block */
     unsigned int elemPtr; /* pointer to the "current" element : cacca : probably useless */
     massElem_t elem[MAX_ELEMS_IN_BLOCK];
} massBlock_t;

typedef struct massArchive_t_{
     unsigned int blockQty; /* number of blocks actually contained in this archive */
     unsigned int blockPtr; /* pointer to the "current" block */
     massBlock_t block[MAX_BLOCKS_IN_ARCHIVE];
} massArchive_t;

typedef struct massFile_t_{
     char* name; /* filename */
     unsigned int blocks_in_archive;
     unsigned int max_elems_in_block;
     unsigned int max_name_len;
     unsigned int max_val_len;
     unsigned int max_line_len;
} massFile_t;
/* TYPEDEFS end. */

/*** FUNCTION DECLARATIONS */
	static __inline__ bool archiveIsEmpty(massArchive_t* archive);

	static __inline__ bool hasElemNameVal(massBlock_t inBlock, char* elemName, char* elemValue);
	bool hasElemName(massBlock_t inBlock, char* elemName);
	static __inline__ bool dateIs(massBlock_t inBlock, char* date);

	static __inline__ void blockCopy(massBlock_t* dest, massBlock_t* source);

	static __inline__ void blockPrint(massBlock_t block, bool extras);
	void archivePrint(massArchive_t* archive, bool extras);

	static __inline__ void getFileSpecs(char* fileName);

	static __inline__ void filter_dateIs(massArchive_t* inArchive, char* date);
	static __inline__ void filter_hasElem(massArchive_t* inArchive, char* elemName, char* elemValue);
	static __inline__ void filter_hasNotElem(massArchive_t* inArchive, char* elemName, char* elemValue);

	static __inline__ float sumTott(massArchive_t* inArchive);

	void getFile(char* fileName, massArchive_t* archive, uint8_t verbose);

	float sumElem(massArchive_t* inArchive, char* elemName);
	void getElemVal(massBlock_t inBlock, char* elemName, char* elemValBuffer);

/* FUNCTION DECLARATIONS end.  */



/*** FUNCTION DEFINITIONS */
void getElemVal(massBlock_t inBlock, char* elemName, char* elemValBuffer){
	unsigned int i;
   	strCopy(elemValBuffer, "NIL");/* default */
	for(i=0;i<inBlock.elemQty;i++){
		if(strEqual(inBlock.elem[i].name, elemName)){
   			strCopy(elemValBuffer, inBlock.elem[i].value);
   		}
   	}
   	return;
}


static __inline__ bool archiveIsEmpty(massArchive_t* archive){
     return archive->blockQty==0;}

static __inline__ bool hasElemNameVal(massBlock_t inBlock, char* elemName, char* elemValue){
     unsigned int i;
     for(i=0;i<inBlock.elemQty;i++){
          if(strEqual(inBlock.elem[i].name, elemName) && strEqual(inBlock.elem[i].value, elemValue)){
               return true;}}
     return false;}
bool hasElemName(massBlock_t inBlock, char* elemName){
	unsigned int i;
	for(i=0;i<inBlock.elemQty;i++){
		if(strEqual(inBlock.elem[i].name, elemName)){
			return true;
		}
	}
	return false;
}
     
static __inline__ bool dateIs(massBlock_t inBlock, char* date){
     unsigned int i;
     for(i=0;i<inBlock.elemQty;i++){
          if(strEqual(inBlock.elem[i].name, "DATE") && strEqual(inBlock.elem[i].value, date)){
               return true;}}
     return false;}

static __inline__ void blockCopy(massBlock_t* dest, massBlock_t* source){
     unsigned int i;
     for(i=0;i<source->elemQty;i++){
          strcpy(dest->elem[i].name, source->elem[i].name);
          strcpy(dest->elem[i].value, source->elem[i].value);}
     dest->elemQty = source->elemQty;
     dest->elemPtr = source->elemPtr;}

static __inline__ void blockPrint(massBlock_t block, bool extras){
     unsigned int i;
     if(extras){
          printf(">>elemQty: %d\n", block.elemQty);
          printf(">>elemPtr: %d\n", block.elemPtr);}
     for(i=0;i<block.elemQty;i++){
          printf(">>%s :: %s\n", block.elem[i].name, block.elem[i].value);}
     printf("\n");}

void archivePrint(massArchive_t* archive, bool extras){
	unsigned int i;
	
	if(extras){
		printf(">>blockQty: %d\n", archive->blockQty);
		printf(">>blockPtr: %d\n\n", archive->blockPtr);
	}
	for(i=0;i<archive->blockQty;i++){
	blockPrint(archive->block[i], extras);}
	printf("\n");
}

static __inline__ void getFileSpecs(char* fileName){
     /*strcpy(file->name, fileName);*/
     FILE* filePointer;
     wint_t c;
     
          /*unsigned int blocks_in_archive = 0;
          unsigned int max_elems_in_block = 0;
          unsigned int max_name_len = 0;
          unsigned int max_val_len = 0;*/
          unsigned int max_line_len = 0;
          unsigned int max_line_len_tmp = 0;
          
     filePointer = fopen(fileName, "r");
     printf("==scanning file \"%s\"...\n", fileName);

     while (((c = fgetwc(filePointer)) != WEOF)){
          if(c != '\n'){ max_line_len_tmp++;}
               else{ max_line_len_tmp = 0;}
          max_line_len = max(max_line_len, max_line_len_tmp);}
     fclose(filePointer);
     
     printf("==max_line_len: %d >> ", max_line_len);
     if(max_line_len<=MAX_LINE_LEN){ printf("OK\n");}
          else{ printf("::ERROR!!::\n");}
}

static __inline__ void filter_dateIs(massArchive_t* inArchive, char* date){
     unsigned int elemIndex;
     unsigned int blockIndex;
     unsigned int blockIndex_out = 0;
     for(blockIndex=0;blockIndex<inArchive->blockQty;blockIndex++){
          for(elemIndex=0;elemIndex<inArchive->block[blockIndex].elemQty;elemIndex++){
               if(strEqual(inArchive->block[blockIndex].elem[elemIndex].name, "DATE") && strEqual(inArchive->block[blockIndex].elem[elemIndex].value, date)){
                    blockCopy(&inArchive->block[blockIndex_out], &inArchive->block[blockIndex]);
                    blockIndex_out++;}}}
     inArchive->blockQty = blockIndex_out;}

static __inline__ void filter_hasElem(massArchive_t* inArchive, char* elemName, char* elemValue){
     unsigned int elemIndex;
     unsigned int blockIndex;
     unsigned int blockIndex_out = 0;
     for(blockIndex=0;blockIndex<inArchive->blockQty;blockIndex++){
          for(elemIndex=0;elemIndex<inArchive->block[blockIndex].elemQty;elemIndex++){
               if(strEqual(inArchive->block[blockIndex].elem[elemIndex].name, elemName) && strEqual(inArchive->block[blockIndex].elem[elemIndex].value, elemValue)){
                    blockCopy(&inArchive->block[blockIndex_out], &inArchive->block[blockIndex]);
                    blockIndex_out++;
               }
          }
     }
     inArchive->blockQty = blockIndex_out;
}

static __inline__ void filter_hasNotElem(massArchive_t* inArchive, char* elemName, char* elemValue){
     unsigned int elemIndex;
     unsigned int blockIndex;
     unsigned int blockIndex_out = 0;
     bool hasElem;
     for(blockIndex=0;blockIndex<inArchive->blockQty;blockIndex++){
          hasElem = false;
          for(elemIndex=0;elemIndex<inArchive->block[blockIndex].elemQty;elemIndex++){
               if(strEqual(inArchive->block[blockIndex].elem[elemIndex].name, elemName) && strEqual(inArchive->block[blockIndex].elem[elemIndex].value, elemValue)){
                    hasElem = true;
               }
          }
          if(!hasElem){ /* if block has NOT the elem, let's pass it thru */
               blockCopy(&inArchive->block[blockIndex_out], &inArchive->block[blockIndex]);
               blockIndex_out++;
          }
     }
     inArchive->blockQty = blockIndex_out;
}

static __inline__ float sumTott(massArchive_t* inArchive){
     unsigned int elemIndex;
     unsigned int blockIndex;
     float sumOut = 0;
     for(blockIndex=0;blockIndex<inArchive->blockQty;blockIndex++){
          for(elemIndex=0;elemIndex<inArchive->block[blockIndex].elemQty;elemIndex++){
               if(strEqual(inArchive->block[blockIndex].elem[elemIndex].name, "TOTT")){
                    sumOut = hm_add(sumOut, str_toFloat(inArchive->block[blockIndex].elem[elemIndex].value));}}}
     return sumOut;}
float sumElem(massArchive_t* inArchive, char* elemName){
	unsigned int elemIndex;
	unsigned int blockIndex;
	float sumOut = 0.f;
	for(blockIndex=0;blockIndex<inArchive->blockQty;blockIndex++){
		for(elemIndex=0;elemIndex<inArchive->block[blockIndex].elemQty;elemIndex++){
			if(strEqual(inArchive->block[blockIndex].elem[elemIndex].name, elemName)){
				sumOut += str_toFloat(inArchive->block[blockIndex].elem[elemIndex].value);
			}
		}
	}
	return sumOut;
}

void getFile(char* fileName, massArchive_t* archive, uint8_t verbose){
	FILE* filePointer;
	char lineBuf[MAX_LINE_LEN];
	unsigned int lines = 0;
	unsigned int massElem_index = 0;
	char nameTemp[MAX_LINE_LEN];
	unsigned int massArchive_index = 0;
	char* token;
	/*unsigned int lineLen;*/
	unsigned int block_array_full = 0; /* just to keep track of errors */
	unsigned int name_arr_full = 0; /* just to keep track of errors */
	unsigned int value_arr_full = 0; /* just to keep track of errors */
	long int filePos;

	filePointer = fopen(fileName, "r");
	if(filePointer==NULL){
		printf("::==Couldn't open \"%s\", now exiting...\n", fileName);
	}
	else{ /* file open successful, do everything */
		if(verbose){
			printf("==file \"%s\" opened, now starting...\n", fileName);
		}
		filePos = ftell(filePointer);
		while(fgets(lineBuf, MAX_LINE_LEN, filePointer)){ /* while it's not EOF */
			#ifdef DEBUG
				printf("==OUTER WHILE-LOOP start\n");
			#endif
			/*lineBuf[strlen(lineBuf)-1]='\0';*/ /* get rid of the newline */
				lineBuf[strcspn(lineBuf, "\r\n")] = 0; /* TODO : works for LF, CR, CRLF, LFCR, ... */
			#ifdef DEBUG
				printf("==line %d: %s\n", lines, lineBuf);
			#endif
			if(startsWith(lineBuf, "`")){ /* it means it's the end of the MASS data */
				lines++; /* just to acknowledge the fact that we did actually read that last line, and show it out in the final count */
				#ifdef DEBUG
				printf("::==line started with backtick, MASS file ended!\n");
				#endif
				break;
			}
			else if(startsWith(lineBuf, "MASS.")){
				#ifdef DEBUG
					printf("::==this is the JS object definition, skipping\n");
				#endif
				lines++;
			}
			else if(startsWith(lineBuf, MASS_INLINE_COMMENT)){ /* whole-line comment */
				#ifdef DEBUG
					printf("::==whole-line comment, skipping: %s\n", lineBuf);
				#endif
				lines++;
			}
			else{ /* if it's not the .js header nor the footer, and not a whole-line comment */
				/*printf(">>>before>>>%s\n", lineBuf);*/
				terminateStringOnString_destructive(lineBuf, MASS_INLINE_COMMENT, true); /* get rid of comments at the end of the line */
				/*printf(">>>after>>>%s\n", lineBuf);*/
				if(!startsWith(lineBuf, "  ") /*&& line<50*/){ /* if it's a block header */
					#ifdef DEBUG
						printf("==found a block with header: \"%s\", now starting to fill array with elements...\n", lineBuf);
					#endif
					/*isHeader = true;*/
					massElem_index = 0;
					archive->block[massArchive_index].elemQty = 0;
					/* now let's write the header into the block array (array of elems) */
					strcpy(nameTemp, lineBuf);
					strcpy(strstr(nameTemp, "  "), ""); /* terminates the string to exclude the next two spaces, just after the NAME */
					#ifdef DEBUG
						printf("==writing header NAME: \"%s\"...", nameTemp);
					#endif
					if((strlen(nameTemp)+1)<=MAX_NAME_LEN){
						strcpy(archive->block[massArchive_index].elem[massElem_index].name, nameTemp);
						#ifdef DEBUG
							printf("SUCCESS!\n");
						#endif
					}
					else{
						printf("\n::== NAME array too small [%d>>%d] for: \"%s\"\n", (strlen(nameTemp)+1), MAX_NAME_LEN, nameTemp);
						name_arr_full++;
						strcpy(archive->block[massArchive_index].elem[massElem_index].name, "");
					}
					token = strstr(lineBuf+2, "  ")+2; /* prende il secondo token, dopo i due spazi che sono dopo il NAME, ovvero il VALUE */
					#ifdef DEBUG
						printf("==writing header VALUE: \"%s\"...", token);
					#endif
					if((strlen(token)+1)<=MAX_VALUE_LEN){
						strcpy(archive->block[massArchive_index].elem[massElem_index].value, token);
						#ifdef DEBUG
							printf("SUCCESS!\n");
						#endif
					}
					else{
						printf("::== VALUE array too small [%d>>%d] for: \"%s\"\n", (strlen(token)+1), MAX_VALUE_LEN, token);
						value_arr_full++;
						strcpy(archive->block[massArchive_index].elem[massElem_index].value, "");
					}
					#ifdef DEBUG
						printf("==from array: name: %s | value: %s\n", archive->block[massArchive_index].elem[massElem_index].name, archive->block[massArchive_index].elem[massElem_index].value);
					#endif
					archive->block[massArchive_index].elemQty++;
					massElem_index++;
					lines++; /* just to count the total number of lines read */
					/* I wrote the header into the array, now let's loop thru the rest of the elemnts of this block */
					filePos = ftell(filePointer);
					while(fgets(lineBuf, MAX_LINE_LEN, filePointer)){ /* if it's not EOF */
						#ifdef DEBUG
							printf("::==NON_HEADER ELEMENTS WHILE-LOOP start\n");
						#endif
						/*lineLen = strlen(lineBuf);*/ /* memorizzo la lunghezza della riga per poi eventualmente tornare indietro. il +1 NON SO PERCHé (TODO) */
						if(startsWith(lineBuf, MASS_INLINE_COMMENT)){ /* whole-line comment */
							#ifdef DEBUG
								printf("::==comment, skipping: %s\n", lineBuf);
							#endif
							lines++;
						}
						else if(startsWith(lineBuf, "  ")){ /* if it's not another header */
							if(massElem_index>=MAX_ELEMS_IN_BLOCK){
								printf("::==BLOCK ARRAY IS FULL. fuck off and die.\n");
								block_array_full++;
								break;
							}
							/*lineBuf[strlen(lineBuf)-1]='\0';*/ /* get rid of the newline */
								lineBuf[strcspn(lineBuf, "\r\n")] = 0; /* TODO : works for LF, CR, CRLF, LFCR, ... */
							terminateStringOnString_destructive(lineBuf, MASS_INLINE_COMMENT, true); /* CACCA ---- get rid of comments at the end of the line */
							/*printf(">>>after decomment: %s || %d\n", lineBuf, strlen(lineBuf));*/
							#ifdef DEBUG
								printf("==line %d: %s\n", lines, lineBuf);
							#endif
							if(strlen(lineBuf)>2){ /* if the line contains more than only the two leading spaces*/
								/* prende il primo token dopo i due spazi, ovvero il NAME */
								strcpy(nameTemp, lineBuf+2); /* nameTemp now starts after the two leading spaces */
								strcpy(strstr(nameTemp, "  "), ""); /* terminates the string to exclude the next two spaces, just after the NAME */
								if((strlen(nameTemp)+1)<=MAX_NAME_LEN){
									strcpy(archive->block[massArchive_index].elem[massElem_index].name, nameTemp);
								}
								else{
									printf("\n::== NAME array too small [%d>>%d] for: \"%s\"\n", (strlen(nameTemp)+1), MAX_NAME_LEN, nameTemp);
									name_arr_full++;
									strcpy(archive->block[massArchive_index].elem[massElem_index].name, "");
								}
								token = strstr(lineBuf+2, "  ")+2; /* prende il secondo token, dopo i due spazi che sono dopo il NAME, ovvero il VALUE */
								if((strlen(token)+1)<=MAX_VALUE_LEN){
									strcpy(archive->block[massArchive_index].elem[massElem_index].value, token);
								}
								else{
									printf("::== VALUE array too small [%d>>%d] for: \"%s\"\n", (strlen(token)+1), MAX_VALUE_LEN, token);
									value_arr_full++;
									strcpy(archive->block[massArchive_index].elem[massElem_index].value, "");
								}
								#ifdef DEBUG
									printf("==from array: name: %s | value: %s\n", archive->block[massArchive_index].elem[massElem_index].name, archive->block[massArchive_index].elem[massElem_index].value);
								#endif
								archive->block[massArchive_index].elemQty++;
								massElem_index++;
							}/* if the line contains more than only the two leading spaces*/
							lines++; /* just to count the total number of lines read */
						} /* if it's not another header */
						else{ /* it's a whole-line comment OR another header */
							#ifdef DEBUG
								printf("::==breaking out of NON_HEADER ELEMENTS WHILE-LOOP\n");
							#endif
							break;
						}
						#ifdef DEBUG
							printf("::==NON_HEADER ELEMENTS WHILE-LOOP end\n");
						#endif
					} /* while(fgets(lineBuf, MAX_LINE_LEN, filePointer)){ */
					#ifdef DEBUG
						printf("==block.elemQty: %d\n", archive->block[massArchive_index].elemQty);
					#endif

					/** code to do something with the block **/
					/*printf(">>>blockHeader:: NAME: %s, VALUE: %s\n", block.elem[0].name, block.elem[0].value);*/
					/*****************************************/

					archive->block[massArchive_index].elemPtr = 0;
					massArchive_index++;


				
					/*fseek(filePointer, -1*lineLen, SEEK_CUR);*/ /* go back one line */
					fseek(filePointer, filePos, SEEK_SET); /* go back one line */
						/*fgets(lineBuf, MAX_LINE_LEN, filePointer);
						printf("== (%d) POST-SEEK line %d: |%s| (%c)\n", -1*lineLen, lines, lineBuf, lineBuf[0]);*/
					lines--; /* just to count the total number of lines read */
				} /* if it's a block header */
				lines++; /* just to count the total number of lines read */
			} /* if it's not the .js header nor the footer, and not a whole-line comment */
			archive->blockQty = massArchive_index;
			archive->blockPtr = 0;
			#ifdef DEBUG
				printf("==OUTER WHILE-LOOP end\n");
			#endif
			lineBuf[0]='\0';
		} /* while(fgets(lineBuf, MAX_LINE_LEN, filePointer)){ */
		if(verbose){
			printf("\n\n==read %d lines\n", lines);
			printf("\n\n==wrote %d blocks in archive (%d blocks remaining)\n\n", archive->blockQty, MAX_BLOCKS_IN_ARCHIVE-archive->blockQty);
			printf("==NAME-array FULL errors: %d\n", name_arr_full);
			printf("==VALUE-array FULL errors: %d\n", value_arr_full);
			printf("==block array(array of elems) FULL errors: %d\n", block_array_full);
			printf("==TOTAL ERRORS: %d\n\n", name_arr_full+value_arr_full+block_array_full);
		}

		fclose(filePointer);
	} /* if fileopen was successful */
} /* getFile */

/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
}
#endif
#endif /* _MASS_H_ */
