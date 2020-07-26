#ifndef __BAOTIME_H__
#define __BAOTIME_H__

/* 202007240242 */

/*
 * C90 compliant
 * need to use -Wno-long-long
 */

#include <windows.h>

#ifdef WIN32
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h> /* for nanosleep */
#else
#include <unistd.h> /* for usleep */
#endif /* OS switch */
/**********************************/

#include <stdbool.h>
#include <math.h>

/* gettimeofday for WINDOWS */
#ifdef WIN32
#include <stdint.h>
/* already defined in c:\mingw\include\sys\time.h:55:8 */
/*typedef struct timeval{*/
/*     time_t     tv_sec;*/    /* seconds */
/*     useconds_t tv_usec;*/   /* microseconds */
/*} timeval;*/
typedef struct timezone{
     int tz_minuteswest;     /* minutes west of Greenwich */
     int tz_dsttime;         /* type of DST correction */
} timezone;

int gettimeofday(struct timeval * tp, struct timezone * tzp __attribute__((unused))) /*  __attribute__((unused)) is a GCC flag to suppress the -Wunused-parameter for this variable */
{
    /* Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
     * This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
     * until 00:00:00 January 1, 1970 */
    
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL); /* this is C99 -- cacca -- need to use -Wno-long-long to compile C90 */

    SYSTEMTIME  system_time; /* for .wMilliseconds >> 16bits */
    FILETIME    file_time/*, EPOCHdiff*/; /* for dwLowDateTime and dwHighDateTime >> unsigned 32bits */
    uint64_t    time;

    GetSystemTime( &system_time ); /* system time can be retrieved only in SYSTEMTIME format (year,month,day....) */
    SystemTimeToFileTime( &system_time, &file_time ); /* here is converted in FILETIME format (number of 100-nanosecond intervals since January 1, 1601 (UTC)) */
    
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;
    
    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}
#endif
/**********************************/

/* globals: */
struct timeval __BAOTIME_H__stop, __BAOTIME_H__startTime, __BAOTIME_H__stopTime, __BAOTIME_H__difference, __BAOTIME_H__savedTime, __BAOTIME_H__updatedTime;
bool __BAOTIME_H__running = false;
/**********************************/




/* prototypes: */
static __inline__ float sec_to_hm(unsigned long int sec);
static __inline__ void pauseTimer();
static __inline__ void startTimer();
static __inline__ void timertoggle();
static __inline__ void resetTimer();
static __inline__ struct timeval timevalDiff(struct timeval a, struct timeval b);
static __inline__ struct timeval timevalSum(struct timeval a, struct timeval b);
static __inline__ void getTime();
static __inline__ void sleep_ms(int milliseconds);

/**********************************/

static __inline__ void sleep_ms(int milliseconds){ /* cross-platform sleep function */
     #ifdef WIN32
         Sleep(milliseconds);
     #elif _POSIX_C_SOURCE >= 199309L
         struct timespec ts;
         ts.tv_sec = milliseconds / 1000;
         ts.tv_nsec = (milliseconds % 1000) * 1000000;
         nanosleep(&ts, NULL);
     #else
         usleep(milliseconds * 1000);
     #endif
}

/* SW StopWatch functions: */

/* writes current time in __BAOTIME_H__startTime, if timer already running, do nothing */
static __inline__ void startTimer(){
     if(!__BAOTIME_H__running){
          gettimeofday(&__BAOTIME_H__startTime, NULL);
          __BAOTIME_H__running = true;}}

/* writes current time in stopTime, if timer is not running, do nothing */
static __inline__ void stopTimer(){
     if(__BAOTIME_H__running){
          gettimeofday(&__BAOTIME_H__stopTime, NULL);
          __BAOTIME_H__running = false;}}
          
static __inline__ void resetTimer(){
  __BAOTIME_H__savedTime.tv_sec = 0; __BAOTIME_H__savedTime.tv_usec = 0;
  __BAOTIME_H__difference.tv_sec = 0; __BAOTIME_H__difference.tv_usec = 0;
  __BAOTIME_H__startTime.tv_sec = 0; __BAOTIME_H__startTime.tv_usec = 0;
  __BAOTIME_H__stopTime.tv_sec = 0; __BAOTIME_H__stopTime.tv_usec = 0;
  __BAOTIME_H__running = FALSE;}
          
static __inline__ struct timeval elapsed(){
     return timevalDiff(__BAOTIME_H__stopTime, __BAOTIME_H__startTime);}


static __inline__ void pauseTimer(){
     if ((__BAOTIME_H__difference.tv_sec == 0) && (__BAOTIME_H__difference.tv_usec == 0)){
     } /* if timer never started, don't allow pause button to do anything */
     else if (__BAOTIME_H__running) {
          __BAOTIME_H__savedTime = __BAOTIME_H__difference;
          __BAOTIME_H__running = false;}
     else {
          startTimer();}} /* if the timer was already paused, when they click pause again, start the timer again */
          


static __inline__ void timertoggle(){
     if(!__BAOTIME_H__running){
         startTimer();}
     else{
         pauseTimer();}}



/* if a<b the result will be unexpected behavior -- cacca */
static __inline__ struct timeval timevalDiff(struct timeval a, struct timeval b){
     struct timeval output;
     unsigned long int totUsecDiff = (a.tv_sec*1000000+a.tv_usec)-(b.tv_sec*1000000+b.tv_usec);
     output.tv_sec = floor(totUsecDiff/1000000);
     output.tv_usec = totUsecDiff-(floor(totUsecDiff/1000000)*1000000);
     return output;}

static __inline__ struct timeval timevalSum(struct timeval a, struct timeval b){
     struct timeval output;
     output.tv_sec = a.tv_sec + b.tv_sec;
     output.tv_usec = a.tv_usec + b.tv_usec;
     return output;}

static __inline__ void getTime(){
     gettimeofday(&__BAOTIME_H__updatedTime, NULL);
     if ((__BAOTIME_H__savedTime.tv_sec >= 0) && (__BAOTIME_H__savedTime.tv_usec >= 0)){
          __BAOTIME_H__difference = timevalSum(timevalDiff(__BAOTIME_H__updatedTime, __BAOTIME_H__startTime), __BAOTIME_H__savedTime);}
     else {
          __BAOTIME_H__difference =  timevalDiff(__BAOTIME_H__updatedTime, __BAOTIME_H__startTime);}}
          
static __inline__ float sec_to_hm(unsigned long int sec){
     return floor(((float)sec / 3600)) + ((((float)sec / 3600) - floor(((float)sec / 3600))) * 0.6);}
     
#endif /* __BAOTIME_H__ */