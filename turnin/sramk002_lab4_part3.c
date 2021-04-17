/*      Author: Sidharth Ramkumar (sramk002@ucr.edu)
 *       *  Partner(s) Name: 
 *        *      Lab Section: 022
 *         *      Assignment: Lab #4  Exercise #3
 *          *      Exercise Description: [optional - include for your own benefit]
 *           *
 *            *      I acknowledge all content contained herein, excluding template or example
 *             *      code, is my own original work.
 *              */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define X (PINA & 0x01)
#define Y  (PINA & 0x02)
#define pound (PINA & 0x04)   
#define lock (PINA & 0x80)

enum KeyPad { SMStart, Wait, Pound_Press, Pound_Wait, Y_Press, Y_Wait } KeyPad_State;

void TickFct(){
   switch(KeyPad_State) {
        case SMStart:
        KeyPad_State = Wait;
        break;

        case Wait:
        if (!X && !Y && pound){
        KeyPad_State = Pound_Press;
        } else {
        KeyPad_State = Wait;
        }
        break;

        case Pound_Press:
        if (pound && !Y && !X){
        KeyPad_State = Pound_Press;
        } else if (!pound && !X && !Y){
        KeyPad_State = Pound_Wait;
        } else if (pound && (X||Y)){
        KeyPad_State = Wait;
        }
        break;

        case Pound_Wait:
        if (!pound && !X && !Y){
        KeyPad_State = Pound_Wait;
        } else if (!pound && Y && !X){
        KeyPad_State = Y_Press;
        } else if (pound || X) {
        KeyPad_State = Wait;
        }
        break;

        case Y_Press:
        if (!Y && !pound && !X){
        KeyPad_State = Y_Wait;
        } else if (Y && !pound && !X){
        KeyPad_State = Y_Press;
        } else if (Y && (pound || X)){
        KeyPad_State = Wait;
        }
        break;

        case Y_Wait:
        if (lock){
        KeyPad_State = Wait;
        } else {
        KeyPad_State = Y_Wait;
        }
        break;
   }

   switch (KeyPad_State){
        case SMStart:
        PORTC = 0x00;

        case Wait
        PORTC = 0x01;
        PORTB = 0x00;
        break;

        case Pound_Press:
        PORTC = 0x02;
        PORTB = 0x00;
        break;

        case Pound_Wait:
        PORTC = 0x03;
        PORTB = 0x00;
        break;

        case Y_Press:
        PORTC = 0x04;
        PORTB = 0x00;
        break

        case Y_Wait:
        PORTC = 0x05;
        PORTB = 0x01;
        break;
   }
}
int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF;
        DDRB = 0xFF; PORTB = 0x00;
        DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

KeyPad_State = SM_Start;
    while (1) {
        TickFct();
    }
    return 1;
}
