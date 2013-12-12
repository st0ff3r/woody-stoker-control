#define TIMER2_RELOAD	0x18	// 1 ms @ 4MHz
#define TIMER3_RELOAD	0x0000	// ~ 131 ms @ 4MHz

// outputs
#define LATCH_DATA			LATD
#define LATCH_DATA_READ		PORTD
#define LATCH_DATA_TRIS		TRISD

#define LATCH_1				LATAbits.LATA4
#define LATCH_1_TRIS		TRISAbits.TRISA4
#define LATCH_1_ENABLED		0x0	// inverted
#define LATCH_1_DISABLED	0x1	// inverted

#define LATCH_2				LATAbits.LATA7
#define LATCH_2_TRIS		TRISAbits.TRISA7
#define LATCH_2_ENABLED		0x1
#define LATCH_2_DISABLED	0x0

#define LATCH_3				LATAbits.LATA6
#define LATCH_3_TRIS		TRISAbits.TRISA6
#define LATCH_3_ENABLED		0x1
#define LATCH_3_DISABLED	0x0

#define LATCH_4				LATCbits.LATC2
#define LATCH_4_TRIS		TRISCbits.TRISC2
#define LATCH_4_ENABLED		0x1
#define LATCH_4_DISABLED	0x0

#define RELAY				LATCbits.LATC5    // Relæ
#define RELAY_TRIS			TRISCbits.TRISC5


#define EXT_FEEDER_L1		0b00000001		// Ekstern snegl
#define FAN_L2				0b00000010		// Blæser
#define INT_FEEDER_L3		0b00000100		// Intern snegl
#define HEATER_L4			0b00001000		// Eltænder via T3
#define L5					0b00010000
#define L6					0b00100000




// check it...
//#define EXT_CONTACT		PORTCbits.RC3
//#define EXT_CONTACT_TRIS	TRISCbits.TRISC3

//#define EXT_CONTACT		PORTCbits.RC4
//#define EXT_CONTACT_TRIS	TRISCbits.TRISC4

// inputs
#define EXT_CONTACT		PORTCbits.RC3
#define EXT_CONTACT_TRIS	TRISCbits.TRISC3

#define B_UP			PORTBbits.RB5
#define B_UP_TRIS		TRISBbits.TRISB5

#define B_MENU			PORTBbits.RB6
#define B_MENU_TRIS		TRISBbits.TRISB6

#define B_DOWN			PORTBbits.RB7
#define B_DOWN_TRIS		TRISBbits.TRISB7

// ad inputs
#define LAMBDA_TL082_TRIS	PORTAbits.RA0
#define ALL_TEMP_NUL_TRIS         PORTAbits.RA1
#define ALL_TEMP_NUL_1KOHM_TRIS   PORTAbits.RA2   // 1Kohm modstand
#define BOILER_TEMP_TRIS	PORTAbits.RA3
#define SMOKE_TEMP_TRIS		PORTAbits.RA4
#define CHIMNEY_TEMP_TRIS	PORTAbits.RA5

#define PHOTO_SENSOR_TRIS	PORTBbits.RB4

//#define clrwdt() __asm clrwdt __endasm

void sleep_ms(unsigned long ms);
void init_timers();
void init_latches();

void set_ac_power(unsigned char header_mask, unsigned char value);
unsigned char get_inputs();
void my_usart_open();
void _debug();
