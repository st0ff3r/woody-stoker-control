#include <pic18fregs.h>

#include <stdlib.h>
#include <stdio.h>
//#include <pic16/adc.h>
#include <usart.h>
#include "config.h"
#include "pillefyrsstyring.h"
#include "glcd.h"
//#include "menu_system.h"

#define AC_POWER_OUTS 6
#define DEBUG

unsigned int i;
unsigned long timer_1_ms;
unsigned int boiler_temp;
unsigned int smoke_temp;
unsigned int chimney_temp;

unsigned char lcd_buf[22];

//unsigned char last_button;

volatile unsigned char sensor_inputs;
unsigned char last_inputs;

unsigned char output_ac_power_pwm[AC_POWER_OUTS];
volatile unsigned char _output_ac_power_pwm[AC_POWER_OUTS];

void main(void) {
    OSCCONbits.SCS = 0x10;
    OSCCONbits.IRCF = 0x7;	// 8 MHz

	timer_1_ms = 0;
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
	usart_puts("OpenStoker starting... serial working\n\r");

	// set up ad
//	adc_open(6, ADC_FOSC_64, ADC_CFG_6A, ADC_FRM_RJUST | ADC_INT_OFF | ADC_VCFG_VDD_AN2);

	// init io
	init_latches();
	latched_lcd_power(1);
	lcd_init();
//	lcd_print("OpenStoker starting...", 0, NON_INVERTED); // starting...");
	set_ac_power(0x00, 0x00);
	
	sleep_ms(1000);
	RELAY = 1;
	
	last_inputs = get_inputs();
	output_ac_power_pwm[AC_POWER_OUTS] = (127, 127, 127, 127, 127, 127);

	for (i = 0; i < 100; i++) {
		lcd_plot_pixel(i, i);
	}
	while (1) {
		if (sensor_inputs != last_inputs) {
			last_inputs = sensor_inputs;
			_debug();	// blocks main for a while :-/
		}
	}
}

static void isr_high_prio(void) __interrupt 1 {
	if (INTCONbits.TMR0IF) {
		TMR0H = (unsigned char)(TIMER0_RELOAD >> 8);
		TMR0L = (unsigned char)TIMER0_RELOAD;   /* Reload the Timer ASAP */
		INTCONbits.TMR0IF = 0;  /* Clear the Timer Flag  */
	}
	// get inputs
	sensor_inputs = get_inputs();
	// set outputs
	for (i = 0; i < AC_POWER_OUTS; i++) {
		if (_output_ac_power_pwm[i] == 0) {
			// turn OFF ac power
			set_ac_power(/* EXT_FEEDER_L1 | */ FAN_L2 | INT_FEEDER_L3 | L5 | L6, 0x00);
			_output_ac_power_pwm[i] = output_ac_power_pwm[i];		// reload values
		}
		else {
			set_ac_power(/* EXT_FEEDER_L1 | */ FAN_L2 | INT_FEEDER_L3 | L5 | L6, 0xff);
			_output_ac_power_pwm[i]--;
		}
	}
}

static void isr_low_prio(void) __interrupt 2 {
	if (PIR1bits.TMR1IF) {
		TMR1H = (unsigned char)(TIMER1_RELOAD >> 8);    // 8 ms delay at 8 MHz
		TMR1L = (unsigned char)TIMER1_RELOAD;
		PIR1bits.TMR1IF = 0;    /* Clear the Timer Flag  */
		timer_1_ms++;
	}

	// serial rx interrupt
	if (usart_drdy()) {
		// retransmit it
		usart_putc(usart_getc());
	}
}

void sleep_ms(unsigned long ms) {
	unsigned long start_timer_1_ms;
	start_timer_1_ms = timer_1_ms;	

// while the absolute value of the time diff < ms
	while ( (((signed long)(timer_1_ms - start_timer_1_ms) < 0) ? (-1 * (timer_1_ms - start_timer_1_ms)) : (timer_1_ms - start_timer_1_ms)) < ms) {
		// do nothing
	}
}

void init_timers() {
	// timer 0
	T0CONbits.TMR0ON = 1;
	T0CONbits.T08BIT = 0;   // use timer0 16-bit counter
	T0CONbits.T0CS = 0;             // internal clock source
	T0CONbits.PSA = 1;              // disable timer0 prescaler
	INTCON2bits.TMR0IP = 1; // high priority
	INTCONbits.T0IE = 1;    // Ensure that TMR0 Interrupt is enabled
	INTCONbits.TMR0IF = 1;  // Force Instant entry to Timer 0 Interrupt

	// timer 1
	T1CONbits.TMR1ON = 1;
	T1CONbits.RD16 = 1;
	T1CONbits.TMR1CS = 0;   // internal clock source
	T1CONbits.T1OSCEN = 0;  // dont put t1 on pin
	T1CONbits.T1CKPS0 = 1;
	T1CONbits.T1CKPS1 = 1;
	IPR1bits.TMR1IP = 0;	// low priority
	PIE1bits.TMR1IE = 1;	// Ensure that TMR1 Interrupt is enabled
	PIR1bits.TMR1IF = 1;	// Force Instant entry to Timer 1 Interrupt

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
	SPBRG = 103;					// 8MHz => 19230 baud
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