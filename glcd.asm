;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.3.0 #8604 (Oct 27 2013) (Mac OS X x86_64)
; This file was generated Tue Dec 10 23:11:01 2013
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

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_glcd__lcd_plot_pixel	code
_lcd_plot_pixel:
;	.line	202; glcd.c	void lcd_plot_pixel(unsigned char rx, unsigned char ry) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
;	.line	207; glcd.c	if (rx & 64) {
	BTFSS	r0x00, 6
	BRA	_00225_DS_
;	.line	208; glcd.c	lcd_selectside(LCD_RIGHT);
	MOVLW	0x02
	MOVWF	POSTDEC1
	CALL	_lcd_selectside
	MOVF	POSTINC1, F
	BRA	_00226_DS_
_00225_DS_:
;	.line	211; glcd.c	lcd_selectside(LCD_LEFT);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_lcd_selectside
	MOVF	POSTINC1, F
_00226_DS_:
;	.line	214; glcd.c	lcd_setpage( ry >> 3);		// fast /8
	SWAPF	r0x01, W
	RLNCF	WREG, W
	ANDLW	0x1f
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_lcd_setpage
	MOVF	POSTINC1, F
;	.line	215; glcd.c	lcd_setyaddr( rx & 0b00111111);
	MOVLW	0x3f
	ANDWF	r0x00, F
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_lcd_setyaddr
	MOVF	POSTINC1, F
;	.line	216; glcd.c	d = lcd_read();				// read to move data to GLCD buffer,
	CALL	_lcd_read
;	.line	217; glcd.c	d = lcd_read();				// read again to transfer to pic
	CALL	_lcd_read
	MOVWF	r0x02
;	.line	218; glcd.c	lcd_setyaddr( rx & 0b00111111); 
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_lcd_setyaddr
	MOVF	POSTINC1, F
;	.line	219; glcd.c	lcd_write (d | (1 << (ry & 0b111)));
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
;	.line	187; glcd.c	unsigned char lcd_read (void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	190; glcd.c	LCD_TRIS = 0xFF;
	MOVLW	0xff
	MOVWF	_TRISD
;	.line	191; glcd.c	RW = 1;	// read
	BSF	_PORTEbits, 1
;	.line	192; glcd.c	DI = 1;	// data
	BSF	_PORTEbits, 0
;	.line	194; glcd.c	lcd_enable();
	CALL	_lcd_enable
;	.line	195; glcd.c	d = LCD_DATA;
	MOVFF	_PORTD, r0x00
;	.line	196; glcd.c	LCD_TRIS = 0x00;
	CLRF	_TRISD
;	.line	198; glcd.c	return d;
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_selectside	code
_lcd_selectside:
;	.line	166; glcd.c	void lcd_selectside(unsigned char sides) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	169; glcd.c	if (sides & LCD_LEFT) {
	BTFSS	r0x00, 0
	BRA	_00200_DS_
;	.line	170; glcd.c	CS1 = 0;
	BCF	_PORTCbits, 0
	BRA	_00201_DS_
_00200_DS_:
;	.line	173; glcd.c	CS1 = 1;
	BSF	_PORTCbits, 0
_00201_DS_:
;	.line	176; glcd.c	if (sides & LCD_RIGHT) {
	BTFSS	r0x00, 1
	BRA	_00203_DS_
;	.line	177; glcd.c	CS2 = 0;
	BCF	_PORTCbits, 1
	BRA	_00205_DS_
_00203_DS_:
;	.line	180; glcd.c	CS2 = 1;
	BSF	_PORTCbits, 1
_00205_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_write	code
_lcd_write:
;	.line	156; glcd.c	void lcd_write (unsigned char d) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	157; glcd.c	lcd_waitbusy();
	CALL	_lcd_waitbusy
;	.line	158; glcd.c	DI = 1;	// data
	BSF	_PORTEbits, 0
;	.line	159; glcd.c	RW = 0;	// write
	BCF	_PORTEbits, 1
;	.line	160; glcd.c	LCD_TRIS = 0; 
	CLRF	_TRISD
;	.line	161; glcd.c	LCD_DATA = d;
	MOVFF	r0x00, _PORTD
;	.line	162; glcd.c	lcd_enable();
	CALL	_lcd_enable
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_waitbusy	code
_lcd_waitbusy:
;	.line	149; glcd.c	void lcd_waitbusy(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
_00178_DS_:
;	.line	150; glcd.c	while (lcd_status() & 0b10000000) {
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
;	.line	138; glcd.c	void lcd_setyaddr(unsigned char y) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	140; glcd.c	lcd_waitbusy();
	CALL	_lcd_waitbusy
;	.line	141; glcd.c	DI = 0; RW = 0;
	BCF	_PORTEbits, 0
	BCF	_PORTEbits, 1
;	.line	142; glcd.c	LCD_DATA = 0b01000000 | (y & 0b00111111);
	MOVLW	0x3f
	ANDWF	r0x00, F
	MOVLW	0x40
	IORWF	r0x00, W
	MOVWF	_PORTD
;	.line	143; glcd.c	lcd_enable();
	CALL	_lcd_enable
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_setpage	code
_lcd_setpage:
;	.line	126; glcd.c	void lcd_setpage(unsigned char page) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	128; glcd.c	lcd_waitbusy();
	CALL	_lcd_waitbusy
;	.line	129; glcd.c	DI = 0; RW = 0; 
	BCF	_PORTEbits, 0
	BCF	_PORTEbits, 1
;	.line	130; glcd.c	LCD_DATA = 0b10111000 | page;
	MOVLW	0xb8
	IORWF	r0x00, W
	MOVWF	_PORTD
;	.line	131; glcd.c	lcd_enable();
	CALL	_lcd_enable
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_cls	code
_lcd_cls:
;	.line	98; glcd.c	void lcd_cls(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
;	.line	102; glcd.c	lcd_selectside(LCD_BOTH);
	MOVLW	0x03
	MOVWF	POSTDEC1
	CALL	_lcd_selectside
	MOVF	POSTINC1, F
;	.line	103; glcd.c	for (x = 0; x < 8; x++) {
	CLRF	r0x00
_00146_DS_:
;	.line	105; glcd.c	lcd_setpage(x);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_lcd_setpage
	MOVF	POSTINC1, F
;	.line	108; glcd.c	lcd_setyaddr(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_lcd_setyaddr
	MOVF	POSTINC1, F
;	.line	111; glcd.c	LCD_DATA = 0; RW = 0; DI = 1;
	CLRF	_PORTD
	BCF	_PORTEbits, 1
	BSF	_PORTEbits, 0
;	.line	114; glcd.c	for (y = 0; y < 64; y++) {
	MOVLW	0x40
	MOVWF	r0x01
_00145_DS_:
;	.line	115; glcd.c	lcd_enable(); 
	CALL	_lcd_enable
	nop 
	nop 
	MOVF	r0x01, W
	MOVWF	r0x02
	DECF	r0x02, W
	MOVWF	r0x01
;	.line	114; glcd.c	for (y = 0; y < 64; y++) {
	MOVF	r0x01, W
	BNZ	_00145_DS_
;	.line	103; glcd.c	for (x = 0; x < 8; x++) {
	INCF	r0x00, F
	MOVLW	0x08
	SUBWF	r0x00, W
	BNC	_00146_DS_
;	.line	121; glcd.c	lcd_selectside(LCD_LEFT);
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
;	.line	86; glcd.c	void lcd_screenon(unsigned char on) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	88; glcd.c	CS1 = 0;
	BCF	_PORTCbits, 0
;	.line	89; glcd.c	CS2 = 0;
	BCF	_PORTCbits, 1
;	.line	90; glcd.c	RW = 0;
	BCF	_PORTEbits, 1
;	.line	91; glcd.c	DI = 0;
	BCF	_PORTEbits, 0
;	.line	92; glcd.c	LCD_TRIS = 0;	// all outputs	
	CLRF	_TRISD
;	.line	93; glcd.c	LATD = 0b00111110 | (on & 0b00000001);	// main screen turn on!
	MOVLW	0x01
	ANDWF	r0x00, F
	MOVLW	0x3e
	IORWF	r0x00, W
	MOVWF	_LATD
;	.line	94; glcd.c	lcd_enable();
	CALL	_lcd_enable
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_reset	code
_lcd_reset:
;	.line	67; glcd.c	void lcd_reset(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	74; glcd.c	sleep_ms(1);
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
;	.line	75; glcd.c	RESET = 1;
	BSF	_PORTCbits, 5
;	.line	76; glcd.c	sleep_ms(1);
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
;	.line	77; glcd.c	RESET = 0;
	BCF	_PORTCbits, 5
_00120_DS_:
;	.line	80; glcd.c	while (lcd_status() & 0b00010000) {
	CALL	_lcd_status
	MOVWF	r0x00
	BTFSS	r0x00, 4
	BRA	_00123_DS_
;	.line	81; glcd.c	sleep_ms(1);
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
;	.line	44; glcd.c	unsigned char lcd_status(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
;	.line	51; glcd.c	_lcd_tris = LCD_TRIS;
	MOVFF	_TRISD, r0x00
;	.line	54; glcd.c	LCD_TRIS = 0xFF;	// all inputs
	MOVLW	0xff
	MOVWF	_TRISD
;	.line	55; glcd.c	DI = 0; RW = 1;		// command/read
	BCF	_PORTEbits, 0
	BSF	_PORTEbits, 1
;	.line	57; glcd.c	lcd_enable();
	CALL	_lcd_enable
;	.line	58; glcd.c	_status = LCD_DATA;
	MOVFF	_PORTD, r0x01
;	.line	61; glcd.c	LCD_TRIS = _lcd_tris;
	MOVFF	r0x00, _TRISD
;	.line	63; glcd.c	return _status;
	MOVF	r0x01, W
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_enable	code
_lcd_enable:
;	.line	36; glcd.c	void lcd_enable(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	37; glcd.c	ENABLE = 1;
	BSF	_PORTEbits, 2
	nop 
	nop 
;	.line	39; glcd.c	ENABLE = 0;
	BCF	_PORTEbits, 2
	nop 
	nop 
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_glcd__lcd_init	code
_lcd_init:
;	.line	15; glcd.c	void lcd_init(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	16; glcd.c	LCD_TRIS = 0x00;
	CLRF	_TRISD
;	.line	17; glcd.c	ENABLE_TRIS = 0;
	BCF	_TRISEbits, 2
;	.line	18; glcd.c	RW_TRIS	= 0;
	BCF	_TRISEbits, 1
;	.line	19; glcd.c	DI_TRIS = 0;
	BCF	_TRISEbits, 0
;	.line	20; glcd.c	RESET_TRIS = 0;
	BCF	_TRISCbits, 5
;	.line	21; glcd.c	CS1_TRIS = 0;
	BCF	_TRISCbits, 0
;	.line	22; glcd.c	CS2_TRIS = 0;
	BCF	_TRISCbits, 1
;	.line	24; glcd.c	CS1 = 1;
	BSF	_PORTCbits, 0
;	.line	25; glcd.c	CS2 = 1;
	BSF	_PORTCbits, 1
;	.line	31; glcd.c	lcd_reset();
	CALL	_lcd_reset
;	.line	32; glcd.c	lcd_screenon(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_lcd_screenon
	MOVF	POSTINC1, F
;	.line	33; glcd.c	lcd_cls();
	CALL	_lcd_cls
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  846 (0x034e) bytes ( 0.65%)
;           	  423 (0x01a7) words
; udata size:	    1 (0x0001) bytes ( 0.03%)
; access size:	    3 (0x0003) bytes


	end
