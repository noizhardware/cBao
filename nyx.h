#ifndef _NYX_H_
     #ifdef __cplusplus
     extern "C" {
     #endif
#define _NYX_H_

#define PIEZO 2

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
     tone(PIEZO, MORSE_FREQ, DASH);\
     delay(DASH + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, MORSE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_LETTERS);\
     tone(PIEZO, MORSE_FREQ, DASH);\
     delay(DASH + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, MORSE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, MORSE_FREQ, DASH);\
     delay(DASH + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, MORSE_FREQ, DASH);\
     delay(DASH + PAUSE_BETWEEN_LETTERS);\
     tone(PIEZO, 1000, DASH);\
     delay(DASH + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, 1200, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, 600, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, 900, DASH);\
     delay(100);\
     tone(PIEZO, 1200, DOT);\
     delay(100);\
     tone(PIEZO, 2400, DASH);

#define WRYTE_STARTUP_SOUND \
     tone(PIEZO, MORSE_FREQ*4, DOT);
     
#define WRYTE_FREQ MORSE_FREQ*8

#define BEEP_WRYTE_EEPROM_ONE \
     tone(PIEZO, WRYTE_FREQ, DOT);
#define BEEP_WRYTE_EEPROM_TWO \
     tone(PIEZO, WRYTE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, WRYTE_FREQ, DOT);
#define BEEP_WRYTE_EEPROM_THREE \
     tone(PIEZO, WRYTE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, WRYTE_FREQ, DOT);\
     delay(DOT + PAUSE_BETWEEN_SIGNS);\
     tone(PIEZO, WRYTE_FREQ, DOT);
#define BEEP_WRYTE_EEPROM_FOUR \
     tone(PIEZO, WRYTE_FREQ, DASH*2);
#define BEEP_WRYTE_EEPROM_FULL \
     tone(PIEZO, WRYTE_FREQ*2, DASH*2);
     
#define ERROR_SOUND \
     tone(PIEZO, MORSE_FREQ*10, DASH);
  
// pins where the PS/2 keyboard is connected
#define DATAPIN 4
#define IRQPIN  3
  
#define VIBRO 7 // pin where the vibro is connected

     #ifdef __cplusplus
     }
     #endif
#endif /* _NYX_H_ */