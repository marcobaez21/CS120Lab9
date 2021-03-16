/*	Author: Marco Baez
 *  Partner(s) Name: NA
 *	Lab Section:21
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link: https://drive.google.com/drive/folders/1-1_Zf0EL01XEZT5VoUOW-SXjQH8O5fE9?usp=sharing
 *
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;
unsigned char CombineLED  = 0x00;

enum ThreeLEDsStates {StartThreeLEDs, ThreeLEDsOn} three;
enum BlinkingLEDStates {StartBlinkingLED, BlinkingLEDOn} blink;
enum CombineLEDsStates {StartCombineLED, CombineLEDOn} combine;

void ThreeLEDsSM(){
	switch(three){
		case StartThreeLEDs:
			three = ThreeLEDsOn;
			break;

		case ThreeLEDsOn:
			if(threeLEDs<3){++threeLEDs;}
			else{threeLEDs=1;}
			break;
	}
}

void BlinkingLEDSM(){
	switch(blink){
		case StartBlinkingLED:
			blink=BlinkingLEDOn;
			break;

		case BlinkingLEDOn:
			if(blinkingLED==0){blinkingLED=1;}
			else {blinkingLED=0;}
			break;
	}
}

void CombineLEDsSM(){
	switch(combine){
		case StartCombineLED:
			combine=CombineLEDOn;
			break;

		case CombineLEDOn:
			if(threeLEDs == 1){CombineLED=0x01;}
			if(threeLEDs == 2){CombineLED=0x02;}
			if(threeLEDs == 3){CombineLED=0x04;}

			if(blinkingLED==1){CombineLED=CombineLED | 0x08;}
			else{CombineLED=CombineLED & 0xF7;}
			break;
	}
	PORTB=CombineLED;
}

int main(void) {
    
    DDRB=0xFF; PORTB=0x00;

    three=StartThreeLEDs;
    blink=StartBlinkingLED;
    combine=StartCombineLED;

    TimerSet(1000);
    TimerOn();

    while (1) {
	ThreeLEDsSM();
	BlinkingLEDSM();
	CombineLEDsSM();
	while(!TimerFlag){}
	TimerFlag=0;
    }
    return 0;
}
