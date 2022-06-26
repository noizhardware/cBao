/* arduino micro (ATmega32U4) */
#ifndef _ARDUMICRO_H_
#define _ARDUMICRO_H_

     /* pins [2..12] are just numbers on the board */

     #define RX 0
     #define TX 1
     #define SDA 2
     #define SCL 3

     #define RXLED 17
     #define SS RXLED /* they're connected */
     #define TXLED 30
     #define LED_BUILTIN 13 /* green LED */

     #define SCK 15
     #define MISO 14
     #define MOSI 16

     #define A0 A0
     #define A1 A1
     #define A2 A2
     #define A3 A3
     #define A4 A4
     #define A5 A5

     #define 4 A6
     #define 6 A7

#endif /* _ARDUMICRO_H_ */