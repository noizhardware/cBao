#include <stdio.h>
#include "baofiles.h"


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
     #include "direntWin.h"
#endif

#ifdef __linux__
  #include <dirent.h>
#endif

/* 202008172159 */
/* 2020h17-2159 */

int main(){
     int loopTable = 0;
     char** lines;

     DIR *d;
     struct dirent *dir;
     #define MAX_DIR_QTY 128
     #define MAX_DIR_NAMELEN 32
     char dirArray[MAX_DIR_QTY][MAX_DIR_NAMELEN];
     unsigned int dirArrIndex;


     lines = fileToLines("test.txt", 256, 256);


     printf("==fileToLines:\n");

     while(lines[loopTable][0]!=EOF){
          printf("%s\n", lines[loopTable]);
          loopTable++;}

     freeStringTable(lines);


/* dirlist */

printf("==dirlist:\n");
d = opendir(".");
    if(d){
      dirArrIndex = 0;
        while ((dir = readdir(d)) != NULL){
            sprintf(dirArray[dirArrIndex], "%s", dir->d_name);
            dirArrIndex++;}
        closedir(d);
        sprintf(dirArray[dirArrIndex], "%c", EOF);
      }

    dirArrIndex = 0;
    while(dirArray[dirArrIndex][0]!=EOF){
      printf("%s\n", dirArray[dirArrIndex]);
      dirArrIndex++;
    }

     return 0;}
