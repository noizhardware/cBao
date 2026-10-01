/*** TODO
	
*/
/*** DOCU
	
*/

#define FILENAME_CREATED "2022f19-0925"
#define FILENAME_VERSION "2026c13-1102"

/*** DEFINES */
	#define SERIAL_ON
/* DEFINES end. */

/*** INCLUDES */
	#include <avr/io.h>
/* INCLUDES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
/* FUNCTION DECLARATIONS end. */



/*** MAIN */
void setup(){
	/**** serial setup */
	#ifdef SERIAL_ON
		uint16_t startTime;
		Serial.begin( 9600 );
		startTime = millis();
		while(!Serial){ /* that alone would stall the system if no serial connection is present :( */
			if ((millis()- startTime) >= 2000){ /* if it takes more than 2seconds to find the Serial, fuck it, we'll do without it. */
				break;
			}
		}
		Serial.print("== FILENAME v."); Serial.println(FILENAME_VERSION);
	#endif /* SERIAL_ON */
}

void loop(){
}
/* MAIN end. */

/*** FUNCTION DEFINITIONS */
/* FUNCTION DEFINITIONS end. */
