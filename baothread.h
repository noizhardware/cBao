#ifndef _BAOTHREAD_H_
#define _BAOTHREAD_H_

/* 2021a28-2253 */

typedef struct cycle_t_{
     uint16_t len; /* cycle length */
     uint32_t last; /* buffer for last recorded status */
} cycle_t;

bool cycleCheck(cycle_t* cycle){ /* branchless protothreading */
     uint32_t currentMillis = millis(); /* overflows every 49.7 days - 136 years if I keep track of seconds on another int32 and manage the overflow */
     bool cycleIsOver = (currentMillis - cycle->last >= cycle->len); /* has (cycleLength) milliseconds passed since last reading? */
     cycle->last = (currentMillis * cycleIsOver) + ((cycle->last)*(!cycleIsOver)); /* if yes, update lastMillis with current time, if not, lastMillis remains unchanged */
     return cycleIsOver;} /* retuns whether the (cycleLength) time has passed or not */
bool microCheck(cycle_t* cycle){ /* usec resolution */
     uint32_t currentUsec = micros(); /* overflows every 71.58 minutes */
     bool cycleIsOver = (currentUsec - cycle->last >= cycle->len); /* has (cycleLength) microseconds passed since last reading? */
     cycle->last = (currentUsec * cycleIsOver) + ((cycle->last)*(!cycleIsOver)); /* if yes, update lastUsec with current time, if not, lastUsec remains unchanged */
     return cycleIsOver;} /* retuns whether the (cycleLength) time has passed or not */

#endif /* _BAOTHREAD_H_ */