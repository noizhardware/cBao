#ifndef _NYX_HENRIK_H_
#define _NYX_HENRIK_H_

/* v2020k03-2212 */
/* "henrik" add-on board for nyx, hardware bindings */

/* TODO:

fino al 2 Nov compreso, coding
3-4-5 Nov, suonare e girare video

* nei save, fare in modo di dereferenziare il puntatore a funzione, magari creare un typedef enum, signal_function_t, usando anche solo 8 bit con __attribute__ ((__packed__))
  - che a sto punto, potrei anche implementare il polimorfismo nelle closures. cià.

* BUG: i  save e load non sono compatibili tra modalità DEBUG e non
  se salvo una roba in modalità DEBUG, poi in modalità normale non mela loada, e viceversa
  ACHTUNG: non è proprio un bug: è che nei save, io salvo il puntatore a funzione, e se il codice poi cambia, l'indirizzo di quella funzione sarà diverso, e loadarlo cosi com'è probabilmente distrugge tutto... :)))

* le signal functions posso metterle con return type uint8_t >> uint8_t sq(uint24_t freq, uint8_t duty, uint_8 phase)
* use fixed point values where possible. like PHASE can just be a uint8 [0..100], or even [0..255] >> precision of 0,4 phase
* same with duty
* for freq: se mi accontento di usare freqs massime di 6553.6Hz, posso metterle in un uint16, con 1 decimal digit. 3200.4 >> 32004
* se voglio posso usare 24bit >> max 16777.216Hz, 3 decimal digits precision (vedi R:\s\c\bitfield.c)
  
* pause/resume - anche su singoli canali? (è un po un s&h in effetti...)

* s&h function, con trigger da tastiera, o programmabile

* live mode: qwert keys at as gates for channels
  - extra functions:
    + invert (always ON >> press >> momentarily OFF)
    + "arpeggio" : trigger a pattern instead of an on-off
    
quanto tempo mi posso dare per creare sto video?
come lo ripartisco?
- C code
- prove
- filming
    
* branchlessify, where possible
* separate actual hardware bindings from functions
* rimane cmq il problema che a piu di 250Hz non jela fa, vedi R:\s\avr\non-blocking-rtttl-arduino-master che fa musica non-blocking coi timerzzz
  mi sa che il problema è che sia digitalWrite() che dw() sono troppo lenti, e anche micros() stesso mi sa
  per ora non ha nemmeno senso usare i microseconds, tanto anche coi millis arrivo fino a 1000Hz, quando l'hardware mi sta reggendo a 250Hz a malapena
*/

/* MANUAL:
* ESC + [F1..F5] : select a channel
  ESC + (\ or 1) : cycle selection left-right
* A + Q or Z : increase-decrease frequency by a FINE amount
  S + W or X : increase-decrease frequency by a NORMAL amount
  A + Q or Z : increase-decrease frequency by a COARSE amount
* X + C or Z : increase-decrease duty by a FINE amount
  S + D or A : increase-decrease duty by a NORMAL amount
  W + E or Q : increase-decrease duty by a COARSE amount
* P + [1..8] : set phase to [0..0.875] in 1/8 increments (0.125) like an 8-step step sequencer
  P + 9 or L : increase-decrease phase by a FINE amount
  P + 0 or ò : increase-decrease phase by a NORMAL amount
  P + ' or à : increase-decrease phase by a COARSE amount
* Ctrl + Esc : enter CONSOLE
* Shift + Esc : quit CONSOLE (or type `qq` in the console)
  - ss filename --save current settings to eeprom
  - ll filename --load saved settings from eeprom
  - wipe --wipe eeprom
  - reset --reset the firmware
  - qq --quit console
  - DEBUG mode only:
    - she --serial.print contents of eeprom (SHow Eeprom)
    - now --serial.print current oscillator settings
* \ + 1 or 2 : set selected signal to 0 or 1
  \ + Tab : restore the original signal
  
*/

/* includes */
     #include <float.h>
          #include "R:/s/c/i/ardumicro.h"
          #include "R:/s/c/i/nyx.h"
          #include "R:/s/c/i/baoardu.h"
          #include "R:/s/c/i/baostring.h"
     #include "R:/s/c/i/eepromThings.h"
/* includes END. */

/* defines */
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

     #define FRAMERATE 75 /* Hz - for UI and GUI things */
     #define FRAMELENGTH 1000/FRAMERATE /* milliseconds */


     #define DEVICE_SAMPLE_RATE 1000 /* Hz - if I'm using milliseconds, 1000Hz is the fastest I can achieve >> 1ms for each sample*/
     // #define SAMPLELENGTH 1000000/DEVICE_SAMPLE_RATE /* microseconds */
     #define SAMPLELENGTH 1000/DEVICE_SAMPLE_RATE /* milliseconds */

     #define MAX_COMMAND_LEN 80
     #define MAX_SAVENAME_LEN 16
     #define MAX_VARNAME_LEN 16

     #define clk ((float)millis())
     // #define clk ((float)(micros()/1000)) /* in milliseconds. ha-haaa! so I still have a float in milliseconds, but a more precise one. 0.001ms precision >> 1MHz resolution MA NON FUNZIA, a 100Hz mi butta fuori invece 83Hz, bhooo */     
          /* dirty hack, so I can use the functions from baosnd.h
          "clk" was originally meant to ++ on each sample advance.
          Here my samplerate is 1000Hz (1ms sample length), the shortest I can get easily, using millis(),
          and taking into account that probably a bunch of other things are just not
          fast enough to even keep up with micros(). (I tried it :/)
          With micros() I'd have a 1us resolution -> 1MHz max freq! */
     
     #define NIL 0

/* defines END. */

/* defines macros */
     #define HENRIK_SETUP \
          pinMode(MJ_1, OUTPUT); \
          pinMode(LED_1, OUTPUT); \
               pinMode(MJ_2, OUTPUT); \
               pinMode(LED_2, OUTPUT); \
                    pinMode(MJ_3, OUTPUT); \
                    pinMode(LED_3, OUTPUT); \
                         pinMode(MJ_4, OUTPUT); \
                         pinMode(LED_4, OUTPUT); \
                              pinMode(MJ_5, OUTPUT); \
                              pinMode(LED_5, OUTPUT); \
          pinMode(LED_ERROR_RED, OUTPUT); \
          pinMode(LED_ERROR_GREEN, OUTPUT); \
           \
          digitalWrite(MJ_1, LOW); \
          digitalWrite(LED_1, LOW); \
               digitalWrite(MJ_2, LOW); \
               digitalWrite(LED_2, LOW); \
                    digitalWrite(MJ_3, LOW); \
                    digitalWrite(LED_3, LOW); \
                         digitalWrite(MJ_4, LOW); \
                         digitalWrite(LED_4, LOW); \
                              digitalWrite(MJ_5, LOW); \
                              digitalWrite(LED_5, LOW); \
          digitalWrite(LED_ERROR_RED, LOW); \
          digitalWrite(LED_ERROR_GREEN, LOW)
          
     #define usec micros() /* uint32_t */
     /*Returns the number of microseconds since the Arduino board began running the current program. This number will overflow (go back to zero), after approximately 70 minutes.
     On 16 MHz Arduino boards (e.g. Duemilanove and Nano), this function has a resolution of 4uS(250kHz) (i.e. the value returned is always a multiple of 4).
     On 8 MHz Arduino boards (e.g. the LilyPad), this function has a resolution of 8uS(125kHz).*/
     
     #define tt clk/1000.f /* seconds elapsed from start, in milliseconds - max resolution 1ms*/
     
     
/* defines macros END. */

/* typedefs */

     typedef struct led_t{
          uint8_t pin;
          uint32_t last;
          uint8_t state;
     } led_t;

     
     /* signal is a closure: a float-returning function pointer, and 3x float arguments for that function */
     typedef struct signal_t{
          float (*func_ptr)(float, float, float);
          float freq;
          float duty;
          float phase;
     } signal_t;
     
     // typedef enum type_t{
     //      INT,
     //      FLOAT
     // } type_t;
     // 
     // typedef struct closure_t{ 
     //      void* func_ptr;
     //      type_t type;
     // } closure_t;
/* typedefs END. */

/* function declarations */
     #undef sq /* to get rid of #define sq(x) ((x)*(x)) */
     static __inline__ float sq(float freq, float duty, float phase);
     // static __inline__ float saw1bit(float freq, float unused_for_now);
     static __inline__ float low(float unused1, float unused2, float unused3);
     static __inline__ float high(float unused1, float unused2, float unused3);
               static __inline__ void LED_ERROR_RED_thread();
               static __inline__ void LED_ERROR_GREEN_thread();
                    static __inline__ uint8_t led_mj(uint8_t led);
                    static __inline__ float led_mjState(uint8_t led);
                    static __inline__ float* mj_freq(uint8_t mj);
                    // static __inline__ uint8_t* mj_duty(uint8_t mj);
                    static __inline__ float* mj_duty(uint8_t mj);
                    static __inline__ float* mj_phase(uint8_t mj);
     static __inline__ bool isSelected(uint8_t mj);
     // static __inline__ bool MJstate(uint8_t mj);
     static __inline__ void LED_output_thread(led_t* led);
     
     static __inline__ void store(uint8_t mj);
     static __inline__ void restore(uint8_t mj);
     
     static inline uint16_t inRange(const uint16_t in, const uint16_t low, const uint16_t hi);
     static __inline__ void keyboard_thread();
     
     static __inline__ float signal(signal_t sig);
     // static __inline__ void clk_thread();
     
     static __inline__ bool save(char* saveName);
     static __inline__ bool load(char* saveName);
     static __inline__ uint16_t getFreeSlot();
     
/* function declarations END. */



/* global vars */

     #ifdef DEBUG
          int h_DEBUG;
          #endif

     // uint32_t buzzer_lastUsec = 0;
     // bool buzzer_state = LOW;

     // static float clk = 0.f;
     // uint32_t clk_last = 0;

     unsigned long keyboard_lastMillis = 0; 
     
     /* initialize signals */
     signal_t mj1_sig = {sq, 5.f, .25f, 0.00f};
     signal_t mj2_sig = {sq, 5.f, .25f, 0.25f};
     signal_t mj3_sig = {sq, 5.f, .25f, 0.50f};
     signal_t mj4_sig = {sq, 5.f, .25f, 0.75f};
     signal_t mj5_sig = {sq, 5.f, .25f, 0.90f};
     
     /* to store signal "status" globally */
     signal_t mj1_last_sig;
     signal_t mj2_last_sig;
     signal_t mj3_last_sig;
     signal_t mj4_last_sig;
     signal_t mj5_last_sig;
     bool mj1_isStored = false;
     bool mj2_isStored = false;
     bool mj3_isStored = false;
     bool mj4_isStored = false;
     bool mj5_isStored = false;
     
     signal_t low_sig = {low, 0, 0 ,0}; /* this is a signal that's always LOW */
     signal_t high_sig = {high, 0, 0 ,0}; /* this is a signal that's always HIGH */

     led_t led_1 = {LED_1, 0, LOW};
     led_t led_2 = {LED_2, 0, LOW};
     led_t led_3 = {LED_3, 0, LOW};
     led_t led_4 = {LED_4, 0, LOW};
     led_t led_5 = {LED_5, 0, LOW};

     led_t led_error_red = {LED_ERROR_RED, 0, LOW};
     led_t led_error_green = {LED_ERROR_GREEN, 0, LOW};

     float max_freq = 250.f; /* mi pare sia il limite dopo il quale si impasta e fa robe strane, TODO fare che sia ridefinibile in console mode */
     float min_freq = 0.025f; /* wavelength = 40seconds */

     float min_duty = 0.f; /* TODO: fare che siano ridefinibili */
     float max_duty = 100.f;
     
     float min_phase = 0.f;
     float max_phase = 0.99f;


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
     #define P 7
     #define CONSOLE 8
     #define BACKSLASH 9
     #define LOWSIG 10
     #define HIGHSIG 11
     #define RESTORESIG 12
     uint8_t menu_state = NONE;

     /* increments */
     float freq_fine = 0.5f;
     float freq_normal = 1.0f;
     float freq_coarse = 10.0f;
          float duty_fine = .01f;
          float duty_normal = .05f;
          float duty_coarse = .10f;
               float phase_fine = .03125f; /* 1/32 */
               float phase_normal = .0625f; /* 1/16 */
               float phase_coarse = .125f; /* 1/8 */

     uint16_t c;
     PS2KeyAdvanced keyboard;
     char command[MAX_COMMAND_LEN];
     uint8_t commandPtr = 0;
     uint16_t i;

     uint16_t startTime;

     bool keyboardOn = true; // keylock
     bool ledOn = true; // LED lock
     bool buzzerOn = true; // BUZZER lock

/* global vars END. */


/* function definitions */ 

#undef sq /* to get rid of #define sq(x) ((x)*(x)) */
static __inline__ float sq(float freq, float duty, float phase){ /* duty [0..1] */
     /* (wrapping time every wavelength) / (wavelength) >> [0..1] position in current wave cycle */
     /* also: to clk I'm subtracting the desired phase difference, with phase in range[0..1], that's phase*wavelength */
     float wavelength = (((float)DEVICE_SAMPLE_RATE)/freq);
     return ((fmod(clk-(phase*wavelength), wavelength) / wavelength) < duty);}

static __inline__ float low(__attribute__((unused)) float unused1, __attribute__((unused)) float unused2, __attribute__((unused)) float unused3){
     return 0.f;}
static __inline__ float high(__attribute__((unused)) float unused1, __attribute__((unused)) float unused2, __attribute__((unused)) float unused3){
     return 1.f;}

// static __inline__ float saw1bit(float freq, float unused_for_now_1, float unused_for_now_2){
//      /* let's modulate the duty of a sq */
//      #ifdef DEBUG
//           Serial.print("modulated duty: ");
//           Serial.println((fmod(clk, ((float)DEVICE_SAMPLE_RATE/freq))/((float)DEVICE_SAMPLE_RATE/freq)));
//           #endif
//      return sq(freq, (fmod(clk, ((float)DEVICE_SAMPLE_RATE/freq))/((float)DEVICE_SAMPLE_RATE/freq)), 0.);}

static __inline__ float signal(signal_t sig){ /* take a float function + 3x floats */
     return sig.func_ptr(sig.freq, sig.duty, sig.phase);}
     /* TODO: make this somewhat more generic */

static __inline__ void store(uint8_t mj){ /* stores the current signal ONLY IF there is not another stored */
     switch(mj){
          case MJ_1:
               if(!mj1_isStored){
                    mj1_last_sig = mj1_sig;
                    mj1_isStored = true;}
               break;
          case MJ_2:
               if(!mj2_isStored){
                    mj2_last_sig = mj2_sig;
                    mj2_isStored = true;}
               break;
          case MJ_3:
               if(!mj3_isStored){
                    mj3_last_sig = mj3_sig;
                    mj3_isStored = true;}
               break;
          case MJ_4:
               if(!mj4_isStored){
                    mj4_last_sig = mj4_sig;
                    mj4_isStored = true;}
               break;
          case MJ_5:
               if(!mj5_isStored){
                    mj5_last_sig = mj5_sig;
                    mj5_isStored = true;}
               break;
     }
}
static __inline__ void restore(uint8_t mj){ /* restores a signal ONLY IF there is sometning stored for that signal */
     switch(mj){
          case MJ_1:
               if(mj1_isStored){
                    mj1_sig = mj1_last_sig;
                    mj1_isStored = false;}
               break;
          case MJ_2:
               if(mj2_isStored){
                    mj2_sig = mj2_last_sig;
                    mj2_isStored = false;}
               break;
          case MJ_3:
               if(mj3_isStored){
                    mj3_sig = mj3_last_sig;
                    mj3_isStored = false;}
               break;
          case MJ_4:
               if(mj4_isStored){
                    mj4_sig = mj4_last_sig;
                    mj4_isStored = false;}
               break;
          case MJ_5:
               if(mj5_isStored){
                    mj5_sig = mj5_last_sig;
                    mj5_isStored = false;}
               break;
     }
}


// static __inline__ void clk_thread(){ /* this should increment clk by 1 at each SAMPLE advance, so every SAMPLELENGTH milliseconds */
//      clk*=(clk<FLT_MAX);
//      clk+=cycleCheck(&clk_last, (uint16_t)SAMPLELENGTH);
// }

/* save structure:
(savename string)(terminating \0)(size of data)(data)(terminating \0) - il terminating \0 è solo dopo l'ULTIMO save in eeprom, tra un save e l'altro non c'è nulla che li separa
eg:
(name)(\0)(dataSize)(data)(name)(\0)(dataSize)(data)(final \0)
*/
static __inline__ bool save(char* saveName){ /* returns true if save was successful */ /* cacca, non ho ancora messo il caso in cui non sia successful */
     uint16_t ptr = getFreeSlot(); /* get the address of the first free slot in eeprom */
     #ifdef DEBUG
          Serial.print("writing at eeprom address: ");
          Serial.println(ptr);
          #endif
     uint8_t dataSize;
     size_t i;
     for(i=0;i<strlen(saveName);i++){ /* write the name string in eeprom */
          setEEPROMbyte(ptr, saveName[i]);
          ptr++;}
     setEEPROMbyte(ptr, '\0'); /* terminate the savename string */
     ptr++;
     #ifdef DEBUG
          Serial.print("after writing the name, I'm at address: ");
          Serial.println(ptr);
          #endif
     /* let's write data size, for now it's 70bytes (2+4+4+4)*5 */
     dataSize = 70;
     setEEPROMbyte(ptr, dataSize); ptr++;
     /* now let's write the actual data */
     setEEPROMshort(ptr, (uint16_t)mj1_sig.func_ptr); ptr+=2; /* explicit cast from function pointer to uint16 for eeprom writing */
     setEEPROMfloat(ptr, mj1_sig.freq); ptr+=4;
     setEEPROMfloat(ptr, mj1_sig.duty); ptr+=4;
     setEEPROMfloat(ptr, mj1_sig.phase); ptr+=4;
          setEEPROMshort(ptr, (uint16_t)mj2_sig.func_ptr); ptr+=2;
          setEEPROMfloat(ptr, mj2_sig.freq); ptr+=4;
          setEEPROMfloat(ptr, mj2_sig.duty); ptr+=4;
          setEEPROMfloat(ptr, mj2_sig.phase); ptr+=4;
               setEEPROMshort(ptr, (uint16_t)mj3_sig.func_ptr); ptr+=2;
               setEEPROMfloat(ptr, mj3_sig.freq); ptr+=4;
               setEEPROMfloat(ptr, mj3_sig.duty); ptr+=4;
               setEEPROMfloat(ptr, mj3_sig.phase); ptr+=4;
                    setEEPROMshort(ptr, (uint16_t)mj4_sig.func_ptr); ptr+=2;
                    setEEPROMfloat(ptr, mj4_sig.freq); ptr+=4;
                    setEEPROMfloat(ptr, mj4_sig.duty); ptr+=4;
                    setEEPROMfloat(ptr, mj4_sig.phase); ptr+=4;
                         setEEPROMshort(ptr, (uint16_t)mj5_sig.func_ptr); ptr+=2;
                         setEEPROMfloat(ptr, mj5_sig.freq); ptr+=4;
                         setEEPROMfloat(ptr, mj5_sig.duty); ptr+=4;
                         setEEPROMfloat(ptr, mj5_sig.phase); ptr+=4;
     #ifdef DEBUG
          Serial.print("last written DATA is at address: ");
          Serial.println(ptr);
          Serial.println("save DONE. EEPROM contents:");
          for(h_DEBUG=0;h_DEBUG<EEPROM_SIZE;h_DEBUG++){
               Serial.print(getEEPROMbyte(h_DEBUG));
               Serial.print(" ");}
          Serial.println("");
          for(h_DEBUG=0;h_DEBUG<EEPROM_SIZE;h_DEBUG++){
               Serial.print((char)getEEPROMbyte(h_DEBUG));
               Serial.print(" ");}
          Serial.println("");
          #endif
     return true;
}
static __inline__ bool load(char* loadName){ /* returns true if load was successful, false if savename was not found */
     char detectedName[MAX_SAVENAME_LEN];
     uint16_t ptr = EEPROM_START;
     uint8_t strIndex;
     bool found = false;
     uint8_t __attribute__((unused)) saveSize;
     if(getEEPROMbyte(EEPROM_START)=='\0'){ /* if first byte in eeprom is 0, let's assume eeprom is empty -> file not found */
          #ifdef DEBUG
               Serial.println("first element in eeprom was 0, file not found.");
               #endif
          return false;} /* file not found */
     else{ /* eeprom is not all empty, let's search */
          while(!found){
               strIndex=0;
               while((getEEPROMbyte(ptr)!='\0')&&(strIndex<MAX_SAVENAME_LEN)){ /* cacca: dovrebbe essere h<= ???? bhoo  -- also, potrei confrontare i filenames lettera per lettera, è piu veloce */
                    detectedName[strIndex]=getEEPROMbyte(ptr);
                    strIndex++;
                    ptr++;}
               detectedName[strIndex]='\0'; /* terminate the string */
               #ifdef DEBUG
                    Serial.print("detected name: ");
                    Serial.println(detectedName);
                    #endif
               found = strEqual(detectedName, loadName); /* if found, will exit the while loop */
               if(!found){ /* if that was not our loadName, let's skip to the next loadName, if there is one */
                    ptr++; /* advance pointer, will now point to dataSize for the current save */
                    ptr+=getEEPROMbyte(ptr)+1; /* advance pointer to the next chunk */
                    if(getEEPROMbyte(ptr)=='\0'){ /* if it's a \0, saves end here, we didn't find our save */
                         return false;}}
          }
          /* here we load the data and then return TRUE */ /* cacca: sto loadando solo [mj1_sig..mj5_sig], e di base saveSize mi è inutile al momento... */
          #ifdef DEBUG
               Serial.print("Now loading ");
               Serial.print(detectedName);
               Serial.println("...");
               #endif
          ptr++;
          saveSize=getEEPROMbyte(ptr); ptr++;
               mj1_sig.func_ptr = (float (*)(float, float, float))getEEPROMshort(ptr); ptr+=2; /* doing explicit cast from uin16 to function pointer */
               mj1_sig.freq = getEEPROMfloat(ptr); ptr+=4;
               mj1_sig.duty = getEEPROMfloat(ptr); ptr+=4;
               mj1_sig.phase = getEEPROMfloat(ptr); ptr+=4;
                    mj2_sig.func_ptr = (float (*)(float, float, float))getEEPROMshort(ptr); ptr+=2;
                    mj2_sig.freq = getEEPROMfloat(ptr); ptr+=4;
                    mj2_sig.duty = getEEPROMfloat(ptr); ptr+=4;
                    mj2_sig.phase = getEEPROMfloat(ptr); ptr+=4;
                         mj3_sig.func_ptr = (float (*)(float, float, float))getEEPROMshort(ptr); ptr+=2;
                         mj3_sig.freq = getEEPROMfloat(ptr); ptr+=4;
                         mj3_sig.duty = getEEPROMfloat(ptr); ptr+=4;
                         mj3_sig.phase = getEEPROMfloat(ptr); ptr+=4;
                              mj4_sig.func_ptr = (float (*)(float, float, float))getEEPROMshort(ptr); ptr+=2;
                              mj4_sig.freq = getEEPROMfloat(ptr); ptr+=4;
                              mj4_sig.duty = getEEPROMfloat(ptr); ptr+=4;
                              mj4_sig.phase = getEEPROMfloat(ptr); ptr+=4;
                                   mj5_sig.func_ptr = (float (*)(float, float, float))getEEPROMshort(ptr); ptr+=2;
                                   mj5_sig.freq = getEEPROMfloat(ptr); ptr+=4;
                                   mj5_sig.duty = getEEPROMfloat(ptr); ptr+=4;
                                   mj5_sig.phase = getEEPROMfloat(ptr); ptr+=4;
          #ifdef DEBUG
               Serial.print("Finished loading ");
               Serial.println(detectedName);
               #endif
          return true; /* loading was successful!!! */     
     }
}

static __inline__ uint16_t getFreeSlot(){
     uint8_t saveSize;
     uint16_t ptr = EEPROM_START;
     bool found = false;
     if(getEEPROMbyte(EEPROM_START)=='\0'){ /* if first byte in eeprom is 0, let's assume eeprom is empty */
          return EEPROM_START;} /* so first free slot is at address EEPROM_START */
     else{
          while(!found){ /* while a free slot is not found, keep looking */
               while(getEEPROMbyte(ptr)!='\0'){ /* move pointer until we find a '\0', that will be a saveName terminator */
                    ptr++;}
               ptr++; /* advance pointer of 1 more */
               saveSize = getEEPROMbyte(ptr); /* first byte after name-terminator is the size of that save */
               ptr+=saveSize+1; /* move the pointer to skip that entire save, and point to the first byte after it */
               found = (getEEPROMbyte(ptr)=='\0');} /* if that byte is a '\0' (it was set by the save() function, to be sure to have a \0 after each save), we found the first free save location, now pointed by ptr */
          return ptr; /* a free slot has been found, let's return it */ /* cacca non sto gestendo l'errore, se non trova nessuno slot libero che fa? dovrebbe anche controllare che non esista un save collo stesso nome...*/
     }
}
     
static __inline__ void LED_ERROR_RED_thread(){
     if(cycleCheck(&led_error_red.last, FRAMELENGTH)){
          dw(led_error_red.pin, led_error_red.state);}}
static __inline__ void LED_ERROR_GREEN_thread(){
     if(cycleCheck(&led_error_green.last, FRAMELENGTH)){
          dw(led_error_green.pin, led_error_green.state);}}

static __inline__ uint8_t led_mj(uint8_t led){ /* given a LED name, returns the corresponding MJ name */
     return    (led==LED_1)*MJ_1 +
               (led==LED_2)*MJ_2 +
               (led==LED_3)*MJ_3 +
               (led==LED_4)*MJ_4 +
               (led==LED_5)*MJ_5;}
static __inline__ float led_mjState(uint8_t led){ /* given a LED name, returns the corresponding mj state, calling the mj function */
     return    (led==LED_1)*signal(mj1_sig) +
               (led==LED_2)*signal(mj2_sig) +
               (led==LED_3)*signal(mj3_sig) +
               (led==LED_4)*signal(mj4_sig) +
               (led==LED_5)*signal(mj5_sig);}
static __inline__ float* mj_freq(uint8_t mj){ /* given a MJ name, returns the corresponding MJ_freq pointer */
     /* all float pointers are casted to uint16(that's the size of a float pointer), so I can multiply them by a bool, sum them all, and then cast back to a float pointer */
     return    (float*)((mj==MJ_1)*((uint16_t)(&mj1_sig.freq)) + /* cacca, qui sto guardando i SEGNALI (s1..s5), e non veramente i minijack */
               (mj==MJ_2)*((uint16_t)(&mj2_sig.freq)) +
               (mj==MJ_3)*((uint16_t)(&mj3_sig.freq)) +
               (mj==MJ_4)*((uint16_t)(&mj4_sig.freq)) +
               (mj==MJ_5)*((uint16_t)(&mj5_sig.freq)));}
static __inline__ float* mj_duty(uint8_t mj){ /* given a MJ name, returns the corresponding MJ_duty pointer */
     /* all uint8 pointers are casted to uint16(that's the size of a float pointer), so I can multiply them by a bool, sum them all, and then cast back to a float pointer */
     return    (float*)((mj==MJ_1)*((uint16_t)(&mj1_sig.duty)) + /* cacca, qui sto guardando i SEGNALI (s1..s5), e non veramente i minijack */
               (mj==MJ_2)*((uint16_t)(&mj2_sig.duty)) +
               (mj==MJ_3)*((uint16_t)(&mj3_sig.duty)) +
               (mj==MJ_4)*((uint16_t)(&mj4_sig.duty)) +
               (mj==MJ_5)*((uint16_t)(&mj5_sig.duty)));}
static __inline__ float* mj_phase(uint8_t mj){ /* given a MJ name, returns the corresponding MJ_phase pointer */
     /* all uint8 pointers are casted to uint16(that's the size of a float pointer), so I can multiply them by a bool, sum them all, and then cast back to a float pointer */
     return    (float*)((mj==MJ_1)*((uint16_t)(&mj1_sig.phase)) + /* cacca, qui sto guardando i SEGNALI (s1..s5), e non veramente i minijack */
               (mj==MJ_2)*((uint16_t)(&mj2_sig.phase)) +
               (mj==MJ_3)*((uint16_t)(&mj3_sig.phase)) +
               (mj==MJ_4)*((uint16_t)(&mj4_sig.phase)) +
               (mj==MJ_5)*((uint16_t)(&mj5_sig.phase)));}
static __inline__ signal_t* mj_signal(uint8_t mj){ /* given a MJ name, returns the corresponding MJ signal pointer */
     /* all signal_t pointers are casted to uint16(that's the size of a float pointer), so I can multiply them by a bool, sum them all, and then cast back to a signal_t pointer */
     return    (signal_t*)((mj==MJ_1)*((uint16_t)(&mj1_sig)) + /* cacca, qui sto guardando i SEGNALI (s1..s5), e non veramente i minijack */
               (mj==MJ_2)*((uint16_t)(&mj2_sig)) +
               (mj==MJ_3)*((uint16_t)(&mj3_sig)) +
               (mj==MJ_4)*((uint16_t)(&mj4_sig)) +
               (mj==MJ_5)*((uint16_t)(&mj5_sig)));}

static __inline__ bool isSelected(uint8_t mj){
     return mj==selected_MJ;}

static __inline__ void LED_output_thread(led_t* led){
          led->state =   (cycleCheck(&(led->last), FRAMELENGTH)) * /* IF the cycle is due */
                         ledOn * ( /* IF the ledOn global flag in ON */
                         (leds_function == MJ)*led_mjState(led->pin) + /* mirror its MJ counterpart */
                         (leds_function == SEL)*isSelected(led_mj(led->pin))); /* display currently selected channel */
          dw(led->pin, led->state);} /* regardless, write the state to the pin */


/***************************************************/


static __inline__ uint16_t inRange(const uint16_t in, const uint16_t low, const uint16_t hi){
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
               
                    /* menu states (using single "if"s, it's faster than "else if"s) */
                    if(menu_state==NONE){ /* allow entering a menu only if no other menu is selected.
                         first rule of Menu Club: one menu at a time */
                         menu_state =   (c==kkA)*A +
                                        (c==kkS)*S +
                                        (c==kkD)*D +
                                        (c==kkW)*W +
                                        (c==kkX)*X +
                                        (c==kkP)*P +
                                        (c==kkESC)*SELECTING +
                                        (c==kkBACKSLASH)*BACKSLASH + /* on-off signals */
                                        (c==kk1)*LOWSIG +
                                        (c==kk2)*HIGHSIG +
                                        (c==kkTAB)*RESTORESIG +
                                        (c==kkCTRL_ESC)*CONSOLE;} /* if it's not any on the menu selector keys, this will return 0(NONE), as nothing is added, all values are 0(false) */
                    if(menu_state==SELECTING){
                         leds_function = SEL;
                         if(c==kkESC_REL){ /* exit selection */
                              #ifdef DEBUG
                                   Serial.println("exited CHANNEL SELECTION MENU");
                                   #endif
                              leds_function = MJ;
                              menu_state = NONE;}
                         else if(c==kk1){ /* cycling selection ->RIGHT */
                              selected_MJ =  (selected_MJ==MJ_1) * MJ_2 +
                                             (selected_MJ==MJ_2) * MJ_3 +
                                             (selected_MJ==MJ_3) * MJ_4 +
                                             (selected_MJ==MJ_4) * MJ_5 +
                                             (selected_MJ==MJ_5) * MJ_1;}
                         else if(c==kkBACKSLASH){ /* cycling selection <-LEFT */
                              selected_MJ =  (selected_MJ==MJ_1) * MJ_5 +
                                             (selected_MJ==MJ_2) * MJ_1 +
                                             (selected_MJ==MJ_3) * MJ_2 +
                                             (selected_MJ==MJ_4) * MJ_3 +
                                             (selected_MJ==MJ_5) * MJ_4;}
                         else if(c==kkF1){
                              selected_MJ = MJ_1;}
                         else if(c==kkF2){
                              selected_MJ = MJ_2;}
                         else if(c==kkF3){
                              selected_MJ = MJ_3;}
                         else if(c==kkF4){
                              selected_MJ = MJ_4;}
                         else if(c==kkF5){
                              selected_MJ = MJ_5;}}
                    
                    else if(menu_state==A){ /* freq(fine) */
                         #ifdef DEBUG
                              Serial.println("entered menu \"A\"");
                              #endif
                         *mj_freq(selected_MJ) += /* if changed freq will be in range, change it. TODO: flash red error when MAX or MIN*/
                                                  (c==kkQ)*((*mj_freq(selected_MJ)+freq_fine)<=max_freq) * freq_fine +
                                                  (c==kkZ)*((*mj_freq(selected_MJ)-freq_fine)>=min_freq) * (-freq_fine);
                         #ifdef DEBUG
                              Serial.print("freq: ");
                              Serial.println(*mj_freq(selected_MJ));
                              #endif
                         menu_state = (c==kkA_REL)*NONE + (c!=kkA_REL)*A; /* detect A key release and exit A menu */
                         #ifdef DEBUG
                              if(c==kkA_REL){ Serial.println("exited menu \"A\"");}
                              #endif
                    }
                    else if(menu_state==S){ /* freq(normal), duty(normal) */
                         #ifdef DEBUG
                              Serial.println("entered menu \"S\"");
                              #endif
                         *mj_freq(selected_MJ) += /* if changed freq will be in range, change it */
                                                  (c==kkW)*((*mj_freq(selected_MJ)+freq_normal)<=max_freq) * freq_normal +
                                                  (c==kkX)*((*mj_freq(selected_MJ)-freq_normal)>=min_freq) * (-freq_normal);
                         #ifdef DEBUG
                              Serial.print("freq: ");
                              Serial.println(*mj_freq(selected_MJ));
                              #endif
                         *mj_duty(selected_MJ) += /* if changed duty will be in range, change it */
                                                  (c==kkD)*((*mj_duty(selected_MJ)+duty_normal)<=max_duty) * duty_normal +
                                                  (c==kkA)*((*mj_duty(selected_MJ)-duty_normal)>=min_duty) * (-duty_normal);
                         #ifdef DEBUG
                              Serial.print("duty: ");
                              Serial.println(*mj_duty(selected_MJ));
                              #endif
                         menu_state = (c==kkS_REL)*NONE + (c!=kkS_REL)*S; /* detect S key release and exit S menu */
                         #ifdef DEBUG
                              if(c==kkS_REL){ Serial.println("exited menu \"S\"");}
                              #endif
                    }
                    else if(menu_state==D){ /* freq(coarse) */
                         *mj_freq(selected_MJ) += /* if changed freq will be in range, change it */
                                                  (c==kkE)*((*mj_freq(selected_MJ)+freq_coarse)<=max_freq) * freq_coarse +
                                                  (c==kkC)*((*mj_freq(selected_MJ)-freq_coarse)>=min_freq) * (-freq_coarse);
                         menu_state = (c==kkD_REL)*NONE + (c!=kkD_REL)*D; /* detect D key release and exit D menu */
                    }
                    else if(menu_state==W){ /* duty(coarse) */
                         *mj_duty(selected_MJ) += /* if changed duty will be in range, change it */
                                                  (c==kkE)*((*mj_duty(selected_MJ)+duty_coarse)<=max_duty) * duty_coarse +
                                                  (c==kkQ)*((*mj_duty(selected_MJ)-duty_coarse)>=min_duty) * (-duty_coarse);
                         menu_state = (c==kkW_REL)*NONE + (c!=kkW_REL)*W; /* detect W key release and exit W menu */
                    }
                    else if(menu_state==X){ /* duty(fine) */
                         *mj_duty(selected_MJ) += /* if changed duty will be in range, change it */
                                                  (c==kkC)*((*mj_duty(selected_MJ)+duty_fine)<=max_duty) * duty_fine +
                                                  (c==kkZ)*((*mj_duty(selected_MJ)-duty_fine)>=min_duty) * (-duty_fine);
                         menu_state = (c==kkX_REL)*NONE + (c!=kkX_REL)*X; /* detect X key release and exit X menu */
                    }     
                    else if(menu_state==P){ /* phase */
                         switch(c){
                              case kk1: *mj_phase(selected_MJ) = 0.f; break;
                              case kk2: *mj_phase(selected_MJ) = 0.0625f*2.f; break;
                              case kk3: *mj_phase(selected_MJ) = 0.0625f*4.f; break;
                              case kk4: *mj_phase(selected_MJ) = 0.0625f*6.f; break;
                              case kk5: *mj_phase(selected_MJ) = 0.0625f*8.f; break;
                              case kk6: *mj_phase(selected_MJ) = 0.0625f*10.f; break;
                              case kk7: *mj_phase(selected_MJ) = 0.0625f*12.f; break;
                              case kk8: *mj_phase(selected_MJ) = 0.0625f*14.f; break;}
                         *mj_phase(selected_MJ) += /* if changed phase will be in range, change it */
                                                  (c==kk9)*((*mj_phase(selected_MJ)+phase_fine)<=max_phase) * phase_fine +
                                                  (c==kkL)*((*mj_phase(selected_MJ)-phase_fine)>=min_phase) * (-phase_fine) +
                                                       (c==kk0)*((*mj_phase(selected_MJ)+phase_normal)<=max_phase) * phase_normal +
                                                       (c==kkOO)*((*mj_phase(selected_MJ)-phase_normal)>=min_phase) * (-phase_normal) +
                                                            (c==kkQUOTESINGLE)*((*mj_phase(selected_MJ)+phase_coarse)<=max_phase) * phase_coarse +
                                                            (c==kkAA)*((*mj_phase(selected_MJ)-phase_coarse)>=min_phase) * (-phase_coarse);
                         menu_state = (c==kkP_REL)*NONE + (c!=kkP_REL)*P; /* detect P key release and exit P menu */
                    }
                    else if(menu_state==BACKSLASH){  /* turn signals LOW-HIGH */
                         switch(c){
                              case kk1:
                                   store(selected_MJ);
                                   *mj_signal(selected_MJ) = low_sig;
                                   break;
                              case kk2:
                                   store(selected_MJ);
                                   *mj_signal(selected_MJ) = high_sig;
                                   break;
                              case kkTAB:
                                   restore(selected_MJ);
                                   break;}
                         menu_state = (c==kkBACKSLASH_REL)*NONE + (c!=kkBACKSLASH_REL)*BACKSLASH;} /* detect BACKSLASH key release and exit BACKSLASH menu */
                    else if(menu_state==LOWSIG){  /* turn signals LOW */
                         switch(c){
                              case kkF1:
                                   store(MJ_1);
                                   mj1_sig = low_sig;
                                   break;
                              case kkF2:
                                   store(MJ_2);
                                   mj2_sig = low_sig;
                                   break;
                              case kkF3:
                                   store(MJ_3);
                                   mj3_sig = low_sig;
                                   break;
                              case kkF4:
                                   store(MJ_4);
                                   mj4_sig = low_sig;
                                   break;
                              case kkF5:
                                   store(MJ_5);
                                   mj5_sig = low_sig;
                                   break;}
                         menu_state = (c==kk1_REL)*NONE + (c!=kk1_REL)*LOWSIG;} /* detect 1 key release and exit LOWSIG menu */
                    else if(menu_state==HIGHSIG){  /* turn signals HIGH */
                         switch(c){
                              case kkF1:
                                   store(MJ_1);
                                   mj1_sig = high_sig;
                                   break;
                              case kkF2:
                                   store(MJ_2);
                                   mj2_sig = high_sig;
                                   break;
                              case kkF3:
                                   store(MJ_3);
                                   mj3_sig = high_sig;
                                   break;
                              case kkF4:
                                   store(MJ_4);
                                   mj4_sig = high_sig;
                                   break;
                              case kkF5:
                                   store(MJ_5);
                                   mj5_sig = high_sig;
                                   break;}
                         menu_state = (c==kk2_REL)*NONE + (c!=kk2_REL)*HIGHSIG;} /* detect 2 key release and exit HIGHSIG menu */
                    else if(menu_state==RESTORESIG){  /* restore a signal */
                         switch(c){
                              case kkF1: restore(MJ_1); break;
                              case kkF2: restore(MJ_2); break;
                              case kkF3: restore(MJ_3); break;
                              case kkF4: restore(MJ_4); break;
                              case kkF5: restore(MJ_5); break;}
                         menu_state = (c==kkTAB_REL)*NONE + (c!=kkTAB_REL)*RESTORESIG;} /* detect TAB key release and exit RESTORESIG menu */
                    /* TODO console ideas:
                     * togliere gli spazi tra comandi e roba? rd1f 2.2 == rd 1f 2.2 oppure addirittura rd1f2.2
                     * reactive???? rd 2f mul 1f 2
                     * sequence savefiles
                     * rnd -- randomize everything, o solo un parametro alla volta
                     * eddy -- sets all outputs to HIGH looooooooooool
                     * di base ci stanno i segnali [s1..s5] che sono quelli che controllo dall'interfaccia iniziale
                       che vengono solitamente routati agli output [o1..o5]
                     * ho altri segnali [sa..sz] che posso creare e routare dove e come voglio
                     * tt come numero accessibile del tempo che scorre, sul quale basare tutto cazzooooo
                    */
                    else if(menu_state==CONSOLE){
                         #ifdef DEBUG
                              Serial.println("entered CONSOLE");
                              #endif
                         /* console code here */
                         if(c==kkBACKSPACE){
                              commandPtr-=(commandPtr>0); // moves the command pointer one step back, if it's not already in initial position
                              command[commandPtr] = '\0';} // and writes a terminating 0
                         else if(c==kkESC){ /* abort command */
                              commandPtr = 0;
                              command[0] = '\0';} /* just reset the pointer */
                         else if(c==kkENTER){ /* execute command */
                              #ifdef DEBUG
                                   Serial.print("command is: ");
                                   Serial.println(command);
                                   #endif
                              if(startsWith(command, "ss ")){ /* save */
                                   char* saveName = command + 3;
                                   #ifdef DEBUG
                                        Serial.print("saveName is: ");
                                        Serial.println(saveName);
                                        #endif
                                   save(saveName);
                              }
                              if(startsWith(command, "ll ")){ /* load */
                                   char* loadName = command + 3;
                                   #ifdef DEBUG
                                        Serial.print("loadName is: ");
                                        Serial.println(loadName);
                                        #endif
                                   if(load(loadName)){
                                        /* TODO: something to confirm load success */
                                        #ifdef DEBUG
                                             Serial.println("loading SUCCESS!!!");
                                             #endif
                                   }
                                   else{
                                        /* TODO: flash error */
                                        #ifdef DEBUG
                                             Serial.println("loading FAIL.");
                                             #endif
                                   }
                              }
                              else if(startsWith(command, "rr ")){ /* ReDefine */
                                   #ifdef DEBUG
                                        Serial.println("entered RR command");
                                        #endif
                                   char rdName[MAX_VARNAME_LEN];
                                   float rdVal; /* cacca: per ora sono tutti float, poi se cambio non lo saranno */
                                   uint8_t rdNameIndex = 0;
                                   while(command[3+rdNameIndex]!=' '){ /* copy the name of the variable into rdName, until a whitespace is reached */
                                        rdName[rdNameIndex] = command[3+rdNameIndex];
                                        rdNameIndex++;}
                                   rdName[rdNameIndex]='\0'; /* terminate string */
                                   #ifdef DEBUG
                                        Serial.print("rdName: ");
                                        Serial.println(rdName);
                                        Serial.print("remaining string: ");
                                        Serial.println(command+3+rdNameIndex+1);
                                        #endif
                                   rdVal = str_toFloat(command+3+rdNameIndex+1); /* << here starts the value string */
                                   #ifdef DEBUG
                                        Serial.print("rdVal: ");
                                        Serial.println(rdVal);
                                        #endif
                                   /* TODO: mettere che posso cambiare anche il puntatore a funzione, oltre che i valori!!! */
                                   if(strEqual(rdName, "1f")){
                                        mj1_sig.freq=rdVal;}
                                   else if(strEqual(rdName, "1d")){
                                        mj1_sig.duty=rdVal;}
                                   else if(strEqual(rdName, "1p")){
                                        mj1_sig.phase=rdVal;}
                                        else if(strEqual(rdName, "2f")){
                                             mj2_sig.freq=rdVal;}
                                        else if(strEqual(rdName, "2d")){
                                             mj2_sig.duty=rdVal;}
                                        else if(strEqual(rdName, "2p")){
                                             mj2_sig.phase=rdVal;}
                                             else if(strEqual(rdName, "3f")){
                                                  mj3_sig.freq=rdVal;}
                                             else if(strEqual(rdName, "3d")){
                                                  mj3_sig.duty=rdVal;}
                                             else if(strEqual(rdName, "3p")){
                                                  mj3_sig.phase=rdVal;}
                                                  else if(strEqual(rdName, "4f")){
                                                       mj4_sig.freq=rdVal;}
                                                  else if(strEqual(rdName, "4d")){
                                                       mj4_sig.duty=rdVal;}
                                                  else if(strEqual(rdName, "4p")){
                                                       mj4_sig.phase=rdVal;}
                                                       else if(strEqual(rdName, "5f")){
                                                            mj5_sig.freq=rdVal;}
                                                       else if(strEqual(rdName, "5d")){
                                                            mj5_sig.duty=rdVal;}
                                                       else if(strEqual(rdName, "5p")){
                                                            mj5_sig.phase=rdVal;}
                              
                              }
                              if(strEqual(command, "wipe")){ /* wipe EEPROM clean */
                                   wipeEEPROMsoft();} /* all flags will be wiped */
                              if(strEqual(command, "reset")){ /* reset the arduino */
                                   arduReset();}
                              if(strEqual(command, "qq")){ /* quit console */
                                   #ifdef DEBUG
                                        Serial.println("exited CONSOLE");
                                        #endif
                                   menu_state = NONE;}
                              #ifdef DEBUG
                                   if(strEqual(command, "she")){ /* SHow Eeprom contents */
                                             Serial.println("EEPROM contents: ");
                                             for(h_DEBUG=0;h_DEBUG<EEPROM_SIZE;h_DEBUG++){
                                                  Serial.print(getEEPROMbyte(h_DEBUG));
                                                  Serial.print(" ");}
                                             Serial.println("");
                                             for(h_DEBUG=0;h_DEBUG<EEPROM_SIZE;h_DEBUG++){
                                                  Serial.print((char)getEEPROMbyte(h_DEBUG));
                                                  Serial.print(" ");}
                                             Serial.println("");
                                   }
                                   if(strEqual(command, "now")){ /* show current signal parameters */
                                        Serial.println("current signal parameters: ");
                                             Serial.print("mj1_sig: ");
                                             Serial.print(mj1_sig.freq);
                                             Serial.print(" ");
                                             Serial.print(mj1_sig.duty);
                                             Serial.print(" ");
                                             Serial.print(mj1_sig.phase);
                                             Serial.println("");
                                                  Serial.print("mj2_sig: ");
                                                  Serial.print(mj2_sig.freq);
                                                  Serial.print(" ");
                                                  Serial.print(mj2_sig.duty);
                                                  Serial.print(" ");
                                                  Serial.print(mj2_sig.phase);
                                                  Serial.println("");
                                                       Serial.print("mj3_sig: ");
                                                       Serial.print(mj3_sig.freq);
                                                       Serial.print(" ");
                                                       Serial.print(mj3_sig.duty);
                                                       Serial.print(" ");
                                                       Serial.print(mj3_sig.phase);
                                                       Serial.println("");
                                                            Serial.print("mj4_sig: ");
                                                            Serial.print(mj4_sig.freq);
                                                            Serial.print(" ");
                                                            Serial.print(mj4_sig.duty);
                                                            Serial.print(" ");
                                                            Serial.print(mj4_sig.phase);
                                                            Serial.println("");
                                                                 Serial.print("mj5_sig: ");
                                                                 Serial.print(mj5_sig.freq);
                                                                 Serial.print(" ");
                                                                 Serial.print(mj5_sig.duty);
                                                                 Serial.print(" ");
                                                                 Serial.print(mj5_sig.phase);
                                                                 Serial.println("");
                                   }
                              #endif
                              else{
                                   /* ERROR: unrecognized command */
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
                         menu_state = (c==kkSHIFT_ESC)*NONE + (c!=kkSHIFT_ESC)*menu_state; /* detect Shift+Esc key press and exit CONSOLE menu */
                         led_error_green.state = (menu_state==CONSOLE);
                    }
                    /* menu states END. */
                    
                    /* other keypresses */
                    if(c==kkF9){
                         led_error_red.state = !led_error_red.state;}
                    else if(c==kkF10){
                         led_error_green.state = !led_error_green.state;}
                    else if(c==kkF8 || c==kkSCREEN){
                         ledOn = !ledOn;}
                    else if(c==kkENTER){
                         buzzerOn = !buzzerOn;}
                    /* other keypresses END. */

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

#endif /* _NYX_HENRIK_H_ */

/*
,,code
,,nyx
,,music
*/