#include <pic18fregs.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pic16/adc.h>
#include <usart.h>
#include "config.h"
#include "pillefyrsstyring.h"
#include "glcd.h"
//#include "menu_system.h"

#define AC_POWER_OUTS 6
#define AD_INPUTS 8
#define DEBUG
//#define DEBUG_PWM_ON_LED
#define WITHOUT_SERIAL

unsigned int i;
unsigned long timer_1_ms;
//unsigned char buffer[32];

volatile unsigned char sensor_inputs;
unsigned char last_inputs;

volatile unsigned char output_ac_power_pwm[AC_POWER_OUTS];
volatile unsigned char ac_power_pwm_counter;

unsigned int ad_inputs[AD_INPUTS];

// command queue
#define QUEUE_SIZE	100
volatile unsigned int fifo_head, fifo_tail;
volatile unsigned char fifo_buffer[QUEUE_SIZE];

#define COMMAND_LENGTH 20 //AC_POWER_OUTS + 1
unsigned char command[COMMAND_LENGTH + 1];
unsigned char command_index;
unsigned char valid_command[AC_POWER_OUTS + 1];

unsigned char _latch_2_data;

void main(void) {
	volatile unsigned char c;
	unsigned char j;
	unsigned char buffer[10];
	
    OSCCONbits.SCS = 0x10;
    OSCCONbits.IRCF = 0x7;	// 8 MHz
	WDTCONbits.SWDTEN = 1;	// enable watchdog
	clr_wdt();

	timer_1_ms = 0;
	
	fifo_head = 0;
	fifo_tail = 0;
	command_index = 0;
	
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

	sleep_ms(1000);	// let stuff settle...
	usart_puts("OpenStoker starting... serial working\n\r");

	// set up ad
	// #define __SDCC_ADC_STYLE    1822200
   /*
    * The reference voltage configuration should be factored out into
    * the config argument (ADC_VCFG_*) to adc_open to facilitate a
    * merger with the 1220-style ADC.
    */
	/*
		#define ADC_CFG_16A     0x00
	*/
	/* 15 analog ports cannot be configured! */
	/*
		#define ADC_CFG_14A     0x01
		#define ADC_CFG_13A     0x02
		#define ADC_CFG_12A     0x03
		#define ADC_CFG_11A     0x04
		#define ADC_CFG_10A     0x05
		#define ADC_CFG_9A      0x06
		#define ADC_CFG_8A      0x07
		#define ADC_CFG_7A      0x08
		#define ADC_CFG_6A      0x09
		#define ADC_CFG_5A      0x0a
		#define ADC_CFG_4A      0x0b
		#define ADC_CFG_3A      0x0c
		#define ADC_CFG_2A      0x0d
		#define ADC_CFG_1A      0x0e
		#define ADC_CFG_0A      0x0f
	*/
	/*
		* adc_open's `config' argument:
		* ADCON1
		*
		* ADC_FRM_* | ADC_INT_* | ADC_VCFG_* | ADC_NVCFG_* | ADC_PVCFG_*
		*
		*    7     6     5     4     3     2     1     0
		* +-----+-----+-----+-----+-----+-----+-----+-----+
		* | FRM | INT |   VCFG    |   PVCFG   |   NVCFG   |
		* +-----+-----+-----+-----+-----+-----+-----+-----+
	*/

	adc_open(ADC_CHN_0, ADC_FOSC_4 | ADC_ACQT_20, ADC_CFG_12A, ADC_FRM_RJUST | ADC_INT_OFF | ADC_VCFG_AN3_AN2);

	// init io
	init_latches();
//	lcd_init();
//	lcd_print("OpenStoker starting...", 0, NON_INVERTED); // starting...");
	
#ifndef WITHOUT_SERIAL
	while (!fifo_in_use()) {
		latched_lcd_power(1);
		sleep_ms(1000);
		latched_lcd_power(0);
		sleep_ms(1000);
	}
#else
	RELAY = 1;
#endif
	latched_lcd_power(1);
	
	last_inputs = get_inputs();
//	for (i = 0; i < 100; i++) {
//		lcd_plot_pixel(i, i);
//	}
	while (1) {
		if (fifo_get(&c)) {
			if (c == '\n' || c == '.') {
				// end of command
				command_index = 0;
				if (validate_command(command, valid_command)) {
					clr_wdt();
					RELAY = 1;

					switch (valid_command[0]) {					// only look at first character
						case 's':	// set ac power values
							for (j = 0; j < AC_POWER_OUTS; j++) {
								output_ac_power_pwm[j] = valid_command[j + 1];
							}
							usart_putc('!');	// ok values set to ac power pwm system
							usart_puts("\n\r");
							break;
						case 'g':
							sprintf(buffer, "g%02x\n\r", sensor_inputs);
							usart_puts(buffer);
							break;
						case 'z':
							usart_putc('z');
							usart_puts("\n\r");
							sleep_ms(100);
							reset();
							break;
						case 'a':
							for (j = 0; j < AD_INPUTS; j++) {
								sprintf(buffer, "ad%d: %04x\n\r", j, ad_inputs[0]);
								usart_puts(buffer);
							}
							break;
						default:
							usart_putc('?');	// unknown command
					}		
				}
				else {
					usart_putc('?');			// command not valid
				}

			}
			else {
				// add character to command and check for overflow
				if (command_index <= COMMAND_LENGTH) {
					command[command_index] = c;
					command_index++;
				}
				else {
					command[COMMAND_LENGTH] = '\0';	// null terminate it
					command_index = 0;
					usart_putc('+');		// overflow
					usart_puts("\n\r");
				}
			}
		}

		if (sensor_inputs != last_inputs) {
			last_inputs = sensor_inputs;
			_debug();	// blocks main for a while :-/
		}
		
		// get ad values
		for (j = 0; j < AD_INPUTS; j++) {
			adc_setchannel(j);
			adc_conv();
			while(adc_busy()) {
				// wait
			}
			ad_inputs[j] = adc_read();
		}
	}
}

static void isr_high_prio(void) __interrupt 1 {
	if (INTCONbits.TMR0IF) {
		TMR0H = (unsigned char)(TIMER0_RELOAD >> 8);
		TMR0L = (unsigned char)TIMER0_RELOAD;   /* Reload the Timer ASAP */
		INTCONbits.TMR0IF = 0;  /* Clear the Timer Flag  */

		// get inputs
		sensor_inputs = get_inputs();
		// set outputs

		for (i = 0; i < AC_POWER_OUTS; i++) {
			if (ac_power_pwm_counter < output_ac_power_pwm[i]) {
				// turn ON ac power
				set_ac_power(1 << i, 0xff);
#ifdef DEBUG_PWM_ON_LED
				if (i == 0) {
					RELAY = 1;
				}
#endif
			}
			else {
				// turn OFF ac power
				set_ac_power(1 << i, 0x00);
#ifdef DEBUG_PWM_ON_LED
				if (i == 0) {
					RELAY = 0;
				}
#endif
			}
		}
		ac_power_pwm_counter++;
	}
}

static void isr_low_prio(void) __interrupt 2 {
	unsigned char c;
	if (PIR1bits.TMR1IF) {
		TMR1H = (unsigned char)(TIMER1_RELOAD >> 8);    // 1 ms delay at 8 MHz
		TMR1L = (unsigned char)TIMER1_RELOAD;
		PIR1bits.TMR1IF = 0;    /* Clear the Timer Flag  */
		timer_1_ms++;
	}

	// serial rx interrupt
	if (usart_drdy()) {
		// retransmit it
		c = usart_getc();
		fifo_put(c);
		usart_putc(c);
	}
	// ad
//	if (PIR2bits.TMR3IF) {
//		TMR3H = (unsigned char)(TIMER3_RELOAD >> 8);    // 8 ms delay at 8 MHz
//		TMR3L = (unsigned char)TIMER3_RELOAD;
//		PIR2bits.TMR3IF = 0;    /* Clear the Timer Flag  */
		
//		usart_puts("yes\n\r");
//    }
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
	T0CONbits.T0PS0 = 0;
	T0CONbits.T0PS1 = 0;
	T0CONbits.T0PS2 = 0;	// prescaler 1:2
	T0CONbits.T08BIT = 0;   // use timer0 16-bit counter
	T0CONbits.T0CS = 0;             // internal clock source
	T0CONbits.PSA = 0;              // enable timer0 prescaler
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

	/*
    // timer 2
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 1;
    T2CONbits.T2OUTPS0 = 1;
    T2CONbits.T2OUTPS1 = 1;
    T2CONbits.T2OUTPS2 = 1;
    T2CONbits.T2OUTPS3 = 1;
    IPR1bits.TMR2IP = 0;            // low priority
    PIE1bits.TMR2IE = 1;
    PIR1bits.TMR2IF = 1;
	*/

	/*
    // timer 3
    T3CONbits.RD16 = 1;
    T3CONbits.TMR3CS = 0;   // internal clock source
    T3CONbits.T3CKPS0 = 1;
    T3CONbits.T3CKPS0 = 1;
    IPR2bits.TMR3IP = 0;            // low priority
    T3CONbits.TMR3ON = 1;
    PIE2bits.TMR3IE = 1;
    PIR2bits.TMR3IF = 1;
	*/

	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;	/* Enable Global interrupts   */	
}

void init_latches() {
	LATCH_DATA_TRIS = 0x00;		// outputs
	LATCH_1_TRIS = 0x0; 			// output
	LATCH_1 = LATCH_1_DISABLED;	// no inputs from input latch
	
	LATCH_2_TRIS = 0x0; 			// output
	LATCH_2 = LATCH_2_DISABLED;
	_latch_2_data = 0x00;
	
	LATCH_3_TRIS = 0x0; 			// output
	LATCH_3 = LATCH_3_DISABLED;
	
	LATCH_4_TRIS = 0x0; 			// output
	LATCH_4 = LATCH_4_DISABLED;
	
	RELAY_TRIS = 0x0;				// output
	RELAY = 0x0;					// all power outputs off
	
}

void set_ac_power(unsigned char header_mask, unsigned char value) {
	header_mask &= (/*EXT_FEEDER_L1 |*/ FAN_L2 | INT_FEEDER_L3 /*| HEATER_L4 | L5 | L6*/);	// BUG HERE! turning on L1 or L6 restarts
	
	value &= header_mask;
	LATCH_DATA_TRIS = 0x00;		// outputs
	if (value) {	// set it
		_latch_2_data |= header_mask;
		LATCH_DATA = _latch_2_data;
	}
	else {			// clear it
		_latch_2_data &= ~header_mask;
		LATCH_DATA = _latch_2_data;
	}
	LATCH_2 = LATCH_2_ENABLED;
	LATCH_2 = LATCH_2_DISABLED;
	LATCH_DATA = 0x00;
}

unsigned char get_inputs() {
	unsigned char data;
//	unsigned char prev_tris;
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

unsigned char fifo_in_use() {
	return fifo_head - fifo_tail;
}

unsigned char fifo_put(unsigned char c) {
	if (fifo_in_use() != QUEUE_SIZE) {
		fifo_buffer[fifo_head++ % QUEUE_SIZE] = c;
		return 1;
	}
	else {
		return 0;
	}
}

unsigned char fifo_get(unsigned char *c) {
	if (fifo_in_use() != 0) {
		*c = fifo_buffer[fifo_tail++ % QUEUE_SIZE];
		return 1;
	}
	else {
		return 0;
	}
}

void base64decode(unsigned char *s, unsigned char *buffer) {
    char *h = s; /* this will walk through the hex string */
    char *b = buffer; /* point inside the buffer */
    
    /* offset into this string is the numeric value */
    char xlate[] = "0123456789abcdef";
    
    while (*h) {
        *b = ((strchr(xlate, *h) - xlate) * 16) /* multiply leading digit by 16 */
        + ((strchr(xlate, *(h+1)) - xlate));
        h += 2;
        b++;
    }
}

void base64encode(unsigned char *s) {
//    unsigned char * buffer = malloc((strlen(s) * 2) + 1);
    
//    char *h = s; /* this will walk through the hex string */
//    char *b = buffer; /* point inside the buffer */
//    while (*h) {
        
//    }
}

unsigned char validate_command(unsigned char *encoded_command, unsigned char *validated_command) {
    unsigned char decoded_command[7 + 2];
    unsigned int checksum, received_checksum;
    
    base64decode(encoded_command, decoded_command);
    received_checksum = (decoded_command[7] << 8) + decoded_command[8];
	checksum = crc16(decoded_command, 7, 0);
    
    if (received_checksum == checksum) {
		memcpy(validated_command, decoded_command, 7);
        return 1;
    }
    else {
        return 0;
    }
}

void reset() {
__asm 
  reset
__endasm;
}

void _debug() {
	latched_lcd_power(0);
	sleep_ms(200);
	latched_lcd_power(1);
	sleep_ms(200);
}