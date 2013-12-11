#include <pic18fregs.h>

#include <stdlib.h>
#include <stdio.h>
#include "test.h"

#pragma config  OSC = INTIO67, FCMEN = OFF, IESO = OFF                  //CONFIG1H 
#pragma config  PWRT = OFF, BOREN = OFF                                 //CONFIG2L 
#pragma config  WDT = OFF                                               //CONFIG2H 
#pragma config  CCP2MX = PORTC, PBADEN = OFF, LPT1OSC = OFF, MCLRE = ON //CONFIG3H 
#pragma config  STVREN = OFF, LVP = OFF, XINST = OFF                    //CONFIG4L 

int i;

void main(void) {
    OSCCONbits.SCS = 0x10;	// Internal oscillator block
    OSCCONbits.IRCF = 0x7;	// 8 MHz (INTOSC drives clock directly)
	
	TRISC = 0x00;
	
	while (1) {
		PORTC = 0xFF;
		for (i = 0; i < 10000; i++) {
			// do nothing
		}
		PORTC = 0x00;
		for (i = 0; i < 10000; i++) {
			// do nothing
		}
	}
}