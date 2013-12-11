		/************************************************************/
		/*															*/
		/*  Demonstration program of a user interface for a PIC18F 	*/
		/*		microcontroller with a Nokia 6100 LCD display		*/
		/*															*/
		/************************************************************/

#include <p18cxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NumericTypedefs.h"
#include "Fonts.h"
#include "Images.h"
#include "HardwareIO.h"
#include "GeneralFuncs.h"
#include "LCDDriver.h"
#include "UserInterface.h"
#include "HardwareIO.h"


/* ------------------------------------------------------------------------ */
/*					  Hardware configuration bit settings	   				*/
/* ------------------------------------------------------------------------ */

//
// configuration settings for the PIC18F2620 (values documented in MPLAB_C18_Config_Settings.pdf)
//
#pragma config OSC = HSPLL			// oscillator selection: HS oscillator, PLL enabled
#pragma config FCMEN = OFF			// fail-safe clock monitor: disabled
#pragma config IESO = OFF			// internal/external switch over: disabled
#pragma config PWRT = OFF			// power up timer: disabled
#pragma config BOREN = OFF			// brown-out reset:disabled
#pragma config WDT = OFF			// watchdog timer: HW disabled / SW controlled
#pragma config WDTPS = 32768		// Watchdog Postscaler: 1:32768
#pragma config MCLRE = ON			// MCLR: enabled
#pragma config LPT1OSC = OFF		// low power timer1 oscillator: disabled
#pragma config PBADEN = OFF			// port B A/D: digital IO
#pragma config CCP2MX = PORTBE		// CCP2 Mux: CCP2 multiplexed with RB3
#pragma config STVREN = ON			// stack overflow reset: enabled
#pragma config LVP = OFF			// low voltage ICSP: disabled
#pragma config XINST = OFF			// extended instruction set: disabled
#pragma config DEBUG = ON			// ICD2 debugger:  enable
#pragma config CP0 = OFF			// code protection 0800-1FFF: disabled
#pragma config CP1 = OFF			// code protection 2000-3FFF: disabled
#pragma config CP2 = OFF			// code protection 4000-5FFF: disabled
#pragma config CP3 = OFF			// code protection 6000-7FFF: disabled
#pragma config CPB = OFF			// boot block code protection: disabled
#pragma config CPD = OFF			// data EEPROM code protection: disabled
#pragma config WRT0 = OFF			// table write protection 0800-1FFF: disabled
#pragma config WRT1 = OFF			// table write protection 2000-3FFF: disabled
#pragma config WRT2 = OFF			// table write protection 4000-5FFF: disabled
#pragma config WRT3 = OFF			// table write protection 6000-7FFF: disabled
#pragma config WRTB = OFF			// boot block write protection: disabled
#pragma config WRTC = OFF			// config register write protection: disabled
#pragma config WRTD = OFF			// data EEPROM write protection: disabled
#pragma config EBTR0 = OFF			// table read protection 0800-1FFF: disabled
#pragma config EBTR1 = OFF			// table read protection 2000-3FFF: disabled
#pragma config EBTR2 = OFF			// table read protection 4000-5FFF: disabled
#pragma config EBTR3 = OFF			// table read protection 6000-7FFF: disabled
#pragma config EBTRB = OFF			// boot block table read protection: disabled



/* ------------------------------------------------------------------------ */
/*             	    Private variables local to this module					*/
/* ------------------------------------------------------------------------ */
#pragma udata

static SHORTLONG StartTime;
static byte StopwatchMode;
static byte StopWatchTenthsSeconds;
static byte StopWatchSeconds;
static byte StopWatchMinutes;
static byte StopWatchHours;
static int GetANumber = 0;


/* ------------------------------------------------------------------------ */
/*						  Local function declarations  	 					*/
/* ------------------------------------------------------------------------ */

static void SelectApplication(void);
static void StopWatchDisplayEventHandler(byte);
static void DrawStopwatch(void);
static ram char *TimeDigits(ram char *, byte);
static void ShowAboutCommand(void);
static void ShowAboutCommandCallback(byte);
static void ShowColorBarsCommand();
static void ShowColorBarsCommandEventHandler();
static void DrawColorBars(void);
static void ShowPicturesCommand(void);
static void ShowPicturesCommandEventHandler(byte);
static void ShowGetANumberCommand(void);
static void GetANumberCallback(byte, int);
static void ShowLineDrawingCommand(void);
static void ShowLineDrawingCommandEventHandler(byte);
static void ShowBeingBusyCommand(void);
static SetDigitsSizeCallback(byte);
static SetShowTenthsFlgCallback(byte);
static void SetContrastCommand(void);
static void SetContrastCallback(byte, int);
static void ResetAllSettingsCommand(void);
static void ResetAllSettingCommandCallback(byte);

static void SaveContrastConfigValue(byte);
static byte GetContrastConfigValue(void);
static void ResetContrastConfigValue(void);

static void SaveShowTenthsFlgConfigValue(byte);
static byte GetShowTenthsFlgConfigValue(void);
static void ResetShowTenthsFlgConfigValue(void);

static void SaveDigitsSizeConfigValue(byte);
static byte GetDigitsSizeConfigValue(void);
static void ResetDigitsSizeConfigValue(void);



/* ------------------------------------------------------------------------ */
/*						  Top level of the application 		 				*/
/* ------------------------------------------------------------------------ */
#pragma code

//
// forward declarations of the sub menus
//
MENU_ITEM SettingsMenu[];
MENU_ITEM ShowMoreMenu[];


//
// the main menu
//
MENU_ITEM MainMenu[] = {
	{MENU_ITEM_TYPE_MAIN_MENU_HEADER, "Main menu", SelectApplication},
	{MENU_ITEM_TYPE_SUB_MENU, "Show", ShowMoreMenu},
	{MENU_ITEM_TYPE_SUB_MENU, "Settings", SettingsMenu},
	{MENU_ITEM_TYPE_COMMAND, "About", ShowAboutCommand},
	{MENU_ITEM_TYPE_END_OF_MENU, "", 0}};


//
// the Show sub menu
//
MENU_ITEM ShowMoreMenu[] = {
	{MENU_ITEM_TYPE_SUB_MENU_HEADER, "Show", MainMenu},
	{MENU_ITEM_TYPE_COMMAND, "Color bars", ShowColorBarsCommand},
	{MENU_ITEM_TYPE_COMMAND, "Pictures", ShowPicturesCommand},
	{MENU_ITEM_TYPE_COMMAND, "Get number", ShowGetANumberCommand},
	{MENU_ITEM_TYPE_COMMAND, "Line drawing", ShowLineDrawingCommand},
	{MENU_ITEM_TYPE_COMMAND, "Being busy", ShowBeingBusyCommand},
	{MENU_ITEM_TYPE_END_OF_MENU, "", 0}};


//
// the Settings sub menu
//
MENU_ITEM SettingsMenu[] = {
	{MENU_ITEM_TYPE_SUB_MENU_HEADER, "Stopwatch Settings", MainMenu},
	{MENU_ITEM_TYPE_ALTERNATE, "Digits", SetDigitsSizeCallback},
	{MENU_ITEM_TYPE_ALTERNATE, "Tenths", SetShowTenthsFlgCallback},
	{MENU_ITEM_TYPE_COMMAND, "Set contrast", SetContrastCommand},
	{MENU_ITEM_TYPE_COMMAND, "Reset all settings", ResetAllSettingsCommand},
	{MENU_ITEM_TYPE_END_OF_MENU, "", 0}};


/* ------------------------------------------------------------------------ */


//
// top level procedure and event main loop
//
void main(void)
{	byte Event;
	
	//
	// initialize everything
	//
	HardwareIOInitialize();
    LCDDriverInitialize(LCD_COLOR_MODE_RGB8);  
    
    
    //
    // set the LCD contrast using the config value saved in EEPROM
    //  
    LCDSetContrast(GetContrastConfigValue());


	//
	// setup the main application: the stopwatch
	//
	SelectApplication();
	

	//
	// main loop: check for events, then execute them
	//	
	while(1)
	{	//
		// check for button events (does not wait if an event is not ready)
		//
	 	Event = GetButtonsEvents();	
	
		//
		// execute the event
		//
		UIExecuteEvent(Event);
	}
}



/* ------------------------------------------------------------------------ */
/*			  		   The main application:  A stopwatch					*/
/* ------------------------------------------------------------------------ */

//
// constants used to draw the Stopwatch Display
//
#define STOPWATCH_DISPLAY_CENTER_Y			((UI_DISPLAY_SPACE_TOP_Y + UI_DISPLAY_SPACE_BOTTOM_Y) / 2)
#define STOPWATCH_DISPLAY_FOREGROUND_RGB8	RGB8_BLACK	


//
// modes of the stopwatch
//
#define STOPWATCH_READY		0
#define STOPWATCH_RUNNING	1
#define STOPWATCH_STOPPED	2



//
// Note: the correct value should be 3906.25
//
#define COUNTER_TICKS_PER_TENTH_SECOND 3906


/* ------------------------------------------------------------------------ */


//
// select and display the main application
//
static void SelectApplication(void)
{	//
	// set the title bar label and blank the DisplaySpace
	//
	UIDrawTitleBar("Stop Watch", ROM_STRING);
	UIBlankDisplaySpace();
	
	//
	// initialize the stopwatch
	//
	StopwatchMode = STOPWATCH_READY;
	StopWatchTenthsSeconds = 0;
	StopWatchSeconds = 0;
	StopWatchMinutes = 0;
	StopWatchHours = 0;
	DrawStopwatch();

	
	//
	// set the button bar and the event handler
	//
	UIDrawButtonBar("Start", "Menu");
	UISetEventHandler(StopWatchDisplayEventHandler);
}



//
// event handler for the Stopwatch Display
//		Enter:	Event = type of event
//
static void StopWatchDisplayEventHandler(byte Event)
{	static short long CounterTicksPerSecond;
	static byte AddExtraCounterTickCount;
	SHORTLONG CurrentTime;

	switch(Event)
	{	case EVENT_LEFT_BUTTON_PUSHED:
			//
			// left button pressed, determine the stopwatch's mode
			//
			switch(StopwatchMode)
			{	case STOPWATCH_READY:
					//
					// start the stopwatch
					//
					StartTime.byte0 = TMR0L;
					StartTime.byte1 = TMR0H;
					StartTime.byte2 = 0;
					
					CounterTicksPerSecond = COUNTER_TICKS_PER_TENTH_SECOND;
					AddExtraCounterTickCount = 0;

					StopwatchMode = STOPWATCH_RUNNING;
					UIDrawButtonBar("Stop", "Menu");
					return;

				case STOPWATCH_RUNNING:
					//
					// stop the stopwatch
					//
					DrawStopwatch();
					StopwatchMode = STOPWATCH_STOPPED;
					UIDrawButtonBar("Reset", "Menu");
					return;

				case STOPWATCH_STOPPED:
					//
					// reset the stopwatch
					//
					StopWatchTenthsSeconds = 0;
					StopWatchSeconds = 0;
					StopWatchMinutes = 0;
					StopWatchHours = 0;
					
					StopwatchMode = STOPWATCH_READY;
					DrawStopwatch();
					UIDrawButtonBar("Start", "Menu");
					return;
			}
			return;

		case EVENT_RIGHT_BUTTON_PUSHED:
			UISelectMenuDisplay(MainMenu);
			return;
	}
	
	
	//
	// if the stopwatch is running, check if it is time to advance the stopwatch's time
	//
	if (StopwatchMode == STOPWATCH_RUNNING)
	{	//
		// read the timer
		//
		CurrentTime.byte0 = TMR0L;
		CurrentTime.byte1 = TMR0H;
		CurrentTime.byte2 = 0;
		if (CurrentTime._shortlong < StartTime._shortlong)
			CurrentTime.byte2 = 1;
	
		//
		// return if timer hasn not yet advanced by .1 seconds
		//
		if (CurrentTime._shortlong < StartTime._shortlong + CounterTicksPerSecond)
			return;
	
		//
		// time to advanced the stopwatch, add .1 seconds to the current time
		//
		if (++StopWatchTenthsSeconds == 10)
		{	StopWatchTenthsSeconds = 0;
			if (++StopWatchSeconds == 60)
			{	StopWatchSeconds = 0;
				if (++StopWatchMinutes == 60)
				{	StopWatchMinutes = 0;
					if (++StopWatchHours == 100)
					{	StopWatchHours = 0;
					}
				}
			}
		}
		
		
		//
		// reset start time for the next .1 second period
		//
		StartTime._shortlong += CounterTicksPerSecond;
		StartTime.byte2 = 0;
	
	
		//
		// determine how long to wait for the next .1 seconds, every 4 times add one 
		// extra counter tick because the true value of COUNTER_TICKS_PER_TENTH_SECOND = 3906.25, 
		// not 3906
		//
		AddExtraCounterTickCount++;
		if (AddExtraCounterTickCount == 4)
		{	CounterTicksPerSecond = COUNTER_TICKS_PER_TENTH_SECOND + 1;
			AddExtraCounterTickCount = 0;
		}
		else
			CounterTicksPerSecond = COUNTER_TICKS_PER_TENTH_SECOND;
	
	
		//
		// update the display of the stopwatch's time
		//
		DrawStopwatch();
	}
}



//
// draw the stopwatch time
//
static void DrawStopwatch(void)
{	char SBuf[12];
	ram char *SBufPntr;
	byte X, Y;
	rom byte *Font;
	

	//
	// get the font used to display the stopwatch time
	//
	switch(GetDigitsSizeConfigValue())
	{	case 0:
			Font = Font_Small;
			break;
			
		case 2:
			Font = Font_LargeNumbers;
			break;
			
		default:
			Font = Font_MediumBold;
			break;
	}
	
	
	//
	// determine the center XY coord in the Display Space
	//
	X = (UI_DISPLAY_SPACE_LEFT_X + UI_DISPLAY_SPACE_RIGHT_X) / 2;
	Y = (UI_DISPLAY_SPACE_TOP_Y + UI_DISPLAY_SPACE_BOTTOM_Y) / 2;
	Y += Font[FONT_TABLE_HEIGHT_IDX] / 2;


	//
	// build the string showing the current time
	//
	SBufPntr = SBuf;

	SBufPntr = TimeDigits(SBufPntr, StopWatchHours);
	*SBufPntr++ = ':';

	SBufPntr = TimeDigits(SBufPntr, StopWatchMinutes);
	*SBufPntr++ = ':';

	SBufPntr = TimeDigits(SBufPntr, StopWatchSeconds);


	//
	// if enabled, add the tenths of seconds to the time string
	//
	if (GetShowTenthsFlgConfigValue())
	{	*SBufPntr++ = ':';
		*SBufPntr++ = StopWatchTenthsSeconds + '0';
	}
	
	*SBufPntr++ = 0;
	
	
	//
	// display the time string
	//
	X = LCDDrawStringRGB8(SBuf, RAM_STRING, 
	  X, Y, JUSTIFY_CENTER, Font, 
	  RGB8_BLACK, UI_DISPLAY_SPACE_BACKGROUND_RGB8);
}




//
// convert a number into a two digit string, pad with leading zeros
//
static ram char *TimeDigits(ram char *SBufPntr, byte N)
{	*SBufPntr++ = (N / 10) + '0';
	*SBufPntr++ = (N % 10) + '0';
	*SBufPntr = 0;
	return(SBufPntr);
}



/* ------------------------------------------------------------------------ */
/*			  Main menu command to display the About information			*/
/* ------------------------------------------------------------------------ */

//
// the "About" menu command
//
static void ShowAboutCommand(void)
{	char *S;
	
	S = "This is a demonstration of a graphical user interface for the PIC18F microcontrollers with a Nokia 6100 LCD display.\r\r(c) 2008, S. Reifel & Co.";
	UISelectMessageDisplay("About", S, ROM_STRING, JUSTIFY_CENTER, MESSAGE_DISPLAY_BACK, Font_Small, ShowAboutCommandCallback);

	StopwatchMode = STOPWATCH_READY;
}



//
// callback function for the ShowAboutCommand
//
static void ShowAboutCommandCallback(byte Action)
{	switch(Action)
	{	case MESSAGE_DISPLAY_ACTION_BACK:
			UISelectPreviousMenuDisplay();
			break;
	}
}



/* ------------------------------------------------------------------------ */
/*				 Show menu command to display the color bars				*/
/* ------------------------------------------------------------------------ */

//
// the "Show color bars" menu command
//
static void ShowColorBarsCommand(void)
{	//
	// set the title bar label, blank the DisplaySpace and draw the buttons
	//
	UIDrawTitleBar("Show Color Bars", ROM_STRING);
	UIBlankDisplaySpace();
	UIDrawButtonBar("Back", "");

	//
	// set the event handler
	//
	UISetEventHandler(ShowColorBarsCommandEventHandler);

	//
	// display the colorbars
	//
	DrawColorBars();
}



//
// event handler for the Show colorbars command
//
static void ShowColorBarsCommandEventHandler(byte Event)
{	//
	// determine the type of event
	//
	switch(Event)
	{	case EVENT_LEFT_BUTTON_PUSHED:
		case EVENT_RIGHT_BUTTON_PUSHED:
			UISelectPreviousMenuDisplay();
			break;
	}
}



//
// draw color bars using RGB8 and RGB12 colors
//
static void DrawColorBars(void)
{	byte ColorRGB8;
	word ColorRGB12;
	byte x, x1, y1;


	//
	// set display for RGB8 colors
	//
	LCDSelectColorMode(LCD_COLOR_MODE_RGB8, 0);
	

	// RGB8 blue color band
	y1 = 35;
	for (x = 0; x < 16; x++)
	{	x1 = x * 8;
		ColorRGB8 = x & 0x03;
		LCDDrawFilledRectangleRGB8(x1, y1, x1 + 8, y1 + 8, ColorRGB8);
	}
	y1 += 8;
	
	// RGB8 green color band
	for (x = 0; x < 16; x++)
	{	x1 = x * 8;
		ColorRGB8 = (x << 2) & 0x1C;
		LCDDrawFilledRectangleRGB8(x1, y1, x1 + 8, y1 + 8, ColorRGB8);
	}
	y1 += 8;
	
	// RGB8 red color band
	for (x = 0; x < 16; x++)
	{	x1 = x * 8;
		ColorRGB8 = (x << 5) & 0xE0;
		LCDDrawFilledRectangleRGB8(x1, y1, x1 + 8, y1 + 8, ColorRGB8);
	}
	y1 += 8;
	y1 += 8;



	//
	// set display for RGB12 colors
	//
	LCDSelectColorMode(LCD_COLOR_MODE_RGB12, 0);


	// RGB12 blue color band		
	for (x = 0; x < 16; x++)
	{	x1 = x * 8;
		ColorRGB12 = (word)x;
		LCDDrawFilledRectangleRGB12(x1, y1, x1 + 8, y1 + 8, ColorRGB12);
	}
	y1 += 8;

	// RGB12 green color band		
	for (x = 0; x < 16; x++)
	{	x1 = x * 8;
		ColorRGB12 = (word)x  << 4;
		LCDDrawFilledRectangleRGB12(x1, y1, x1 + 8, y1 + 8, ColorRGB12);
	}
	y1 += 8;

	// RGB12 red color band		
	for (x = 0; x < 16; x++)
	{	x1 = x * 8;
		ColorRGB12 = (word)x << 8;
		LCDDrawFilledRectangleRGB12(x1, y1, x1 + 8, y1 + 8, ColorRGB12);
	}
	y1 += 8;
	y1 += 8;
	
	
	//
	// set display for RGB8 colors
	//
	LCDSelectColorMode(LCD_COLOR_MODE_RGB8, 0);
}



/* ------------------------------------------------------------------------ */
/*					 Show menu command to display pictures					*/
/* ------------------------------------------------------------------------ */

//
// the "Show pictures" menu command
//
static void ShowPicturesCommand(void)
{	byte X, Y;

	//
	// set the title bar label, blank the DisplaySpace and draw the buttons
	//
	UIDrawTitleBar("Show Pictures", ROM_STRING);
	UIBlankDisplaySpace();
	UIDrawButtonBar("Back", "");

	//
	// set the event handler
	//
	UISetEventHandler(ShowPicturesCommandEventHandler);

	//
	// determine the coord so the images is centered
	//
	X = (UI_DISPLAY_SPACE_RIGHT_X - Image_Pei_64[1]) / 2;
	Y = ((UI_DISPLAY_SPACE_TOP_Y + UI_DISPLAY_SPACE_BOTTOM_Y) / 2) - (Image_Pei_64[2] / 2);


	//
	// display the RGB12 image, then switch back to RGB8
	//
	LCDSelectColorMode(LCD_COLOR_MODE_RGB12, 0);
	LCDDrawBitmapRGB12(Image_Pei_64, 33, 33);
	LCDSelectColorMode(LCD_COLOR_MODE_RGB8, 0);
}



//
// event handler for the Show pictures command
//
static void ShowPicturesCommandEventHandler(byte Event)
{	//
	// determine the type of event
	//
	switch(Event)
	{	case EVENT_LEFT_BUTTON_PUSHED:
		case EVENT_RIGHT_BUTTON_PUSHED:
			UISelectPreviousMenuDisplay();
			break;
	}
}



/* ------------------------------------------------------------------------ */
/*					   Show menu command to get a number					*/
/* ------------------------------------------------------------------------ */

//
// the "Get a number" menu command
//
static void ShowGetANumberCommand(void)
{	//
	// select a slider control
	//	
	UISelectSliderDisplay("Get a Number", -500, 500, 1, 10, GetANumber,
	"Descriptions of what this number is used for", 
	TRUE, TRUE, GetANumberCallback);
}



//
// callback function for the get a number slider
//
static void GetANumberCallback(byte Action, int Value)
{	switch(Action)
	{	case SLIDER_DISPLAY_ACTION_VALUE_CHANGED:
			//
			// value changed
			//
			break;

		case SLIDER_DISPLAY_ACTION_VALUE_SET:
			GetANumber = Value;
			
			//
			// reselect the calling menu
			//
			UISelectPreviousMenuDisplay();
			break;

		case SLIDER_DISPLAY_ACTION_CANCELED:
			//
			// reselect the calling menu
			//
			UISelectPreviousMenuDisplay();
			break;
	}
}



/* ------------------------------------------------------------------------ */
/*				  Show menu command of line drawing graphics				*/
/* ------------------------------------------------------------------------ */

//
// the "Show line drawing" menu command
//
static void ShowLineDrawingCommand(void)
{	byte x1, y1, x2, y2, width, height;


	//
	// set the title bar label, blank the DisplaySpace and draw the buttons
	//
	UIDrawTitleBar("Show Line Drawing", ROM_STRING);
	UIBlankDisplaySpace();
	UIDrawButtonBar("Back", "");

	//
	// set the event handler
	//
	UISetEventHandler(ShowLineDrawingCommandEventHandler);

	//
	// draw lines and circules
	//
	LCDSelectColorMode(LCD_COLOR_MODE_RGB8, 0);
 	width = 30;
	height = 50;
	x1 = 25;
	y1 = 40;
	x2 = x1 + width - 1;
	y2 = y1 + height - 1;
	LCDDrawLineRGB8(x1, y1, x2, y1, RGB8_BLACK);
	LCDDrawLineRGB8(x2, y1, x2, y2, RGB8_BLACK);
	LCDDrawLineRGB8(x2, y2, x1, y2, RGB8_BLACK);
	LCDDrawLineRGB8(x1, y2, x1, y1, RGB8_BLACK);
	LCDDrawLineRGB8(x1, y1, x2, y2, RGB8_BLACK);
	LCDDrawLineRGB8(x1, y2, x2, y1, RGB8_BLACK);

	LCDDrawCircleRGB8(x1 + width + 35, y1 + height/2, 15, RGB8_RED);
}



//
// event handler for the Show line drawing command
//
static void ShowLineDrawingCommandEventHandler(byte Event)
{	//
	// determine the type of event
	//
	switch(Event)
	{	case EVENT_LEFT_BUTTON_PUSHED:
		case EVENT_RIGHT_BUTTON_PUSHED:
			UISelectPreviousMenuDisplay();
			break;
	}
}



/* ------------------------------------------------------------------------ */
/*					Show menu Command to display being busy					*/
/* ------------------------------------------------------------------------ */

//
// the "Show being busy" menu command
//
static void ShowBeingBusyCommand(void)
{	byte X, Y;
	
	//
	// set the title bar label, blank the DisplaySpace and draw the buttons
	//
	UIDrawTitleBar("Working...", ROM_STRING);
	UIBlankDisplaySpace();
	UIDrawButtonBar("", "");

	//
	// Don't need to set event handler since this function does not return right away
	//
	//UISetEventHandler(ShowBeingBusyCommandEventHandler);

	//
	// determine the coord so the images is centered
	//
	X = (UI_DISPLAY_SPACE_RIGHT_X - Image_Hourglass[1]) / 2;
	Y = ((UI_DISPLAY_SPACE_TOP_Y + UI_DISPLAY_SPACE_BOTTOM_Y) / 2) - (Image_Hourglass[2] / 2);

	//
	// display an hourglass
	//
	LCDDrawBitmapRGB8(Image_Hourglass, X, Y);
	
	//
	// wait 1 second
	//
	DelayMS(1000);
	
	//
	// return to the calling menu
	//
	UISelectPreviousMenuDisplay();
}



/* ------------------------------------------------------------------------ */
/*	 Settings menu callback function to set size of the stopwatch digits	*/
/* ------------------------------------------------------------------------ */

//
// callback function to set the Digits size, this is driven by an "Alternate" menu item 
//
static SetDigitsSizeCallback(byte Action)
{	byte DigitsSizeValue;
	
	DigitsSizeValue = GetDigitsSizeConfigValue();
	
	switch(Action)
	{	case MENU_ACTION_ALTERNATE_SELECTION:
			DigitsSizeValue++;
			if (DigitsSizeValue > 2)
				DigitsSizeValue = 0;

			SaveDigitsSizeConfigValue(DigitsSizeValue);
			break;
			
		case MENU_ACTION_ALTERNATE_GET_TEXT:
			switch(DigitsSizeValue)
			{	case 0:
					return("Small");
				case 1:
					return("Medium");
				case 2:
					return("Large");
			}
	}
}



/* ------------------------------------------------------------------------ */
/*	 Settings menu callback function to toggle showing tenths of seconds	*/
/* ------------------------------------------------------------------------ */

//
// callback function to enable the display of "Tenths of seconds", this is 
// driven by an "Alternate" menu item 
//
static SetShowTenthsFlgCallback(byte Action)
{	switch(Action)
	{	case MENU_ACTION_ALTERNATE_SELECTION:
			SaveShowTenthsFlgConfigValue(!GetShowTenthsFlgConfigValue());
			break;
			
		case MENU_ACTION_ALTERNATE_GET_TEXT:
			if (GetShowTenthsFlgConfigValue())
				return("Show");
			else
				return("Hide");
	}
}



/* ------------------------------------------------------------------------ */
/*			 Settings menu command to set the LCD contrast level			*/
/* ------------------------------------------------------------------------ */

//
// the "Set contrast" menu command (using a Slider Display)
//
static void SetContrastCommand(void)
{	//
	// select a slider control
	//	
	UISelectSliderDisplay("Settings", 0, 63, 2, 2, GetContrastConfigValue(),
	"Set contrast", 
	FALSE, FALSE, SetContrastCallback);
}



//
// callback function for the Set Contrast slider
//
static void SetContrastCallback(byte Action, int Value)
{	switch(Action)
	{	case SLIDER_DISPLAY_ACTION_VALUE_CHANGED:
			//
			// change the contrast value
			//
			LCDSetContrast(Value);
			break;

		case SLIDER_DISPLAY_ACTION_VALUE_SET:
			//
			// set the contrast value, and save
			//
			LCDSetContrast(Value);
			SaveContrastConfigValue(Value);
			
			//
			// reselect the calling menu
			//
			UISelectPreviousMenuDisplay();
			break;

		case SLIDER_DISPLAY_ACTION_CANCELED:
			//
			// restore originial contrast value
			//
    		LCDSetContrast(GetContrastConfigValue());
			
			//
			// reselect the calling menu
			//
			UISelectPreviousMenuDisplay();
			break;
	}
}



/* ------------------------------------------------------------------------ */
/*					Settings menu command to Reset Settings					*/
/* ------------------------------------------------------------------------ */

//
// menu command to ask the user if the default configuration settings should be restored
//
static void ResetAllSettingsCommand(void)
{	UISelectMessageDisplay("Settings", "Restore configuration settings to their originial defaults?", ROM_STRING, JUSTIFY_CENTER, MESSAGE_DISPLAY_YES_NO, Font_MediumBold, ResetAllSettingCommandCallback);
}


//
// callback function for the ResetAllSettingsCommand Mesage Display
//
static void ResetAllSettingCommandCallback(byte Action)
{	switch(Action)
	{	case MESSAGE_DISPLAY_ACTION_YES:
			//
			// restore settings
			//
			ResetContrastConfigValue();
			LCDSetContrast(GetContrastConfigValue());

			ResetShowTenthsFlgConfigValue();
			ResetDigitsSizeConfigValue();

			UISelectPreviousMenuDisplay();
			break;

		case MESSAGE_DISPLAY_ACTION_NO:
			UISelectPreviousMenuDisplay();
			break;
	}
}


/* ------------------------------------------------------------------------ */
/*				   Read / write EEPROM configuration values					*/
/* ------------------------------------------------------------------------ */

//
// indexes into the EEPROM for configuation data, NOTE: saving a byte uses two bytes of EEPROM
//
#define CONFIG_CONTRAST_BYTE_IDX 			0
#define CONFIG_SHOW_TENTHS_FLG_BYTE_IDX 	2
#define CONFIG_DIGITS_SIZE_BYTE_IDX 		4


//
// get/set contrast configuration value
//
#define CONFIG_CONTRAST_DEFAULT 48
static void SaveContrastConfigValue(byte Value) {WriteConfigurationByte(CONFIG_CONTRAST_BYTE_IDX, Value);}
static byte GetContrastConfigValue(void) {return(ReadConfigurationByte(CONFIG_CONTRAST_BYTE_IDX, CONFIG_CONTRAST_DEFAULT));}
static void ResetContrastConfigValue(void) {ResetConfigurationByte(CONFIG_CONTRAST_BYTE_IDX);}


//
// get/set show tenths flag
//
#define CONFIG_SHOW_TENTHS_FLG_DEFAULT TRUE
static void SaveShowTenthsFlgConfigValue(byte Value) {WriteConfigurationByte(CONFIG_SHOW_TENTHS_FLG_BYTE_IDX, Value);}
static byte GetShowTenthsFlgConfigValue(void) {return(ReadConfigurationByte(CONFIG_SHOW_TENTHS_FLG_BYTE_IDX, CONFIG_SHOW_TENTHS_FLG_DEFAULT));}
static void ResetShowTenthsFlgConfigValue(void) {ResetConfigurationByte(CONFIG_SHOW_TENTHS_FLG_BYTE_IDX);}


//
// get/set digit size value
//
#define CONFIG_DIGITS_SIZE_DEFAULT 2
static void SaveDigitsSizeConfigValue(byte Value) {WriteConfigurationByte(CONFIG_DIGITS_SIZE_BYTE_IDX, Value);}
static byte GetDigitsSizeConfigValue(void) {return(ReadConfigurationByte(CONFIG_DIGITS_SIZE_BYTE_IDX, CONFIG_DIGITS_SIZE_DEFAULT));}
static void ResetDigitsSizeConfigValue(void) {ResetConfigurationByte(CONFIG_DIGITS_SIZE_BYTE_IDX);}


/* ----------------------------- End of Main.c ---------------------------- */
