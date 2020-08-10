#include <stdio.h>
#include "baofiles.h"

/* 202008081633 */

int main(){
     int loopTable = 0;
     char** lines;
     lines = fileToLines("test.txt", 256, 256);

     printf("==fileToLines:\n");

     while(lines[loopTable][0]!=EOF){
          printf("%s\n", lines[loopTable]);
          loopTable++;}

     freeStringTable(lines);

     return 0;}
