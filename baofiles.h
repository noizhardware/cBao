#ifndef __BAOFILES_H__
#define __BAOFILES_H__

/* 202008081633 */

/* C90 compliant <3 */

/* TODO:
* append to file
* prepend to file
* all branchless
*/

/* #include <stdio.h>*/
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "baostring.h"

#ifdef __cplusplus
extern "C" {
#endif

/* prototypes */
static __inline__ char* fileRead(char* fileName);
static __inline__ long int fileSize(char* filename);
static __inline__ bool fileWrite(char* fileName, char* stuffToWrite);
static __inline__ char** fileToLines(char* fileName, unsigned int maxLineSize, unsigned int maxLinesInFile);
/* prototypes END */

static __inline__ char* fileRead(char* file){
     FILE* fp;
     long fileSize;
     char* fileContents;

     fp = fopen ( file , "rb" );
     if(!fp){
          perror(file);
          exit(1);}

     /* this block writes the size of the file in fileSize */
     fseek( fp , 0L , SEEK_END);
     fileSize = ftell( fp );
     rewind( fp );

     /* allocate memory for entire content */
     fileContents = malloc(fileSize+1);
     if(!fileContents){
          fclose(fp);
          fputs("memory alloc fails",stderr);
          exit(1);}

     /* copy the file into the buffer */
     if(fread(fileContents, fileSize, 1, fp) != 1){
          fclose(fp);
          free(fileContents);
          fputs("entire read fails",stderr);
          exit(1);}
          
     /* close the file */
     fclose(fp);
     return fileContents;}
     
static __inline__ bool fileWrite(char* fileName, char* stuffToWrite){     
     FILE* out = fopen(fileName, "w"); /* open file for writing */
     char* ORIGINALstuffToWrite;
     if (!out) {
          return false;} /* file error*/
     ORIGINALstuffToWrite = stuffToWrite;
     while (*stuffToWrite != '\0'){
          fputc(*stuffToWrite, out);
          stuffToWrite++;}
     /*fputc(EOF, out); // non c'è bisogno, lo fa da solo*/
     stuffToWrite = ORIGINALstuffToWrite;
     fclose(out);
     return true;}
     
static __inline__ long int fileSize(char* filename){ /*returns size in bytes, NOT counting the EOF byte  */
     FILE* in = fopen(filename, "r");
     long int size;
     fseek(in, 0L, SEEK_END);
     size = ftell(in);
     fclose(in);
     return size;}
     
/* (file)>>(array of lines) terminated by an EOF*/
static __inline__ char** fileToLines(char* fileName, unsigned int maxLineSize, unsigned int maxLinesInFile){
     char** line = makeStringTable(maxLinesInFile, maxLineSize);
     FILE *fptr = NULL; 
     int i = 0;
     fptr = fopen(fileName, "r");
     while(fgets(line[i], maxLineSize, fptr)){
          line[i][strlen(line[i]) - 1] = '\0';
          i++;}
     line[i][0]=(char)EOF;
     return line;}
     
     
#ifdef __cplusplus
}
#endif
#endif /* __BAOFILES_H__ */