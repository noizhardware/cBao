#ifndef _FLOOW_H_
#define _FLOOW_H_
/* 202007241415 */

#ifdef WIN32
#include <windows.h>
 
unsigned char* getFloowDate();

/***************************************/
 
unsigned char* getFloowDate(){
     unsigned char* floowOut;
     floowOut = (char*) malloc(8);
     /* *charpointer = '\0' */
     SYSTEMTIME local;
     GetLocalTime(&local);
     /* strcpy(floowOut, local.wYear) */
     itoa(local.wYear,floowOut,10); /* 10 means "base 10" LOL */
     unsigned char floowMonths[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'w'};
     unsigned char floowMonth = floowMonths[local.wMonth-1];
     *(floowOut+4) = floowMonth;
     if(local.wDay<10){
          itoa(0,floowOut+5,10);
          itoa(local.wDay,floowOut+6,10);}
     else{
          itoa(local.wDay,floowOut+5,10);}
     return floowOut;}






#endif

/*
     abc pmg jh xyzw
     abc pqr st wxyz
     abc kms tu wxyz
*/
 
/*
#include <stdio.h>
int main()
{

    SYSTEMTIME st, lt;

    GetSystemTime(&st);
    GetLocalTime(&lt);
    printf("The system time is: %02d:%02d\n", st.wHour, st.wMinute);
    printf(" The local time is: %02d:%02d\n", lt.wHour, lt.wMinute);
    printf("Today is: %d-%02d-%02d\n", lt.wYear, lt.wMonth, lt.wDay);
    printf("floow date: %s\n", getFloowDate());
    return 0;
}
*/
#endif /* _FLOOW_H_ */