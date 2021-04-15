/*	Author: Sidharth Ramkumar (sramk002)
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define button (PINA & 0x01)

enum LED_States {LED_waitPA0, LED_pressPA0, LED_wait2PA0, LED_press2PA0 } LED_State;

void TickFct_LED(){
   switch (LED_State) {
	case LED_waitPA0: 
	if (button) {
	LED_State = LED_pressPA0;
	} else {
	LED_State = LED_waitPA0;
	}		
	break;

	case LED_pressPA0: 
	if (button) {
	LED_State = LED_pressPA0;
	} else {
	LED_State = LED_wait2PA0;
	} 
	break;

	case LED_wait2PA0:
	if (button) {
	LED_State = LED_press2PA0;
	} else {
	LED_State = LED_wait2PA0;
	}	
	break;

	case LED_press2PA0:
	if (button) {
	LED_State = LED_press2PA0;
	} else {
	LED_State = LED_waitPA0;
	}
	break;

	default:
	break;		 
   }

   switch(LED_State){
   	case LED_pressPA0:
	case LED_wait2PA0: 
	PORTB = 0x02;
	break;

	case LED_waitPA0:
	case LED_press2PA0:
	PORTB = 0x01;
	break;

	default: 
	break; 
   }   	
}



int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	TickFct_LED();	
    }
    return 1;
}
