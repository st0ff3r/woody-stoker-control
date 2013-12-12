#include <pic18fregs.h>

#include <stdlib.h>
#include <stdio.h>
//#include <pic16/adc.h>
#include <usart.h>
#include "config.h"
#include "pillefyrsstyring.h"
#include "glcd.h"
//#include "menu_system.h"

#define DEBUG

unsigned int i;
unsigned long timer_2;
unsigned int boiler_temp;
unsigned int smoke_temp;
unsigned int chimney_temp;

unsigned char lcd_buf[22];

unsigned char last_button;

unsigned char last_inputs;

void main(void) {
    OSCCONbits.SCS = 0x10;
    OSCCONbits.IRCF = 0x6;	// 4 MHz

	timer_2 = 0;
	boiler_temp = 0;
	smoke_temp = 0;
	chimney_temp = 0;
	
    // set up interrupt and timers
    RCONbits.IPEN = 1;

	init_timers();

	// USART interrupt low priority
	IPR1bits.RCIP = 0;
	IPR1bits.TXIP = 0;
	/*
	usart_open(	USART_TX_INT_OFF &
				USART_RX_INT_ON & 
				USART_BRGH_HIGH & 
				USART_ASYNCH_MODE & 
				USART_EIGHT_BIT &
				USART_CONT_RX,
				12     // 19200 kbps @ 4 MHz
	);
	*/
	my_usart_open();

/*
	sleep_ms(100);
	sprintf(debug_buf, "Hardware ID: '%d'", eeprom_id);
	usart_puts(debug_buf);
	sleep_ms(500);
*/
//	usart_puts("serial working\n");

	// set up ad
//	adc_open(6, ADC_FOSC_64, ADC_CFG_6A, ADC_FRM_RJUST | ADC_INT_OFF | ADC_VCFG_VDD_AN2);

	// init io
	init_latches();
	latched_lcd_power(1);
//	lcd_init();
//	lcd_print("OpenStoker starting...", 0, NON_INVERTED); // starting...");
	set_ac_power(0x00, 0x00);
	sleep_ms(1000);
	RELAY = 1;
	
	last_inputs = get_inputs();
	for (i = 0; i < 100; i++) {
		lcd_plot_pixel(i, i);
	}
	while (1) {
		usart_puts("serial working\n\r");
		if (get_inputs() != last_inputs) {
			last_inputs = get_inputs();
			_debug();
		}
		set_ac_power(/* EXT_FEEDER_L1 | */ FAN_L2 | INT_FEEDER_L3 | L5 | L6, 0xff);
		sleep_ms(200);
		set_ac_power(/* EXT_FEEDER_L1 | */ FAN_L2 | INT_FEEDER_L3 | L5 | L6, 0x00);
		sleep_ms(200);
	}
}

static void timer_control(void) __interrupt 1 {
	if (PIR1bits.TMR2IF) {
		PR2 = TIMER2_RELOAD;		// 1 ms delay at 4 MHz
		PIR1bits.TMR2IF = 0;
		timer_2++;
	}
}

static void slow_timer_control(void) __interrupt 2 {
	if (PIR2bits.TMR3IF) {
		TMR3H = (unsigned char)(TIMER3_RELOAD >> 8);    // 8 ms delay at 8 MHz
		TMR3L = (unsigned char)TIMER3_RELOAD;
		PIR2bits.TMR3IF = 0;    /* Clear the Timer Flag  */

	}	// serial rx interrupt
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

void init_timers() {
	// timer 2
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0;
    T2CONbits.T2OUTPS0 = 1;
    T2CONbits.T2OUTPS1 = 0;
    T2CONbits.T2OUTPS2 = 0;
    T2CONbits.T2OUTPS3 = 1;
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
}

void init_latches() {
	LATCH_DATA_TRIS = 0x00;		// outputs
	LATCH_1_TRIS = 0x0; 			// output
	LATCH_1 = LATCH_1_DISABLED;	// no inputs from input latch
	
	LATCH_2_TRIS = 0x0; 			// output
	LATCH_2 = LATCH_2_DISABLED;
	
	LATCH_3_TRIS = 0x0; 			// output
	LATCH_3 = LATCH_3_DISABLED;
	
	LATCH_4_TRIS = 0x0; 			// output
	LATCH_4 = LATCH_4_DISABLED;
	
	RELAY_TRIS = 0x0;				// output
	RELAY = 0x0;					// all power outputs off
	
}

void set_ac_power(unsigned char header_mask, unsigned char value) {
	header_mask &= 0b00111111;		// only 6 outputs on this hardware
	value &= header_mask;
	LATCH_DATA_TRIS = 0x00;		// outputs
	LATCH_DATA = value;
	LATCH_2 = LATCH_2_ENABLED;
	LATCH_2 = LATCH_2_DISABLED;
	LATCH_DATA = 0x00;
}

unsigned char get_inputs() {
	unsigned char data;
	unsigned char prev_tris;
//	prev_tris = LATCH_DATA_TRIS;
	LATCH_DATA_TRIS = 0xff;		// inputs
	LATCH_1 = LATCH_1_ENABLED;
	data = LATCH_DATA_READ; // & 0b00100000;
	LATCH_1 = LATCH_1_DISABLED;
//	LATCH_DATA_TRIS = prev_tris;
	return data;
}

void my_usart_open() {
	SPBRG = 103;					// 4MHz => 9615 baud
	TXSTAbits.BRGH = 1;	// (1 = high speed)
	TXSTAbits.SYNC = 0;	// (0 = asynchronous)
	BAUDCONbits.BRG16 = 1;
	
	// SPEN - Serial Port Enable Bit 
	RCSTAbits.SPEN = 1; // (1 = serial port enabled)

	// TXIE - USART Transmit Interupt Enable Bit
	PIE1bits.TXIE = 0; // (1 = enabled)
	IPR1bits.TXIP = 0; // USART Tx on low priority interrupt

	// RCIE - USART Receive Interupt Enable Bit
	PIE1bits.RCIE = 1; // (1 = enabled)
	IPR1bits.RCIP = 0; // USART Rx on low priority interrupt
	
	// TX9 - 9-bit Transmit Enable Bit
	TXSTAbits.TX9 = 0; // (0 = 8-bit transmit)
	
	// RX9 - 9-bit Receive Enable Bit
	RCSTAbits.RX9 = 0; // (0 = 8-bit reception)
	
	// CREN - Continuous Receive Enable Bit
	RCSTAbits.CREN = 1; // (1 = Enables receiver)
	
	// TXEN - Trasmit Enable Bit
	TXSTAbits.TXEN = 1; // (1 = transmit enabled)
}

void _debug() {
	latched_lcd_power(1);
	sleep_ms(500);
	latched_lcd_power(0);
	sleep_ms(500);
}