#define TIMER2_RELOAD	0x18	// 1 ms @ 4MHz
#define TIMER3_RELOAD	0x0000	// ~ 131 ms @ 4MHz

// outputs
#define EXT_FEEDER_L1		PORTBbits.RB0    // Ekstern snegl
#define EXT_FEEDER_L1_TRIS	TRISBbits.TRISB0

#define FAN_L2				PORTBbits.RB1    // Blæser
#define FAN_L2_TRIS			TRISBbits.TRISB1

#define INT_FEEDER_L3		PORTBbits.RB2    // Intern snegl
#define INT_FEEDER_L3_TRIS	TRISBbits.TRISB2

#define HEATER_T3_L4		PORTBbits.RB3    // Eltænder via T3
#define HEATER_T3_L4_TRIS	TRISBbits.TRISB3

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

#define clrwdt() __asm clrwdt __endasm

void sleep_ms(unsigned long ms);
void my_usart_open();
unsigned char read_EEPROM(unsigned char address);
void write_EEPROM(unsigned char address, unsigned char d);
