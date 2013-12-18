;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.3.0 #8604 (Oct 27 2013) (Mac OS X x86_64)
; This file was generated Wed Dec 18 01:20:58 2013
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------
	list	p=18f4620
	radix	dec
	CONFIG	OSC=INTIO67,FCMEN=OFF,IESO=OFF
	CONFIG	PWRT=OFF,BOREN=OFF
	CONFIG	WDT=OFF
	CONFIG	WDTPS=8192
	CONFIG	CCP2MX=PORTC,PBADEN=OFF,LPT1OSC=OFF,MCLRE=ON
	CONFIG	STVREN=OFF,LVP=OFF,XINST=OFF


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_sleep_ms
	global	_init_timers
	global	_init_latches
	global	_set_ac_power
	global	_get_inputs
	global	_my_usart_open
	global	_fifo_in_use
	global	_fifo_put
	global	_fifo_get
	global	_base64decode
	global	_base64encode
	global	_validate_command
	global	_reset
	global	__debug
	global	_i
	global	_timer_1_ms
	global	_sensor_inputs
	global	_last_inputs
	global	_output_ac_power_pwm
	global	_ac_power_pwm_counter
	global	_ad_inputs
	global	_fifo_head
	global	_fifo_tail
	global	_fifo_buffer
	global	_command
	global	_command_index
	global	_valid_command
	global	__latch_2_data
	global	_main

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__gptrput1
	extern	__gptrget1
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
	extern	_crc16
	extern	_sprintf
	extern	_strchr
	extern	_memcpy
	extern	_adc_open
	extern	_adc_conv
	extern	_adc_busy
	extern	_adc_read
	extern	_adc_setchannel
	extern	_usart_drdy
	extern	_usart_getc
	extern	_usart_putc
	extern	_usart_puts
	extern	_latched_lcd_power
	extern	__mullong
	extern	__moduint

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
INDF0	equ	0xfef
POSTINC0	equ	0xfee
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
_timer_1_ms	res	4

udata_pillefyrsstyring_1	udata
_fifo_head	res	2

udata_pillefyrsstyring_2	udata
_fifo_tail	res	2

udata_pillefyrsstyring_3	udata
_command_index	res	1

udata_pillefyrsstyring_4	udata
_ac_power_pwm_counter	res	1

udata_pillefyrsstyring_5	udata
_output_ac_power_pwm	res	6

udata_pillefyrsstyring_6	udata
_last_inputs	res	1

udata_pillefyrsstyring_7	udata
_main_c_1_102	res	1

udata_pillefyrsstyring_8	udata
_sensor_inputs	res	1

udata_pillefyrsstyring_9	udata
_command	res	21

udata_pillefyrsstyring_10	udata
_valid_command	res	7

udata_pillefyrsstyring_11	udata
_main_buffer_1_102	res	10

udata_pillefyrsstyring_12	udata
_ad_inputs	res	16

udata_pillefyrsstyring_13	udata
_i	res	2

udata_pillefyrsstyring_14	udata
__latch_2_data	res	1

udata_pillefyrsstyring_15	udata
_fifo_buffer	res	100

udata_pillefyrsstyring_16	udata
_base64decode_xlate_1_149	res	17

udata_pillefyrsstyring_17	udata
_validate_command_decoded_command_1_154	res	9

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block for absolute section
; ;-----------------------------------------
S_pillefyrsstyring_ivec_0x1_isr_high_prio	code	0X000008
ivec_0x1_isr_high_prio:
	GOTO	_isr_high_prio

; ; Starting pCode block for absolute section
; ;-----------------------------------------
S_pillefyrsstyring_ivec_0x2_isr_low_prio	code	0X000018
ivec_0x2_isr_low_prio:
	GOTO	_isr_low_prio

; I code from now on!
; ; Starting pCode block
S_pillefyrsstyring__main	code
_main:
;	.line	47; pillefyrsstyring.c	OSCCONbits.SCS = 0x10;
	MOVF	_OSCCONbits, W
	ANDLW	0xfc
	MOVWF	_OSCCONbits
;	.line	48; pillefyrsstyring.c	OSCCONbits.IRCF = 0x7;	// 8 MHz
	MOVF	_OSCCONbits, W
	ANDLW	0x8f
	IORLW	0x70
	MOVWF	_OSCCONbits
;	.line	49; pillefyrsstyring.c	WDTCONbits.SWDTEN = 1;	// enable watchdog
	BSF	_WDTCONbits, 0
	clrwdt 
	BANKSEL	_timer_1_ms
;	.line	52; pillefyrsstyring.c	timer_1_ms = 0;
	CLRF	_timer_1_ms, B
	BANKSEL	(_timer_1_ms + 1)
	CLRF	(_timer_1_ms + 1), B
	BANKSEL	(_timer_1_ms + 2)
	CLRF	(_timer_1_ms + 2), B
	BANKSEL	(_timer_1_ms + 3)
	CLRF	(_timer_1_ms + 3), B
	BANKSEL	_fifo_head
;	.line	54; pillefyrsstyring.c	fifo_head = 0;
	CLRF	_fifo_head, B
	BANKSEL	(_fifo_head + 1)
	CLRF	(_fifo_head + 1), B
	BANKSEL	_fifo_tail
;	.line	55; pillefyrsstyring.c	fifo_tail = 0;
	CLRF	_fifo_tail, B
	BANKSEL	(_fifo_tail + 1)
	CLRF	(_fifo_tail + 1), B
	BANKSEL	_command_index
;	.line	56; pillefyrsstyring.c	command_index = 0;
	CLRF	_command_index, B
	BANKSEL	_output_ac_power_pwm
;	.line	59; pillefyrsstyring.c	output_ac_power_pwm[0] = 0;
	CLRF	_output_ac_power_pwm, B
	BANKSEL	(_output_ac_power_pwm + 1)
;	.line	60; pillefyrsstyring.c	output_ac_power_pwm[1] = 0;
	CLRF	(_output_ac_power_pwm + 1), B
	BANKSEL	(_output_ac_power_pwm + 2)
;	.line	61; pillefyrsstyring.c	output_ac_power_pwm[2] = 0;
	CLRF	(_output_ac_power_pwm + 2), B
	BANKSEL	(_output_ac_power_pwm + 3)
;	.line	62; pillefyrsstyring.c	output_ac_power_pwm[3] = 0;
	CLRF	(_output_ac_power_pwm + 3), B
	BANKSEL	(_output_ac_power_pwm + 4)
;	.line	63; pillefyrsstyring.c	output_ac_power_pwm[4] = 0;
	CLRF	(_output_ac_power_pwm + 4), B
	BANKSEL	(_output_ac_power_pwm + 5)
;	.line	64; pillefyrsstyring.c	output_ac_power_pwm[5] = 0;
	CLRF	(_output_ac_power_pwm + 5), B
	BANKSEL	_ac_power_pwm_counter
;	.line	65; pillefyrsstyring.c	ac_power_pwm_counter = 0;
	CLRF	_ac_power_pwm_counter, B
;	.line	68; pillefyrsstyring.c	RCONbits.IPEN = 1;
	BSF	_RCONbits, 7
;	.line	70; pillefyrsstyring.c	init_timers();
	CALL	_init_timers
;	.line	73; pillefyrsstyring.c	IPR1bits.RCIP = 0;
	BCF	_IPR1bits, 5
;	.line	74; pillefyrsstyring.c	IPR1bits.TXIP = 0;
	BCF	_IPR1bits, 4
;	.line	85; pillefyrsstyring.c	my_usart_open();
	CALL	_my_usart_open
;	.line	87; pillefyrsstyring.c	sleep_ms(1000);	// let stuff settle...
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
;	.line	88; pillefyrsstyring.c	usart_puts("OpenStoker starting... serial working\n\r");
	MOVLW	UPPER(__str_0)
	MOVWF	r0x02
	MOVLW	HIGH(__str_0)
	MOVWF	r0x01
	MOVLW	LOW(__str_0)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_usart_puts
	MOVLW	0x03
	ADDWF	FSR1L, F
;	.line	130; pillefyrsstyring.c	adc_open(ADC_CHN_0, ADC_FOSC_4 | ADC_ACQT_20, ADC_CFG_12A, ADC_FRM_RJUST | ADC_INT_OFF | ADC_VCFG_AN3_AN2);
	MOVLW	0xb0
	MOVWF	POSTDEC1
	MOVLW	0x03
	MOVWF	POSTDEC1
	MOVLW	0x3c
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_adc_open
	MOVLW	0x04
	ADDWF	FSR1L, F
;	.line	133; pillefyrsstyring.c	init_latches();
	CALL	_init_latches
_00105_DS_:
;	.line	138; pillefyrsstyring.c	while (!fifo_in_use()) {
	CALL	_fifo_in_use
	MOVWF	r0x00
	MOVF	r0x00, W
	BNZ	_00107_DS_
;	.line	139; pillefyrsstyring.c	latched_lcd_power(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_power
	MOVF	POSTINC1, F
;	.line	140; pillefyrsstyring.c	sleep_ms(1000);
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
;	.line	141; pillefyrsstyring.c	latched_lcd_power(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_power
	MOVF	POSTINC1, F
;	.line	142; pillefyrsstyring.c	sleep_ms(1000);
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
	BRA	_00105_DS_
_00107_DS_:
;	.line	147; pillefyrsstyring.c	latched_lcd_power(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_power
	MOVF	POSTINC1, F
;	.line	149; pillefyrsstyring.c	last_inputs = get_inputs();
	CALL	_get_inputs
	BANKSEL	_last_inputs
	MOVWF	_last_inputs, B
_00135_DS_:
;	.line	154; pillefyrsstyring.c	if (fifo_get(&c)) {
	MOVLW	HIGH(_main_c_1_102)
	MOVWF	r0x01
	MOVLW	LOW(_main_c_1_102)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_fifo_get
	MOVWF	r0x00
	MOVLW	0x03
	ADDWF	FSR1L, F
	MOVF	r0x00, W
	BTFSC	STATUS, 2
	BRA	_00127_DS_
	BANKSEL	_main_c_1_102
;	.line	155; pillefyrsstyring.c	if (c == '\n' || c == '.') {
	MOVF	_main_c_1_102, W, B
	XORLW	0x0a
	BZ	_00122_DS_
_00208_DS_:
	BANKSEL	_main_c_1_102
	MOVF	_main_c_1_102, W, B
	XORLW	0x2e
	BZ	_00122_DS_
	BRA	_00123_DS_
_00122_DS_:
	BANKSEL	_command_index
;	.line	157; pillefyrsstyring.c	command_index = 0;
	CLRF	_command_index, B
;	.line	158; pillefyrsstyring.c	if (validate_command(command, valid_command)) {
	MOVLW	HIGH(_command)
	MOVWF	r0x01
	MOVLW	LOW(_command)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVLW	HIGH(_valid_command)
	MOVWF	r0x04
	MOVLW	LOW(_valid_command)
	MOVWF	r0x03
	MOVLW	0x80
	MOVWF	r0x05
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_validate_command
	MOVWF	r0x00
	MOVLW	0x06
	ADDWF	FSR1L, F
	MOVF	r0x00, W
	BTFSC	STATUS, 2
	BRA	_00117_DS_
	clrwdt 
;	.line	160; pillefyrsstyring.c	RELAY = 1;
	BSF	_LATCbits, 5
	BANKSEL	_valid_command
;	.line	162; pillefyrsstyring.c	switch (valid_command[0]) {					// only look at first character
	MOVF	_valid_command, W, B
	MOVWF	r0x00
	MOVF	r0x00, W
	XORLW	0x61
	BNZ	_00212_DS_
	BRA	_00156_DS_
_00212_DS_:
	MOVF	r0x00, W
	XORLW	0x67
	BNZ	_00214_DS_
	BRA	_00110_DS_
_00214_DS_:
	MOVF	r0x00, W
	XORLW	0x73
	BZ	_00108_DS_
	MOVF	r0x00, W
	XORLW	0x7a
	BNZ	_00218_DS_
	BRA	_00111_DS_
_00218_DS_:
	BRA	_00114_DS_
_00108_DS_:
;	.line	164; pillefyrsstyring.c	for (j = 0; j < AC_POWER_OUTS; j++) {
	CLRF	r0x00
_00137_DS_:
;	.line	165; pillefyrsstyring.c	output_ac_power_pwm[j] = valid_command[j + 1];
	MOVLW	LOW(_output_ac_power_pwm)
	ADDWF	r0x00, W
	MOVWF	r0x01
	CLRF	r0x02
	MOVLW	HIGH(_output_ac_power_pwm)
	ADDWFC	r0x02, F
	INCF	r0x00, W
	MOVWF	r0x03
	MOVLW	LOW(_valid_command)
	ADDWF	r0x03, W
	MOVWF	r0x04
	CLRF	r0x05
	MOVLW	HIGH(_valid_command)
	ADDWFC	r0x05, F
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, FSR0H
	MOVFF	INDF0, r0x04
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	r0x04, INDF0
;	.line	164; pillefyrsstyring.c	for (j = 0; j < AC_POWER_OUTS; j++) {
	MOVFF	r0x03, r0x00
	MOVLW	0x06
	SUBWF	r0x00, W
	BNC	_00137_DS_
;	.line	167; pillefyrsstyring.c	usart_putc('!');	// ok values set to ac power pwm system
	MOVLW	0x21
	CALL	_usart_putc
;	.line	168; pillefyrsstyring.c	usart_puts("\n\r");
	MOVLW	UPPER(__str_1)
	MOVWF	r0x02
	MOVLW	HIGH(__str_1)
	MOVWF	r0x01
	MOVLW	LOW(__str_1)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_usart_puts
	MOVLW	0x03
	ADDWF	FSR1L, F
;	.line	169; pillefyrsstyring.c	break;
	BRA	_00127_DS_
_00110_DS_:
;	.line	171; pillefyrsstyring.c	sprintf(buffer, "g%02x\n\r", sensor_inputs);
	MOVFF	_sensor_inputs, r0x00
	CLRF	r0x01
	MOVLW	UPPER(__str_2)
	MOVWF	r0x04
	MOVLW	HIGH(__str_2)
	MOVWF	r0x03
	MOVLW	LOW(__str_2)
	MOVWF	r0x02
	MOVLW	HIGH(_main_buffer_1_102)
	MOVWF	r0x06
	MOVLW	LOW(_main_buffer_1_102)
	MOVWF	r0x05
	MOVLW	0x80
	MOVWF	r0x07
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	CALL	_sprintf
	MOVLW	0x08
	ADDWF	FSR1L, F
;	.line	172; pillefyrsstyring.c	usart_puts(buffer);
	MOVLW	HIGH(_main_buffer_1_102)
	MOVWF	r0x01
	MOVLW	LOW(_main_buffer_1_102)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_usart_puts
	MOVLW	0x03
	ADDWF	FSR1L, F
;	.line	173; pillefyrsstyring.c	break;
	BRA	_00127_DS_
_00111_DS_:
;	.line	175; pillefyrsstyring.c	usart_putc('z');
	MOVLW	0x7a
	CALL	_usart_putc
;	.line	176; pillefyrsstyring.c	usart_puts("\n\r");
	MOVLW	UPPER(__str_1)
	MOVWF	r0x02
	MOVLW	HIGH(__str_1)
	MOVWF	r0x01
	MOVLW	LOW(__str_1)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_usart_puts
	MOVLW	0x03
	ADDWF	FSR1L, F
;	.line	177; pillefyrsstyring.c	sleep_ms(100);
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
;	.line	178; pillefyrsstyring.c	reset();
	CALL	_reset
;	.line	179; pillefyrsstyring.c	break;
	BRA	_00127_DS_
_00156_DS_:
;	.line	181; pillefyrsstyring.c	for (j = 0; j < AD_INPUTS; j++) {
	CLRF	r0x00
_00139_DS_:
;	.line	182; pillefyrsstyring.c	sprintf(buffer, "ad%d: %04x\n\r", j, ad_inputs[0]);
	MOVFF	r0x00, r0x01
	CLRF	r0x02
	MOVLW	UPPER(__str_3)
	MOVWF	r0x05
	MOVLW	HIGH(__str_3)
	MOVWF	r0x04
	MOVLW	LOW(__str_3)
	MOVWF	r0x03
	MOVLW	HIGH(_main_buffer_1_102)
	MOVWF	r0x07
	MOVLW	LOW(_main_buffer_1_102)
	MOVWF	r0x06
	MOVLW	0x80
	MOVWF	r0x08
	BANKSEL	(_ad_inputs + 1)
	MOVF	(_ad_inputs + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_ad_inputs
	MOVF	_ad_inputs, W, B
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x08, W
	MOVWF	POSTDEC1
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	CALL	_sprintf
	MOVLW	0x0a
	ADDWF	FSR1L, F
;	.line	183; pillefyrsstyring.c	usart_puts(buffer);
	MOVLW	HIGH(_main_buffer_1_102)
	MOVWF	r0x02
	MOVLW	LOW(_main_buffer_1_102)
	MOVWF	r0x01
	MOVLW	0x80
	MOVWF	r0x03
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	CALL	_usart_puts
	MOVLW	0x03
	ADDWF	FSR1L, F
;	.line	181; pillefyrsstyring.c	for (j = 0; j < AD_INPUTS; j++) {
	INCF	r0x00, F
	MOVLW	0x08
	SUBWF	r0x00, W
	BTFSS	STATUS, 0
	BRA	_00139_DS_
;	.line	185; pillefyrsstyring.c	break;
	BRA	_00127_DS_
_00114_DS_:
;	.line	187; pillefyrsstyring.c	usart_putc('?');	// unknown command
	MOVLW	0x3f
	CALL	_usart_putc
;	.line	188; pillefyrsstyring.c	}		
	BRA	_00127_DS_
_00117_DS_:
;	.line	191; pillefyrsstyring.c	usart_putc('?');			// command not valid
	MOVLW	0x3f
	CALL	_usart_putc
	BRA	_00127_DS_
_00123_DS_:
;	.line	197; pillefyrsstyring.c	if (command_index <= COMMAND_LENGTH) {
	MOVLW	0x15
	BANKSEL	_command_index
	SUBWF	_command_index, W, B
	BC	_00120_DS_
;	.line	198; pillefyrsstyring.c	command[command_index] = c;
	MOVLW	LOW(_command)
	BANKSEL	_command_index
	ADDWF	_command_index, W, B
	MOVWF	r0x00
	CLRF	r0x01
	MOVLW	HIGH(_command)
	ADDWFC	r0x01, F
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	_main_c_1_102, INDF0
	BANKSEL	_command_index
;	.line	199; pillefyrsstyring.c	command_index++;
	INCF	_command_index, F, B
	BRA	_00127_DS_
_00120_DS_:
	BANKSEL	(_command + 20)
;	.line	202; pillefyrsstyring.c	command[COMMAND_LENGTH] = '\0';	// null terminate it
	CLRF	(_command + 20), B
	BANKSEL	_command_index
;	.line	203; pillefyrsstyring.c	command_index = 0;
	CLRF	_command_index, B
;	.line	204; pillefyrsstyring.c	usart_putc('+');		// overflow
	MOVLW	0x2b
	CALL	_usart_putc
;	.line	205; pillefyrsstyring.c	usart_puts("\n\r");
	MOVLW	UPPER(__str_1)
	MOVWF	r0x02
	MOVLW	HIGH(__str_1)
	MOVWF	r0x01
	MOVLW	LOW(__str_1)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_usart_puts
	MOVLW	0x03
	ADDWF	FSR1L, F
_00127_DS_:
	BANKSEL	_sensor_inputs
;	.line	210; pillefyrsstyring.c	if (sensor_inputs != last_inputs) {
	MOVF	_sensor_inputs, W, B
	BANKSEL	_last_inputs
	XORWF	_last_inputs, W, B
	BZ	_00162_DS_
;	.line	211; pillefyrsstyring.c	last_inputs = sensor_inputs;
	MOVFF	_sensor_inputs, _last_inputs
;	.line	212; pillefyrsstyring.c	_debug();	// blocks main for a while :-/
	CALL	__debug
_00162_DS_:
;	.line	216; pillefyrsstyring.c	for (j = 0; j < AD_INPUTS; j++) {
	CLRF	r0x00
	CLRF	r0x01
	CLRF	r0x02
_00141_DS_:
;	.line	217; pillefyrsstyring.c	adc_setchannel(j);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_adc_setchannel
	MOVF	POSTINC1, F
;	.line	218; pillefyrsstyring.c	adc_conv();
	CALL	_adc_conv
_00130_DS_:
;	.line	219; pillefyrsstyring.c	while(adc_busy()) {
	CALL	_adc_busy
	MOVWF	r0x03
	MOVF	r0x03, W
	BNZ	_00130_DS_
;	.line	222; pillefyrsstyring.c	ad_inputs[j] = adc_read();
	MOVLW	LOW(_ad_inputs)
	ADDWF	r0x01, W
	MOVWF	r0x03
	MOVLW	HIGH(_ad_inputs)
	ADDWFC	r0x02, W
	MOVWF	r0x04
	CALL	_adc_read
	MOVWF	r0x05
	MOVFF	PRODL, r0x06
	MOVFF	r0x03, FSR0L
	MOVFF	r0x04, FSR0H
	MOVFF	r0x05, POSTINC0
	MOVFF	r0x06, INDF0
;	.line	216; pillefyrsstyring.c	for (j = 0; j < AD_INPUTS; j++) {
	MOVLW	0x02
	ADDWF	r0x01, F
	BTFSC	STATUS, 0
	INCF	r0x02, F
	INCF	r0x00, F
	MOVLW	0x08
	SUBWF	r0x00, W
	BNC	_00141_DS_
	BRA	_00135_DS_
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring___debug	code
__debug:
;	.line	503; pillefyrsstyring.c	void _debug() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	504; pillefyrsstyring.c	latched_lcd_power(0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_latched_lcd_power
	MOVF	POSTINC1, F
;	.line	505; pillefyrsstyring.c	sleep_ms(200);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0xc8
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
;	.line	506; pillefyrsstyring.c	latched_lcd_power(1);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_latched_lcd_power
	MOVF	POSTINC1, F
;	.line	507; pillefyrsstyring.c	sleep_ms(200);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0xc8
	MOVWF	POSTDEC1
	CALL	_sleep_ms
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__reset	code
_reset:
;	.line	497; pillefyrsstyring.c	void reset() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	reset
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__validate_command	code
_validate_command:
;	.line	480; pillefyrsstyring.c	unsigned char validate_command(unsigned char *encoded_command, unsigned char *validated_command) {
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
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
	MOVLW	0x06
	MOVFF	PLUSW2, r0x04
	MOVLW	0x07
	MOVFF	PLUSW2, r0x05
;	.line	484; pillefyrsstyring.c	base64decode(encoded_command, decoded_command);
	MOVLW	HIGH(_validate_command_decoded_command_1_154)
	MOVWF	r0x07
	MOVLW	LOW(_validate_command_decoded_command_1_154)
	MOVWF	r0x06
	MOVLW	0x80
	MOVWF	r0x08
	MOVF	r0x08, W
	MOVWF	POSTDEC1
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_base64decode
	MOVLW	0x06
	ADDWF	FSR1L, F
;	.line	485; pillefyrsstyring.c	received_checksum = (decoded_command[7] << 8) + decoded_command[8];
	MOVFF	(_validate_command_decoded_command_1_154 + 7), r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	MOVWF	r0x06
	CLRF	r0x02
	MOVFF	(_validate_command_decoded_command_1_154 + 8), r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	ADDWF	r0x02, F
	MOVF	r0x01, W
	ADDWFC	r0x06, F
;	.line	486; pillefyrsstyring.c	checksum = crc16(decoded_command, 7, 0);
	MOVLW	HIGH(_validate_command_decoded_command_1_154)
	MOVWF	r0x01
	MOVLW	LOW(_validate_command_decoded_command_1_154)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x07
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x07
	MOVWF	POSTDEC1
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_crc16
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVLW	0x09
	ADDWF	FSR1L, F
;	.line	488; pillefyrsstyring.c	if (received_checksum == checksum) {
	MOVF	r0x02, W
	XORWF	r0x00, W
	BNZ	_00381_DS_
	MOVF	r0x06, W
	XORWF	r0x01, W
	BZ	_00382_DS_
_00381_DS_:
	BRA	_00374_DS_
_00382_DS_:
;	.line	489; pillefyrsstyring.c	memcpy(validated_command, decoded_command, 7);
	MOVF	r0x05, W
	MOVWF	r0x05
	MOVF	r0x04, W
	MOVWF	r0x04
	MOVF	r0x03, W
	MOVWF	r0x03
	MOVLW	HIGH(_validate_command_decoded_command_1_154)
	MOVWF	r0x01
	MOVLW	LOW(_validate_command_decoded_command_1_154)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x07
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	CALL	_memcpy
	MOVLW	0x08
	ADDWF	FSR1L, F
;	.line	490; pillefyrsstyring.c	return 1;
	MOVLW	0x01
	BRA	_00376_DS_
_00374_DS_:
;	.line	493; pillefyrsstyring.c	return 0;
	CLRF	WREG
_00376_DS_:
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
S_pillefyrsstyring__base64encode	code
_base64encode:
;	.line	470; pillefyrsstyring.c	void base64encode(unsigned char *s) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	478; pillefyrsstyring.c	}
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__base64decode	code
_base64decode:
;	.line	455; pillefyrsstyring.c	void base64decode(unsigned char *s, unsigned char *buffer) {
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
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
	MOVLW	0x06
	MOVFF	PLUSW2, r0x04
	MOVLW	0x07
	MOVFF	PLUSW2, r0x05
;	.line	460; pillefyrsstyring.c	char xlate[] = "0123456789abcdef";
	MOVLW	0x30
	BANKSEL	_base64decode_xlate_1_149
	MOVWF	_base64decode_xlate_1_149, B
	MOVLW	0x31
	BANKSEL	(_base64decode_xlate_1_149 + 1)
	MOVWF	(_base64decode_xlate_1_149 + 1), B
	MOVLW	0x32
	BANKSEL	(_base64decode_xlate_1_149 + 2)
	MOVWF	(_base64decode_xlate_1_149 + 2), B
	MOVLW	0x33
	BANKSEL	(_base64decode_xlate_1_149 + 3)
	MOVWF	(_base64decode_xlate_1_149 + 3), B
	MOVLW	0x34
	BANKSEL	(_base64decode_xlate_1_149 + 4)
	MOVWF	(_base64decode_xlate_1_149 + 4), B
	MOVLW	0x35
	BANKSEL	(_base64decode_xlate_1_149 + 5)
	MOVWF	(_base64decode_xlate_1_149 + 5), B
	MOVLW	0x36
	BANKSEL	(_base64decode_xlate_1_149 + 6)
	MOVWF	(_base64decode_xlate_1_149 + 6), B
	MOVLW	0x37
	BANKSEL	(_base64decode_xlate_1_149 + 7)
	MOVWF	(_base64decode_xlate_1_149 + 7), B
	MOVLW	0x38
	BANKSEL	(_base64decode_xlate_1_149 + 8)
	MOVWF	(_base64decode_xlate_1_149 + 8), B
	MOVLW	0x39
	BANKSEL	(_base64decode_xlate_1_149 + 9)
	MOVWF	(_base64decode_xlate_1_149 + 9), B
	MOVLW	0x61
	BANKSEL	(_base64decode_xlate_1_149 + 10)
	MOVWF	(_base64decode_xlate_1_149 + 10), B
	MOVLW	0x62
	BANKSEL	(_base64decode_xlate_1_149 + 11)
	MOVWF	(_base64decode_xlate_1_149 + 11), B
	MOVLW	0x63
	BANKSEL	(_base64decode_xlate_1_149 + 12)
	MOVWF	(_base64decode_xlate_1_149 + 12), B
	MOVLW	0x64
	BANKSEL	(_base64decode_xlate_1_149 + 13)
	MOVWF	(_base64decode_xlate_1_149 + 13), B
	MOVLW	0x65
	BANKSEL	(_base64decode_xlate_1_149 + 14)
	MOVWF	(_base64decode_xlate_1_149 + 14), B
	MOVLW	0x66
	BANKSEL	(_base64decode_xlate_1_149 + 15)
	MOVWF	(_base64decode_xlate_1_149 + 15), B
	BANKSEL	(_base64decode_xlate_1_149 + 16)
	CLRF	(_base64decode_xlate_1_149 + 16), B
_00351_DS_:
;	.line	462; pillefyrsstyring.c	while (*h) {
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrget1
	MOVWF	r0x06
	MOVF	r0x06, W
	BTFSC	STATUS, 2
	BRA	_00354_DS_
;	.line	463; pillefyrsstyring.c	*b = ((strchr(xlate, *h) - xlate) * 16) /* multiply leading digit by 16 */
	MOVLW	HIGH(_base64decode_xlate_1_149)
	MOVWF	r0x08
	MOVLW	LOW(_base64decode_xlate_1_149)
	MOVWF	r0x07
	MOVLW	0x80
	MOVWF	r0x09
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	MOVF	r0x09, W
	MOVWF	POSTDEC1
	MOVF	r0x08, W
	MOVWF	POSTDEC1
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	CALL	_strchr
	MOVWF	r0x06
	MOVFF	PRODL, r0x07
	MOVFF	PRODH, r0x08
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVLW	LOW(_base64decode_xlate_1_149)
	SUBWF	r0x06, F
	MOVLW	HIGH(_base64decode_xlate_1_149)
	SUBWFB	r0x07, F
; ;multiply lit val:0x10 by variable r0x06 and store in r0x06
	MOVF	r0x06, W
	MULLW	0x10
	MOVFF	PRODL, r0x06
;	.line	464; pillefyrsstyring.c	+ ((strchr(xlate, *(h+1)) - xlate));
	MOVLW	HIGH(_base64decode_xlate_1_149)
	MOVWF	r0x08
	MOVLW	LOW(_base64decode_xlate_1_149)
	MOVWF	r0x07
	MOVLW	0x80
	MOVWF	r0x09
	MOVF	r0x00, W
	ADDLW	0x01
	MOVWF	r0x0a
	MOVLW	0x00
	ADDWFC	r0x01, W
	MOVWF	r0x0b
	MOVLW	0x00
	ADDWFC	r0x02, W
	MOVWF	r0x0c
	MOVFF	r0x0a, FSR0L
	MOVFF	r0x0b, PRODL
	MOVF	r0x0c, W
	CALL	__gptrget1
	MOVWF	r0x0a
	MOVF	r0x0a, W
	MOVWF	POSTDEC1
	MOVF	r0x09, W
	MOVWF	POSTDEC1
	MOVF	r0x08, W
	MOVWF	POSTDEC1
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	CALL	_strchr
	MOVWF	r0x07
	MOVFF	PRODL, r0x08
	MOVFF	PRODH, r0x09
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVLW	LOW(_base64decode_xlate_1_149)
	SUBWF	r0x07, F
	MOVLW	HIGH(_base64decode_xlate_1_149)
	SUBWFB	r0x08, F
	MOVF	r0x07, W
	ADDWF	r0x06, F
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x03, FSR0L
	MOVFF	r0x04, PRODL
	MOVF	r0x05, W
	CALL	__gptrput1
;	.line	465; pillefyrsstyring.c	h += 2;
	MOVLW	0x02
	ADDWF	r0x00, F
	MOVLW	0x00
	ADDWFC	r0x01, F
	ADDWFC	r0x02, F
;	.line	466; pillefyrsstyring.c	b++;
	INCF	r0x03, F
	BNC	_00351_DS_
	INFSNZ	r0x04, F
	INCF	r0x05, F
_00363_DS_:
	BRA	_00351_DS_
_00354_DS_:
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
S_pillefyrsstyring__fifo_get	code
_fifo_get:
;	.line	445; pillefyrsstyring.c	unsigned char fifo_get(unsigned char *c) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
;	.line	446; pillefyrsstyring.c	if (fifo_in_use() != 0) {
	CALL	_fifo_in_use
	MOVWF	r0x03
	MOVF	r0x03, W
	BZ	_00344_DS_
;	.line	447; pillefyrsstyring.c	*c = fifo_buffer[fifo_tail++ % QUEUE_SIZE];
	MOVFF	_fifo_tail, r0x03
	MOVFF	(_fifo_tail + 1), r0x04
	BANKSEL	_fifo_tail
	INCFSZ	_fifo_tail, F, B
	BRA	_10392_DS_
	BANKSEL	(_fifo_tail + 1)
	INCF	(_fifo_tail + 1), F, B
_10392_DS_:
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x64
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	CALL	__moduint
	MOVWF	r0x03
	MOVFF	PRODL, r0x04
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVLW	LOW(_fifo_buffer)
	ADDWF	r0x03, F
	MOVLW	HIGH(_fifo_buffer)
	ADDWFC	r0x04, F
	MOVFF	r0x03, FSR0L
	MOVFF	r0x04, FSR0H
	MOVFF	INDF0, r0x03
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrput1
;	.line	448; pillefyrsstyring.c	return 1;
	MOVLW	0x01
	BRA	_00346_DS_
_00344_DS_:
;	.line	451; pillefyrsstyring.c	return 0;
	CLRF	WREG
_00346_DS_:
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__fifo_put	code
_fifo_put:
;	.line	435; pillefyrsstyring.c	unsigned char fifo_put(unsigned char c) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	436; pillefyrsstyring.c	if (fifo_in_use() != QUEUE_SIZE) {
	CALL	_fifo_in_use
	MOVWF	r0x01
	MOVF	r0x01, W
	XORLW	0x64
	BZ	_00330_DS_
;	.line	437; pillefyrsstyring.c	fifo_buffer[fifo_head++ % QUEUE_SIZE] = c;
	MOVFF	_fifo_head, r0x01
	MOVFF	(_fifo_head + 1), r0x02
	BANKSEL	_fifo_head
	INCFSZ	_fifo_head, F, B
	BRA	_20393_DS_
	BANKSEL	(_fifo_head + 1)
	INCF	(_fifo_head + 1), F, B
_20393_DS_:
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x64
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	CALL	__moduint
	MOVWF	r0x01
	MOVFF	PRODL, r0x02
	MOVLW	0x04
	ADDWF	FSR1L, F
	MOVLW	LOW(_fifo_buffer)
	ADDWF	r0x01, F
	MOVLW	HIGH(_fifo_buffer)
	ADDWFC	r0x02, F
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, FSR0H
	MOVFF	r0x00, INDF0
;	.line	438; pillefyrsstyring.c	return 1;
	MOVLW	0x01
	BRA	_00332_DS_
_00330_DS_:
;	.line	441; pillefyrsstyring.c	return 0;
	CLRF	WREG
_00332_DS_:
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__fifo_in_use	code
_fifo_in_use:
;	.line	431; pillefyrsstyring.c	unsigned char fifo_in_use() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	BANKSEL	_fifo_head
;	.line	432; pillefyrsstyring.c	return fifo_head - fifo_tail;
	MOVF	_fifo_head, W, B
	MOVWF	r0x00
	BANKSEL	_fifo_tail
	MOVF	_fifo_tail, W, B
	MOVWF	r0x01
	MOVF	r0x01, W
	SUBWF	r0x00, F
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__my_usart_open	code
_my_usart_open:
;	.line	401; pillefyrsstyring.c	void my_usart_open() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	402; pillefyrsstyring.c	SPBRG = 103;					// 8MHz => 19230 baud
	MOVLW	0x67
	MOVWF	_SPBRG
;	.line	403; pillefyrsstyring.c	TXSTAbits.BRGH = 1;	// (1 = high speed)
	BSF	_TXSTAbits, 2
;	.line	404; pillefyrsstyring.c	TXSTAbits.SYNC = 0;	// (0 = asynchronous)
	BCF	_TXSTAbits, 4
;	.line	405; pillefyrsstyring.c	BAUDCONbits.BRG16 = 1;
	BSF	_BAUDCONbits, 3
;	.line	408; pillefyrsstyring.c	RCSTAbits.SPEN = 1; // (1 = serial port enabled)
	BSF	_RCSTAbits, 7
;	.line	411; pillefyrsstyring.c	PIE1bits.TXIE = 0; // (1 = enabled)
	BCF	_PIE1bits, 4
;	.line	412; pillefyrsstyring.c	IPR1bits.TXIP = 0; // USART Tx on low priority interrupt
	BCF	_IPR1bits, 4
;	.line	415; pillefyrsstyring.c	PIE1bits.RCIE = 1; // (1 = enabled)
	BSF	_PIE1bits, 5
;	.line	416; pillefyrsstyring.c	IPR1bits.RCIP = 0; // USART Rx on low priority interrupt
	BCF	_IPR1bits, 5
;	.line	419; pillefyrsstyring.c	TXSTAbits.TX9 = 0; // (0 = 8-bit transmit)
	BCF	_TXSTAbits, 6
;	.line	422; pillefyrsstyring.c	RCSTAbits.RX9 = 0; // (0 = 8-bit reception)
	BCF	_RCSTAbits, 6
;	.line	425; pillefyrsstyring.c	RCSTAbits.CREN = 1; // (1 = Enables receiver)
	BSF	_RCSTAbits, 4
;	.line	428; pillefyrsstyring.c	TXSTAbits.TXEN = 1; // (1 = transmit enabled)
	BSF	_TXSTAbits, 5
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__get_inputs	code
_get_inputs:
;	.line	389; pillefyrsstyring.c	unsigned char get_inputs() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	393; pillefyrsstyring.c	LATCH_DATA_TRIS = 0xff;		// inputs
	MOVLW	0xff
	MOVWF	_TRISD
;	.line	394; pillefyrsstyring.c	LATCH_1 = LATCH_1_ENABLED;
	BCF	_LATAbits, 4
;	.line	395; pillefyrsstyring.c	data = LATCH_DATA_READ; // & 0b00100000;
	MOVFF	_PORTD, r0x00
;	.line	396; pillefyrsstyring.c	LATCH_1 = LATCH_1_DISABLED;
	BSF	_LATAbits, 4
;	.line	398; pillefyrsstyring.c	return data;
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__set_ac_power	code
_set_ac_power:
;	.line	371; pillefyrsstyring.c	void set_ac_power(unsigned char header_mask, unsigned char value) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
;	.line	372; pillefyrsstyring.c	header_mask &= (EXT_FEEDER_L1 | FAN_L2 | INT_FEEDER_L3 |HEATER_L4 | L5 | L6);	// BUG HERE! turning on L1 or L6 restarts
	MOVLW	0x3f
	ANDWF	r0x00, F
;	.line	374; pillefyrsstyring.c	value &= header_mask;
	MOVF	r0x00, W
	ANDWF	r0x01, F
;	.line	375; pillefyrsstyring.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	376; pillefyrsstyring.c	if (value) {	// set it
	MOVF	r0x01, W
	BZ	_00307_DS_
;	.line	377; pillefyrsstyring.c	_latch_2_data |= header_mask;
	MOVF	r0x00, W
	BANKSEL	__latch_2_data
	IORWF	__latch_2_data, F, B
;	.line	378; pillefyrsstyring.c	LATCH_DATA = _latch_2_data;
	MOVFF	__latch_2_data, _LATD
	BRA	_00308_DS_
_00307_DS_:
;	.line	381; pillefyrsstyring.c	_latch_2_data &= ~header_mask;
	COMF	r0x00, F
	MOVF	r0x00, W
	BANKSEL	__latch_2_data
	ANDWF	__latch_2_data, F, B
;	.line	382; pillefyrsstyring.c	LATCH_DATA = _latch_2_data;
	MOVFF	__latch_2_data, _LATD
_00308_DS_:
;	.line	384; pillefyrsstyring.c	LATCH_2 = LATCH_2_ENABLED;
	BSF	_LATAbits, 7
;	.line	385; pillefyrsstyring.c	LATCH_2 = LATCH_2_DISABLED;
	BCF	_LATAbits, 7
;	.line	386; pillefyrsstyring.c	LATCH_DATA = 0x00;
	CLRF	_LATD
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__init_latches	code
_init_latches:
;	.line	351; pillefyrsstyring.c	void init_latches() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	352; pillefyrsstyring.c	LATCH_DATA_TRIS = 0x00;		// outputs
	CLRF	_TRISD
;	.line	353; pillefyrsstyring.c	LATCH_1_TRIS = 0x0; 			// output
	BCF	_TRISAbits, 4
;	.line	354; pillefyrsstyring.c	LATCH_1 = LATCH_1_DISABLED;	// no inputs from input latch
	BSF	_LATAbits, 4
;	.line	356; pillefyrsstyring.c	LATCH_2_TRIS = 0x0; 			// output
	BCF	_TRISAbits, 7
;	.line	357; pillefyrsstyring.c	LATCH_2 = LATCH_2_DISABLED;
	BCF	_LATAbits, 7
	BANKSEL	__latch_2_data
;	.line	358; pillefyrsstyring.c	_latch_2_data = 0x00;
	CLRF	__latch_2_data, B
;	.line	360; pillefyrsstyring.c	LATCH_3_TRIS = 0x0; 			// output
	BCF	_TRISAbits, 6
;	.line	361; pillefyrsstyring.c	LATCH_3 = LATCH_3_DISABLED;
	BCF	_LATAbits, 6
;	.line	363; pillefyrsstyring.c	LATCH_4_TRIS = 0x0; 			// output
	BCF	_TRISCbits, 2
;	.line	364; pillefyrsstyring.c	LATCH_4 = LATCH_4_DISABLED;
	BCF	_LATCbits, 2
;	.line	366; pillefyrsstyring.c	RELAY_TRIS = 0x0;				// output
	BCF	_TRISCbits, 5
;	.line	367; pillefyrsstyring.c	RELAY = 0x0;					// all power outputs off
	BCF	_LATCbits, 5
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__init_timers	code
_init_timers:
;	.line	297; pillefyrsstyring.c	void init_timers() {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
;	.line	299; pillefyrsstyring.c	T0CONbits.TMR0ON = 1;
	BSF	_T0CONbits, 7
;	.line	300; pillefyrsstyring.c	T0CONbits.T0PS0 = 0;
	BCF	_T0CONbits, 0
;	.line	301; pillefyrsstyring.c	T0CONbits.T0PS1 = 0;
	BCF	_T0CONbits, 1
;	.line	302; pillefyrsstyring.c	T0CONbits.T0PS2 = 0;	// prescaler 1:2
	BCF	_T0CONbits, 2
;	.line	303; pillefyrsstyring.c	T0CONbits.T08BIT = 0;   // use timer0 16-bit counter
	BCF	_T0CONbits, 6
;	.line	304; pillefyrsstyring.c	T0CONbits.T0CS = 0;             // internal clock source
	BCF	_T0CONbits, 5
;	.line	305; pillefyrsstyring.c	T0CONbits.PSA = 0;              // enable timer0 prescaler
	BCF	_T0CONbits, 3
;	.line	306; pillefyrsstyring.c	INTCON2bits.TMR0IP = 1; // high priority
	BSF	_INTCON2bits, 2
;	.line	307; pillefyrsstyring.c	INTCONbits.T0IE = 1;    // Ensure that TMR0 Interrupt is enabled
	BSF	_INTCONbits, 5
;	.line	308; pillefyrsstyring.c	INTCONbits.TMR0IF = 1;  // Force Instant entry to Timer 0 Interrupt
	BSF	_INTCONbits, 2
;	.line	311; pillefyrsstyring.c	T1CONbits.TMR1ON = 1;
	BSF	_T1CONbits, 0
;	.line	312; pillefyrsstyring.c	T1CONbits.RD16 = 1;
	BSF	_T1CONbits, 7
;	.line	313; pillefyrsstyring.c	T1CONbits.TMR1CS = 0;   // internal clock source
	BCF	_T1CONbits, 1
;	.line	314; pillefyrsstyring.c	T1CONbits.T1OSCEN = 0;  // dont put t1 on pin
	BCF	_T1CONbits, 3
;	.line	315; pillefyrsstyring.c	T1CONbits.T1CKPS0 = 1;
	BSF	_T1CONbits, 4
;	.line	316; pillefyrsstyring.c	T1CONbits.T1CKPS1 = 1;
	BSF	_T1CONbits, 5
;	.line	317; pillefyrsstyring.c	IPR1bits.TMR1IP = 0;	// low priority
	BCF	_IPR1bits, 0
;	.line	318; pillefyrsstyring.c	PIE1bits.TMR1IE = 1;	// Ensure that TMR1 Interrupt is enabled
	BSF	_PIE1bits, 0
;	.line	319; pillefyrsstyring.c	PIR1bits.TMR1IF = 1;	// Force Instant entry to Timer 1 Interrupt
	BSF	_PIR1bits, 0
;	.line	347; pillefyrsstyring.c	INTCONbits.PEIE = 1;
	BSF	_INTCONbits, 6
;	.line	348; pillefyrsstyring.c	INTCONbits.GIE = 1;	/* Enable Global interrupts   */	
	BSF	_INTCONbits, 7
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pillefyrsstyring__sleep_ms	code
_sleep_ms:
;	.line	287; pillefyrsstyring.c	void sleep_ms(unsigned long ms) {
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
;	.line	289; pillefyrsstyring.c	start_timer_1_ms = timer_1_ms;	
	MOVFF	_timer_1_ms, r0x04
	MOVFF	(_timer_1_ms + 1), r0x05
	MOVFF	(_timer_1_ms + 2), r0x06
	MOVFF	(_timer_1_ms + 3), r0x07
_00278_DS_:
;	.line	292; pillefyrsstyring.c	while ( (((signed long)(timer_1_ms - start_timer_1_ms) < 0) ? (-1 * (timer_1_ms - start_timer_1_ms)) : (timer_1_ms - start_timer_1_ms)) < ms) {
	MOVF	r0x04, W
	BANKSEL	_timer_1_ms
	SUBWF	_timer_1_ms, W, B
	MOVWF	r0x08
	MOVF	r0x05, W
	BANKSEL	(_timer_1_ms + 1)
	SUBWFB	(_timer_1_ms + 1), W, B
	MOVWF	r0x09
	MOVF	r0x06, W
	BANKSEL	(_timer_1_ms + 2)
	SUBWFB	(_timer_1_ms + 2), W, B
	MOVWF	r0x0a
	MOVF	r0x07, W
	BANKSEL	(_timer_1_ms + 3)
	SUBWFB	(_timer_1_ms + 3), W, B
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
	BNC	_00283_DS_
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
	BRA	_00284_DS_
_00283_DS_:
	MOVFF	r0x08, r0x0c
	MOVFF	r0x09, r0x0d
	MOVFF	r0x0a, r0x0e
	MOVFF	r0x0b, r0x0f
_00284_DS_:
	MOVF	r0x03, W
	SUBWF	r0x0f, W
	BNZ	_00291_DS_
	MOVF	r0x02, W
	SUBWF	r0x0e, W
	BNZ	_00291_DS_
	MOVF	r0x01, W
	SUBWF	r0x0d, W
	BNZ	_00291_DS_
	MOVF	r0x00, W
	SUBWF	r0x0c, W
_00291_DS_:
	BTFSS	STATUS, 0
	BRA	_00278_DS_
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
S_pillefyrsstyring__isr_low_prio	code
_isr_low_prio:
;	.line	261; pillefyrsstyring.c	static void isr_low_prio(void) __interrupt 2 {
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
;	.line	263; pillefyrsstyring.c	if (PIR1bits.TMR1IF) {
	BTFSS	_PIR1bits, 0
	BRA	_00262_DS_
;	.line	264; pillefyrsstyring.c	TMR1H = (unsigned char)(TIMER1_RELOAD >> 8);    // 1 ms delay at 8 MHz
	MOVLW	0xfe
	MOVWF	_TMR1H
;	.line	265; pillefyrsstyring.c	TMR1L = (unsigned char)TIMER1_RELOAD;
	MOVLW	0xc8
	MOVWF	_TMR1L
;	.line	266; pillefyrsstyring.c	PIR1bits.TMR1IF = 0;    /* Clear the Timer Flag  */
	BCF	_PIR1bits, 0
	BANKSEL	_timer_1_ms
;	.line	267; pillefyrsstyring.c	timer_1_ms++;
	INCF	_timer_1_ms, F, B
	BNC	_00262_DS_
	BANKSEL	(_timer_1_ms + 1)
	INCF	(_timer_1_ms + 1), F, B
	BNC	_00262_DS_
	BANKSEL	(_timer_1_ms + 2)
	INCFSZ	(_timer_1_ms + 2), F, B
	BRA	_30394_DS_
	BANKSEL	(_timer_1_ms + 3)
	INCF	(_timer_1_ms + 3), F, B
_30394_DS_:
_00273_DS_:
_00262_DS_:
;	.line	271; pillefyrsstyring.c	if (usart_drdy()) {
	CALL	_usart_drdy
	MOVWF	r0x00
	MOVF	r0x00, W
	BZ	_00265_DS_
;	.line	273; pillefyrsstyring.c	c = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x00
;	.line	274; pillefyrsstyring.c	fifo_put(c);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_fifo_put
	MOVF	POSTINC1, F
;	.line	275; pillefyrsstyring.c	usart_putc(c);
	MOVF	r0x00, W
	CALL	_usart_putc
_00265_DS_:
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

; ; Starting pCode block
S_pillefyrsstyring__isr_high_prio	code
_isr_high_prio:
;	.line	227; pillefyrsstyring.c	static void isr_high_prio(void) __interrupt 1 {
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
	MOVFF	r0x01, POSTDEC1
;	.line	228; pillefyrsstyring.c	if (INTCONbits.TMR0IF) {
	BTFSS	_INTCONbits, 2
	BRA	_00237_DS_
;	.line	229; pillefyrsstyring.c	TMR0H = (unsigned char)(TIMER0_RELOAD >> 8);
	MOVLW	0xfd
	MOVWF	_TMR0H
;	.line	230; pillefyrsstyring.c	TMR0L = (unsigned char)TIMER0_RELOAD;   /* Reload the Timer ASAP */
	CLRF	_TMR0L
;	.line	231; pillefyrsstyring.c	INTCONbits.TMR0IF = 0;  /* Clear the Timer Flag  */
	BCF	_INTCONbits, 2
;	.line	234; pillefyrsstyring.c	sensor_inputs = get_inputs();
	CALL	_get_inputs
	BANKSEL	_sensor_inputs
	MOVWF	_sensor_inputs, B
	BANKSEL	_i
;	.line	237; pillefyrsstyring.c	for (i = 0; i < AC_POWER_OUTS; i++) {
	CLRF	_i, B
	BANKSEL	(_i + 1)
	CLRF	(_i + 1), B
_00235_DS_:
;	.line	238; pillefyrsstyring.c	if (ac_power_pwm_counter < output_ac_power_pwm[i]) {
	MOVLW	LOW(_output_ac_power_pwm)
	BANKSEL	_i
	ADDWF	_i, W, B
	MOVWF	r0x00
	MOVLW	HIGH(_output_ac_power_pwm)
	BANKSEL	(_i + 1)
	ADDWFC	(_i + 1), W, B
	MOVWF	r0x01
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, FSR0H
	MOVFF	INDF0, r0x00
	MOVF	r0x00, W
	BANKSEL	_ac_power_pwm_counter
	SUBWF	_ac_power_pwm_counter, W, B
	BC	_00230_DS_
;	.line	240; pillefyrsstyring.c	set_ac_power(1 << i, 0xff);
	MOVLW	0x01
	MOVWF	r0x00
	CLRF	r0x01
	BANKSEL	_i
	MOVF	_i, W, B
	BZ	_00252_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00253_DS_:
	RLCF	r0x00, F
	RLCF	r0x01, F
	ADDLW	0x01
	BNC	_00253_DS_
_00252_DS_:
	MOVLW	0xff
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_set_ac_power
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
	BRA	_00236_DS_
_00230_DS_:
;	.line	249; pillefyrsstyring.c	set_ac_power(1 << i, 0x00);
	MOVLW	0x01
	MOVWF	r0x00
	CLRF	r0x01
	BANKSEL	_i
	MOVF	_i, W, B
	BZ	_00254_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00255_DS_:
	RLCF	r0x00, F
	RLCF	r0x01, F
	ADDLW	0x01
	BNC	_00255_DS_
_00254_DS_:
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_set_ac_power
	MOVF	POSTINC1, F
	MOVF	POSTINC1, F
_00236_DS_:
	BANKSEL	_i
;	.line	237; pillefyrsstyring.c	for (i = 0; i < AC_POWER_OUTS; i++) {
	INCFSZ	_i, F, B
	BRA	_40395_DS_
	BANKSEL	(_i + 1)
	INCF	(_i + 1), F, B
_40395_DS_:
	MOVLW	0x00
	BANKSEL	(_i + 1)
	SUBWF	(_i + 1), W, B
	BNZ	_00256_DS_
	MOVLW	0x06
	BANKSEL	_i
	SUBWF	_i, W, B
_00256_DS_:
	BTFSS	STATUS, 0
	BRA	_00235_DS_
	BANKSEL	_ac_power_pwm_counter
;	.line	257; pillefyrsstyring.c	ac_power_pwm_counter++;
	INCF	_ac_power_pwm_counter, F, B
_00237_DS_:
	MOVFF	PREINC1, r0x01
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

; ; Starting pCode block
__str_0:
	DB	0x4f, 0x70, 0x65, 0x6e, 0x53, 0x74, 0x6f, 0x6b, 0x65, 0x72, 0x20, 0x73
	DB	0x74, 0x61, 0x72, 0x74, 0x69, 0x6e, 0x67, 0x2e, 0x2e, 0x2e, 0x20, 0x73
	DB	0x65, 0x72, 0x69, 0x61, 0x6c, 0x20, 0x77, 0x6f, 0x72, 0x6b, 0x69, 0x6e
	DB	0x67, 0x0a, 0x0d, 0x00
; ; Starting pCode block
__str_1:
	DB	0x0a, 0x0d, 0x00
; ; Starting pCode block
__str_2:
	DB	0x67, 0x25, 0x30, 0x32, 0x78, 0x0a, 0x0d, 0x00
; ; Starting pCode block
__str_3:
	DB	0x61, 0x64, 0x25, 0x64, 0x3a, 0x20, 0x25, 0x30, 0x34, 0x78, 0x0a, 0x0d
	DB	0x00


; Statistics:
; code size:	 3378 (0x0d32) bytes ( 2.58%)
;           	 1689 (0x0699) words
; udata size:	  202 (0x00ca) bytes ( 5.26%)
; access size:	   16 (0x0010) bytes


	end
