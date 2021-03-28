#ifndef _BUZZ_H_
#define _BUZZ_H_
     #ifdef __cplusplus
     extern "C" {
     #endif

static inline void buzzInit(unsigned char buzzPin);
static inline void vibDash(unsigned int ms);


unsigned char buzzerPin;

static inline void buzzInit(unsigned char buzzPin){
     buzzerPin = buzzPin;
     pinMode(buzzPin, OUTPUT);
     digitalWrite(buzzPin, 0);}

static inline void buzzDash(unsigned int ms){
     digitalWrite(buzzerPin, 1);
     delay(ms);
     digitalWrite(buzzerPin, 0);}

     #ifdef __cplusplus
     }
     #endif
#endif /* _BUZZ_H_ */