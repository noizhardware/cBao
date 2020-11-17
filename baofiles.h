#ifndef __BAOFILES_H__
#define __BAOFILES_H__

/* 2020i18-1842 */

/* ANSI C compliant <3 */

/* TODO:
* get rid of mallocs and use fixed-size buffers???
* append to file
* prepend to file
* all branchless
*/

/* #include <stdio.h>*/
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* cacca -- direntwin has an error - disabling it for win for now... */
#ifndef __WIN32__
     #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
          #include "direntWin.h"
     #endif
#endif

#ifdef __linux__
  #include <dirent.h>
#endif

#include "baostring.h"

#ifdef __cplusplus
extern "C" {
#endif

/* prototypes */
static __inline__ char* fileRead(char* fileName);
static __inline__ long int fileSize(char* filename);
static __inline__ bool fileWrite(char* fileName, char* stuffToWrite);
static __inline__ char** fileToLines(char* fileName, unsigned int maxLineSize, unsigned int maxLinesInFile);

static __inline__ void fileRead_nomalloc(char* file, char* buf);
/*static __inline__ void fileToLines_nomalloc(char* fileName, char** linesBuf, unsigned int maxLineSize, unsigned int maxLinesInFile);*/

/* prototypes END */

static __inline__ void fileRead_nomalloc(char* file, char* buf){
     FILE* fp;
     long fileSize;
     /*char* fileContents;*/

     fp = fopen ( file , "rb" );
     if(!fp){
          perror(file);
          exit(1);}

     /* this block writes the size of the file in fileSize */
     fseek( fp , 0L , SEEK_END);
     fileSize = ftell( fp );
     rewind( fp );

     /* let's just NOT check if the buffer size is enough LoL */
     /*if(ARRAYELEMS(buf)<fileSize+1){
          fclose(fp);
          fputs("buffer is too small",stderr);
          exit(1);}*/

     /* copy the file into the buffer */
     if(fread(buf, fileSize, 1, fp) != 1){
          fclose(fp);
          fputs("entire read fails",stderr);
          exit(1);}

     /* close the file */
     fclose(fp);}

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
     FILE* fptr = NULL;
     int i = 0;
     fptr = fopen(fileName, "r");
     while(fgets(line[i], maxLineSize, fptr)){
          line[i][strlen(line[i]) - 1] = '\0';
          i++;}
     line[i][0]=(char)EOF;
     fclose(fptr);
     return line;}

/* (file)>>(array of lines) cacca non funzia ncazzo */
/*static __inline__ void fileToLines_nomalloc(char* fileName, char* linesBuf[], unsigned int maxLineSize, unsigned int maxLinesInFile){
     FILE* fptr = NULL;
     unsigned int line = 0;
     unsigned int charac = 0;
     char c;
     char* test = "";
     fptr = fopen(fileName, "r");
     printf("file opened...\n");
     for(line=0;line<maxLinesInFile;line++){
          for(charac=0;charac<maxLineSize;charac++){
               c=fgetc(fptr);
               if(feof(fptr)){ break;}
               *linesBuf[line][charac]=c;
               if(c=='\0'){ break;}
          }
     }

     fclose(fptr);}*/

     /* dirlist - cacca - disabled for win for now */
#ifndef __WIN32__
static __inline__ char** dirList(char* directory, unsigned int maxFilesInDir, unsigned int maxFilenameLen){
    char** dirList = makeStringTable(maxFilesInDir, maxFilenameLen);

     DIR *d;
     struct dirent *dir;
     unsigned int arrIndex = 0;

     d = opendir(directory);
         if(d){
             while (((dir = readdir(d)) != NULL)&&(arrIndex<(maxFilenameLen-1))){ /* the -1 is to leave space for the EOF terminator */
               /*printf("arrIndex: %d\n", arrIndex);*/
                 sprintf(dirList[arrIndex], "%s", dir->d_name);
                 /*dirList[arrIndex][0] = 0;*/
                 arrIndex++;}
             closedir(d);
             sprintf(dirList[arrIndex], "%c", EOF);}
        else{
          fprintf(stderr, "Cannot find specified directory.\n");}
    return dirList;
}
#endif

#ifdef __cplusplus
}
#endif
#endif /* __BAOFILES_H__ */
