;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.3.0 #8604 (Oct 27 2013) (Mac OS X x86_64)
; This file was generated Thu Dec 12 21:26:20 2013
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------
	list	p=18f4620
	radix	dec
	CONFIG	OSC=INTIO67,FCMEN=OFF,IESO=OFF
	CONFIG	PWRT=OFF,BOREN=OFF
	CONFIG	WDT=OFF
	CONFIG	CCP2MX=PORTC,PBADEN=OFF,LPT1OSC=OFF,MCLRE=ON
	CONFIG	STVREN=OFF,LVP=OFF,XINST=OFF


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_last_inputs
	global	_last_button
	global	_lcd_buf
	global	_chimney_temp
	global	_smoke_temp
	global	_boiler_temp
	global	_i
	global	_sleep_ms
	global	_init_timers
	global	_init_latches
	global	_set_ac_power
	global	_get_inputs
	global	__debug
	global	_timer_2
	global	_main

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	_PORTAbits
	extern	_PORTBbits
	extern	_PORTCbits
	extern	_PORTDbits
	extern	_PORTEbits
	extern	_LATAbits
	extern	_LATBbits
	extern	_LATCbits
	extern	_LATDbits
	extern	_LATEbits
	extern	_DDRAbits
	extern	_TRISAbits
	extern	_DDRBbits
	extern	_TRISBbits
	extern	_DDRCbits
	extern	_TRISCbits
	extern	_DDRDbits
	extern	_TRISDbits
	extern	_DDREbits
	extern	_TRISEbits
	extern	_OSCTUNEbits
	extern	_PIE1bits
	extern	_PIR1bits
	extern	_IPR1bits
	extern	_PIE2bits
	extern	_PIR2bits
	extern	_IPR2bits
	extern	_EECON1bits
	extern	_RCSTAbits
	extern	_TXSTAbits
	extern	_T3CONbits
	extern	_CMCONbits
	extern	_CVRCONbits
	extern	_ECCP1ASbits
	extern	_PWM1CONbits
	extern	_BAUDCONbits
	extern	_BAUDCTLbits
	extern	_CCP2CONbits
	extern	_CCP1CONbits
	extern	_ADCON2bits
	extern	_ADCON1bits
	extern	_ADCON0bits
	extern	_SSPCON2bits
	extern	_SSPCON1bits
	extern	_SSPSTATbits
	extern	_T2CONbits
	extern	_T1CONbits
	extern	_RCONbits
	extern	_WDTCONbits
	extern	_HLVDCONbits
	extern	_LVDCONbits
	extern	_OSCCONbits
	extern	_T0CONbits
	extern	_STATUSbits
	extern	_INTCON3bits
	extern	_INTCON2bits
	extern	_INTCONbits
	extern	_STKPTRbits
	extern	_stdin
	extern	_stdout
	extern	_PORTA
	extern	_PORTB
	extern	_PORTC
	extern	_PORTD
	extern	_PORTE
	extern	_LATA
	extern	_LATB
	extern	_LATC
	extern	_LATD
	extern	_LATE
	extern	_DDRA
	extern	_TRISA
	extern	_DDRB
	extern	_TRISB
	extern	_DDRC
	extern	_TRISC
	extern	_DDRD
	extern	_TRISD
	extern	_DDRE
	extern	_TRISE
	extern	_OSCTUNE
	extern	_PIE1
	extern	_PIR1
	extern	_IPR1
	extern	_PIE2
	extern	_PIR2
	extern	_IPR2
	extern	_EECON1
	extern	_EECON2
	extern	_EEDATA
	extern	_EEADR
	extern	_EEADRH
	extern	_RCSTA
	extern	_TXSTA
	extern	_TXREG
	extern	_RCREG
	extern	_SPBRG
	extern	_SPBRGH
	extern	_T3CON
	extern	_TMR3
	extern	_TMR3L
	extern	_TMR3H
	extern	_CMCON
	extern	_CVRCON
	extern	_ECCP1AS
	extern	_PWM1CON
	extern	_BAUDCON
	extern	_BAUDCTL
	extern	_CCP2CON
	extern	_CCPR2
	extern	_CCPR2L
	extern	_CCPR2H
	extern	_CCP1CON
	extern	_CCPR1
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_ADCON2
	extern	_ADCON1
	extern	_ADCON0
	extern	_ADRES
	extern	_ADRESL
	extern	_ADRESH
	extern	_SSPCON2
	extern	_SSPCON1
	extern	_SSPSTAT
	extern	_SSPADD
	extern	_SSPBUF
	extern	_T2CON
	extern	_PR2
	extern	_TMR2
	extern	_T1CON
	extern	_TMR1
	extern	_TMR1L
	extern	_TMR1H
	extern	_RCON
	extern	_WDTCON
	extern	_HLVDCON
	extern	_LVDCON
	extern	_OSCCON
	extern	_T0CON
	extern	_TMR0
	extern	_TMR0L
	extern	_TMR0H
	extern	_STATUS
	extern	_FSR2L
	extern	_FSR2H
	extern	_PLUSW2
	extern	_PREINC2
	extern	_POSTDEC2
	extern	_POSTINC2
	extern	_INDF2
	extern	_BSR
	extern	_FSR1L
	extern	_FSR1H
	extern	_PLUSW1
	extern	_PREINC1
	extern	_POSTDEC1
	extern	_POSTINC1
	extern	_INDF1
	extern	_WREG
	extern	_FSR0L
	extern	_FSR0H
	extern	_PLUSW0
	extern	_PREINC0
	extern	_POSTDEC0
	extern	_POSTINC0
	extern	_INDF0
	extern	_INTCON3
	extern	_INTCON2
	extern	_INTCON
	extern	_PROD
	extern	_PRODL
	extern	_PRODH
	extern	_TABLAT
	extern	_TBLPTR
	extern	_TBLPTRL
	extern	_TBLPTRH
	extern	_TBLPTRU
	extern	_PC
	extern	_PCL
	extern	_PCLATH
	extern	_PCLATU
	extern	_STKPTR
	extern	_TOS
	extern	_TOSL
	extern	_TOSH
	extern	_TOSU
	extern	_usart_drdy
	extern	_usart_getc
	extern	_usart_putc
	extern	_latched_lcd_power
	extern	__mullong

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
PCLATH	equ	0xffa
PCLATU	equ	0xffb
WREG	equ	0xfe8
BSR	equ	0xfe0
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1
r0x05	res	1
r0x06	res	1
r0x07	res	1
r0x08	res	1
r0x09	res	1
r0x0a	res	1
r0x0b	res	1
r0x0c	res	1
r0x0d	res	1
r0x0e	res	1
r0x0f	res	1

udata_pillefyrsstyring_0	udata
_i	res	2

udata_pillefyrsstyring_1	udata
_boiler_temp	res	2

udata_pillefyrsstyring_2	udata
_smoke_temp	res	2

udata_pillefyrsstyring_3	udata
_chimney_temp	res	2

udata_pillefyrsstyring_4	udata
_lcd_buf	res	22

udata_pillefyrsstyring_5	udata
_last_button	res	1

udata_pillefyrsstyring_6	udata
_last_inputs	res	1

udata_pillefyrsstyring_7	udata
_timer_2	res	4

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block for absolute section
; ;-----------------------------------------
S_pillefyrsstyring_ivec_0x1_timer_control	code	0X000008
ivec_0x1_timer_control:
	GOTO	_timer_control

; I code from now on!
; ; Starting pCode block
S_pillefyrsstyring__main	code
_main:
;	.line	27; pillefyrsstyring.c	OSCCONbits.SCS = 0x10;
	MOVF	_OSCCONbits, W
	ANDLW	0xfc
	MOVWF	_OSCCONbits
;	.line	28; pillefyrsstyring.c	OSCCONbits.IRCF = 0x6;	// 4 MHz
	MOVF	_OSCCONbits, W
	ANDLW	0x8f
	IORLW	0x60
	MOVWF	_OSCCONbits
	BANKSEL	_timer_2
;	.line	30; pillefyrsstyring.c	timer_2 = 0;
	CLRF	_timer_2, B
	BANKSEL	(_timer_2 + 1)
	CLRF	(_timer_2 + 1), B
	BANKSEL	(_timer_2 + 2)
	CLRF	(_timer_2 + 2), B
	BANKSEL	(_timer_2 + 3)
	CLRF	(_timer_2 + 3), B
	BANKSEL	_boiler_temp
;	.line	31; pillefyrsstyring.c	boiler_temp = 0;
	CLRF	_boiler_temp, B
	BANKSEL	(_boiler_temp + 1)
	CLRF	(_boiler_temp + 1), B
	BANKSEL	_smoke_temp
;	.line	32; pillefyrsstyring.c	smoke_temp = 0;
	CLRF	_smoke_temp, B
	BANKSEL	(_smoke_temp + 1)
	CLRF	(_smoke_temp + 1), B
	BANKSEL	_chimney_temp
;	.line	33; pillefyrsstyring.c	chimney_temp = 0;
	CLRF	_chimney_temp, B
	BANKSEL	(_chimney_temp + 1)
	CLRF	(_chimney_temp + 1), B
;	.line	35; pillefyrsstyring.c	init_timers();
	CALL	_init_timers
;	.line	60; pillefyrsstyring.c	init_latches();
	CALL	_init_latches
;	.line	61; pillefyrsstyring.c	latched_lcd_power(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_power
	MOVF	POSTINC1, F
;	.line	64; pillefyrsstyring.c	sleep_ms(1000);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x03
	MOVWF	POSTDEC1
	MOVLW	0xe8
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
;	.line	65; pillefyrsstyring.c	set_ac_power(0x00, 0x00);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_set_ac_power
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
;	.line	66; pillefyrsstyring.c	RELAY = 1;
	BSF	_LATCbits, 5
;	.line	68; pillefyrsstyring.c	TRISCbits.TRISC7 = 0x1;	// rx
	BSF	_TRISCbits, 7
;	.line	69; pillefyrsstyring.c	TRISCbits.TRISC6 = 0x0;	// tx
	BCF	_TRISCbits, 6
_00106_DS_:
;	.line	71; pillefyrsstyring.c	LATCbits.LATC6 = PORTCbits.RC7;
	CLRF	r0x00
	BTFSC	_PORTCbits, 7
	INCF	r0x00, F
	MOVF	r0x00, W
	ANDLW	0x01
	RRNCF	WREG, W
	RRNCF	WREG, W
	MOVWF	PRODH
	MOVF	_LATCbits, W
	ANDLW	0xbf
	IORWF	PRODH, W
	MOVWF	_LATCbits
	BRA	_00106_DS_
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring___debug	code
__debug:
;	.line	167; pillefyrsstyring.c	void _debug() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	168; pillefyrsstyring.c	latched_lcd_power(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_power
	MOVF	POSTINC1, F
;	.line	169; pillefyrsstyring.c	sleep_ms(500);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xf4
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
;	.line	170; pillefyrsstyring.c	latched_lcd_power(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_power
	MOVF	POSTINC1, F
;	.line	171; pillefyrsstyring.c	sleep_ms(500);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVLW	0xf4
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__get_inputs	code
_get_inputs:
;	.line	155; pillefyrsstyring.c	unsigned char get_inputs() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	159; pillefyrsstyring.c	LATCH_DATA_TRIS = 0xff;		// inputs
	MOVLW	0xff
	MOVWF	_TRISD
;	.line	160; pillefyrsstyring.c	LATCH_1 = LATCH_1_ENABLED;
	BCF	_LATAbits, 4
;	.line	161; pillefyrsstyring.c	data = LATCH_DATA_READ; // & 0b00100000;
	MOVFF	_PORTD, r0x00
;	.line	162; pillefyrsstyring.c	LATCH_1 = LATCH_1_DISABLED;
	BSF	_LATAbits, 4
;	.line	164; pillefyrsstyring.c	return data;
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__set_ac_power	code
_set_ac_power:
;	.line	145; pillefyrsstyring.c	void set_ac_power(unsigned char header_mask, unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
;	.line	146; pillefyrsstyring.c	header_mask &= 0b00111111;		// only 6 outputs on this hardware
	MOVLW	0x3f
	ANDWF	r0x00, F
;	.line	147; pillefyrsstyring.c	value &= header_mask;
	MOVF	r0x00, W
	ANDWF	r0x01, F
;	.line	148; pillefyrsstyring.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	149; pillefyrsstyring.c	LATCH_DATA = value;
	MOVFF	r0x01, _LATD
;	.line	150; pillefyrsstyring.c	LATCH_2 = LATCH_2_ENABLED;
	BSF	_LATAbits, 7
;	.line	151; pillefyrsstyring.c	LATCH_2 = LATCH_2_DISABLED;
	BCF	_LATAbits, 7
;	.line	152; pillefyrsstyring.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__init_latches	code
_init_latches:
;	.line	126; pillefyrsstyring.c	void init_latches() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	127; pillefyrsstyring.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	128; pillefyrsstyring.c	LATCH_1_TRIS = 0x0; 			// output
	BCF	_TRISAbits, 4
;	.line	129; pillefyrsstyring.c	LATCH_1 = LATCH_1_DISABLED;	// no inputs from input latch
	BSF	_LATAbits, 4
;	.line	131; pillefyrsstyring.c	LATCH_2_TRIS = 0x0; 			// output
	BCF	_TRISAbits, 7
;	.line	132; pillefyrsstyring.c	LATCH_2 = LATCH_2_DISABLED;
	BCF	_LATAbits, 7
;	.line	134; pillefyrsstyring.c	LATCH_3_TRIS = 0x0; 			// output
	BCF	_TRISAbits, 6
;	.line	135; pillefyrsstyring.c	LATCH_3 = LATCH_3_DISABLED;
	BCF	_LATAbits, 6
;	.line	137; pillefyrsstyring.c	LATCH_4_TRIS = 0x0; 			// output
	BCF	_TRISCbits, 2
;	.line	138; pillefyrsstyring.c	LATCH_4 = LATCH_4_DISABLED;
	BCF	_LATCbits, 2
;	.line	140; pillefyrsstyring.c	RELAY_TRIS = 0x0;				// output
	BCF	_TRISCbits, 5
;	.line	141; pillefyrsstyring.c	RELAY = 0x0;					// all power outputs off
	BCF	_LATCbits, 5
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__init_timers	code
_init_timers:
;	.line	99; pillefyrsstyring.c	void init_timers() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	101; pillefyrsstyring.c	T2CONbits.T2CKPS0 = 1;
	BSF	_T2CONbits, 0
;	.line	102; pillefyrsstyring.c	T2CONbits.T2CKPS1 = 0;
	BCF	_T2CONbits, 1
;	.line	103; pillefyrsstyring.c	T2CONbits.T2OUTPS0 = 1;
	BSF	_T2CONbits, 3
;	.line	104; pillefyrsstyring.c	T2CONbits.T2OUTPS1 = 0;
	BCF	_T2CONbits, 4
;	.line	105; pillefyrsstyring.c	T2CONbits.T2OUTPS2 = 0;
	BCF	_T2CONbits, 5
;	.line	106; pillefyrsstyring.c	T2CONbits.T2OUTPS3 = 1;
	BSF	_T2CONbits, 6
;	.line	107; pillefyrsstyring.c	IPR1bits.TMR2IP = 1;		// high priority
	BSF	_IPR1bits, 1
;	.line	108; pillefyrsstyring.c	PIR1bits.TMR2IF = 1;
	BSF	_PIR1bits, 1
;	.line	109; pillefyrsstyring.c	T2CONbits.TMR2ON = 1;
	BSF	_T2CONbits, 2
;	.line	110; pillefyrsstyring.c	PIE1bits.TMR2IE = 1;
	BSF	_PIE1bits, 1
;	.line	113; pillefyrsstyring.c	T3CONbits.RD16 = 1;
	BSF	_T3CONbits, 7
;	.line	114; pillefyrsstyring.c	T3CONbits.TMR3CS = 0;	// internal clock source
	BCF	_T3CONbits, 1
;	.line	115; pillefyrsstyring.c	T3CONbits.T3CKPS0 = 1;
	BSF	_T3CONbits, 4
;	.line	116; pillefyrsstyring.c	T3CONbits.T3CKPS0 = 1;
	BSF	_T3CONbits, 4
;	.line	117; pillefyrsstyring.c	IPR2bits.TMR3IP = 0;		// low priority
	BCF	_IPR2bits, 1
;	.line	118; pillefyrsstyring.c	T3CONbits.TMR3ON = 1;
	BSF	_T3CONbits, 0
;	.line	120; pillefyrsstyring.c	PIR2bits.TMR3IF = 1;
	BSF	_PIR2bits, 1
;	.line	122; pillefyrsstyring.c	INTCONbits.PEIE = 1;
	BSF	_INTCONbits, 6
;	.line	123; pillefyrsstyring.c	INTCONbits.GIE = 1;	/* Enable Global interrupts   */	
	BSF	_INTCONbits, 7
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__sleep_ms	code
_sleep_ms:
;	.line	89; pillefyrsstyring.c	void sleep_ms(unsigned long ms) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x09, POSTDEC1
	MOVFF	r0x0a, POSTDEC1
	MOVFF	r0x0b, POSTDEC1
	MOVFF	r0x0c, POSTDEC1
	MOVFF	r0x0d, POSTDEC1
	MOVFF	r0x0e, POSTDEC1
	MOVFF	r0x0f, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
;	.line	91; pillefyrsstyring.c	start_timer_2 = timer_2;	
	MOVFF	_timer_2, r0x04
	MOVFF	(_timer_2 + 1), r0x05
	MOVFF	(_timer_2 + 2), r0x06
	MOVFF	(_timer_2 + 3), r0x07
_00130_DS_:
;	.line	94; pillefyrsstyring.c	while ( (((signed long)(timer_2 - start_timer_2) < 0) ? (-1 * (timer_2 - start_timer_2)) : (timer_2 - start_timer_2)) < ms) {
	MOVF	r0x04, W
	BANKSEL	_timer_2
	SUBWF	_timer_2, W, B
	MOVWF	r0x08
	MOVF	r0x05, W
	BANKSEL	(_timer_2 + 1)
	SUBWFB	(_timer_2 + 1), W, B
	MOVWF	r0x09
	MOVF	r0x06, W
	BANKSEL	(_timer_2 + 2)
	SUBWFB	(_timer_2 + 2), W, B
	MOVWF	r0x0a
	MOVF	r0x07, W
	BANKSEL	(_timer_2 + 3)
	SUBWFB	(_timer_2 + 3), W, B
	MOVWF	r0x0b
	MOVF	r0x08, W
	MOVWF	r0x0c
	MOVF	r0x09, W
	MOVWF	r0x0d
	MOVF	r0x0a, W
	MOVWF	r0x0e
	MOVF	r0x0b, W
	MOVWF	r0x0f
	BSF	STATUS, 0
	BTFSS	r0x0f, 7
	BCF	STATUS, 0
	BNC	_00135_DS_
	MOVF	r0x0b, W
	MOVWF	POSTDEC1
	MOVF	r0x0a, W
	MOVWF	POSTDEC1
	MOVF	r0x09, W
	MOVWF	POSTDEC1
	MOVF	r0x08, W
	MOVWF	POSTDEC1
	MOVLW	0xff
	MOVWF	POSTDEC1
	MOVLW	0xff
	MOVWF	POSTDEC1
	MOVLW	0xff
	MOVWF	POSTDEC1
	MOVLW	0xff
	MOVWF	POSTDEC1
	CALL	__mullong
	MOVWF	r0x0c
	MOVFF	PRODL, r0x0d
	MOVFF	PRODH, r0x0e
	MOVFF	FSR0L, r0x0f
	MOVLW	0x08
	ADDWF	FSR1L, F
	BRA	_00136_DS_
_00135_DS_:
	MOVFF	r0x08, r0x0c
	MOVFF	r0x09, r0x0d
	MOVFF	r0x0a, r0x0e
	MOVFF	r0x0b, r0x0f
_00136_DS_:
	MOVF	r0x03, W
	SUBWF	r0x0f, W
	BNZ	_00143_DS_
	MOVF	r0x02, W
	SUBWF	r0x0e, W
	BNZ	_00143_DS_
	MOVF	r0x01, W
	SUBWF	r0x0d, W
	BNZ	_00143_DS_
	MOVF	r0x00, W
	SUBWF	r0x0c, W
_00143_DS_:
	BTFSS	STATUS, 0
	BRA	_00130_DS_
	MOVFF	PREINC1, r0x0f
	MOVFF	PREINC1, r0x0e
	MOVFF	PREINC1, r0x0d
	MOVFF	PREINC1, r0x0c
	MOVFF	PREINC1, r0x0b
	MOVFF	PREINC1, r0x0a
	MOVFF	PREINC1, r0x09
	MOVFF	PREINC1, r0x08
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__timer_control	code
_timer_control:
;	.line	76; pillefyrsstyring.c	static void timer_control(void) __interrupt 1 {
	MOVFF	STATUS, POSTDEC1
	MOVFF	BSR, POSTDEC1
	MOVWF	POSTDEC1
	MOVFF	PRODL, POSTDEC1
	MOVFF	PRODH, POSTDEC1
	MOVFF	FSR0L, POSTDEC1
	MOVFF	FSR0H, POSTDEC1
	MOVFF	PCLATH, POSTDEC1
	MOVFF	PCLATU, POSTDEC1
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	77; pillefyrsstyring.c	if (PIR1bits.TMR2IF) {
	BTFSS	_PIR1bits, 1
	BRA	_00114_DS_
;	.line	78; pillefyrsstyring.c	PR2 = TIMER2_RELOAD;		// 1 ms delay at 4 MHz
	MOVLW	0x18
	MOVWF	_PR2
;	.line	79; pillefyrsstyring.c	PIR1bits.TMR2IF = 0;
	BCF	_PIR1bits, 1
	BANKSEL	_timer_2
;	.line	80; pillefyrsstyring.c	timer_2++;
	INCF	_timer_2, F, B
	BNC	_00114_DS_
	BANKSEL	(_timer_2 + 1)
	INCF	(_timer_2 + 1), F, B
	BNC	_00114_DS_
	BANKSEL	(_timer_2 + 2)
	INCFSZ	(_timer_2 + 2), F, B
	BRA	_10168_DS_
	BANKSEL	(_timer_2 + 3)
	INCF	(_timer_2 + 3), F, B
_10168_DS_:
_00125_DS_:
_00114_DS_:
;	.line	83; pillefyrsstyring.c	if (usart_drdy()) {
	CALL	_usart_drdy
	MOVWF	r0x00
	MOVF	r0x00, W
	BZ	_00117_DS_
;	.line	85; pillefyrsstyring.c	usart_putc(usart_getc());
	CALL	_usart_getc
	MOVWF	r0x00
	MOVF	r0x00, W
	CALL	_usart_putc
_00117_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	MOVFF	PREINC1, PCLATU
	MOVFF	PREINC1, PCLATH
	MOVFF	PREINC1, FSR0H
	MOVFF	PREINC1, FSR0L
	MOVFF	PREINC1, PRODH
	MOVFF	PREINC1, PRODL
	MOVF	PREINC1, W
	MOVFF	PREINC1, BSR
	MOVFF	PREINC1, STATUS
	RETFIE	



; Statistics:
; code size:	  896 (0x0380) bytes ( 0.68%)
;           	  448 (0x01c0) words
; udata size:	   36 (0x0024) bytes ( 0.94%)
; access size:	   16 (0x0010) bytes


	end
