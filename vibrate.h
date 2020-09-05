#ifndef _VIBRATE_H_
     #ifdef __cplusplus
     extern "C" {
     #endif
#define _VIBRATE_H_

static inline void vibInit(unsigned char vibPin);
static inline void vibDash(unsigned int ms);


unsigned char vibroPin;

static inline void vibInit(unsigned char vibPin){
     vibroPin = vibPin;}

static inline void vibDash(unsigned int ms){
     digitalWrite(vibroPin, 1);
     delay(ms);
     digitalWrite(vibroPin, 0);}

     #ifdef __cplusplus
     }
     #endif
#endif /* _VIBRATE_H_ */