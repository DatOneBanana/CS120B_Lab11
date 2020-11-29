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
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int firstOrsecond = 1;


void transmit_data(unsigned char data){
	int i;
	for(i = 0; i < 8; ++i){
		if(firstOrsecond == 1){
			PORTC = 0x08;
		}else{
			PORTC = 0x20;
		}
		PORTC |= ((data >> i) & 0x01);
		PORTC |= 0x02;
	}
	if(firstOrsecond == 1){
		PORTC |= 0x04;
	} else {
		PORTC |= 0x10;
	}
	PORTC = 0x00;
}

enum States{Start, decide, increment, decrement, onOroff}state;
unsigned char value;
int counter = 0;

unsigned char temp;
unsigned char temp2;
unsigned int temp3 = 0;

void tick(){
	temp = ~PINB & 0x01;
	temp2 = ~PINB & 0x02;
	switch(state){
		case Start:
			state = decide;
			break;
		case decide:
			if(temp && temp2){
				state = onOroff;

			}
			else if(temp && !temp2){
				state = increment;
			}
			else if(!temp && temp2){
				state = decrement;
			}
			else { state = Start; }
			break;
		case increment:
			state = decide;
			break;
		case decrement:
			state = decide;
			break;
		case onOroff:
			state = decide;
			break;
		}
	switch(state){
		case Start:
			break;
		case decide:
			break;
		case increment:
			counter++;
			break;
		case decrement:
			counter--;
			break;
		case onOroff:
			if(temp3 == 1){
				temp3 = 0;
			}
			else{
				temp3 = 1;
			}
			break;
		}

}

enum SECONDSTATS{Start5, decide2, increment2, decrement2, onOroff2}state5;

int counter2 = 0;

unsigned char temp4;
unsigned char temp5;
unsigned char temp6;

void tick5(){
	temp4 = ~PINB & 0x04;
        temp5 = ~PINB & 0x08;
        switch(state5){
                case Start5:
                        state5 = decide2;
                        break;
                case decide2:
                        if(temp4 && temp5){
                                state5 = onOroff2;

                        }
                        else if(temp4 && !temp5){
                                state5 = increment2;
                        }
                        else if(!temp4 && temp5){
                                state5 = decrement2;
                        }
                        else { state5 = decide2; }
                        break;
                case increment2:
                        state5 = decide2;
                        break;
                case decrement2:
                        state5 = decide2;
                        break;
                case onOroff2:
                        state5 = decide2;
                        break;
                }
        switch(state5){
                case Start5:
                        break;
                case decide2:
                        break;
                case increment2:
                        counter2++;
                        break;
                case decrement2:
                        counter2--;
                        break;
                case onOroff2:
                        if(temp6 == 1){
                                temp6 = 0;
                        }
                        else{
                                temp6 = 1;
			}
			break;
		}
}


enum LEDSTATES{Start2, Led1, Led2, Led3, Led4, Led5, Led6, Led7} state2;

void tick2(){
	switch(state2){
		case Start2:
			state2 = Led1;
			break;
		case Led1:
			state2 = Led2;
			break;
		case Led2:
			state2 = Led3;
			break;
		case Led3:
			state2 = Led4;
			break;
		case Led4:
			state2 = Led5;
			break;
		case Led5:
			state2 = Led6;
			break;
		case Led6:
			state2 = Led7;
			break;
		case Led7:
			state2 = Led1;
			break;
	}
	switch(state2){
		case Start2:
			break;
		case Led1:
			value = 0x01;
			break;
		case Led2:
			value = 0x02;
			break;
		case Led3:
			value = 0x04;
			break;
		case Led4:
			value = 0x08;
			break;
		case Led5:
			value = 0x10;
			break;
		case Led6:
			value = 0x20;
			break;
		case Led7:
			value = 0x40;
			break;
	}
}

enum LED2STATES{Start3, Pat1, Pat2} state3;
void tick3(){
	switch(state3){
		case Start3:
			state3 = Pat1;
			break;
		case Pat1:
			state3 = Pat2;
			break;
		case Pat2:
			state3 = Pat1;
			break;
	}
	switch(state3){
		case Start3:
			break;
		case Pat1:
			value = 0xF0;
			break;
		case Pat2:
			value = 0x0F;
			break;
	}
}

enum LED3STATES{Start4, Phase1, Phase2, Phase3, Phase4} state4;

void tick4(){
	switch(state4){
		case Start4:
			state4 = Phase1;
			break;
		case Phase1:
			state4 = Phase2;
			break;
		case Phase2:
			state4 = Phase3;
			break;
		case Phase3:
			state4 = Phase4;
			break;
		case Phase4:
			state4 = Phase1;
			break;
	}
	switch(state4){
		case Start4:
			break;
		case Phase1:
			value = 0xC0;
			break;
		case Phase2:
			value = 0x30;
			break;
		case Phase3:
			value = 0x0C;
			break;
		case Phase4:
			value = 0x03;
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	TimerSet(200);
	TimerOn();

	state = Start;
	state2 = Start2;
	state3 = Start3;
	state4 = Start4;
	state5 = Start5;
	unsigned char nullVal = 0;
    /* Insert your solution below */
    while (1) {
	
	firstOrSecond = 1;
	tick();

	if(temp3 == 1){
		transmit_data(nullVal);
	}
	else{
		if(counter % 3 == 0){
			tick2();
		} else if(counter % 3 == 1){
			tick3();
		} else if(counter % 3 == 2){
			tick4();
		}
		transmit_data(value);
	}

	firstOrSecond = 0;
	tick5();
	if(temp6 == 1){
		transmit_data(nullVal);
	}
	else{
		if(counter2 % 3 == 0){
			tick2();
		} else if(counter % 3 == 1){
			tick3();
		} else if(counter % 3 == 2){
			tick4();
		}
		transmit_data(value);
	}
	while(!TimerFlag){
	}
	TimerFlag = 0;
    }
    return 1;
}
