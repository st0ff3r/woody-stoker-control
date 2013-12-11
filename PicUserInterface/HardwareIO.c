		/************************************************************/
		/*															*/
		/*    Functions that interface directly with the hardware	*/
		/*															*/
		/************************************************************/


#include <p18cxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NumericTypedefs.h"
#include "HardwareIO.h"
#include "GeneralFuncs.h"
#include "LCDDriver.h"


/* ------------------------------------------------------------------------ */
/*					   Private constants and datatypes		   				*/
/* ------------------------------------------------------------------------ */

//
// structure for storing the state of a push button
//
typedef struct _BUTTON_STATE
{	byte State;
	unsigned int EventStartTime;
} BUTTON_STATE;



//
// indexes into ButtonState
//
#define LEFT_BUTTON_IDX		0
#define RIGHT_BUTTON_IDX	1
#define UP_BUTTON_IDX 		2
#define DOWN_BUTTON_IDX 	3
#define LAST_BUTTON_IDX 	3



//
// values for State in ButtonState
//
#define WAITING_FOR_BUTTON_DOWN 				0
#define DEBOUNCE_AFTER_BUTTON_DOWN				1
#define WAITING_FOR_BUTTON_UP	 				2
#define WAITING_FOR_BUTTON_UP_AFTER_AUTO_REPEAT	3
#define DEBOUNCE_AFTER_BUTTON_UP				4



//
// timer values for dealing with buttons
//
// 5 * 25.6us * 256 = ~38ms
#define BUTTON_DEBOUNCE_PERIOD 5			

// 120 * 25.6us * 256 = ~786ms
#define BUTTON_AUTO_REPEAT_DELAY 120	

// 20 * 25.6us * 256 = ~131ms		
#define BUTTON_AUTO_REPEAT_RATE 20	



/* ------------------------------------------------------------------------ */
/*             	    Private variables local to this module					*/
/* ------------------------------------------------------------------------ */
#pragma udata

static BUTTON_STATE ButtonState[LAST_BUTTON_IDX + 1];


/* ------------------------------------------------------------------------ */
/*						  Local function declarations  	 					*/
/* ------------------------------------------------------------------------ */

static byte CheckButton(byte);



/* ------------------------------------------------------------------------ */
/*						  	 	Public functions 			 				*/
/* ------------------------------------------------------------------------ */
#pragma code


//
// initialize this module
//
void HardwareIOInitialize(void)
{	//
	// configure port A analog / digitial IO bits
	//
    ADCON1 |= 0x0A;                 			// the number of analog inputs (CHECK THIS)
	
			
	//
	// configure the IO bits that connect to the buttons
	//
	PUSH_BUTTON_UP_TRIS = 1;
	PUSH_BUTTON_DOWN_TRIS = 1;
	PUSH_BUTTON_LEFT_TRIS = 1;
	PUSH_BUTTON_RIGHT_TRIS = 1;
	

	//
	// configure timer 0: 16 bits, 256 prescaler, timer clock input rate =
	// 40Mhz / 4 / 256 = 25.6us
	//
	TMR0H = 0;                					// initialize counter to 0
	TMR0L = 0;
	INTCONbits.INT0IE = 0;						// disable the timer's interrupt
	T0CON = 0b10000111;							// prescaler = 256 & start timer


	//
	// output bit used for testing
	//	
	TEST_BIT_TRIS = 0;
	TEST_BIT = 0;


	//
	// initialize the state variables used for each button
	//
	ButtonState[LEFT_BUTTON_IDX].State = WAITING_FOR_BUTTON_DOWN;
	ButtonState[RIGHT_BUTTON_IDX].State = WAITING_FOR_BUTTON_DOWN;
	ButtonState[UP_BUTTON_IDX].State = WAITING_FOR_BUTTON_DOWN;
	ButtonState[DOWN_BUTTON_IDX].State = WAITING_FOR_BUTTON_DOWN;
}


/* ------------------------------------------------------------------------ */
/*						  	  Button event functions 		 				*/
/* ------------------------------------------------------------------------ */

//
// Event funtions poll the microcontroller's IO devices, then generates events 
// to inform the application of changes.  Typical events are button pushes and 
// advances of a real time clock.

//
// check for events from the buttons
//		Exit:	event value returned if one has occured
//				EVENT_NONE returned if there has been no event
//
byte GetButtonsEvents(void)
{	byte Event;
	
	//
	// check each of the 4 buttons for an event
	//
	Event = CheckButton(LEFT_BUTTON_IDX);
	if (Event != EVENT_NONE) 
		return(Event);
	
	Event = CheckButton(RIGHT_BUTTON_IDX);
	if (Event != EVENT_NONE) 
		return(Event);
	
	Event = CheckButton(UP_BUTTON_IDX);
	if (Event != EVENT_NONE) 
		return(Event);
	
	Event = CheckButton(DOWN_BUTTON_IDX);
	if (Event != EVENT_NONE) 
		return(Event);
	
	return(EVENT_NONE);
}



//
// check for an event from a push button
//		Enter:	ButtonIdx = index of which button to test
//		Exit:	event value returned, EVENT_NONE returned if no event
//
static byte CheckButton(byte ButtonIdx)
{	byte ButtonValue;
	byte TimerVal;
	byte EventBase;
	byte TimerHighByte;
	unsigned int CurrentTime;


	//
	// read the IO bit attached to the selected button 
	//
	switch(ButtonIdx)
	{	case LEFT_BUTTON_IDX:
			ButtonValue = PUSH_BUTTON_LEFT;
			EventBase = EVENT_LEFT_BUTTON_BASE;
			break;
			
		case RIGHT_BUTTON_IDX:
			ButtonValue = PUSH_BUTTON_RIGHT;
			EventBase = EVENT_RIGHT_BUTTON_BASE;
			break;
			
		case UP_BUTTON_IDX:
			ButtonValue = PUSH_BUTTON_UP;
			EventBase = EVENT_UP_BUTTON_BASE;
			break;
			
		case DOWN_BUTTON_IDX:
			ButtonValue = PUSH_BUTTON_DOWN;
			EventBase = EVENT_DOWN_BUTTON_BASE;
			break;	
	}


	//
	// check if nothing is going on (waiting for button to go down and it's not pressed)
	//
	if ((ButtonState[ButtonIdx].State == WAITING_FOR_BUTTON_DOWN) && (ButtonValue != 0))
		return(EVENT_NONE);							// return no new event

	//
	// something is going on, read the time
	//
	TimerVal = TMR0L;
	TimerHighByte = TMR0H;
	CurrentTime = TimerHighByte;		
	if (CurrentTime < ButtonState[ButtonIdx].EventStartTime) 
		CurrentTime += 256;

	//
	// check the state that the button was in last
	//
	switch(ButtonState[ButtonIdx].State)
	{	case WAITING_FOR_BUTTON_DOWN:			// waiting for button to go down
			if (ButtonValue == 0)				// check if button is now down
			{									// button down, start timer
				ButtonState[ButtonIdx].EventStartTime = TimerHighByte;
				ButtonState[ButtonIdx].State = DEBOUNCE_AFTER_BUTTON_DOWN;
				return(EventBase + BUTTON_PUSHED); // return button "pressed" event
			}
			break;
			
		case DEBOUNCE_AFTER_BUTTON_DOWN:		// waiting for timer after button has gone down
												// check if it has been up long enough
			if (CurrentTime >= ((unsigned int) ButtonState[ButtonIdx].EventStartTime + BUTTON_DEBOUNCE_PERIOD))
			{									// debouncing period over, start auto repeat timer
				ButtonState[ButtonIdx].EventStartTime = TimerHighByte;
				ButtonState[ButtonIdx].State = WAITING_FOR_BUTTON_UP;
			}
			break;
				
		case WAITING_FOR_BUTTON_UP:				// waiting for button to go back up
			if (ButtonValue != 0)				// check if button is now up
			{									// button up, start debounce timer
				ButtonState[ButtonIdx].EventStartTime = TimerHighByte;
				ButtonState[ButtonIdx].State = DEBOUNCE_AFTER_BUTTON_UP;
				return(EventBase + BUTTON_RELEASED); // return button "released" event
			}
												// button still down, check if time to auto repeat
			if (CurrentTime >= ((unsigned int) ButtonState[ButtonIdx].EventStartTime + BUTTON_AUTO_REPEAT_DELAY))
			{									// reset auto repeat timer
				ButtonState[ButtonIdx].EventStartTime = TimerHighByte;
				ButtonState[ButtonIdx].State = WAITING_FOR_BUTTON_UP_AFTER_AUTO_REPEAT;
				return(EventBase + BUTTON_REPEAT); // return button "auto repeat" event
			}
			break;
				
		case WAITING_FOR_BUTTON_UP_AFTER_AUTO_REPEAT:// waiting for button to go back up
			if (ButtonValue != 0)				// check if button is now up
			{									// button up, start debounce timer
				ButtonState[ButtonIdx].EventStartTime = TimerHighByte;
				ButtonState[ButtonIdx].State = DEBOUNCE_AFTER_BUTTON_UP;
				return(EventBase + BUTTON_RELEASED); // return button "down" event
			}
												// button still down, check if time to auto repeat
			if (CurrentTime >= ((unsigned int) ButtonState[ButtonIdx].EventStartTime + BUTTON_AUTO_REPEAT_RATE))
			{									// reset auto repeat timer
				ButtonState[ButtonIdx].EventStartTime = TimerHighByte;
				return(EventBase + BUTTON_REPEAT); // return button "auto repeat" event
			}
			break;
					
		case DEBOUNCE_AFTER_BUTTON_UP:			// waiting for timer after button has gone up
			if (CurrentTime >= ((unsigned int) ButtonState[ButtonIdx].EventStartTime + BUTTON_DEBOUNCE_PERIOD))
				ButtonState[ButtonIdx].State = WAITING_FOR_BUTTON_DOWN;
			break;
	}

	return(EVENT_NONE);								// return no new event
}



/* ------------------------------------------------------------------------ */
/*						  	  EEPROM read/write functions 	 				*/
/* ------------------------------------------------------------------------ */

//
// write a configuration byte
//
void WriteConfigurationByte(byte EEPromAddress, byte Value)
{	if (ReadFromEEPROM(EEPromAddress) == 0xff)
		WriteToEEPROM(EEPromAddress, 0);
	
	WriteToEEPROM(EEPromAddress + 1, Value);
}



//
// read a configuration byte
//
byte ReadConfigurationByte(byte EEPromAddress, byte DefaultValue)
{	if (ReadFromEEPROM(EEPromAddress) == 0xff)
		return(DefaultValue);
	
	return(ReadFromEEPROM(EEPromAddress + 1));
}



//
// reset a configuration byte
//
void ResetConfigurationByte(byte EEPromAddress)
{	WriteToEEPROM(EEPromAddress, 0xFF);
}



//
// write a byte to the EEPROM
// Note: writing the first byte to EEPROM takes about 3.7us, writing the next byte while
// the EEPROM is still busy from the last write takes about 3ms
//		Enter:	Address = EEPROM address location (0 - 255) 
//				  Note: Some PIC18F chips support more or less than 256 bytes of EEPROM
//				  The PIC18F2620 has 1024 bytes of EEPROM
//				Data = data byte to write
//
void WriteToEEPROM(byte Address, byte Data)
{
	//
	// wait if the EEPROM is busy from a previous write
	//
	while(EECON1bits.WR)
		;

	//
	// write the high and low byte of the address, then write the data value
	//
	EEADRH = 0;
	EEADR = Address;
  	EEDATA = Data;
  	
	//
	// execute the write to EEPROM sequence
	//
  	EECON1bits.EEPGD = 0;						// point to data memory
	EECON1bits.CFGS = 0;						// access EEPROM
	EECON1bits.WREN = 1;						// enable writes to the EEPROM
	INTCONbits.GIE = 0;							// disable interrupts
	EECON2 = 0x55;								// begin the write sequence
	EECON2 = 0xAA;
	EECON1bits.WR = 1;							// begin the write
	EECON1bits.WREN = 0;						// disable writes to the EEPROM on complete
	INTCONbits.GIE = 1;							// re-enable interrups
}



//
// read a byte from the EEPROM
//		Enter:	Address = EEPROM address location (0 - 255) 
//				  Note: Some PIC18F chips support more or less than 256 bytes of EEPROM
//				  The PIC18F2620 has 1024 bytes of EEPROM
//		Exit:	byte returned
//
byte ReadFromEEPROM(byte Address)
{	//
	// wait if the EEPROM is busy from a previous write
	//
	while(EECON1bits.WR)
		;

	//
	// write the high and low byte of the address
	//
	EEADRH = 0;
	EEADR = Address;
	
	//
	// execute the read to EEPROM sequence
	//
  	EECON1bits.CFGS = 0;						// access EEPROM
	EECON1bits.EEPGD = 0;						// point to data memory
	EECON1bits.RD = 1;							// begin the read
	return(EEDATA);              				// return the byte read
}


/* --------------------------- End of HardwareIO.c ------------------------ */
