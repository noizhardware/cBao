#ifndef _BAOAVR_H_
#define _BAOAVR_H_

void dw(uint8_t pin, bool val);


/***************************/

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
}

bool cycleCheck(uint32_t* lastMillis, uint16_t cycleLength){ /* branchless protothreading */
     uint32_t currentMillis = millis(); /* overflows every 49.7 days - 136 years if I manage to keep trasck of seconds on another int32 and manage the overflow */
     bool cond = (currentMillis - *lastMillis >= cycleLength); /* has (cycleLength) milliseconds passed since last reading? */
     *lastMillis = (currentMillis * cond) + ((*lastMillis)*(!cond)); /* if yes, update lastMillis with current time, if not, lastMillis remains unchanged */
     return cond;} /* retuns of the (cycleLength) time has passed or not */

#endif /* _BAOAVR_H_ */