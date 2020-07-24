#ifndef __BAOTIME_H__
#define __BAOTIME_H__
/* 202007221953 */

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

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    /* Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
     * This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
     * until 00:00:00 January 1, 1970 */
    
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL); /* this is C99 -- cacca */

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}
#endif
/**********************************/

/* globals: */
struct timeval stop, startTime, difference, savedTime, updatedTime;
bool running = false;
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
static __inline__ void pauseTimer(){
     if ((difference.tv_sec == 0) && (difference.tv_usec == 0)){
     } /* if timer never started, don't allow pause button to do anything */
     else if (running) {
          savedTime = difference;
          running = FALSE;}
     else {
          startTimer();}} /* if the timer was already paused, when they click pause again, start the timer again */
          
static __inline__ void startTimer(){
     if(!running){
          gettimeofday(&startTime, NULL);
          getTime();
          /* CURPOS(2, 2); */
          /* printw("%lu ms", startTime.tv_sec * 1000 + startTime.tv_usec); */
          running = TRUE;}
     else{
          pauseTimer();}}

static __inline__ void timertoggle(){
     if(!running){
         startTimer();}
     else{
         pauseTimer();}}

static __inline__ void resetTimer(){
  savedTime.tv_sec = 0; savedTime.tv_usec = 0;
  difference.tv_sec = 0; difference.tv_usec = 0;
  running = FALSE;}

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
     gettimeofday(&updatedTime, NULL);
     if ((savedTime.tv_sec >= 0) && (savedTime.tv_usec >= 0)){
          difference = timevalSum(timevalDiff(updatedTime, startTime), savedTime);}
     else {
          difference =  timevalDiff(updatedTime, startTime);}}
          
static __inline__ float sec_to_hm(unsigned long int sec){
     return floor(((float)sec / 3600)) + ((((float)sec / 3600) - floor(((float)sec / 3600))) * 0.6);}
     
#endif /* __BAOTIME_H__ */