/*      Author: Sidharth Ramkumar (sramk002@ucr.edu)
 *       *  Partner(s) Name: 
 *        *      Lab Section: 022
 *         *      Assignment: Lab #4  Exercise #5
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
enum LockState {Locked = 0, Unlocked = 1} door;

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
        break;
         
        case Wait:
        case Pound_Press:
        case Pound_Wait:
        case Y_Press:
        door = Locked;
        break;

        case Y_Wait:
        door = Unlocked;
        break;
       
     default: 
       door = Locked;
   }
  PORTB = door;
}
int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF;
        DDRB = 0xFF; PORTB = 0x00;
//        DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

KeyPad_State = SMStart;
door = Locked;
    while (1) {
        TickFct();
    }
    return 1;
}
