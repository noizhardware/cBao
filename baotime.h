#ifndef _BAOTIME_H_
#define _BAOTIME_H_

#define BAOTIME_VERSION "2023k15-2138"

/*** TODO
 * need to use -Wno-long-long >> define BAOTIME_LONGLONG_ENABLED if you do so
 * you can use
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wlong-long"
		your code here
	#pragma GCC diagnostic pop

*/


/*** INCLUDES */
#ifndef _POSIX_C_SOURCE
     #define _POSIX_C_SOURCE 199309L
#endif

     #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
          #include <time.h>
          #include <windows.h>
     #endif

     #ifdef __linux__
          #include <sys/time.h>
     #endif

     #ifdef WIN32
     #elif _POSIX_C_SOURCE >= 199309L
     #include <time.h> /* for nanosleep */
     #else
     #include <unistd.h> /* for usleep */
     #endif /* OS switch */
     /**********************************/

     #include <stdbool.h>
     #include <math.h>
     #include "baostring.h"

     /* gettimeofday for WINDOWS */
     #ifdef WIN32
     #include <stdint.h>
     /* already defined in c:\mingw\include\sys\time.h:55:8 */
     /*typedef struct timeval{*/
     /*     time_t     tv_sec;*/    /* seconds */
     /*     useconds_t tv_usec;*/   /* microseconds */
     /*} timeval;*/

     /* already defined in c:\mingw\include\time.h:382:22 */
     /*typedef struct timezone{*/
          /*int tz_minuteswest; */    /* minutes west of Greenwich */
          /*int tz_dsttime;  */       /* type of DST correction */
     /*} timezone;*/
     
/* INCLUDES end. */

#ifdef __cplusplus
     extern "C" {
#endif

/*** DEFINES */
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
struct timeval __BAOTIME_H__stop, __BAOTIME_H__startTime, __BAOTIME_H__stopTime, __BAOTIME_H__difference, __BAOTIME_H__savedTime, __BAOTIME_H__updatedTime, __BAOTIME_H__splitTime;
bool __BAOTIME_H__running = false;

     struct timespec baotime_start, baotime_end;
     double baotime_time_spent;
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
     static __inline__ float sec_to_hm(unsigned long int sec);
     static __inline__ unsigned long int hm_to_sec(float hm);

     #ifdef BAOTIME_LONGLONG_ENABLED
          static __inline__ void pauseTimer();
          static __inline__ void startTimer();
          static __inline__ void splitTimer();
          static __inline__ void getTime();
          static __inline__ void stopTimer();
          static __inline__ void timertoggle();
     #endif /* #ifdef BAOTIME_LONGLONG_ENABLED */
     
     #ifndef BAOTIME_LONGLONG_ENABLED
          static __inline__ void startTimer();
          static __inline__ double getTimerNs();
          static __inline__ double getTimerMs();
     #endif

     static __inline__ void resetTimer();
     static __inline__ struct timeval timevalDiff(struct timeval a, struct timeval b);
     static __inline__ struct timeval timevalSum(struct timeval a, struct timeval b);
     static __inline__ void sleep_ms(int milliseconds);
     static __inline__ struct timeval elapsed();
     static __inline__ struct timeval getSplit();
     static __inline__ float hm_add(float a, float b);
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */

#ifndef BAOTIME_LONGLONG_ENABLED
     static __inline__ void startTimer(){
          clock_gettime(CLOCK_REALTIME, &baotime_start);
     }
     static __inline__ double getTimerNs(){
          clock_gettime(CLOCK_REALTIME, &baotime_end);
          return ((baotime_end.tv_sec - baotime_start.tv_sec) * 1000000000) +
                         (baotime_end.tv_nsec - baotime_start.tv_nsec); /* in nanoseconds */
     }
     static __inline__ double getTimerMs(){
          clock_gettime(CLOCK_REALTIME, &baotime_end);
          return
               ((baotime_end.tv_sec - baotime_start.tv_sec) * 1000) +
               ((baotime_end.tv_nsec - baotime_start.tv_nsec) / 1000000); /* in milliseconds */
     }
#endif

#ifdef BAOTIME_LONGLONG_ENABLED
     struct timezone;
int gettimeofday(struct timeval* tp, struct timezone* tzp){
    /* Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
     * This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
     * until 00:00:00 January 1, 1970 */

    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL); /* this is C99 -- cacca -- need to use -Wno-long-long to compile C90 */

    SYSTEMTIME  system_time; /* for .wMilliseconds >> 16bits */
    FILETIME    file_time/*, EPOCHdiff*/; /* for dwLowDateTime and dwHighDateTime >> unsigned 32bits */
    uint64_t    time;
    
    (void)tzp;

    GetSystemTime( &system_time ); /* system time can be retrieved only in SYSTEMTIME format (year,month,day....) mSec precision*/
    SystemTimeToFileTime( &system_time, &file_time ); /* here is converted in FILETIME format (number of 100-nanosecond intervals since January 1, 1601 (UTC)) */

    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000); /* will ALWAYS have 3 non-information-carrying trailing zeroes */
    return 0;
}
#endif /* #ifdef BAOTIME_LONGLONG_ENABLED */
#endif /* #ifdef WIN32 */
/**********************************/



static __inline__ float hm_add(float a, float b){
     return sec_to_hm(hm_to_sec(a)+hm_to_sec(b));}

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
#ifdef BAOTIME_LONGLONG_ENABLED
/* writes current time in __BAOTIME_H__startTime, if timer already running, it gets reset and started */
static __inline__ void startTimer(){
          gettimeofday(&__BAOTIME_H__startTime, NULL);
          __BAOTIME_H__running = true;}

/* writes current time in stopTime, if timer is not running, do nothing */
static __inline__ void stopTimer(){
     if(__BAOTIME_H__running){
          gettimeofday(&__BAOTIME_H__stopTime, NULL);
          __BAOTIME_H__running = false;}}

/* writes current time in splitTime, doesn't stop the timer, if timer is not running, do nothing */
static __inline__ void splitTimer(){
     if(__BAOTIME_H__running){
          gettimeofday(&__BAOTIME_H__splitTime, NULL);}}
#endif /* #ifdef BAOTIME_LONGLONG_ENABLED */
          
static __inline__ void resetTimer(){
  __BAOTIME_H__savedTime.tv_sec = 0; __BAOTIME_H__savedTime.tv_usec = 0;
  __BAOTIME_H__difference.tv_sec = 0; __BAOTIME_H__difference.tv_usec = 0;
  __BAOTIME_H__startTime.tv_sec = 0; __BAOTIME_H__startTime.tv_usec = 0;
  __BAOTIME_H__stopTime.tv_sec = 0; __BAOTIME_H__stopTime.tv_usec = 0;
  __BAOTIME_H__running = false;}

static __inline__ struct timeval elapsed(){
     return timevalDiff(__BAOTIME_H__stopTime, __BAOTIME_H__startTime);}
     
static __inline__ struct timeval getSplit(){
     return timevalDiff(__BAOTIME_H__splitTime, __BAOTIME_H__startTime);}

#ifdef BAOTIME_LONGLONG_ENABLED
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
#endif /* #ifdef BAOTIME_LONGLONG_ENABLED */



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
     
#ifdef BAOTIME_LONGLONG_ENABLED
static __inline__ void getTime(){
     gettimeofday(&__BAOTIME_H__updatedTime, NULL);
     if ((__BAOTIME_H__savedTime.tv_sec >= 0) && (__BAOTIME_H__savedTime.tv_usec >= 0)){
          __BAOTIME_H__difference = timevalSum(timevalDiff(__BAOTIME_H__updatedTime, __BAOTIME_H__startTime), __BAOTIME_H__savedTime);}
     else {
          __BAOTIME_H__difference =  timevalDiff(__BAOTIME_H__updatedTime, __BAOTIME_H__startTime);}}
#endif /* #ifdef BAOTIME_LONGLONG_ENABLED */

static __inline__ float sec_to_hm(unsigned long int sec){
     return floor(((float)sec / 3600)) + ((((float)sec / 3600) - floor(((float)sec / 3600))) * 0.6);}
static __inline__ unsigned long int hm_to_sec(float hm){
     return (unsigned long int)(floor(hm)*3600) + (unsigned long int)(fmod(hm, 1.0)*6000.f);}

static __inline__ uint16_t getYear(){
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     return (uint16_t)(tm.tm_year + 1900);}

static __inline__ uint16_t getMonth(){
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     return (uint16_t)(tm.tm_mon + 1);}

static __inline__ uint16_t getDay(){
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     return (uint16_t)(tm.tm_mday);}

static __inline__ uint16_t getHour(){
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     return (uint16_t)(tm.tm_hour);}
static __inline__ uint16_t getMin(){
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     return (uint16_t)(tm.tm_min);}
static __inline__ uint16_t getSec(){
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     return (uint16_t)(tm.tm_sec);}

/*static __inline__ void getFloowDate(char* storage){
     char* out;
     sprintf(out, "%d", getYear());*/
     /*out[7]='\0';*/
     /*return out;}*/
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
     }
#endif
#endif /* _BAOTIME_H_ */
