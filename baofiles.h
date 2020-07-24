#ifndef __BAOFILES_H__
#define __BAOFILES_H__

/* 202007241409 */

/* C90 compliant <3 */

/* TODO:
* append to file
* prepend to file
* branchless
*/

/* #include <stdio.h>*/
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "baostring.h"

#ifdef __cplusplus
extern "C" {
#endif

static __inline__ char* fileRead(char* fileName);
static __inline__ long int fileSize(char* filename);
static __inline__ bool fileWrite(char* fileName, char* stuffToWrite);

/* you need to free() the string when you're done using it */
static __inline__ char* fileRead_OLD(char* fileName){
     FILE* in = fopen(fileName, "r");
     int c;
     char* fileContents = malloc(fileSize(fileName)+1); /* to include the '\0' terminator */
     
     *fileContents = '\0';
     
     if(in == NULL){
          printf("read error\n");
          exit(-1);}
          /********************************
          il problema è quando entro in questo while loop, per qualche motivo, riscrivendo fileContents
          ripetutamente, si perde la possibilità di fare "free" fuori dal while loop
          ********************************/
     while ((c = fgetc(in)) != EOF) {
          fileContents = appendChar(fileContents, c);
          fileContents = realloc(fileContents, strlen(fileContents)+1);
     }
     /*free(fileContents);*/
          
     /*fileContents = realloc(fileContents, fileSize(fileName)+1);*/ /* to include the '\0' terminator */
     /*fileContents[fileSize(fileName)] = '\0';*/ /* terminate the string */

     if (fclose(in)){
          printf("error closing file.\n");
          exit(-1);}
     /*else{
          printf("fclose success!\n");}*/
     return fileContents;}
     
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
     
#ifdef __cplusplus
}
#endif

#endif /* __BAOFILES_H__ */

/*
     #define init_charPointer(charpointer) \
     char* charpointer;\
     charpointer = malloc(0);\
     *charpointer = '\0'


     int main(){

// char* my;
// *my = '\0';
// my = malloc(sizeof("ci")+2);
// strcpy(my, "ci");

init_charPointer(trackingFileName);

trackingFileName = fileRead(".beacon");

// trackingFileName = fileRead("test.txt");

printf("%s\n", trackingFileName);

free(trackingFileName);




       return 0;
 }*/