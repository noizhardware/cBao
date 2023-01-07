#ifndef _BAOARDU_H_
#define _BAOARDU_H_

#define BAOARDU_H_VERSION "2022j22-1317"

/*** TODO

*/
/*** DOCU

*/

/*** INCLUDES */
	#include <avr/interrupt.h>
	#include <avr/sleep.h>
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
	#define __inline__ inline /* arduino IDE */
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
	void dw(uint8_t pin, bool val); /* slim digitalWrite */
	void arduStop();
	void arduReset(); /* Restarts program from beginning but does not reset the peripherals and registers */
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
void arduStop(){
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();  // Disable interrupts
	sleep_mode();
	return;
}

void dw(uint8_t pin, bool val){ /* slim digitalWrite */
     uint8_t bit = digitalPinToBitMask(pin);
     uint8_t port = digitalPinToPort(pin);

     volatile uint8_t* out;
     /*volatile in C actually came into existence for the purpose of not caching the values of the variable automatically. It will tell the compiler not to cache the value of this variable. So it will generate code to take the value of the given volatile variable from the main memory every time it encounters it. This mechanism is used because at any time the value can be modified by the OS or any interrupt. So using volatile will help us accessing the value afresh every time.*/
     
     // if (port == NOT_A_PIN){
     //      return;}

     out = portOutputRegister(port); /* address passing */

     // cacca - questo potrebbe essere da rimettere
     // uint8_t oldSREG = SREG;
     // cli();

     // if (val == LOW) {
     //      *out &= ~bit;} /* set the bit to 0 */
     // else{
     //      *out |= bit;} /* set the bit to 1 */
     
     // same, but branchless:
     *out = ((val == LOW)*(*out & ~bit)) + ((val == HIGH)*(*out | bit));

     // cacca - anche questo
     // SREG = oldSREG;
     return;
}

// // cacca: usually already defined in baothread.h
// bool cycleCheck(uint32_t* lastMillis, uint16_t cycleLength){ /* branchless protothreading */
//      uint32_t currentMillis = millis(); /* overflows every 49.7 days - 136 years if I keep track of seconds on another int32 and manage the overflow */
//      bool cond = (currentMillis - *lastMillis >= cycleLength); /* has (cycleLength) milliseconds passed since last reading? */
//      *lastMillis = (currentMillis * cond) + ((*lastMillis)*(!cond)); /* if yes, update lastMillis with current time, if not, lastMillis remains unchanged */
//      return cond;} /* retuns whether the (cycleLength) time has passed or not */
// 
// bool microCheck(uint32_t* lastUsec, uint16_t cycleLength){ /* usec resolution */
//      uint32_t currentUsec = micros(); /* overflows every 71.58 minutes */
//      bool cond = (currentUsec - *lastUsec >= cycleLength); /* has (cycleLength) microseconds passed since last reading? */
//      *lastUsec = (currentUsec * cond) + ((*lastUsec)*(!cond)); /* if yes, update lastUsec with current time, if not, lastUsec remains unchanged */
//      return cond;} /* retuns whether the (cycleLength) time has passed or not */

void arduReset(){ /* Restarts program from beginning but does not reset the peripherals and registers */
	asm volatile ("  jmp 0");
}
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _BAOARDU_H_ */