#ifndef __BAOSTRING_H__
#define __BAOSTRING_H__

/* 202007241411 */

/* C90 compliant <3 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
static __inline__ char* boolToStr(bool in);
static __inline__ bool strEqual(char* st1, char* st2);
static __inline__ char* removeSubstr(char* str, char* toRemove);
/* prototypes END */

static __inline__ char* toUpper(char* str){
     int len = strlen(str);
     int i;
     char* out = malloc(len+1);
     strcpy(out, str);
     for(i=0; i<len; i++){
          out[i] -= 32*(out[i] >= 'a' && out[i] <= 'z');} /* branchless!! */
     return out;}
     
static __inline__ char* appendChar(char* str, char c){
         size_t len = strlen(str);
         char *out = calloc(1, len + 2); /* one for the extra char, one for trailing zero */
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
     if((out = calloc(1, len1 + len2 + 1)) != NULL){ /* one for trailing zero */
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
     
static __inline__ char* boolToStr(bool in){
     if(in){
          return "true";}
     else{
          return "false";}}

static __inline__ bool strEqual(char* st1, char* st2){
     return (strcmp(st1, st2)==0);}

/* removes the first occurrence of sub from the input string, if there is one */
static __inline__ char* removeSubstr(char* str, char* toRemove){
     size_t lenRem = strlen(toRemove);
     size_t lenStr = strlen(str);
     char* out;
     char* match = strstr(str, toRemove);
     if(match != NULL){
          out=calloc(1, lenStr-lenRem+1);
          memcpy(out, str, match-str);
          strcpy(out+(match-str), match+lenRem);}
     else{
          out=calloc(1, lenStr+1);
          strcpy(out, str);}
     return out;}

#ifdef __cplusplus
}
#endif

#endif /* __BAOSTRING_H__ */