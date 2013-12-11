		/************************************************************/
		/*															*/
		/*			       Header file for Events.c					*/
		/*															*/
		/************************************************************/


/* ------------------------------------------------------------------------ */
/*							   Public constants				   				*/
/* ------------------------------------------------------------------------ */

//
// IO bit definitions for the buttons
//
#define PUSH_BUTTON_UP PORTBbits.RB0
#define PUSH_BUTTON_UP_TRIS TRISBbits.TRISB0

#define PUSH_BUTTON_DOWN PORTBbits.RB1
#define PUSH_BUTTON_DOWN_TRIS TRISBbits.TRISB1

#define PUSH_BUTTON_LEFT PORTBbits.RB2
#define PUSH_BUTTON_LEFT_TRIS TRISBbits.TRISB2

#define PUSH_BUTTON_RIGHT PORTBbits.RB3
#define PUSH_BUTTON_RIGHT_TRIS TRISBbits.TRISB3


//
// SPI bit assignments for the 18F2620 and 18F2523
//
#define SPI_SDO LATCbits.LATC5
#define SPI_SCK LATCbits.LATC3
#define SPI_SDO_TRIS TRISCbits.TRISC5
#define SPI_SDI_TRIS TRISCbits.TRISC4
#define SPI_SCK_TRIS TRISCbits.TRISC3


//
// io pin assignments that connect to the LCD display
//
#define LCD_CS LATCbits.LATC1
#define LCD_CS_TRIS TRISCbits.TRISC1
#define LCD_RESET LATCbits.LATC0
#define LCD_RESET_TRIS TRISCbits.TRISC0


//
// test bit
//
#define TEST_BIT LATCbits.LATC7
#define TEST_BIT_TRIS TRISCbits.TRISC7


//
// types of button events
//
#define BUTTON_PUSHED 	0x01
#define BUTTON_RELEASED 0x02
#define BUTTON_REPEAT 	0x03


//
// event types
//
#define EVENT_NONE 					0

#define EVENT_LEFT_BUTTON_BASE		0x00
#define EVENT_LEFT_BUTTON_PUSHED	(EVENT_LEFT_BUTTON_BASE + BUTTON_PUSHED)
#define EVENT_LEFT_BUTTON_RELEASED	(EVENT_LEFT_BUTTON_BASE + BUTTON_RELEASED)
#define EVENT_LEFT_BUTTON_REPEAT	(EVENT_LEFT_BUTTON_BASE + BUTTON_REPEAT)

#define EVENT_RIGHT_BUTTON_BASE		0x04
#define EVENT_RIGHT_BUTTON_PUSHED	(EVENT_RIGHT_BUTTON_BASE + BUTTON_PUSHED)
#define EVENT_RIGHT_BUTTON_RELEASED	(EVENT_RIGHT_BUTTON_BASE + BUTTON_RELEASED)
#define EVENT_RIGHT_BUTTON_REPEAT	(EVENT_RIGHT_BUTTON_BASE + BUTTON_REPEAT)

#define EVENT_UP_BUTTON_BASE		0x08
#define EVENT_UP_BUTTON_PUSHED		(EVENT_UP_BUTTON_BASE + BUTTON_PUSHED)
#define EVENT_UP_BUTTON_RELEASED	(EVENT_UP_BUTTON_BASE + BUTTON_RELEASED)
#define EVENT_UP_BUTTON_REPEAT		(EVENT_UP_BUTTON_BASE + BUTTON_REPEAT)

#define EVENT_DOWN_BUTTON_BASE		0x0C
#define EVENT_DOWN_BUTTON_PUSHED	(EVENT_DOWN_BUTTON_BASE + BUTTON_PUSHED)
#define EVENT_DOWN_BUTTON_RELEASED	(EVENT_DOWN_BUTTON_BASE + BUTTON_RELEASED)
#define EVENT_DOWN_BUTTON_REPEAT	(EVENT_DOWN_BUTTON_BASE + BUTTON_REPEAT)



/* ------------------------------------------------------------------------ */
/*						  Public function declarations			  			*/
/* ------------------------------------------------------------------------ */

void HardwareIOInitialize(void);
byte GetButtonsEvents(void);
void WriteToEEPROM(byte, byte);
byte ReadFromEEPROM(byte);
void WriteConfigurationByte(byte, byte);
byte ReadConfigurationByte(byte, byte);
void ResetConfigurationByte(byte);

/* --------------------------- End of HardwareIO.h ------------------------ */
