#ifndef __BAOSTRING_H__
#define __BAOSTRING_H__

/* C90 compliant <3 */

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
/* #include <stdio.h>*/

/*prototypes*/
/**/static __inline__ bool isFloat(char *str); /*untested*/
/**/static __inline__ bool isInt(char *str); /* untested*/
/**/static __inline__ char digitToChar(unsigned char digit);
static __inline__ void* reallok(void* source, size_t size);
/**/static __inline__ char* removeSubstr(char *inputString, char *sub, bool freeTheSource);
static __inline__ char* terminateStringOnChar(char* inputString, char marker, bool deleteMarker, bool freeTheSource);
static __inline__ char* clearStringUntilChar(char* inputString, char marker, bool deleteMarker);
static __inline__ void terminateStringOnString(char* string, char* marker);
/**/static __inline__ char* appendChar(char* inputString, char ch, bool freeTheSource);
/**/static __inline__ char* appendString(char* inputString, char* stringToAppend, bool freeTheSource);
static __inline__ bool startsWith(const char* string, const char* match);
/**/static __inline__ bool strEqual(char* st1, char* st2);
/**************************************/

static __inline__ bool isFloat(char *str) {
  char *ptr = NULL;
  strtod(str, &ptr);
  return !*ptr;}

static __inline__ bool isInt(char *str) {
  char *ptr = NULL;
  strtol(str, &ptr, 10);
  return !*ptr;}

static __inline__ char digitToChar(unsigned char digit){
     return digit +'0';}

static __inline__ bool strEqual(char* st1, char* st2){
     return (strcmp(st1, st2)==0);}
 
static __inline__ void* reallok(void* source, size_t size){ /* basically alloc with automatic check for success/fail*/
  void* tempPtr = realloc(source, size);
  if(tempPtr != NULL){
       return tempPtr;}
  else{
       return source;}}

/* removes the first occurrence of sub from the input string, if there is one */
static __inline__ char* removeSubstr(char *inputString, char *sub, bool freeTheSource){ /*if freeTheSource is TRUE, the original inputString will be freed from memory. destructive*/
     char* match;
     unsigned int len = strlen(sub);
     char* outputString; /* new internal char* */
     outputString = malloc(strlen(inputString)+1);
     strcpy(outputString, inputString); /* copies inputString into outputString, now they're identical*/
     if ((match = strstr(outputString, sub))){
          *match = '\0';
          strcat(outputString, match+len);
          reallok(outputString,  strlen(inputString)+1-strlen(sub)); /* resize allocated memory*/
          if(freeTheSource){
               free(inputString);} /* frees the old allocation*/
          return outputString;}
     else{
          free(outputString);/* frees the new allocation, because it is useless in this case*/
          return inputString;}
     }
/*
// takes string and removes everything after the first occurrence of the "marker" char. marker must be a single char
// the bool deleteMarker determines whether the marker is deleted as well or not
// deleteMarker TRUE >> marker gets deleted
// terminateStringOnChar(str, ':', FALSE) deletes everything after the first ':'
//if freeTheSource is TRUE, the original inputString will be freed from memory. destructive*/
static __inline__ char* terminateStringOnChar(char* inputString, char marker, bool deleteMarker, bool freeTheSource){
     char* ptr;
     char* outputString; /* new internal char* */
     outputString = malloc(strlen(inputString)+1); 
     strcpy(outputString, inputString); /* copies inputString into outputString, now they're identical*/
     ptr = strchr(outputString, marker);
     if (ptr != NULL){
          ptr += !deleteMarker;
          *ptr = '\0';
          reallok(outputString, strlen(inputString)+1-(ptr-(outputString+1))); /* resize allocated memory*/
          if(freeTheSource){
               free(inputString);} /* frees the old allocation*/
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
          outputString = malloc(strlen(inputString)+1-(ptr-inputString)); /* allocate memory, smaller than inputString*/
          outputString = ptr;
          /*if(freeTheSource){
               //free(inputString);} // frees the old allocation*/
          return outputString;}
     else{ /* not found*/
          return inputString;}}
          
     /*     
// takes string and removes everything after the first occurrence of the "marker" string. marker must be a string(pointer to char)
// terminateStringOnString(str, "suca ") deletes everything after the first "suca "*/
static __inline__ void terminateStringOnString(char* string, char* marker){
     char* ptr;
     ptr = strstr(string, marker);
     if (ptr != NULL){
          *ptr = '\0';}}

static __inline__ bool startsWith(const char* string, const char* match){
     return (strncmp(string, match, strlen(match)) == 0);}

static __inline__ char* appendChar(char* inputString, char ch, bool freeTheSource){ /*if freeTheSource is TRUE, the original inputString will be freed from memory. destructive*/
     char* outputString; /* new internal char* */
     unsigned int len;
     outputString = malloc(strlen(inputString)+2); /* allocate space so it can contain inputString, +1 for the string terminator '\0', and another +1 for the new char that's going to be added*/
     strcpy(outputString, inputString); /* copies inputString into outputString, now they're identical*/
     if(freeTheSource){
          free(inputString);} /* frees the old allocation*/
     len = strlen(outputString); /* size, without terminator*/
     outputString[len] = ch;/* overwrites the terminator with the new char*/
     outputString[len+1] = '\0';/*writes a new terminator*/
     return outputString;}
     
static __inline__ char* appendString(char* inputString, char* stringToAppend, bool freeTheSource){ /*if freeTheSource is TRUE, the original inputString will be freed from memory. destructive*/
     char* outputString; /* new internal char* */
     unsigned int len;
     outputString = malloc(strlen(inputString)+1+strlen(stringToAppend)); /* allocate space so it can contain inputString, +1 for the string terminator '\0', and the size of the new string*/
     strcpy(outputString, inputString); /* copies inputString into outputString, now they're identical*/
     if(freeTheSource){
          free(inputString);} /* frees the old allocation*/
     len = strlen(outputString); /* size, without terminator*/
     outputString += len; /* move pointer to terminator*/
     memcpy(outputString, stringToAppend, strlen(stringToAppend));/* overwrites the terminator with the stringToAppend*/
     outputString -= len; /* reset the pointer*/
     outputString[len+strlen(stringToAppend)] = '\0';/*writes a new terminator*/
     return outputString;}

#endif /* __BAOSTRING_H__ */

/*
//   int main(){
// 
// char* stri = "porcodioooo";
// 
// stri = clearStringUntilChar(stri, 'c');
// 
// printf("%s\n", stri);
// 
// 
//     return 0;
//   }*/