#include <stdio.h>
#include "baofiles.h"

/* 202008081633 */

int main(){
     int loopTable = 0;
     char** lines;
     lines = fileToLines("test.txt");
     
     printf("==fileToLines:\n");
     
     while(lines[loopTable][0]!='\0'){
     printf("%s\n", lines[loopTable]);
     loopTable++;}
     
     freeStringTable(lines);
     
     return 0;}