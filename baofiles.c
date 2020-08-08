#include <stdio.h>
#include "baofiles.h"

/* gcc -ansi -g0 -Wall -Wextra -Wshadow -Wvla -pedantic-errors -o baofiles.exe baofiles.c */

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