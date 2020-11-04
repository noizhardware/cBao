#ifndef _NYX_H_
     #ifdef __cplusplus
     extern "C" {
     #endif
#define _NYX_H_

#include "ardumicro.h"

#define BUZZER A5 /* pin where the piezo buzzer is connected */
#define VIBRO A4 /* pin where the vibro is connected */

/* pins where the PS/2 keyboard is connected */
#define DATAPIN A3 /* can be any pin */
#define IRQPIN 2 /* (clock), must me an interrupt pin, on Arduino Micro: TX, RX, 2, 3 */
  

#define MORSE_FREQ 108
#define MORSE_UNIT 35
#define DOT MORSE_UNIT
#define DASH MORSE_UNIT * 3
#define PAUSE_BETWEEN_SIGNS MORSE_UNIT
#define PAUSE_BETWEEN_LETTERS MORSE_UNIT * 3
#define PAUSE_BETWEEN_WORDS MORSE_UNIT * 7


uint16_t DBL(uint16_t x, unsigned char t){
     uint16_t out = 0;
     for(unsigned char i = 0; i<t; i++){
          out += x * 2;} 
     return out;}

#define STARTUP_SOUND \
     tone(BUZZER, MORSE_FREQ, DASH);\
     delay(DASH + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, MORSE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_LETTERS);\
     tone(BUZZER, MORSE_FREQ, DASH);\
     delay(DASH + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, MORSE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, MORSE_FREQ, DASH);\
     delay(DASH + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, MORSE_FREQ, DASH);\
     delay(DASH + PAUSE_BETWEEN_LETTERS);\
     tone(BUZZER, 1000, DASH);\
     delay(DASH + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, 1200, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, 600, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, 900, DASH);\
     delay(100);\
     tone(BUZZER, 1200, DOT);\
     delay(100);\
     tone(BUZZER, 2400, DASH);

#define WRYTE_STARTUP_SOUND \
     tone(BUZZER, MORSE_FREQ*4, DOT);
     
#define WRYTE_FREQ MORSE_FREQ*8

#define BEEP_WRYTE_EEPROM_ONE \
     tone(BUZZER, WRYTE_FREQ, DOT);
#define BEEP_WRYTE_EEPROM_TWO \
     tone(BUZZER, WRYTE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, WRYTE_FREQ, DOT);
#define BEEP_WRYTE_EEPROM_THREE \
     tone(BUZZER, WRYTE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, WRYTE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(BUZZER, WRYTE_FREQ, DOT);
               #define BEEP_WRYTE_EEPROM_FOUR_A \
                    tone(BUZZER, WRYTE_FREQ, DASH*3);
               #define BEEP_WRYTE_EEPROM_FOUR_B \
                    tone(BUZZER, WRYTE_FREQ, DASH*3);\
                    delay(DASH*3 + PAUSE_BETWEEN_SIGNS);\
                    tone(BUZZER, WRYTE_FREQ, DOT);
               #define BEEP_WRYTE_EEPROM_FOUR_C \
                    tone(BUZZER, WRYTE_FREQ, DASH*3);\
                    delay(DASH*3 + PAUSE_BETWEEN_SIGNS);\
                    tone(BUZZER, WRYTE_FREQ, DOT);\
                    delay(DOT + PAUSE_BETWEEN_SIGNS);\
                    tone(BUZZER, WRYTE_FREQ, DOT);
     #define BEEP_WRYTE_EEPROM_FULL \
          tone(BUZZER, WRYTE_FREQ*2, DASH*4);
     
#define ERROR_SOUND \
     tone(BUZZER, MORSE_FREQ*10, DASH); \
     delay(DASH); \
     tone(BUZZER, MORSE_FREQ*20, DASH);

     #ifdef __cplusplus
     }
     #endif
#endif /* _NYX_H_ */