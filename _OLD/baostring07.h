#include <string.h>
#include <stdbool.h>
// #include <stdio.h>
 
static inline char* removeSubstr(char *inputString, char *sub, bool freeTheSource){ //if freeTheSource is TRUE, the original inputString will be freed from memory. destructive
     char *match;
     unsigned int len = strlen(sub);
     char* outputString; // new internal char*
     outputString = (char*)malloc(strlen(inputString)+1-strlen(sub)); // that's the size on the new string, if we find and remove the sub
     strcpy(outputString, inputString); // copies inputString into outputString, now they're identical
     if ((match = strstr(outputString, sub))){
          *match = '\0';
          strcat(outputString, match+len);
          if(freeTheSource){
               free(inputString);} // frees the old allocation
          return outputString;}
     else{
          free(outputString);// frees the new allocation, because it is useless in this case
          return inputString;}
     }

// takes string and removes everything after the first occurrence of the "marker" char. marker must be a single char
// the bool deleteMarker determines whether the marker is deleted as well or not
// deleteMarker TRUE >> marker gets deleted
// terminateStringOnChar(str, ':', FALSE) deletes everything after the first ':'
//if freeTheSource is TRUE, the original inputString will be freed from memory. destructive
char* terminateStringOnChar(char* inputString, char marker, bool deleteMarker, bool freeTheSource){
     char* ptr;
     char* outputString; // new internal char*
     outputString = (char*)malloc(strlen(inputString)+1); 
     strcpy(outputString, inputString); // copies inputString into outputString, now they're identical
     ptr = strchr(outputString, marker);
     if (ptr != NULL){
          ptr += !deleteMarker;
          *ptr = '\0';
          //realloc(outputString, strlen(outputString)+1-(ptr-outputString));
          if(freeTheSource){
               free(inputString);} // frees the old allocation
          return outputString;}
     else{ // not found
          free(outputString); // freeing the allocation, it was all useless :(
          return inputString;}
     }
          
// takes string and removes everything before the first occurrence of the "marker" char. marker must be a single char
// the bool deleteMarker determines whether the marker is deleted as well or not
// deleteMarker TRUE >> marker gets deleted
// clearStringUntilChar(str, ':', FALSE) deletes everything before the first ':',
char* clearStringUntilChar(char* inputString, char marker, bool deleteMarker){
     char* ptr;
     ptr = strchr(inputString, marker);
     if (ptr != NULL){
       return ptr + deleteMarker;}
       else{return inputString;}}
          
          
// takes string and removes everything after the first occurrence of the "marker" string. marker must be a string(pointer to char)
// terminateStringOnString(str, "suca ") deletes everything after the first "suca "
void terminateStringOnString(char* string, char* marker){
     char* ptr;
     ptr = strstr(string, marker);
     if (ptr != NULL){
          *ptr = '\0';}}

bool startsWith(const char* string, const char* match){
     return (strncmp(string, match, strlen(match)) == 0);}


//   int main(){
// 
// char* stri = "porcodioooo";
// 
// stri = clearStringUntilChar(stri, 'c');
// 
// printf("%s\n", stri);
// 
// 
//     return 0;
//   }