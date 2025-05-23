// #include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* appendChar(char* inputString, char ch);
char* fileRead(char* fileName);
long int fileSize(char* filename);
// TODO: static inline all!!
// use realloc() instead of malloc()

char* appendChar(char* inputString, char ch) {
  
      //  printf("newsiz: %ld\n", sizeof(inputString)+2);
     char* outputString; // new internal char*
     outputString = (char*)malloc(strlen(inputString)+2); // allocate space so it can contain inputString, +1 for the string terminator '\0', and another +1 for the new char that's going to be added
     //*outputString = '\0';// write a terminator in the first byte, so it can be recognized as string (of size 0, for now)
     strcpy(outputString, inputString); // copies inputString into outputString, now they're identical
      //  printf("copied: %s\n", outputString);
      //  printf("new ch: %c\n", ch);
     unsigned int len = strlen(outputString); // size, without terminator
     outputString[len] = ch;// overwrites it with the new char
     outputString[len+1] = '\0';//writes a new terminator
      //  printf("result: %s\n\n", outputString);
     return outputString;}

char* fileRead(char* fileName){
     FILE* in = fopen(fileName, "r");
     int c;
     char* fileContents; // new internal char*
    //  printf("%ld\n", fileSize(fileName)+1);
     fileContents = (char*)malloc(fileSize(fileName)+1);
     *fileContents = '\0';
     while ((c = fgetc(in)) != EOF) {
          fileContents = appendChar(fileContents, c);}
          //printf("%s\n", fileContents);
          fileContents[fileSize(fileName)] = '\0';
     fclose(in);
     return fileContents;}

     long int fileSize(char* filename){ // returns size in bytes, NOT counting the EOF byte  
     FILE* in = fopen(filename, "r");
     fseek(in, 0L, SEEK_END);
     long int size = ftell(in);
     fclose(in);
     return size;}



// 
//      #define init_charPointer(charpointer) \
//      char* charpointer;\
//      charpointer = (char*) malloc(0);\
//      *charpointer = '\0'
// 
// 
//      int main(){
// 
// // char* my;
// // *my = '\0';
// // my = (char*)malloc(sizeof("ci")+2);
// // strcpy(my, "ci");
// 
// init_charPointer(trackingFileName);
// 
// trackingFileName = fileRead(".beacon");
// 
// // trackingFileName = fileRead("test.txt");
// 
// printf("%s\n", trackingFileName);
// 
// free(trackingFileName);
// 
// 
// 
// 
//        return 0;
//      }