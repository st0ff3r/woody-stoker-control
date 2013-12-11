#include <pic18fregs.h>

#include <stdlib.h>
#include <stdio.h>
#include <pic16/adc.h>
#include <usart.h>
#include "config.h"
#include "pillefyrsstyring.h"
#include "glcd.h"
#include "menu_system.h"

#define DEBUG

int i;
unsigned long timer_2;
unsigned int boiler_temp;
unsigned int smoke_temp;
unsigned int chimney_temp;

unsigned char lcd_buf[22];

unsigned char last_button;

void main(void) {
    OSCCONbits.SCS = 0x10;
    OSCCONbits.IRCF = 0x6;	// 4 MHz

	timer_2 = 0;
	boiler_temp = 0;
	smoke_temp = 0;
	chimney_temp = 0;
	
	last_button = NONE;
	
	// init io
	EXT_FEEDER_L1_TRIS = 0;	// output
	EXT_FEEDER_L1 = 0;		// off
	
	FAN_L2_TRIS = 0;		// output
	FAN_L2 = 0;				// off
	
	INT_FEEDER_L3_TRIS = 0;	// output
	INT_FEEDER_L3 = 0;		// off
	
	HEATER_T3_L4_TRIS = 0;		// output
	HEATER_T3_L4 = 0;				// off
	
	B_UP_TRIS = 1;			// input
	B_DOWN_TRIS = 1;		// input
	B_MENU_TRIS = 1;		// input

	LAMBDA_TL082_TRIS = 1;	// input
	ALL_TEMP_NUL_TRIS = 1;	// input
	ALL_TEMP_NUL_1KOHM_TRIS = 1;	// input
	BOILER_TEMP_TRIS = 1;	// input
	SMOKE_TEMP_TRIS	= 1;	// input
	CHIMNEY_TEMP_TRIS = 1; 	// input

	// set up ad
	adc_open(6, ADC_FOSC_64, ADC_CFG_6A, ADC_FRM_RJUST | ADC_INT_OFF | ADC_VCFG_VDD_AN2);

	// timer 2
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0;
    T2CONbits.TOUTPS0 = 1;
    T2CONbits.TOUTPS1 = 0;
    T2CONbits.TOUTPS2 = 0;
    T2CONbits.TOUTPS3 = 1;
	IPR1bits.TMR2IP = 1;		// high priority
	PIR1bits.TMR2IF = 1;
	T2CONbits.TMR2ON = 1;
	PIE1bits.TMR2IE = 1;

	// timer 3
	T3CONbits.RD16 = 1;
	T3CONbits.TMR3CS = 0;	// internal clock source
	T3CONbits.T3CKPS0 = 1;
	T3CONbits.T3CKPS0 = 1;
	IPR2bits.TMR3IP = 0;		// low priority
	T3CONbits.TMR3ON = 1;
	PIE2bits.TMR3IE = 1;
	PIR2bits.TMR3IF = 1;

	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;	/* Enable Global interrupts   */	

	usart_open(	USART_TX_INT_OFF &
				USART_RX_INT_ON & 
				USART_BRGH_HIGH & 
				USART_ASYNCH_MODE & 
				USART_EIGHT_BIT &
				USART_CONT_RX,
				12     // 19200 kbps @ 4 MHz
	);

//	my_usart_open();

/*
	sleep_ms(100);
	sprintf(debug_buf, "Hardware ID: '%d'", eeprom_id);
	usart_puts(debug_buf);
	sleep_ms(500);
*/
//	usart_puts("serial working\n");

	lcd_init();
	lcd_print("OpenStoker starting...", 0, NON_INVERTED); // starting...");
	sleep_ms(3000);

	while (1) {
		if (!B_UP) {					// if up button pressed...
			if (!(last_button & UP)) {	// and if up button state changed
				last_button |= UP;		// change state for button to pressed
				// start timer
			}

		}
		else if (B_UP) {				// if up button released...
			if (last_button & UP) {		// and if up button state changed
				last_button &= ~UP;		// change state for button to released
				button_released(UP);
			}
		}

		if (!B_MENU) {					// if menu button pressed...
			if (!(last_button & MENU)) {// and if menu button state changed
				last_button |= MENU;	// change state for button to pressed
				// check timer
			}

		}
		else if (B_MENU) {				// if menu button released...
			if (last_button & MENU) {	// and if menu button state changed
				last_button &= ~MENU;	// change state for button to released
				button_released(MENU);
			}
		}

		if (!B_DOWN) {					// if down button pressed...
			if (!(last_button & DOWN)) {// and if down button state changed
				last_button |= DOWN;	// change state for button to pressed
				// check timer
			}

		}
		else if (B_DOWN) {				// if up button released...
			if (last_button & DOWN) {	// and if up button state changed
				last_button &= ~DOWN;	// change state for button to released
				button_released(DOWN);
			}
		}

			/*
		if (!B_MENU) {
			lcd_cls();
			lcd_print("Menu (fan)", 0, NON_INVERTED);
			FAN_L2 = 1;
			sleep_ms(1000);
		}
		if (!B_DOWN) {
			lcd_cls();
			lcd_print("Down (el-start)     >  ", 0, INVERTED);
			HEATER_T3_L4 = 1;
			sleep_ms(1000);
		}
		else {
			lcd_cls();
			do_menu_update();
			EXT_FEEDER_L1 = 0;
			FAN_L2 = 0;
			HEATER_T3_L4 = 0;
			sleep_ms(1000);
		}
*/
	}
}

static void timer_control(void) __interrupt 1 {
	if (PIR1bits.TMR2IF) {
		PR2 = TIMER2_RELOAD;		// 1 ms delay at 4 MHz
		PIR1bits.TMR2IF = 0;
		timer_2++;
		clrwdt();
	}
	// serial rx interrupt
	if (usart_drdy()) {
		// retransmit it
		usart_putc(usart_getc());
	}
}

void sleep_ms(unsigned long ms) {
	unsigned long start_timer_2;
	start_timer_2 = timer_2;	

// while the absolute value of the time diff < ms
	while ( (((signed long)(timer_2 - start_timer_2) < 0) ? (-1 * (timer_2 - start_timer_2)) : (timer_2 - start_timer_2)) < ms) {
		// do nothing
	}
}

void my_usart_open() {
	SPBRG = 32; // 20MHz => 9600 baud (BRGH = 0)
	TXSTAbits.BRGH = 0; // (0 = low speed)
	TXSTAbits.SYNC = 0; // (0 = asynchronous)
	
	// SPEN - Serial Port Enable Bit 
	RCSTAbits.SPEN = 1; // (1 = serial port enabled)

	// TXIE - USART Transmit Interupt Enable Bit
	PIE1bits.TXIE = 0; // (1 = enabled)

	// RCIE - USART Receive Interupt Enable Bit
	PIE1bits.RCIE = 1; // (1 = enabled)
	
	// TX9 - 9-bit Transmit Enable Bit
	TXSTAbits.TX9 = 0; // (0 = 8-bit transmit)
	
	// RX9 - 9-bit Receive Enable Bit
	RCSTAbits.RX9 = 0; // (0 = 8-bit reception)
	
	// CREN - Continuous Receive Enable Bit
	RCSTAbits.CREN = 1; // (1 = Enables receiver)
	
	// TXEN - Trasmit Enable Bit
	TXSTAbits.TXEN = 1; // (1 = transmit enabled)
}

unsigned char read_EEPROM(unsigned char address) {
	EECON1 = 0;									//ensure CFGS = 0 and EEPGD = 0 
	EEADR = address;
	EECON1bits.RD = 1;
	return(EEDATA);
}
 
void write_EEPROM(unsigned char address, unsigned char d) {
	char save_int;
	save_int = INTCON;					//save interrupt status
	EECON1 = 0;									//ensure CFGS=0 and EEPGD=0
	EECON1bits.WREN = 1;				//enable write to EEPROM
	EEADR = address;						//setup Address
	EEDATA = d;									//and data
	INTCONbits.GIE=0;						//No interrupts
	EECON2 = 0x55;							//required sequence #1
	EECON2 = 0xaa;							//#2
	EECON1bits.WR = 1;					//#3 = actual write
	INTCON = save_int;					//restore interrupts
	while(!PIR2bits.EEIF) {
		//wait until finished
	}
	EECON1bits.WREN = 0;				//disable write to EEPROM
}


