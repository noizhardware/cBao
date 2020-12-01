#ifndef _BAOSTRING_H_
#define _BAOSTRING_H_

/* 202008081633 */

/* C90 compliant <3 */

/* TODO:
 * get rid of all malloc / calloc
 * prepend to string
 * file to string: bool ftos(fileName, char* buf) >> fills the buffer, returns 1 if buffer space was enough to contain the file, 0 if not
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "baomath.h"

#ifdef __cplusplus
extern "C" {
#endif

/* prototypes */
static __inline__ char* toUpper(char* str);
static __inline__ char* appendChar(char* str, char c);
static __inline__ char* appendString(char* str1, char* str2);
static __inline__ bool isFloat(char *str);
static __inline__ bool isInt(char *str);
static __inline__ char digitToChar(unsigned char digit);
/*static __inline__ char* boolToStr(bool in);*/
static __inline__ bool strEqual(const char* st1, const char* st2);
static __inline__ char* removeSubstr(char* str, char* toRemove);
static __inline__ void* reallok(void* source, size_t size);
static __inline__ char* terminateStringOnChar(char* inputString, char marker, bool deleteMarker);
static __inline__ char* clearStringUntilChar(char* inputString, char marker, bool deleteMarker);
static __inline__ char* terminateStringOnString(char* in, char* marker, bool deleteMarker);
     static __inline__ char* terminateStringOnString(char* in, char* marker, bool deleteMarker);


static __inline__ bool startsWith(const char* str, const char* with);

static __inline__ char** makeStringTable(unsigned int dimensionA, unsigned int dimensionB);
static __inline__ void freeStringTable(char** arr);

static __inline__ uint8_t char_toNum(char c);
static __inline__ bool char_isNum(char c);
static __inline__ uint16_t str_toUint16(char *s);
static __inline__ float str_toFloat(char* str);

/* prototypes END */

static __inline__ bool char_isNum(char c){
	return c >= '0' && c <= '9';}

static __inline__ uint8_t char_toNum(char c){
  return c - '0';}

static __inline__ uint16_t str_toUint16(char* str){
	uint8_t i = 0;
  uint16_t num = 0;
	while(str[i] && char_isNum(str[i])){
		num = num * 10 + char_toNum(str[i]);
    i++;}
	return num;}

static __inline__ float str_toFloat(char* str){
	return (float)atof(str);}

static __inline__ char* toUpper(char* str){
     int len = strlen(str);
     int i;
     char* out = (char*)malloc(len+1); /* cacca: char* cast added for Arduino warning */
     strcpy(out, str);
     for(i=0; i<len; i++){
          out[i] -= 32*(out[i] >= 'a' && out[i] <= 'z');} /* branchless!! */
     return out;}

static __inline__ char* appendChar(char* str, char c){
         size_t len = strlen(str);
         char *out = (char*)calloc(1, len + 2); /* one for the extra char, one for trailing zero */ /* cacca: char* cast added for Arduino warning */
         strcpy(out, str);
         out[len] = c;
         out[len + 1] = '\0';
         free(str);
         return out;}

/* str1 must be previously malloc'd, and will be free'd here. str2 will not be free'd here */
static __inline__ char* appendString(char* str1, char* str2){
     size_t len1 = strlen(str1);
     size_t len2 = strlen(str2);
     char* out;
     if((out = (char*)calloc(1, len1 + len2 + 1)) != NULL){ /* one for trailing zero */ /* cacca: char* cast added for Arduino warning */
          /*snprintf(out, len1 + len2 + 1, "%s%s", str1, str2);*/
          /* snprintf is C99 and up */
          sprintf(out, "%s%s", str1, str2);
          free(str1);
          return out;}
     else{
          printf("calloc failed!\n");
          exit(-1);}}



/* gives true even if it's an int */
static __inline__ bool isFloat(char *str){
  char *ptr = NULL;
  strtod(str, &ptr);
  return !*ptr;}

static __inline__ bool isInt(char *str){
  char *ptr = NULL;
  strtol(str, &ptr, 10);
  return !*ptr;}

static __inline__ char digitToChar(unsigned char digit){
     return digit +'0';}

/* cacca: I cannot really return a string!!! */
/*static __inline__ char* boolToStr(bool in){
     const char* tr = "true";
     const char* fa = "false";
     if(in){
          return tr;}
     else{
          return fa;}}*/

static __inline__ bool strEqual(const char* st1, const char* st2){
     return (strcmp(st1, st2)==0);}

/* removes the first occurrence of sub from the input string, if there is one */
/* you must free the output element of this function */
static __inline__ char* removeSubstr(char* str, char* toRemove){
     size_t lenRem = strlen(toRemove);
     size_t lenStr = strlen(str);
     char* out;
     char* match = strstr(str, toRemove);
     if(match != NULL){
          out=(char*)calloc(1, lenStr-lenRem+1); /* cacca: char* cast added for Arduino warning */
          memcpy(out, str, match-str);
          strcpy(out+(match-str), match+lenRem);}
     else{
          out=(char*)calloc(1, lenStr+1); /* cacca: char* cast added for Arduino warning */
          strcpy(out, str);}
     return out;}

static __inline__ void* reallok(void* source, size_t size){ /* basically alloc with automatic check for success/fail*/
  void* tempPtr = realloc(source, size);
  if(tempPtr != NULL){
       return tempPtr;}
  else{
       return source;}}

/*
// takes string and removes everything after the first occurrence of the "marker" char. marker must be a single char
// the bool deleteMarker determines whether the marker is deleted as well or not
// deleteMarker TRUE >> marker gets deleted
// terminateStringOnChar(str, ':', FALSE) deletes everything after the first ':'
//if freeTheSource is TRUE, the original inputString will be freed from memory. destructive*/
static __inline__ char* terminateStringOnChar(char* inputString, char marker, bool deleteMarker){
     char* ptr;
     char* outputString; /* new internal char* */
     outputString = (char*)malloc(strlen(inputString)+1); /* cacca: char* cast added for Arduino warning */
     strcpy(outputString, inputString); /* copies inputString into outputString, now they're identical*/
     ptr = strchr(outputString, marker);
     if (ptr != NULL){
          ptr += !deleteMarker;
          *ptr = '\0';
          reallok(outputString, strlen(inputString)+1-(ptr-(outputString+1))); /* resize allocated memory*/
          /*if(freeTheSource){
               free(inputString);}*/ /* frees the old allocation*/
          return outputString;}
     else{ /* not found*/
          free(outputString); /* freeing the allocation, it was all useless :(*/
          return inputString;}}

/*
// takes string and removes everything before the first occurrence of the "marker" char. marker must be a single char
// the bool deleteMarker determines whether the marker is deleted as well or not
// deleteMarker TRUE >> marker gets deleted
// clearStringUntilChar(str, ':', FALSE) deletes everything before the first ':',
////////// THIS FUNCTION SHOULD BE OK, BUT IT HAS NEVER BEEN TESTED!!!!! /////////////////////////
///////////////DO NOT FREETHESOURCE, for now///////////////////////////////*/
static __inline__ char* clearStringUntilChar(char* inputString, char marker, bool deleteMarker){
     char* ptr;
     char* outputString; /*new internal char* */
     ptr = strchr(inputString, marker);
     if (ptr != NULL){ /* we've got a match!*/
          ptr += deleteMarker;
          outputString = (char*)malloc(strlen(inputString)+1-(ptr-inputString)); /* allocate memory, smaller than inputString*/ /* cacca: char* cast added for Arduino warning */
          outputString = ptr;
          /*if(freeTheSource){
               //free(inputString);} // frees the old allocation*/
          return outputString;}
     else{ /* not found*/
          return inputString;}}
static __inline__ void clearStringUntilChar_nomalloc(char* inputString, char marker, bool deleteMarker, char* bufferOut){ /* cacca: probably not working, use strtok() if you can */
     char* ptr;
     ptr = strchr(inputString, marker);
     if (ptr != NULL){ /* we've got a match!*/
          ptr += deleteMarker;
          strcpy(bufferOut, ptr);}
     else{ /* not found*/
          strcpy(bufferOut, inputString);}}

/* startsWith */
#ifndef BRANCH
     static __inline__ bool startsWith(const char* str, const char* with){
          unsigned int i;
          size_t c = 0;
          for(i=0; i<((unsigned int)minn(strlen(with),strlen(str))); i++){
               c += str[i]==with[i];}
          return (c==strlen(with))&&(strlen(with)<=strlen(str));} /* "with" must be smaller OR EQUAL to the string! if they are the same, we will return true */
#endif
/* branching version: */
#ifdef BRANCH
     static __inline__ bool startsWith(const char* str, const char* with){
          size_t i;
          size_t c = 0;
          if(strlen(with)<strlen(str)){
          for(i=0; i<(strlen(with)); i++){
               c += str[i]==with[i];}}
          return (c==strlen(with));}
#endif
/* startsWith END */

static __inline__ char** makeStringTable(unsigned int dimensionA, unsigned int dimensionB){
     unsigned int i;
     char* values = (char*)calloc(dimensionA*dimensionB, sizeof(char)); /* cacca: char* cast added for Arduino warning */
     char** rows = (char**)calloc(dimensionB, sizeof(char*)); /* cacca: char** cast added for Arduino warning */
     for (i=0; i<dimensionB; i++){
          rows[i] = values + i*dimensionA;}
     return rows;}

static __inline__ void freeStringTable(char** arr){
     free(*arr);
     free(arr);}

/* terminates the string on a match, if there is one, otherwise returns the same string */
static __inline__ char* terminateStringOnString(char* in, char* marker, bool deleteMarker){
     size_t lenMark = strlen(marker);
     size_t lenStr = strlen(in);
     char* out;
     char* match = strstr(in, marker);
     if(match != NULL){
          out=(char*)calloc(1, match-in+1 + ((!deleteMarker)*lenMark)); /* cacca: char* cast added for Arduino warning */
          memcpy(out, in, match-in + ((!deleteMarker)*lenMark));}
     else{
          out=(char*)calloc(1, lenStr+1); /* cacca: char* cast added for Arduino warning */
          strcpy(out, in);}
     return out;}
/* terminates the string on a match, if there is one, otherwise returns the same string */
static __inline__ void terminateStringOnString_nomalloc(char* in, char* marker, bool deleteMarker, char* bufferOut){
     size_t lenMark = strlen(marker);
     char* match = strstr(in, marker);
     if(match != NULL){
          memcpy(bufferOut, in, match-in + ((!deleteMarker)*lenMark)); /* cacca: not checking for bufferOut max size */
          bufferOut[match-in + ((!deleteMarker)*lenMark)] = '\0'; /* terminate the string */
     }
     else{
          strcpy(bufferOut, in);}}

#ifdef __cplusplus
}
#endif

#endif /* _BAOSTRING_H_ */
