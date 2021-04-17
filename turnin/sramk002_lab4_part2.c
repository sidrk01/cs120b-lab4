        
/*      Author: Sidharth Ramkumar (sramk002@ucr.edu)
 *  Partner(s) Name: 
 *      Lab Section: 022
 *      Assignment: Lab #4  Exercise #2
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define b1 (PINA & 0x01)
#define b2 (PINA & 0x02)

enum Num_States { SMStart, Wait, Inc, Dec, Reset} Num_State;

void TickFct(short *tmpC){
   switch(Num_State) {
        case SMStart:
        Num_State = Wait;
        break;

        case Wait:
        if (b1 && !b2){
        Num_State = Inc;
        } else if (!b1 && b2){
        Num_State = Dec;
        } else if (b1 && b2){
        Num_State = Reset;
        } else {
        Num_State = Wait;        
        }
        break;

        case Inc:
        if (b1 && !b2){
        Num_State = Inc;
        } else if (!b1 && !b2){
        Num_State = Wait;
        } else if (b1 && b2){
        Num_State = Reset;
        }
        break;

        case Dec:
        if (!b1 && b2){
        Num_State = Dec;
        } else if (!b1 && !b2){
        Num_State = Wait;
        } else if (b1 && b2){
        Num_State = Reset;
        }
        break;

        case Reset:
        if (b1 || b2){
        Num_State = Reset;
        } else {
        Num_State = Wait;
        }
        break;
   }

   switch (Num_State){
        case Inc:
        *tmpC += 1;
        break;

        case Dec:
        *tmpC -= 1;
        break;

        case Reset:
        *tmpC = 0x00;
        break;

        default:
        break;
   }
}
int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF;
        DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
        short tmpC = 0x07;
        Num_State = SMStart;
    while (1) {
        TickFct(&tmpC);
        PORTC = tmpC;
    }
    return 1;
}
