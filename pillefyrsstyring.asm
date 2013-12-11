;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.0 #6037 (Jul 16 2012) (Mac OS X x86_64)
; This file was generated Tue Dec 18 04:56:14 2012
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------
	list	p=18f4620
	__config 0x300001, 0x01
	__config 0x300002, 0x1e
	__config 0x300003, 0x00
	__config 0x300005, 0x01
	__config 0x300006, 0x81
	__config 0x300008, 0x0f
	__config 0x300009, 0xc0
	__config 0x30000a, 0x0f
	__config 0x30000b, 0xe0
	__config 0x30000c, 0x0f
	__config 0x30000d, 0x40

	radix dec

;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global _lcd_buf
	global _chimney_temp
	global _smoke_temp
	global _boiler_temp
	global _i
	global _sleep_ms
	global _my_usart_open
	global _read_EEPROM
	global _write_EEPROM
	global _timer_2
	global _last_button
	global _main

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern _PORTAbits
	extern _PORTBbits
	extern _PORTCbits
	extern _PORTDbits
	extern _PORTEbits
	extern _LATAbits
	extern _LATBbits
	extern _LATCbits
	extern _LATDbits
	extern _LATEbits
	extern _TRISAbits
	extern _TRISBbits
	extern _TRISCbits
	extern _TRISDbits
	extern _TRISEbits
	extern _OSCTUNEbits
	extern _PIE1bits
	extern _PIR1bits
	extern _IPR1bits
	extern _PIE2bits
	extern _PIR2bits
	extern _IPR2bits
	extern _EECON1bits
	extern _RCSTAbits
	extern _TXSTAbits
	extern _T3CONbits
	extern _CMCONbits
	extern _CVRCONbits
	extern _ECCP1ASbits
	extern _PWM1CONbits
	extern _BAUDCONbits
	extern _CCP2CONbits
	extern _CCP1CONbits
	extern _ADCON2bits
	extern _ADCON1bits
	extern _ADCON0bits
	extern _SSPCON2bits
	extern _SSPCON1bits
	extern _SSPSTATbits
	extern _T2CONbits
	extern _T1CONbits
	extern _RCONbits
	extern _WDTCONbits
	extern _HLVDCONbits
	extern _OSCCONbits
	extern _T0CONbits
	extern _STATUSbits
	extern _FSR2Hbits
	extern _BSRbits
	extern _FSR1Hbits
	extern _FSR0Hbits
	extern _INTCON3bits
	extern _INTCON2bits
	extern _INTCONbits
	extern _TBLPTRUbits
	extern _PCLATHbits
	extern _PCLATUbits
	extern _STKPTRbits
	extern _TOSUbits
	extern _stdin
	extern _stdout
	extern _PORTA
	extern _PORTB
	extern _PORTC
	extern _PORTD
	extern _PORTE
	extern _LATA
	extern _LATB
	extern _LATC
	extern _LATD
	extern _LATE
	extern _TRISA
	extern _TRISB
	extern _TRISC
	extern _TRISD
	extern _TRISE
	extern _OSCTUNE
	extern _PIE1
	extern _PIR1
	extern _IPR1
	extern _PIE2
	extern _PIR2
	extern _IPR2
	extern _EECON1
	extern _EECON2
	extern _EEDATA
	extern _EEADR
	extern _EEADRH
	extern _RCSTA
	extern _TXSTA
	extern _TXREG
	extern _RCREG
	extern _SPBRG
	extern _SPBRGH
	extern _T3CON
	extern _TMR3L
	extern _TMR3H
	extern _CMCON
	extern _CVRCON
	extern _ECCP1AS
	extern _PWM1CON
	extern _BAUDCON
	extern _CCP2CON
	extern _CCPR2L
	extern _CCPR2H
	extern _CCP1CON
	extern _CCPR1L
	extern _CCPR1H
	extern _ADCON2
	extern _ADCON1
	extern _ADCON0
	extern _ADRESL
	extern _ADRESH
	extern _SSPCON2
	extern _SSPCON1
	extern _SSPSTAT
	extern _SSPADD
	extern _SSPBUF
	extern _T2CON
	extern _PR2
	extern _TMR2
	extern _T1CON
	extern _TMR1L
	extern _TMR1H
	extern _RCON
	extern _WDTCON
	extern _HLVDCON
	extern _OSCCON
	extern _T0CON
	extern _TMR0L
	extern _TMR0H
	extern _STATUS
	extern _FSR2L
	extern _FSR2H
	extern _PLUSW2
	extern _PREINC2
	extern _POSTDEC2
	extern _POSTINC2
	extern _INDF2
	extern _BSR
	extern _FSR1L
	extern _FSR1H
	extern _PLUSW1
	extern _PREINC1
	extern _POSTDEC1
	extern _POSTINC1
	extern _INDF1
	extern _WREG
	extern _FSR0L
	extern _FSR0H
	extern _PLUSW0
	extern _PREINC0
	extern _POSTDEC0
	extern _POSTINC0
	extern _INDF0
	extern _INTCON3
	extern _INTCON2
	extern _INTCON
	extern _PRODL
	extern _PRODH
	extern _TABLAT
	extern _TBLPTRL
	extern _TBLPTRH
	extern _TBLPTRU
	extern _PCL
	extern _PCLATH
	extern _PCLATU
	extern _STKPTR
	extern _TOSL
	extern _TOSH
	extern _TOSU
	extern _adc_open
	extern _usart_open
	extern _usart_drdy
	extern _usart_getc
	extern _usart_putc
	extern _lcd_init
	extern _lcd_print
	extern _button_released
	extern __mullong
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
_timer_2	res	4

udata_pillefyrsstyring_6	udata
_last_button	res	1

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
;	.line	25; pillefyrsstyring.c	OSCCONbits.SCS = 0x10;
	MOVF	_OSCCONbits, W
	ANDLW	0xfc
	MOVWF	_OSCCONbits
;	.line	26; pillefyrsstyring.c	OSCCONbits.IRCF = 0x6;	// 4 MHz
	MOVF	_OSCCONbits, W
	ANDLW	0x8f
	IORLW	0x60
	MOVWF	_OSCCONbits
	BANKSEL	_timer_2
;	.line	28; pillefyrsstyring.c	timer_2 = 0;
	CLRF	_timer_2, B
	BANKSEL	(_timer_2 + 1)
	CLRF	(_timer_2 + 1), B
	BANKSEL	(_timer_2 + 2)
	CLRF	(_timer_2 + 2), B
	BANKSEL	(_timer_2 + 3)
	CLRF	(_timer_2 + 3), B
	BANKSEL	_boiler_temp
;	.line	29; pillefyrsstyring.c	boiler_temp = 0;
	CLRF	_boiler_temp, B
	BANKSEL	(_boiler_temp + 1)
	CLRF	(_boiler_temp + 1), B
	BANKSEL	_smoke_temp
;	.line	30; pillefyrsstyring.c	smoke_temp = 0;
	CLRF	_smoke_temp, B
	BANKSEL	(_smoke_temp + 1)
	CLRF	(_smoke_temp + 1), B
	BANKSEL	_chimney_temp
;	.line	31; pillefyrsstyring.c	chimney_temp = 0;
	CLRF	_chimney_temp, B
	BANKSEL	(_chimney_temp + 1)
	CLRF	(_chimney_temp + 1), B
	BANKSEL	_last_button
;	.line	33; pillefyrsstyring.c	last_button = NONE;
	CLRF	_last_button, B
;	.line	36; pillefyrsstyring.c	EXT_FEEDER_L1_TRIS = 0;	// output
	BCF	_TRISBbits, 0
;	.line	37; pillefyrsstyring.c	EXT_FEEDER_L1 = 0;		// off
	BCF	_PORTBbits, 0
;	.line	39; pillefyrsstyring.c	FAN_L2_TRIS = 0;		// output
	BCF	_TRISBbits, 1
;	.line	40; pillefyrsstyring.c	FAN_L2 = 0;				// off
	BCF	_PORTBbits, 1
;	.line	42; pillefyrsstyring.c	INT_FEEDER_L3_TRIS = 0;	// output
	BCF	_TRISBbits, 2
;	.line	43; pillefyrsstyring.c	INT_FEEDER_L3 = 0;		// off
	BCF	_PORTBbits, 2
;	.line	45; pillefyrsstyring.c	HEATER_T3_L4_TRIS = 0;		// output
	BCF	_TRISBbits, 3
;	.line	46; pillefyrsstyring.c	HEATER_T3_L4 = 0;				// off
	BCF	_PORTBbits, 3
;	.line	48; pillefyrsstyring.c	B_UP_TRIS = 1;			// input
	BSF	_TRISBbits, 5
;	.line	49; pillefyrsstyring.c	B_DOWN_TRIS = 1;		// input
	BSF	_TRISBbits, 7
;	.line	50; pillefyrsstyring.c	B_MENU_TRIS = 1;		// input
	BSF	_TRISBbits, 6
;	.line	52; pillefyrsstyring.c	BOILER_TEMP_TRIS = 1;	// input
	BSF	_PORTAbits, 3
;	.line	53; pillefyrsstyring.c	SMOKE_TEMP_TRIS	= 1;	// input
	BSF	_PORTAbits, 4
;	.line	54; pillefyrsstyring.c	CHIMNEY_TEMP_TRIS = 1; 	// input
	BSF	_PORTAbits, 5
;	.line	57; pillefyrsstyring.c	adc_open(4, ADC_FOSC_64, ADC_CFG_5A, ADC_FRM_RJUST | ADC_INT_OFF);
	MOVLW	0x80
	MOVWF	POSTDEC1
	MOVLW	0x0a
	MOVWF	POSTDEC1
	MOVLW	0x06
	MOVWF	POSTDEC1
	MOVLW	0x04
	MOVWF	POSTDEC1
	CALL	_adc_open
	MOVLW	0x04
	ADDWF	FSR1L, F
;	.line	60; pillefyrsstyring.c	T2CONbits.T2CKPS0 = 1;
	BSF	_T2CONbits, 0
;	.line	61; pillefyrsstyring.c	T2CONbits.T2CKPS1 = 0;
	BCF	_T2CONbits, 1
;	.line	62; pillefyrsstyring.c	T2CONbits.TOUTPS0 = 1;
	BSF	_T2CONbits, 3
;	.line	63; pillefyrsstyring.c	T2CONbits.TOUTPS1 = 0;
	BCF	_T2CONbits, 4
;	.line	64; pillefyrsstyring.c	T2CONbits.TOUTPS2 = 0;
	BCF	_T2CONbits, 5
;	.line	65; pillefyrsstyring.c	T2CONbits.TOUTPS3 = 1;
	BSF	_T2CONbits, 6
;	.line	66; pillefyrsstyring.c	IPR1bits.TMR2IP = 1;		// high priority
	BSF	_IPR1bits, 1
;	.line	67; pillefyrsstyring.c	PIR1bits.TMR2IF = 1;
	BSF	_PIR1bits, 1
;	.line	68; pillefyrsstyring.c	T2CONbits.TMR2ON = 1;
	BSF	_T2CONbits, 2
;	.line	69; pillefyrsstyring.c	PIE1bits.TMR2IE = 1;
	BSF	_PIE1bits, 1
;	.line	72; pillefyrsstyring.c	T3CONbits.RD16 = 1;
	BSF	_T3CONbits, 7
;	.line	73; pillefyrsstyring.c	T3CONbits.TMR3CS = 0;	// internal clock source
	BCF	_T3CONbits, 1
;	.line	74; pillefyrsstyring.c	T3CONbits.T3CKPS0 = 1;
	BSF	_T3CONbits, 4
;	.line	75; pillefyrsstyring.c	T3CONbits.T3CKPS0 = 1;
	BSF	_T3CONbits, 4
;	.line	76; pillefyrsstyring.c	IPR2bits.TMR3IP = 0;		// low priority
	BCF	_IPR2bits, 1
;	.line	77; pillefyrsstyring.c	T3CONbits.TMR3ON = 1;
	BSF	_T3CONbits, 0
;	.line	78; pillefyrsstyring.c	PIE2bits.TMR3IE = 1;
	BSF	_PIE2bits, 1
;	.line	79; pillefyrsstyring.c	PIR2bits.TMR3IF = 1;
	BSF	_PIR2bits, 1
;	.line	81; pillefyrsstyring.c	INTCONbits.PEIE = 1;
	BSF	_INTCONbits, 6
;	.line	82; pillefyrsstyring.c	INTCONbits.GIE = 1;	/* Enable Global interrupts   */	
	BSF	_INTCONbits, 7
;	.line	90; pillefyrsstyring.c	12     // 19200 kbps @ 4 MHz
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x0c
	MOVWF	POSTDEC1
	MOVLW	0x7c
	CALL	_usart_open
	MOVLW	0x02
	ADDWF	FSR1L, F
;	.line	103; pillefyrsstyring.c	lcd_init();
	CALL	_lcd_init
;	.line	104; pillefyrsstyring.c	lcd_print("OpenStoker starting...", 0, NON_INVERTED); // starting...");
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	UPPER(__str_0)
	MOVWF	POSTDEC1
	MOVLW	HIGH(__str_0)
	MOVWF	POSTDEC1
	MOVLW	LOW(__str_0)
	MOVWF	POSTDEC1
	CALL	_lcd_print
	MOVLW	0x05
	ADDWF	FSR1L, F
;	.line	105; pillefyrsstyring.c	sleep_ms(3000);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x0b
	MOVWF	POSTDEC1
	MOVLW	0xb8
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
_00133_DS_:
;	.line	108; pillefyrsstyring.c	if (!B_UP) {					// if up button pressed...
	BTFSC	_PORTBbits, 5
	BRA	_00112_DS_
	BANKSEL	_last_button
;	.line	109; pillefyrsstyring.c	if (!(last_button & UP)) {	// and if up button state changed
	BTFSC	_last_button, 0, B
	BRA	_00113_DS_
	BANKSEL	_last_button
;	.line	110; pillefyrsstyring.c	last_button |= UP;		// change state for button to pressed
	BSF	_last_button, 0, B
	BRA	_00113_DS_
_00112_DS_:
;	.line	115; pillefyrsstyring.c	else if (B_UP) {				// if up button released...
	BTFSS	_PORTBbits, 5
	BRA	_00113_DS_
	BANKSEL	_last_button
;	.line	116; pillefyrsstyring.c	if (last_button & UP) {		// and if up button state changed
	BTFSS	_last_button, 0, B
	BRA	_00113_DS_
	BANKSEL	_last_button
;	.line	117; pillefyrsstyring.c	last_button &= ~UP;		// change state for button to released
	BCF	_last_button, 0, B
;	.line	118; pillefyrsstyring.c	button_released(UP);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_button_released
	INCF	FSR1L, F
_00113_DS_:
;	.line	122; pillefyrsstyring.c	if (!B_MENU) {					// if menu button pressed...
	BTFSC	_PORTBbits, 6
	BRA	_00121_DS_
	BANKSEL	_last_button
;	.line	123; pillefyrsstyring.c	if (!(last_button & MENU)) {// and if menu button state changed
	BTFSC	_last_button, 1, B
	BRA	_00122_DS_
	BANKSEL	_last_button
;	.line	124; pillefyrsstyring.c	last_button |= MENU;	// change state for button to pressed
	BSF	_last_button, 1, B
	BRA	_00122_DS_
_00121_DS_:
;	.line	129; pillefyrsstyring.c	else if (B_MENU) {				// if menu button released...
	BTFSS	_PORTBbits, 6
	BRA	_00122_DS_
	BANKSEL	_last_button
;	.line	130; pillefyrsstyring.c	if (last_button & MENU) {	// and if menu button state changed
	BTFSS	_last_button, 1, B
	BRA	_00122_DS_
	BANKSEL	_last_button
;	.line	131; pillefyrsstyring.c	last_button &= ~MENU;	// change state for button to released
	BCF	_last_button, 1, B
;	.line	132; pillefyrsstyring.c	button_released(MENU);
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	_button_released
	INCF	FSR1L, F
_00122_DS_:
;	.line	136; pillefyrsstyring.c	if (!B_DOWN) {					// if down button pressed...
	BTFSC	_PORTBbits, 7
	BRA	_00130_DS_
	BANKSEL	_last_button
;	.line	137; pillefyrsstyring.c	if (!(last_button & DOWN)) {// and if down button state changed
	BTFSC	_last_button, 2, B
	BRA	_00133_DS_
	BANKSEL	_last_button
;	.line	138; pillefyrsstyring.c	last_button |= DOWN;	// change state for button to pressed
	BSF	_last_button, 2, B
	BRA	_00133_DS_
_00130_DS_:
;	.line	143; pillefyrsstyring.c	else if (B_DOWN) {				// if up button released...
	BTFSS	_PORTBbits, 7
	BRA	_00133_DS_
	BANKSEL	_last_button
;	.line	144; pillefyrsstyring.c	if (last_button & DOWN) {	// and if up button state changed
	BTFSS	_last_button, 2, B
	BRA	_00133_DS_
	BANKSEL	_last_button
;	.line	145; pillefyrsstyring.c	last_button &= ~DOWN;	// change state for button to released
	BCF	_last_button, 2, B
;	.line	146; pillefyrsstyring.c	button_released(DOWN);
	MOVLW	0x04
	MOVWF	POSTDEC1
	CALL	_button_released
	INCF	FSR1L, F
	BRA	_00133_DS_
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__write_EEPROM	code
_write_EEPROM:
;	.line	262; pillefyrsstyring.c	void write_EEPROM(unsigned char address, unsigned char d) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
;	.line	264; pillefyrsstyring.c	save_int = INTCON;					//save interrupt status
	MOVFF	_INTCON, r0x02
;	.line	265; pillefyrsstyring.c	EECON1 = 0;									//ensure CFGS=0 and EEPGD=0
	CLRF	_EECON1
;	.line	266; pillefyrsstyring.c	EECON1bits.WREN = 1;				//enable write to EEPROM
	BSF	_EECON1bits, 2
;	.line	267; pillefyrsstyring.c	EEADR = address;						//setup Address
	MOVFF	r0x00, _EEADR
;	.line	268; pillefyrsstyring.c	EEDATA = d;									//and data
	MOVFF	r0x01, _EEDATA
;	.line	269; pillefyrsstyring.c	INTCONbits.GIE=0;						//No interrupts
	BCF	_INTCONbits, 7
;	.line	270; pillefyrsstyring.c	EECON2 = 0x55;							//required sequence #1
	MOVLW	0x55
	MOVWF	_EECON2
;	.line	271; pillefyrsstyring.c	EECON2 = 0xaa;							//#2
	MOVLW	0xaa
	MOVWF	_EECON2
;	.line	272; pillefyrsstyring.c	EECON1bits.WR = 1;					//#3 = actual write
	BSF	_EECON1bits, 1
;	.line	273; pillefyrsstyring.c	INTCON = save_int;					//restore interrupts
	MOVFF	r0x02, _INTCON
_00209_DS_:
;	.line	274; pillefyrsstyring.c	while(!PIR2bits.EEIF) {
	BTFSS	_PIR2bits, 4
	BRA	_00209_DS_
;	.line	277; pillefyrsstyring.c	EECON1bits.WREN = 0;				//disable write to EEPROM
	BCF	_EECON1bits, 2
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__read_EEPROM	code
_read_EEPROM:
;	.line	255; pillefyrsstyring.c	unsigned char read_EEPROM(unsigned char address) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	256; pillefyrsstyring.c	EECON1 = 0;									//ensure CFGS = 0 and EEPGD = 0 
	CLRF	_EECON1
;	.line	257; pillefyrsstyring.c	EEADR = address;
	MOVFF	r0x00, _EEADR
;	.line	258; pillefyrsstyring.c	EECON1bits.RD = 1;
	BSF	_EECON1bits, 0
;	.line	259; pillefyrsstyring.c	return(EEDATA);
	MOVF	_EEDATA, W
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__my_usart_open	code
_my_usart_open:
;	.line	228; pillefyrsstyring.c	void my_usart_open() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	229; pillefyrsstyring.c	SPBRG = 32; // 20MHz => 9600 baud (BRGH = 0)
	MOVLW	0x20
	MOVWF	_SPBRG
;	.line	230; pillefyrsstyring.c	TXSTAbits.BRGH = 0; // (0 = low speed)
	BCF	_TXSTAbits, 2
;	.line	231; pillefyrsstyring.c	TXSTAbits.SYNC = 0; // (0 = asynchronous)
	BCF	_TXSTAbits, 4
;	.line	234; pillefyrsstyring.c	RCSTAbits.SPEN = 1; // (1 = serial port enabled)
	BSF	_RCSTAbits, 7
;	.line	237; pillefyrsstyring.c	PIE1bits.TXIE = 0; // (1 = enabled)
	BCF	_PIE1bits, 4
;	.line	240; pillefyrsstyring.c	PIE1bits.RCIE = 1; // (1 = enabled)
	BSF	_PIE1bits, 5
;	.line	243; pillefyrsstyring.c	TXSTAbits.TX9 = 0; // (0 = 8-bit transmit)
	BCF	_TXSTAbits, 6
;	.line	246; pillefyrsstyring.c	RCSTAbits.RX9 = 0; // (0 = 8-bit reception)
	BCF	_RCSTAbits, 6
;	.line	249; pillefyrsstyring.c	RCSTAbits.CREN = 1; // (1 = Enables receiver)
	BSF	_RCSTAbits, 4
;	.line	252; pillefyrsstyring.c	TXSTAbits.TXEN = 1; // (1 = transmit enabled)
	BSF	_TXSTAbits, 5
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__sleep_ms	code
_sleep_ms:
;	.line	218; pillefyrsstyring.c	void sleep_ms(unsigned long ms) {
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
;	.line	220; pillefyrsstyring.c	start_timer_2 = timer_2;	
	MOVFF	_timer_2, r0x04
	MOVFF	(_timer_2 + 1), r0x05
	MOVFF	(_timer_2 + 2), r0x06
	MOVFF	(_timer_2 + 3), r0x07
_00185_DS_:
;	.line	223; pillefyrsstyring.c	while ( (((signed long)(timer_2 - start_timer_2) < 0) ? (-1 * (timer_2 - start_timer_2)) : (timer_2 - start_timer_2)) < ms) {
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
	MOVFF	r0x08, r0x0c
	MOVFF	r0x09, r0x0d
	MOVFF	r0x0a, r0x0e
	MOVFF	r0x0b, r0x0f
	BSF	STATUS, 0
	BTFSS	r0x0f, 7
	BCF	STATUS, 0
	BNC	_00190_DS_
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
	BRA	_00191_DS_
_00190_DS_:
	MOVFF	r0x08, r0x0c
	MOVFF	r0x09, r0x0d
	MOVFF	r0x0a, r0x0e
	MOVFF	r0x0b, r0x0f
_00191_DS_:
	MOVF	r0x03, W
	SUBWF	r0x0f, W
	BNZ	_00194_DS_
	MOVF	r0x02, W
	SUBWF	r0x0e, W
	BNZ	_00194_DS_
	MOVF	r0x01, W
	SUBWF	r0x0d, W
	BNZ	_00194_DS_
	MOVF	r0x00, W
	SUBWF	r0x0c, W
_00194_DS_:
	BTFSS	STATUS, 0
	BRA	_00185_DS_
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
;	.line	175; pillefyrsstyring.c	static void timer_control(void) __interrupt 1 {
	MOVFF	WREG, POSTDEC1
	MOVFF	STATUS, POSTDEC1
	MOVFF	BSR, POSTDEC1
	MOVFF	PRODL, POSTDEC1
	MOVFF	PRODH, POSTDEC1
	MOVFF	FSR0L, POSTDEC1
	MOVFF	FSR0H, POSTDEC1
	MOVFF	PCLATH, POSTDEC1
	MOVFF	PCLATU, POSTDEC1
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	176; pillefyrsstyring.c	if (PIR1bits.TMR2IF) {
	BTFSS	_PIR1bits, 1
	BRA	_00166_DS_
;	.line	177; pillefyrsstyring.c	PR2 = TIMER2_RELOAD;		// 1 ms delay at 4 MHz
	MOVLW	0x18
	MOVWF	_PR2
;	.line	178; pillefyrsstyring.c	PIR1bits.TMR2IF = 0;
	BCF	_PIR1bits, 1
	BANKSEL	_timer_2
;	.line	179; pillefyrsstyring.c	timer_2++;
	INCF	_timer_2, F, B
	BNC	_10209_DS_
	BANKSEL	(_timer_2 + 1)
	INCF	(_timer_2 + 1), F, B
_10209_DS_:
	BNC	_20210_DS_
	BANKSEL	(_timer_2 + 2)
	INCF	(_timer_2 + 2), F, B
_20210_DS_:
	BNC	_30211_DS_
	BANKSEL	(_timer_2 + 3)
	INCF	(_timer_2 + 3), F, B
_30211_DS_:
	clrwdt 
_00166_DS_:
;	.line	182; pillefyrsstyring.c	if (PIR2bits.TMR3IF) {
	BTFSS	_PIR2bits, 1
	BRA	_00177_DS_
;	.line	183; pillefyrsstyring.c	TMR3H = (unsigned char)(TIMER3_RELOAD >> 8);	// 8 ms delay at 8 MHz
	CLRF	_TMR3H
;	.line	184; pillefyrsstyring.c	TMR3L = (unsigned char)TIMER3_RELOAD;
	CLRF	_TMR3L
;	.line	185; pillefyrsstyring.c	PIR2bits.TMR3IF = 0;	/* Clear the Timer Flag  */
	BCF	_PIR2bits, 1
;	.line	188; pillefyrsstyring.c	adc_setchannel(3);
	MOVLW	0x03
	MOVWF	POSTDEC1
	CALL	_adc_setchannel
	INCF	FSR1L, F
;	.line	189; pillefyrsstyring.c	adc_conv();
	CALL	_adc_conv
_00167_DS_:
;	.line	190; pillefyrsstyring.c	while(adc_busy()) {
	CALL	_adc_busy
	MOVWF	r0x00
	MOVF	r0x00, W
	BNZ	_00167_DS_
;	.line	193; pillefyrsstyring.c	boiler_temp = adc_read();
	CALL	_adc_read
	BANKSEL	_boiler_temp
	MOVWF	_boiler_temp, B
	MOVFF	PRODL, (_boiler_temp + 1)
;	.line	196; pillefyrsstyring.c	adc_setchannel(4);
	MOVLW	0x04
	MOVWF	POSTDEC1
	CALL	_adc_setchannel
	INCF	FSR1L, F
;	.line	197; pillefyrsstyring.c	adc_conv();
	CALL	_adc_conv
_00170_DS_:
;	.line	198; pillefyrsstyring.c	while(adc_busy()) {
	CALL	_adc_busy
	MOVWF	r0x00
	MOVF	r0x00, W
	BNZ	_00170_DS_
;	.line	201; pillefyrsstyring.c	smoke_temp = adc_read();
	CALL	_adc_read
	BANKSEL	_smoke_temp
	MOVWF	_smoke_temp, B
	MOVFF	PRODL, (_smoke_temp + 1)
;	.line	204; pillefyrsstyring.c	adc_setchannel(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_adc_setchannel
	INCF	FSR1L, F
;	.line	205; pillefyrsstyring.c	adc_conv();
	CALL	_adc_conv
_00173_DS_:
;	.line	206; pillefyrsstyring.c	while(adc_busy()) {
	CALL	_adc_busy
	MOVWF	r0x00
	MOVF	r0x00, W
	BNZ	_00173_DS_
;	.line	209; pillefyrsstyring.c	chimney_temp = adc_read();
	CALL	_adc_read
	BANKSEL	_chimney_temp
	MOVWF	_chimney_temp, B
	MOVFF	PRODL, (_chimney_temp + 1)
_00177_DS_:
;	.line	212; pillefyrsstyring.c	if (usart_drdy()) {
	CALL	_usart_drdy
	MOVWF	r0x00
	MOVF	r0x00, W
	BZ	_00180_DS_
;	.line	214; pillefyrsstyring.c	usart_putc(usart_getc());
	CALL	_usart_getc
	MOVWF	r0x00
	MOVF	r0x00, W
	CALL	_usart_putc
_00180_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	MOVFF	PREINC1, PCLATU
	MOVFF	PREINC1, PCLATH
	MOVFF	PREINC1, FSR0H
	MOVFF	PREINC1, FSR0L
	MOVFF	PREINC1, PRODH
	MOVFF	PREINC1, PRODL
	MOVFF	PREINC1, BSR
	MOVFF	PREINC1, STATUS
	MOVFF	PREINC1, WREG
	RETFIE	

; ; Starting pCode block
__str_0:
	DB	0x4f, 0x70, 0x65, 0x6e, 0x53, 0x74, 0x6f, 0x6b, 0x65, 0x72, 0x20, 0x73
	DB	0x74, 0x61, 0x72, 0x74, 0x69, 0x6e, 0x67, 0x2e, 0x2e, 0x2e, 0x00


; Statistics:
; code size:	 1120 (0x0460) bytes ( 0.85%)
;           	  560 (0x0230) words
; udata size:	   35 (0x0023) bytes ( 0.91%)
; access size:	   16 (0x0010) bytes


	end
