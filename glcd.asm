;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.3.0 #8604 (Oct 27 2013) (Mac OS X x86_64)
; This file was generated Thu Dec 12 04:00:40 2013
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------
	list	p=18f4620
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_lcd_buffer
	global	_lcd_init
	global	_lcd_enable
	global	_lcd_status
	global	_lcd_reset
	global	_lcd_screenon
	global	_lcd_cls
	global	_lcd_setpage
	global	_lcd_setyaddr
	global	_lcd_waitbusy
	global	_lcd_write
	global	_lcd_selectside
	global	_lcd_read
	global	_lcd_plot_pixel
	global	_latched_lcd_power
	global	_latched_lcd_enable
	global	_latched_lcd_di
	global	_latched_lcd_rw
	global	_latched_lcd_rst
	global	_latched_lcd_cs2
	global	_latched_lcd_cs1
	global	_latched_lcd_data
	global	__latch_3_data

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
	extern	_sleep_ms

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
WREG	equ	0xfe8
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1

udata_glcd_0	udata
_lcd_buffer	res	1

udata_glcd_1	udata
__latch_3_data	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_glcd__latched_lcd_data	code
_latched_lcd_data:
;	.line	363; glcd.c	void latched_lcd_data(unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	364; glcd.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	365; glcd.c	LATCH_DATA = value;
	MOVFF	r0x00, _LATD
;	.line	366; glcd.c	LATCH_4 = LATCH_4_ENABLED;
	BSF	_LATCbits, 2
;	.line	367; glcd.c	LATCH_4 = LATCH_4_DISABLED;
	BCF	_LATCbits, 2
;	.line	368; glcd.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__latched_lcd_cs1	code
_latched_lcd_cs1:
;	.line	348; glcd.c	void latched_lcd_cs1(unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	349; glcd.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	350; glcd.c	if (value) {	// set it
	MOVF	r0x00, W
	BZ	_00290_DS_
	BANKSEL	__latch_3_data
;	.line	351; glcd.c	_latch_3_data |= 0b00100000;
	BSF	__latch_3_data, 5, B
;	.line	352; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
	BRA	_00291_DS_
_00290_DS_:
	BANKSEL	__latch_3_data
;	.line	355; glcd.c	_latch_3_data &= 0b11011111;
	BCF	__latch_3_data, 5, B
;	.line	356; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
_00291_DS_:
;	.line	358; glcd.c	LATCH_3 = LATCH_3_ENABLED;
	BSF	_LATAbits, 6
;	.line	359; glcd.c	LATCH_3 = LATCH_3_DISABLED;
	BCF	_LATAbits, 6
;	.line	360; glcd.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__latched_lcd_cs2	code
_latched_lcd_cs2:
;	.line	333; glcd.c	void latched_lcd_cs2(unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	334; glcd.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	335; glcd.c	if (value) {	// set it
	MOVF	r0x00, W
	BZ	_00282_DS_
	BANKSEL	__latch_3_data
;	.line	336; glcd.c	_latch_3_data |= 0b00010000;
	BSF	__latch_3_data, 4, B
;	.line	337; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
	BRA	_00283_DS_
_00282_DS_:
	BANKSEL	__latch_3_data
;	.line	340; glcd.c	_latch_3_data &= 0b11101111;
	BCF	__latch_3_data, 4, B
;	.line	341; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
_00283_DS_:
;	.line	343; glcd.c	LATCH_3 = LATCH_3_ENABLED;
	BSF	_LATAbits, 6
;	.line	344; glcd.c	LATCH_3 = LATCH_3_DISABLED;
	BCF	_LATAbits, 6
;	.line	345; glcd.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__latched_lcd_rst	code
_latched_lcd_rst:
;	.line	318; glcd.c	void latched_lcd_rst(unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	319; glcd.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	320; glcd.c	if (value) {	// set it
	MOVF	r0x00, W
	BZ	_00274_DS_
	BANKSEL	__latch_3_data
;	.line	321; glcd.c	_latch_3_data |= 0b00001000;
	BSF	__latch_3_data, 3, B
;	.line	322; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
	BRA	_00275_DS_
_00274_DS_:
	BANKSEL	__latch_3_data
;	.line	325; glcd.c	_latch_3_data &= 0b11110111;
	BCF	__latch_3_data, 3, B
;	.line	326; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
_00275_DS_:
;	.line	328; glcd.c	LATCH_3 = LATCH_3_ENABLED;
	BSF	_LATAbits, 6
;	.line	329; glcd.c	LATCH_3 = LATCH_3_DISABLED;
	BCF	_LATAbits, 6
;	.line	330; glcd.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__latched_lcd_rw	code
_latched_lcd_rw:
;	.line	303; glcd.c	void latched_lcd_rw(unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	304; glcd.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	305; glcd.c	if (value) {	// set it
	MOVF	r0x00, W
	BZ	_00266_DS_
	BANKSEL	__latch_3_data
;	.line	306; glcd.c	_latch_3_data |= 0b00000100;
	BSF	__latch_3_data, 2, B
;	.line	307; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
	BRA	_00267_DS_
_00266_DS_:
	BANKSEL	__latch_3_data
;	.line	310; glcd.c	_latch_3_data &= 0b11111011;
	BCF	__latch_3_data, 2, B
;	.line	311; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
_00267_DS_:
;	.line	313; glcd.c	LATCH_3 = LATCH_3_ENABLED;
	BSF	_LATAbits, 6
;	.line	314; glcd.c	LATCH_3 = LATCH_3_DISABLED;
	BCF	_LATAbits, 6
;	.line	315; glcd.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__latched_lcd_di	code
_latched_lcd_di:
;	.line	288; glcd.c	void latched_lcd_di(unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	289; glcd.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	290; glcd.c	if (value) {	// set it
	MOVF	r0x00, W
	BZ	_00258_DS_
	BANKSEL	__latch_3_data
;	.line	291; glcd.c	_latch_3_data |= 0b00000010;
	BSF	__latch_3_data, 1, B
;	.line	292; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
	BRA	_00259_DS_
_00258_DS_:
	BANKSEL	__latch_3_data
;	.line	295; glcd.c	_latch_3_data &= 0b11111101;
	BCF	__latch_3_data, 1, B
;	.line	296; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
_00259_DS_:
;	.line	298; glcd.c	LATCH_3 = LATCH_3_ENABLED;
	BSF	_LATAbits, 6
;	.line	299; glcd.c	LATCH_3 = LATCH_3_DISABLED;
	BCF	_LATAbits, 6
;	.line	300; glcd.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__latched_lcd_enable	code
_latched_lcd_enable:
;	.line	273; glcd.c	void latched_lcd_enable(unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	274; glcd.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	275; glcd.c	if (value) {	// set it
	MOVF	r0x00, W
	BZ	_00250_DS_
	BANKSEL	__latch_3_data
;	.line	276; glcd.c	_latch_3_data |= 0b00000001;
	BSF	__latch_3_data, 0, B
;	.line	277; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
	BRA	_00251_DS_
_00250_DS_:
	BANKSEL	__latch_3_data
;	.line	280; glcd.c	_latch_3_data &= 0b11111110;
	BCF	__latch_3_data, 0, B
;	.line	281; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
_00251_DS_:
;	.line	283; glcd.c	LATCH_3 = LATCH_3_ENABLED;
	BSF	_LATAbits, 6
;	.line	284; glcd.c	LATCH_3 = LATCH_3_DISABLED;
	BCF	_LATAbits, 6
;	.line	285; glcd.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__latched_lcd_power	code
_latched_lcd_power:
;	.line	258; glcd.c	void latched_lcd_power(unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	259; glcd.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	260; glcd.c	if (value) {	// set it
	MOVF	r0x00, W
	BZ	_00242_DS_
	BANKSEL	__latch_3_data
;	.line	261; glcd.c	_latch_3_data |= 0b10000000;
	BSF	__latch_3_data, 7, B
;	.line	262; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
	BRA	_00243_DS_
_00242_DS_:
	BANKSEL	__latch_3_data
;	.line	265; glcd.c	_latch_3_data &= 0b01111111;
	BCF	__latch_3_data, 7, B
;	.line	266; glcd.c	LATCH_DATA = _latch_3_data;
	MOVFF	__latch_3_data, _LATD
_00243_DS_:
;	.line	268; glcd.c	LATCH_3 = LATCH_3_ENABLED;
	BSF	_LATAbits, 6
;	.line	269; glcd.c	LATCH_3 = LATCH_3_DISABLED;
	BCF	_LATAbits, 6
;	.line	270; glcd.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_plot_pixel	code
_lcd_plot_pixel:
;	.line	238; glcd.c	void lcd_plot_pixel(unsigned char rx, unsigned char ry) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
;	.line	243; glcd.c	if (rx & 64) {
	BTFSS	r0x00, 6
	BRA	_00225_DS_
;	.line	244; glcd.c	lcd_selectside(LCD_RIGHT);
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	_lcd_selectside
	MOVF	POSTINC1, F
	BRA	_00226_DS_
_00225_DS_:
;	.line	247; glcd.c	lcd_selectside(LCD_LEFT);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_lcd_selectside
	MOVF	POSTINC1, F
_00226_DS_:
;	.line	250; glcd.c	lcd_setpage( ry >> 3);		// fast /8
	SWAPF	r0x01, W
	RLNCF	WREG, W
	ANDLW	0x1f
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_lcd_setpage
	MOVF	POSTINC1, F
;	.line	251; glcd.c	lcd_setyaddr( rx & 0b00111111);
	MOVLW	0x3f
	ANDWF	r0x00, F
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_lcd_setyaddr
	MOVF	POSTINC1, F
;	.line	252; glcd.c	d = lcd_read();				// read to move data to GLCD buffer,
	CALL	_lcd_read
;	.line	253; glcd.c	d = lcd_read();				// read again to transfer to pic
	CALL	_lcd_read
	MOVWF	r0x02
;	.line	254; glcd.c	lcd_setyaddr( rx & 0b00111111); 
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_lcd_setyaddr
	MOVF	POSTINC1, F
;	.line	255; glcd.c	lcd_write (d | (1 << (ry & 0b111)));
	MOVLW	0x07
	ANDWF	r0x01, F
	MOVLW	0x01
	MOVWF	r0x00
	MOVF	r0x01, W
	BZ	_00235_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00236_DS_:
	RLCF	r0x00, F
	ADDLW	0x01
	BNC	_00236_DS_
_00235_DS_:
	MOVF	r0x00, W
	IORWF	r0x02, F
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_lcd_write
	MOVF	POSTINC1, F
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_read	code
_lcd_read:
;	.line	222; glcd.c	unsigned char lcd_read (void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	234; glcd.c	return 1;
	MOVLW	0x01
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_selectside	code
_lcd_selectside:
;	.line	197; glcd.c	void lcd_selectside(unsigned char sides) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	200; glcd.c	if (sides & LCD_LEFT) {
	BTFSS	r0x00, 0
	BRA	_00200_DS_
;	.line	202; glcd.c	latched_lcd_cs1(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_cs1
	MOVF	POSTINC1, F
	BRA	_00201_DS_
_00200_DS_:
;	.line	206; glcd.c	latched_lcd_cs1(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_cs1
	MOVF	POSTINC1, F
_00201_DS_:
;	.line	209; glcd.c	if (sides & LCD_RIGHT) {
	BTFSS	r0x00, 1
	BRA	_00203_DS_
;	.line	211; glcd.c	latched_lcd_cs2(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_cs2
	MOVF	POSTINC1, F
	BRA	_00205_DS_
_00203_DS_:
;	.line	215; glcd.c	latched_lcd_cs2(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_cs2
	MOVF	POSTINC1, F
_00205_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_write	code
_lcd_write:
;	.line	184; glcd.c	void lcd_write (unsigned char d) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	185; glcd.c	lcd_waitbusy();
	CALL	_lcd_waitbusy
;	.line	187; glcd.c	latched_lcd_di(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_di
	MOVF	POSTINC1, F
;	.line	189; glcd.c	latched_lcd_rw(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_rw
	MOVF	POSTINC1, F
;	.line	192; glcd.c	latched_lcd_data(d);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_latched_lcd_data
	MOVF	POSTINC1, F
;	.line	193; glcd.c	lcd_enable();
	CALL	_lcd_enable
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_waitbusy	code
_lcd_waitbusy:
;	.line	177; glcd.c	void lcd_waitbusy(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
_00178_DS_:
;	.line	178; glcd.c	while (lcd_status() & 0b10000000) {
	CALL	_lcd_status
	MOVWF	r0x00
	BTFSS	r0x00, 7
	BRA	_00181_DS_
_00189_DS_:
	nop 
	nop 
	BRA	_00178_DS_
_00181_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_setyaddr	code
_lcd_setyaddr:
;	.line	163; glcd.c	void lcd_setyaddr(unsigned char y) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	165; glcd.c	lcd_waitbusy();
	CALL	_lcd_waitbusy
;	.line	167; glcd.c	latched_lcd_di(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_di
	MOVF	POSTINC1, F
;	.line	168; glcd.c	latched_lcd_rw(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_rw
	MOVF	POSTINC1, F
;	.line	170; glcd.c	latched_lcd_data(0b01000000 | (y & 0b00111111));
	MOVLW	0x3f
	ANDWF	r0x00, F
	BSF	r0x00, 6
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_latched_lcd_data
	MOVF	POSTINC1, F
;	.line	171; glcd.c	lcd_enable();
	CALL	_lcd_enable
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_setpage	code
_lcd_setpage:
;	.line	148; glcd.c	void lcd_setpage(unsigned char page) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	150; glcd.c	lcd_waitbusy();
	CALL	_lcd_waitbusy
;	.line	152; glcd.c	latched_lcd_di(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_di
	MOVF	POSTINC1, F
;	.line	153; glcd.c	latched_lcd_rw(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_rw
	MOVF	POSTINC1, F
;	.line	155; glcd.c	latched_lcd_data(0b10111000 | page);
	MOVLW	0xb8
	IORWF	r0x00, F
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_latched_lcd_data
	MOVF	POSTINC1, F
;	.line	156; glcd.c	lcd_enable();
	CALL	_lcd_enable
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_cls	code
_lcd_cls:
;	.line	117; glcd.c	void lcd_cls(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
;	.line	121; glcd.c	lcd_selectside(LCD_BOTH);
	MOVLW	0x03
	MOVWF	POSTDEC1
	CALL	_lcd_selectside
	MOVF	POSTINC1, F
;	.line	122; glcd.c	for (x = 0; x < 8; x++) {
	CLRF	r0x00
_00146_DS_:
;	.line	124; glcd.c	lcd_setpage(x);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_lcd_setpage
	MOVF	POSTINC1, F
;	.line	127; glcd.c	lcd_setyaddr(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_lcd_setyaddr
	MOVF	POSTINC1, F
;	.line	131; glcd.c	latched_lcd_data(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_data
	MOVF	POSTINC1, F
;	.line	132; glcd.c	latched_lcd_rw(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_rw
	MOVF	POSTINC1, F
;	.line	133; glcd.c	latched_lcd_di(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_di
	MOVF	POSTINC1, F
;	.line	136; glcd.c	for (y = 0; y < 64; y++) {
	MOVLW	0x40
	MOVWF	r0x01
_00145_DS_:
;	.line	137; glcd.c	lcd_enable(); 
	CALL	_lcd_enable
	nop 
	nop 
	MOVF	r0x01, W
	MOVWF	r0x02
	DECF	r0x02, W
	MOVWF	r0x01
;	.line	136; glcd.c	for (y = 0; y < 64; y++) {
	MOVF	r0x01, W
	BNZ	_00145_DS_
;	.line	122; glcd.c	for (x = 0; x < 8; x++) {
	INCF	r0x00, F
	MOVLW	0x08
	SUBWF	r0x00, W
	BNC	_00146_DS_
;	.line	143; glcd.c	lcd_selectside(LCD_LEFT);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_lcd_selectside
	MOVF	POSTINC1, F
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_screenon	code
_lcd_screenon:
;	.line	100; glcd.c	void lcd_screenon(unsigned char on) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	103; glcd.c	latched_lcd_cs1(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_cs1
	MOVF	POSTINC1, F
;	.line	105; glcd.c	latched_lcd_cs2(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_cs2
	MOVF	POSTINC1, F
;	.line	107; glcd.c	latched_lcd_rw(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_rw
	MOVF	POSTINC1, F
;	.line	109; glcd.c	latched_lcd_di(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_di
	MOVF	POSTINC1, F
;	.line	112; glcd.c	latched_lcd_data(0b00111110 | (on & 0b00000001));
	MOVLW	0x01
	ANDWF	r0x00, F
	MOVLW	0x3e
	IORWF	r0x00, F
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_latched_lcd_data
	MOVF	POSTINC1, F
;	.line	113; glcd.c	lcd_enable();
	CALL	_lcd_enable
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_reset	code
_lcd_reset:
;	.line	79; glcd.c	void lcd_reset(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	86; glcd.c	sleep_ms(1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
;	.line	88; glcd.c	latched_lcd_rst(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_rst
	MOVF	POSTINC1, F
;	.line	89; glcd.c	sleep_ms(1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
;	.line	91; glcd.c	latched_lcd_rst(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_rst
	MOVF	POSTINC1, F
_00120_DS_:
;	.line	94; glcd.c	while (lcd_status() & 0b00010000) {
	CALL	_lcd_status
	MOVWF	r0x00
	BTFSS	r0x00, 4
	BRA	_00123_DS_
;	.line	95; glcd.c	sleep_ms(1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
	BRA	_00120_DS_
_00123_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_status	code
_lcd_status:
;	.line	52; glcd.c	unsigned char lcd_status(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	74; glcd.c	sleep_ms(100);	
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x64
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
;	.line	75; glcd.c	return 1;	// no hardware support for reading from latch 4
	MOVLW	0x01
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_enable	code
_lcd_enable:
;	.line	42; glcd.c	void lcd_enable(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	44; glcd.c	latched_lcd_enable(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_enable
	MOVF	POSTINC1, F
	nop 
	nop 
;	.line	47; glcd.c	latched_lcd_enable(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_enable
	MOVF	POSTINC1, F
	nop 
	nop 
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_init	code
_lcd_init:
;	.line	17; glcd.c	void lcd_init(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	18; glcd.c	latched_lcd_power(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_power
	MOVF	POSTINC1, F
	BANKSEL	__latch_3_data
;	.line	26; glcd.c	_latch_3_data = 0x00;
	CLRF	__latch_3_data, B
;	.line	29; glcd.c	latched_lcd_cs1(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_cs1
	MOVF	POSTINC1, F
;	.line	31; glcd.c	latched_lcd_cs2(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_cs2
	MOVF	POSTINC1, F
;	.line	37; glcd.c	lcd_reset();
	CALL	_lcd_reset
;	.line	38; glcd.c	lcd_screenon(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_lcd_screenon
	MOVF	POSTINC1, F
;	.line	39; glcd.c	lcd_cls();
	CALL	_lcd_cls
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	 1458 (0x05b2) bytes ( 1.11%)
;           	  729 (0x02d9) words
; udata size:	    2 (0x0002) bytes ( 0.05%)
; access size:	    3 (0x0003) bytes


	end
