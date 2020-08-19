#include <stdio.h>
#include "baofiles.h"

/* 2020h18-1600 */

#define MAX_FILES_IN_DIR 128
#define MAX_FILENAME_LEN 32

int main(){
     unsigned int i = 0;
     char** lines;

     char** dirArray;

/* fileToLines */
     lines = fileToLines("test.txt", 256, 256);
     printf("==fileToLines:\n");
     while(lines[i][0]!=EOF){
          printf("%s\n", lines[i]);
          i++;}
     freeStringTable(lines);


/* dirlist */
printf("==dirlist:\n");

dirArray = dirList("./libraries", MAX_FILES_IN_DIR, MAX_FILENAME_LEN);

         i = 0;
         while(dirArray[i][0]!=EOF){
           printf("%s\n", dirArray[i]);
           i++;}
           freeStringTable(dirArray);



     return 0;}
