#ifndef _BAOKBD_H_
#define _BAOKBD_H_

#define BAOKBD_VERSION "2021c27-2052"

/*** TODO

*/

/*** MANUAL:
     HOME key : keyboard is LOCKED : ledA is lit
     MAIL key : keyboard is unlocked
     
     Ctrl + ESC : console mode : ledC is lit
          qq : exit console mode
          reset : hard reset the arduino
          arrow up : retype last command (still need to press ENTER to execute it)
*/

/*** USAGE:
     void setup(){
          KBD_SETUP;
          -- rest of your setup code here
     }
     
     void consoleCallback(char* consoleCommand){
          -- your console code here:
          if(strEqual(consoleCommand, "blabla")){
               consoleCommandFound = true;
          }
          else if(strEqual(consoleCommand, "blabla2")){
               consoleCommandFound = true;
          }
          else{
               consoleCommandFound = false;
               -- you should signal an error if no match is present for any command
          }
     }
     
     void keyboardCallback(uint16_t c){
          -- your keyboard code here
     }
     
     void loop(){
          keyboard_thread(&consoleCallback, &keyboardCallback);
          keyboardLeds_thread();
          -- rest of your main loop code here
     }
*/

/*** INCLUDES */
     #include "R:/s/c/i/baothread.h"
     #include "R:/s/c/i/baostring.h"

     #include "R:/s/c/i/PS2KeyAdvanced/PS2KeyAdvanced.h"
     
     #include <Keyboard.h>

     #include "R:/s/c/i/baoArdu.h"
     #include "R:/s/c/i/baoutil.h"
/* INCLUDES end. */

#ifdef __cplusplus
     extern "C" {
#endif

/*** DEFINES */
     #define FRAMERATE 75 /* Hz - for UI things */
     #define FRAMELENGTH 1000/FRAMERATE /* milliseconds */

     #define MAX_COMMAND_LEN 80
     
/* DEFINES end. */

/*** function DEFINES */
     #ifdef DEBUG
          #define KBD_SETUP \
               keyboard.begin( DATAPIN, IRQPIN ); \
               keyboard.resetKey(); /* key code 170 is PROBABLY generated from this one */ \
                    uint16_t startTime; \
                    Serial.begin( 9600 ); \
                    startTime = millis(); \
                    while(!Serial){ /* that alone would stall the system if no serial connection is present :( */ \
                         if ((millis()- startTime) >= 2000){ /* if it takes more than 2seconds to find the Serial, fuck it, we'll do without it. */ \
                         break; }} \
                    Serial.print( "== Control Framerate: " ); Serial.print(FRAMERATE); Serial.print( "Hz (" ); Serial.print(FRAMELENGTH); Serial.println( "ms framelength)" );
     #else
          #define KBD_SETUP \
               keyboard.begin( DATAPIN, IRQPIN ); \
               keyboard.resetKey(); /* key code 170 is PROBABLY generated from this one */
     #endif
/* function DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
     uint16_t c;
     PS2KeyAdvanced keyboard;
     char command[MAX_COMMAND_LEN];
     char command_last[MAX_COMMAND_LEN];
     uint8_t commandPtr = 0;
     bool keyboardOn = true; /* keylock */
     
     #define OFF 0
     #define ON 1
     #define KLED_A 0 /* num lock */
     #define KLED_B 1 /* caps lock */
     #define KLED_C 2 /* scroll lock */
     uint8_t keyboardLeds = 0;
     uint8_t keyboardLeds_last = 0;
     
     bool consoleModeOn = false; /* default: NOT in console mode */
     
     bool consoleCommandFound = false;
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
     static __inline__ void keyboard_thread(void(*consoleCallback)(char* consoleCommand), void(*keyboardCallback)(uint16_t c));
     
     static __inline__ void keyboardLeds_thread();
     static __inline__ void keyboardLed_set(uint8_t ledNum, bool status);
     static __inline__ bool keyboardLed_get(uint8_t ledNum);
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
static __inline__ void keyboardLeds_thread(){
     static cycle_t keyboardLedsCycle = {FRAMELENGTH, 0}; /* millis */
     static uint8_t keyboardLeds_out;
     if(cycleCheck(&keyboardLedsCycle)){
          if(keyboardLeds!=keyboardLeds_last){ /* if leds statuses have changed -- to avoid flickering */
               keyboardLeds_out = 0;
               if(keyboardLed_get(KLED_A)){
                    keyboardLeds_out |= PS2_LOCK_NUM;}
               if(keyboardLed_get(KLED_B)){
                    keyboardLeds_out |= PS2_LOCK_CAPS;}
               if(keyboardLed_get(KLED_C)){
                    keyboardLeds_out |= PS2_LOCK_SCROLL;}
               keyboard.setLock(keyboardLeds_out);
               keyboardLeds_last = keyboardLeds;
               c=0; /* so it won't be typed */
          }
     }
}
static __inline__ void keyboardLed_set(uint8_t ledNum, bool status){
     if(status==ON){
          keyboardLeds |= (1UL<<ledNum);}
     else if(status==OFF){
          keyboardLeds &= ~(1UL<<ledNum);}
}
static __inline__ bool keyboardLed_get(uint8_t ledNum){
     return ((keyboardLeds & (1UL<<ledNum)) >> ledNum)!=0;
}

static __inline__ void keyboard_thread(void(*consoleCallback)(char* consoleCommand), void(*keyboardCallback)(uint16_t c)){
     static cycle_t keyboardCycle = {FRAMELENGTH, 0}; /* millis */
     if(cycleCheck(&keyboardCycle)){
     if(keyboard.available()){
          c = keyboard.read(); /* read the next key */
               
          if( (c > 0) ){ /* see if keyboard buffer is not empty and is not the mysterious 170 or 250 that appears at startup */
               
               /* keylock */
               if(c==kkHOME){
                    keyboardOn = false;
                    keyboardLed_set(KLED_A, ON);
                    #ifdef DEBUG
                         Serial.println("keyboard is LOCKED");
                         #endif
               }
               else if(c==kkMAIL){
                    keyboardOn = true;
                    keyboardLed_set(KLED_A, OFF);
                    #ifdef DEBUG
                         Serial.println("keyboard is UNLOCKED");
                         #endif
               }
               /* keylock END. */
                    
               /* if keyboard is unlocked AND the input char is valid */
               if(keyboardOn && c!=0){

                    if(c==kkCTRL_ESC){
                          consoleModeOn = true;
                          keyboardLed_set(KLED_C, ON); /* cacca: magari voglio usare i led per altre cose... */
                     }
                    
                    if(consoleModeOn){
                         /* console code here */
                         if(c==kkBACKSPACE){
                              commandPtr-=(commandPtr>0); // moves the command pointer one step back, if it's not already in initial position
                              command[commandPtr] = '\0';} // and writes a terminating 0
                         else if(c==kkESC){ /* abort command */
                              commandPtr = 0;
                              command[0] = '\0';} /* just reset the pointer */
                         else if(c==kkARROWUP){ /* retype last command */
                              strcpy(command, command_last);
                              commandPtr=strlen(command);}
                         else if(c==kkARROWL){ /* move cursor, if not already in position 0 */
                              commandPtr -= commandPtr>0; /* cursor will be in overwrite mode!! */
                         }
                         /* TODO: implement move-cursor-right and insert mode */

                         else if(c==kkENTER){ /* execute command */
                              #ifdef DEBUG
                                   Serial.print("command is: ");
                                   Serial.println(command);
                                   #endif
                              strcpy(command_last, command);
                              
                              /* CONSOLE CODE HERE (using a callback) */
                              (*consoleCallback)(command); /* do something with the command entered in console mode */
                              
                              if(strEqual(command, "reset")){ /* reset the arduino */
                                   arduReset();
                              }
                              else if(strEqual(command, "qq")){ /* quit console */
                                   #ifdef DEBUG
                                        Serial.println("exited CONSOLE");
                                        #endif
                                   consoleCommandFound = true;
                                   keyboardLed_set(KLED_C, OFF); /* cacca: magari voglio usare i led per altre cose... */
                                   consoleModeOn = false;
                              }

                              if(!consoleCommandFound){
                                   /* ERROR: unrecognized command */
                                   #ifdef DEBUG
                                        Serial.print(":ERROR: unrecognized command: \"");
                                        Serial.print(command);
                                        Serial.println("\"");
                                        #endif
                              }
                              commandPtr = 0; /* reset the pointer */
                              command[0] = '\0'; /* reset command string */
                         } /* else if(c==kkENTER){ -- execute command */
                         else{ // any key, cram it into the command string
                              if(kbdToChar(c)!=0){ /* verify the pressed key is typable */
                                   command[commandPtr] = kbdToChar(c); // put char in the commmand string
                                   commandPtr+=(commandPtr<MAX_COMMAND_LEN); // advance pointer only if it's not gona overflow - TODO: warning if command is too long
                                   command[commandPtr] = '\0';} // set the next byte to string terminator
                              }
                         /* console code END. */
                         
                    } /* consoleModeOn == true */
                    else{
                         /* NON-CONSOLE CODE HERE (using a callback) */
                         (*keyboardCallback)(c); /* do something with the typed char */
                    }

               } /* if(keyboardOn && c!=0) */
          } /* if( (c > 0) ) */
          else{ /* keyboard buffer is empty */
               #ifdef DEBUG
                    Serial.println("keyboard buffer is EMPTY or contains a key-release code");
                    #endif
          }
     } /* if(keyboard.available()) */
     } /* (cycleCheck(keyboard_lastMillis, FRAMELENGTH)) */
} /* static __inline__ void keyboard_thread(){ */

/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
     }
#endif
#endif /* _BAOKBD_H_ */



