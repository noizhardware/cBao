#ifndef _NYX_HENRIK_H_
#define _NYX_HENRIK_H_

/* v2020j27-2136 */
/* "henrik" add-on board for nyx hardware bindings */

/* TODO:

* live mode: qwert keys at as gates for channels
  - extra functions:
    + invert (always ON >> press >> momentarily OFF)
    + "arpeggio" : trigger a pattern instead of an on-off
    
* branchlessify, where possible
*/

/*manual:
- ESC + [F1..F5] to select a channel
- ESC + (Tab or \) to cycle selection
*/

#include "R:/s/c/i/ardumicro.h"
#include "R:/s/c/i/nyx.h"
#include "R:/s/c/i/baoardu.h"

#define MJ_1 3
#define LED_1 4
     #define MJ_2 5
     #define LED_2 6
          #define MJ_3 7
          #define LED_3 8
               #define MJ_4 9
               #define LED_4 10
                    #define MJ_5 11
                    #define LED_5 12
#define LED_ERROR_RED RX
#define LED_ERROR_GREEN TX

#define FRAMERATE 75 /* Hz */
#define FRAMELENGTH 1000/FRAMERATE /* milliseconds */

unsigned long keyboard_lastMillis = 0; 

unsigned long MJ_1_lastMillis = 0;
unsigned long LED_1_lastMillis = 0;
     unsigned long MJ_2_lastMillis = 0;
     unsigned long LED_2_lastMillis = 0;
          unsigned long MJ_3_lastMillis = 0;
          unsigned long LED_3_lastMillis = 0;
               unsigned long MJ_4_lastMillis = 0;
               unsigned long LED_4_lastMillis = 0;
                    unsigned long MJ_5_lastMillis = 0;
                    unsigned long LED_5_lastMillis = 0;
unsigned long LED_ERROR_RED_lastMillis = 0;
unsigned long LED_ERROR_GREEN_lastMillis = 0;

bool MJ_1_state = LOW;
bool LED_1_state = LOW;
     bool MJ_2_state = LOW;
     bool LED_2_state = LOW;
          bool MJ_3_state = LOW;
          bool LED_3_state = LOW;
               bool MJ_4_state = LOW;
               bool LED_4_state = LOW;
                    bool MJ_5_state = LOW;
                    bool LED_5_state = LOW;
bool LED_ERROR_RED_state = LOW;
bool LED_ERROR_GREEN_state = LOW;

float MJ_1_freq = 1;
float MJ_2_freq = 1.1;
float MJ_3_freq = 1.2;
float MJ_4_freq = 1.3;
float MJ_5_freq = 1.7;
float max_freq = 250; /* mi pare sia il limite dopo il quale si impasta e fa robe strane, TODO fare che sia ridefinibile in console mode */
float min_freq = 0.025; /* wavelength = 40seconds */

uint8_t MJ_1_duty = 25;
uint8_t MJ_2_duty = 30;
uint8_t MJ_3_duty = 50;
uint8_t MJ_4_duty = 75;
uint8_t MJ_5_duty = 90;
uint8_t min_duty = 0; /* TODO: fare che siano ridefinibili */
uint8_t max_duty = 100;


uint8_t selected_MJ = MJ_1; /* initialized to MJ_1 */

#define MJ 1
#define SEL 2
uint8_t leds_function = MJ;

#define NONE 0
#define SELECTING 1
#define A 2
#define S 3
#define D 4
#define W 5
#define X 6
#define CONSOLE 7
uint8_t menu_state = NONE;

/* increments */
float freq_fine = .5f;
float freq_normal = 1.f;
float freq_coarse = 10.f;
     uint8_t duty_fine = 1.f;
     uint8_t duty_normal = 5.f;
     uint8_t duty_coarse = 10.f;




static __inline__ void LED_ERROR_RED_thread(){
     if(cycleCheck(&LED_ERROR_RED_lastMillis, FRAMELENGTH)){
          dw(LED_ERROR_RED, LED_ERROR_RED_state);}}
static __inline__ void LED_ERROR_GREEN_thread(){
     if(cycleCheck(&LED_ERROR_GREEN_lastMillis, FRAMELENGTH)){
          dw(LED_ERROR_GREEN, LED_ERROR_GREEN_state);}}

static __inline__ uint8_t led_mj(uint8_t led){ /* given a LED name, returns the corresponding MJ name */
     return    (led==LED_1)*MJ_1 +
               (led==LED_2)*MJ_2 +
               (led==LED_3)*MJ_3 +
               (led==LED_4)*MJ_4 +
               (led==LED_5)*MJ_5;}

static __inline__ float* mj_freq(uint8_t mj){ /* given a MJ name, returns the corresponding MJ_freq pointer */
     /* all float pointers are casted to uint16(that's the size of a float pointer), so I can multiply them by a bool, sum them all, and then cast back to a float pointer */
     return    (float*)((mj==MJ_1)*((uint16_t)(&MJ_1_freq))+
               (mj==MJ_2)*((uint16_t)(&MJ_2_freq)) +
               (mj==MJ_3)*((uint16_t)(&MJ_3_freq)) +
               (mj==MJ_4)*((uint16_t)(&MJ_4_freq)) +
               (mj==MJ_5)*((uint16_t)(&MJ_5_freq)));}
static __inline__ uint8_t* mj_duty(uint8_t mj){ /* given a MJ name, returns the corresponding MJ_duty pointer */
     /* all uint8 pointers are casted to uint16(that's the size of a uint8 pointer), so I can multiply them by a bool, sum them all, and then cast back to a uint8 pointer */
     return    (uint8_t*)((mj==MJ_1)*((uint16_t)(&MJ_1_duty))+
               (mj==MJ_2)*((uint16_t)(&MJ_2_duty)) +
               (mj==MJ_3)*((uint16_t)(&MJ_3_duty)) +
               (mj==MJ_4)*((uint16_t)(&MJ_4_duty)) +
               (mj==MJ_5)*((uint16_t)(&MJ_5_duty)));}
               
static __inline__ bool isSelected(uint8_t mj){
     return mj==selected_MJ;}

static __inline__ bool MJstate(uint8_t mj){ /* returns current state of a MJ */
     return    (mj==MJ_1)*MJ_1_state +
               (mj==MJ_2)*MJ_2_state +
               (mj==MJ_3)*MJ_3_state +
               (mj==MJ_4)*MJ_4_state +
               (mj==MJ_5)*MJ_5_state;}
          
static __inline__ void LED_output_thread(uint8_t led, uint32_t* last, bool* state){
     if(cycleCheck(last, FRAMELENGTH)){
          *state =  (leds_function == MJ)*MJstate(led_mj(led)) + /* mirror its MJ counterpart */
                    (leds_function == SEL)*isSelected(led_mj(led)); /* display currently selected channel */
          dw(led, *state);}}          

static __inline__ void output_thread(uint8_t output, uint32_t* last, float* freq, uint8_t* duty, bool* state){
     uint16_t cycle = (uint16_t)(1000.f / (*freq)); /* max 65.535 seconds */
     uint16_t cycleHigh = (uint16_t)(cycle * ((float)*duty / 100.f)); /* in milliseconds */
     uint32_t now = millis();
     bool cond = (now - *last >= cycle); /* has the WHOLE cycle passed since last reading? */
     
     // #ifdef DEBUG
     //      Serial.print("output ");
     //      Serial.print(output);
     //      Serial.print(" cycle: ");
     //      Serial.print(cycle);
     //      Serial.print("  high: ");
     //      Serial.println(cycleHigh);
     //      #endif
     
     *state = (now - *last <= cycleHigh); /* HIGH if we're in the HIGH phase of duty cycle, LOW if not */
     *last = (now * cond) + ((*last)*(!cond)); /* if yes, update lastMillis with current time, if not, lastMillis remains unchanged */
     
     dw(output, *state); /* writes the state to the pin, regardless if it's changed or if its cycle is due */
     
}

/***************************************************/
#define MAX_COMMAND_LEN 80

uint16_t eepromPtr;

uint16_t c;
PS2KeyAdvanced keyboard;
uint16_t seqq[MAX_COMMAND_LEN];
uint16_t i;

uint16_t startTime;

bool shift = false;

bool keyboardOn = true; // keylock
bool ledOn = true; // LED lock

static inline uint16_t inRange(const uint16_t in, const uint16_t low, const uint16_t hi){
     #ifdef DEBUG
          Serial.print("==inRange in: ");
          Serial.println(in);
               Serial.print("==inRange low: ");
               Serial.println(low);
                    Serial.print("==inRange hi: ");
                    Serial.println(hi);
                         Serial.print("==inRange result: ");
                         Serial.println( ((in-low) <= (hi-low)) );
                         #endif
          
     return ((in-low) <= (hi-low)); 
}
     
     
static __inline__ void keyboard_thread(){
     if(cycleCheck(&keyboard_lastMillis, FRAMELENGTH)){
     if(keyboard.available()){
          c = keyboard.read(); // read the next key
          // #ifdef DEBUG
          //      Serial.print("raw key read: ");
          //      Serial.println(c);
          //      #endif
               
          if( (c > 0) ){ // see if keyboard buffer is not empty and is not the mysterious 170 or 250 that appears at startup 
               // #ifdef DEBUG
               //      Serial.println("keyboard buffer not empty");
               //      #endif
                    
               /* keylock */
               if(c==kkHOME){
                    keyboardOn = false;
                    keyboard.setLock(0);
                    keyboard.setLock(PS2_LOCK_NUM);
                    c=0; /* so it won't be typed */
                    #ifdef DEBUG
                         Serial.println("keyboard is LOCKED");
                         #endif
               }
               else if(c==kkMAIL){
                    keyboardOn = true;
                    keyboard.setLock(0);
                    c=0; /* so it won't be typed */
                    #ifdef DEBUG
                         Serial.println("keyboard is UNLOCKED");
                         #endif
               }
               /* keylock END. */
                    
               /* verify keylock */
               if(keyboardOn && c!=0){
                    // #ifdef DEBUG
                    //      Serial.print("==keycode: ");
                    //      Serial.println(c);
                    //      Serial.print("==menu state: ");
                    //      Serial.println(menu_state);
                    //      #endif
               
               
                    if(menu_state==NONE){ /* allow entering a menu only if no other menu is selected.
                         first rule of Menu Club: one menu at a time */
                         menu_state =   (c==kkA)*A +
                                        (c==kkS)*S +
                                        (c==kkD)*D +
                                        (c==kkW)*W +
                                        (c==kkX)*X +
                                        (c==kkESC)*SELECTING +
                                        (c==kkCTRL_ESC)*CONSOLE;} /* if it's not any on the menu selector keys, this will return 0(NONE), as nothing is added, all values are 0(false) */
                    if(menu_state==SELECTING){
                         leds_function = SEL;
                         if(c==kkF1){
                              selected_MJ = MJ_1;}
                         if(c==kkF2){
                              selected_MJ = MJ_2;}
                         if(c==kkF3){
                              selected_MJ = MJ_3;}
                         if(c==kkF4){
                              selected_MJ = MJ_4;}
                         if(c==kkF5){
                              selected_MJ = MJ_5;}
                         if(c==kkTAB || c==kkBACKSLASH){ /* cycling selection */
                              selected_MJ =  (selected_MJ==MJ_1) * MJ_2 +
                                             (selected_MJ==MJ_2) * MJ_3 +
                                             (selected_MJ==MJ_3) * MJ_4 +
                                             (selected_MJ==MJ_4) * MJ_5 +
                                             (selected_MJ==MJ_5) * MJ_1;}
                         if(c==kkESC_REL){ /* exit selection */
                              #ifdef DEBUG
                                   Serial.println("exited CHANNEL SELECTION MENU");
                                   #endif
                              leds_function = MJ;
                              menu_state = NONE;}}
                              
                    if(c==kkF9){
                         LED_ERROR_RED_state = !LED_ERROR_RED_state;}
                    else if(c==kkF10){
                         LED_ERROR_GREEN_state = !LED_ERROR_GREEN_state;}
                    else if(c==kkF8 || c==kkSCREEN){
                         ledOn = !ledOn;}
                    
                    if(menu_state==A){ /* freq(fine) */
                         #ifdef DEBUG
                              Serial.println("entered menu \"A\"");
                              #endif
                         *mj_freq(selected_MJ) += /* if changed freq will be in range, change it TODO: flash red error when MAX or MIN*/
                                                  (c==kkQ)*((*mj_freq(selected_MJ)+freq_fine)<=max_freq)*freq_fine +
                                                  (c==kkZ)*((*mj_freq(selected_MJ)-freq_fine)>=min_freq)*(-freq_fine);
                         #ifdef DEBUG
                              Serial.print("freq: ");
                              Serial.println(*mj_freq(selected_MJ));
                              #endif
                         menu_state = (c==kkA_REL)*NONE + (c!=kkA_REL)*A; /* detect A key release and exit A menu */
                         #ifdef DEBUG
                              if(c==kkA_REL){ Serial.println("exited menu \"A\"");}
                              #endif
                    }
                    if(menu_state==S){ /* freq(normal), duty(normal) */
                         #ifdef DEBUG
                              Serial.println("entered menu \"S\"");
                              #endif
                         *mj_freq(selected_MJ) += /* if changed freq will be in range, change it */
                                                  (c==kkW)*((*mj_freq(selected_MJ)+freq_normal)<=max_freq)*freq_normal +
                                                  (c==kkX)*((*mj_freq(selected_MJ)-freq_normal)>=min_freq)*(-freq_normal);
                         #ifdef DEBUG
                              Serial.print("freq: ");
                              Serial.println(*mj_freq(selected_MJ));
                              #endif
                         *mj_duty(selected_MJ) += /* if changed duty will be in range, change it */
                                                  (c==kkD)*((*mj_duty(selected_MJ)+duty_normal)<=max_duty)*duty_normal +
                                                  (c==kkA)*((*mj_duty(selected_MJ)-duty_normal)>=min_duty)*(-duty_normal);
                         #ifdef DEBUG
                              Serial.print("duty: ");
                              Serial.println(*mj_duty(selected_MJ));
                              #endif
                         menu_state = (c==kkS_REL)*NONE + (c!=kkS_REL)*S; /* detect S key release and exit S menu */
                         #ifdef DEBUG
                              if(c==kkS_REL){ Serial.println("exited menu \"S\"");}
                              #endif
                    }
                    if(menu_state==D){ /* freq(coarse) */
                         *mj_freq(selected_MJ) += /* if changed freq will be in range, change it */
                                                  (c==kkE)*((*mj_freq(selected_MJ)+freq_coarse)<=max_freq)*freq_coarse +
                                                  (c==kkC)*((*mj_freq(selected_MJ)-freq_coarse)>=min_freq)*(-freq_coarse);
                         menu_state = (c==kkD_REL)*NONE + (c!=kkD_REL)*D; /* detect D key release and exit D menu */
                    }
                    if(menu_state==W){ /* duty(coarse) */
                         *mj_duty(selected_MJ) += /* if changed duty will be in range, change it */
                                                  (c==kkE)*((*mj_duty(selected_MJ)+duty_coarse)<=max_duty)*duty_coarse +
                                                  (c==kkQ)*((*mj_duty(selected_MJ)-duty_coarse)>=min_duty)*(-duty_coarse);
                         menu_state = (c==kkW_REL)*NONE + (c!=kkW_REL)*W; /* detect W key release and exit W menu */
                    }
                    if(menu_state==X){ /* duty(fine) */
                         *mj_duty(selected_MJ) += /* if changed duty will be in range, change it */
                                                  (c==kkC)*((*mj_duty(selected_MJ)+duty_fine)<=max_duty)*duty_fine +
                                                  (c==kkZ)*((*mj_duty(selected_MJ)-duty_fine)>=min_duty)*(-duty_fine);
                         menu_state = (c==kkX_REL)*NONE + (c!=kkX_REL)*X; /* detect X key release and exit X menu */
                    }     
                    
                    /* cacca idee
                    set freq
                    set duty
                    di base ci stanno i segnali [s1..s5] che sono quelli che controllo dall'interfaccia iniziale
                    che vengono solitamente routati agli output [o1..o5]
                    tt come numero accessibile del tempo che scorre, sul quale basare tutto cazzooooo
                    */
                    if(menu_state==CONSOLE){
                         #ifdef DEBUG
                              Serial.println("entered CONSOLE");
                              #endif
                         /* console code here */
                         menu_state = (c==kkSHIFT_ESC)*NONE + (c!=kkSHIFT_ESC)*CONSOLE; /* detect Shift+Esc key press and exit CONSOLE menu */
                         LED_ERROR_GREEN_state = (menu_state==CONSOLE);
                    }
                    // else if(c==kkF1){ // F1 : dump EEPROM content to keyboard output, stop at terminating '\0'
                    //      #ifdef DEBUG
                    //           Serial.println("dumping to keyboard output...");
                    //           #endif
                    //      i=EEPROM_START;
                    // 
                    //      /* cacca: qui devo mettere che se non trova il terminating zero, scrive tutta la eeprom, e poi SI FERMA */
                    //      /* use getEEPROMptr che returns il max eeprom size se non trova lo zero, e fai un for loop con quello */
                    //      while(getEEPROMbyte(i)!='\0'){ /* write all chars to keyboard output, one by one, until a terminating '\0' is encountered */
                    //           Keyboard.write(toKeyboardCode(getEEPROMbyte(i)));
                    //           i++;}
                    //      #ifdef DEBUG
                    //           //Serial.print("stored address in EEPROM (16bit in address 0 and 1): ");
                    //           Serial.print("address of first 0 in EEPROM(excluding flags): ");
                    //           //Serial.print(getEEPROMshort(0));
                    //           Serial.print(getEEPROMptr());
                    //           Serial.println("");
                    //           for(i=EEPROM_START;i<1024;i++){
                    //                Serial.print(" ");
                    //                Serial.write(getEEPROMbyte(i));}
                    //           Serial.println("");
                    //           for(i=EEPROM_START;i<1024;i++){
                    //                Serial.print(" ");
                    //                Serial.print(getEEPROMbyte(i));}
                    //           Serial.println("");
                    //           Serial.println("DONE!");
                    //           #endif
                    //      }
                    // else if(c==16737){ // Shift + F1 : dump raw EEPROM content to keyboard output, don't look for terminating '\0', dump everything!
                    //      for(i=EEPROM_START; i<EEPROM_SIZE;i++){
                    //           Keyboard.write(toKeyboardCode(getEEPROMbyte(i)));
                    // 
                    //      }}
                    // //else if(c==kkF2){ // test all keyboard.write codes
                    // //     for(i=0;i<300;i++){
                    // //          Keyboard.write(i);
                    // //          Keyboard.write(176);
                    // //          //Keyboard.write(92);
                    // //     }
                    // //}
                    // else if(c==16748){ /* Shift + F12 : reset EEPROM */
                    //      /*wipeEEPROMsoft();*/ /* flags are wiped */
                    //      //setEEPROMshort(0, EEPROM_START); // set first writable address to 2 (0 and 1 contain the address itself, the saved pointer to eeprom)
                    //      setEEPROMbyte(EEPROM_START, '\0'); /* write terminating '\0' on the first usable eeprom cell */
                    //      eepromPtr = EEPROM_START;} // reset the EEPROM pointer
                    // 
                    // //else if(c==kkSHIFTL || c==kkSHIFTR){ // shift pressed -- use to detect key combos
                    // //     shift = true;}
                    // //else if(c==kkSHIFTL_RELEASE || c==kkSHIFTR_RELEASE){ // shift released -- use to detect key combos
                    // //     shift = false;}
                    // 
                    // else if(c==kkBACKSPACE){
                    //      eepromPtr-=(eepromPtr>EEPROM_START); // moves the EEPROM pointer one step back, if it's not already in initial position
                    //      setEEPROMbyte(eepromPtr, '\0');}
                    // /*else if(isTypable(c)){ // regular key, store it in eeprom!!!*/
                    // else{ // regular key, store it in eeprom!!!
                    //      #ifdef DEBUG
                    //           Serial.println("probably regular key!");
                    //           #endif
                    //      if(kbdToChar(c)!=0){ /* verify the pressed key is typable */
                    //           #ifdef DEBUG
                    //                Serial.println("TYPABLE key!");
                    //                #endif
                    //           setEEPROMbyte(eepromPtr, kbdToChar(c)); // put char in EEPROM
                    //           #ifdef DEBUG
                    //                Serial.print("saved in EEPROM at address ");
                    //                Serial.print(eepromPtr);
                    //                Serial.print(": ");
                    //                Serial.write(getEEPROMbyte(eepromPtr));
                    //                Serial.println("");
                    //                #endif
                    //           if(eepromPtr<EEPROM_SIZE){ // advance pointer only if it's not gona overflow
                    //                #ifdef DEBUG
                    //                     Serial.println("advancing pointer...");
                    //                     #endif
                    //                eepromPtr++;
                    //                #ifdef DEBUG
                    //                     Serial.print("pointer is now ");
                    //                     Serial.println(eepromPtr);
                    //                     #endif
                    //                setEEPROMbyte(eepromPtr, '\0'); // set the next byte to string terminator
                    //                //setEEPROMshort(0,eepromPtr); // update the stored eeprom pointer
                    //           }
                    //           else{
                    //                BEEP_WRYTE_EEPROM_FULL;
                    //           }
                    //      }/* if it's not typable, do nothing */
                    // }
               } /* if(keyboardOn && c!=0) */
               
          } /* if( (c > 0) ) */
          else{ /* keyboard buffer is empty */
               #ifdef DEBUG
                    Serial.println("keyboard buffer is EMPTY or contains a key-release code");
                    #endif
          }
     } /* if(keyboard.available()) */
     } /* (cycleCheck(keyboard_lastMillis, FRAMELENGTH)) */
}

#endif /* _NYX_HENRIK_H_ */