/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void transmit_data(unsigned char data){
	int i;
	for(i = 0; i < 8; ++i){
		PORTC = 0x08;
		PORTC |= ((data >> i) & 0x01);
		PORTC |= 0x02;
	}
	PORTC |= 0x04;
	PORTC = 0x00;
}

enum States {Start, Init, Increment, Decrement, Reset, Wait, WaitA} state;
unsigned char value;

unsigned char temp;
unsigned char temp2;

void tick(){
	temp = ~PINB & 0x01;
	temp2 = ~PINB & 0x02;
	switch (state){
		case Start:
			state = Init;
			break;
		case Init:
			if(temp && temp2){
				state = Reset;
			}
			else if(temp && !temp2){
				state = Increment;
			}
			else if(temp2 && !temp){
				state = Decrement;
			}
			else{
				state = Init;
			}
			break;
		case Increment:
			if(!temp && !temp2){
				state = Init;
			}
			else{
				state = WaitA;
			}
			break;
		case Decrement:
			if(temp2 && temp){
				state = Reset;
			}
			else{
				state = WaitA;
			}
			break;
		case Reset:
      			if(temp && temp2){
                                state = Reset;
                        }
                        else if(temp && !temp2){
                                state = Increment;
                        }
                        else if(temp2 && !temp){
                                state = Decrement;
                        }
                        else{
                                state = Init;
                        }
                        break;
		case Wait:
			if(temp && temp2){
                                state = Reset;
                        }
                        else if(temp && !temp2){
                                state = Increment;
                        }
                        else if(temp2 && !temp){
                                state = Decrement;
                        }
                        else{
                                state = Wait;
                        }
                        break;
		case WaitA:
                       if(temp && temp2){
                                state = Reset;
                        }
                        else if(!temp && !temp2){
                                state = Wait;
                        }
                        else{
                                state = WaitA;
                        }
                        break;
		default:
			state = Start;
			break;
		}
	switch(state){
		case Start:
			break;
		case Init:
			break;
		case Increment:
			if(value < 255){
				value++;
			}
			break;
		case Decrement:
			if(value > 0){
				value--;
			}
			break;
		case Reset:
			value = 0x00;
			break;
		default:
			break;
		}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	state = Start;
	value = 1;
    /* Insert your solution below */
    while (1) {
	tick();
	transmit_data(value);
    }
    return 1;
}
