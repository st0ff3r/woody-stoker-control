		/************************************************************/
		/*															*/
		/*		    Driver for the Nokia 6100 LCD display			*/
		/*				  											*/
		/*  This driver is configured for the Nokia 6100 LCD 		*/
		/*  display having a Philips PCF8833 controller chip		*/
		/*				  											*/
		/************************************************************/

//
// This driver is for an OEM LCD display used with Nokia 6100 cellphones.  The
// display is available at very low costs from ebay and sparkfun.com.  In the
// words of James Lynch: "The major irritant in using this display is identifying 
// the graphics controller; there are two possibilities (Epson S1D15G00 or 
// Philips PCF8833)". According to Sparkfun, the controller can be identified
// as follows:
//
// Parts with markings such as these use the Philips PCF8833 compatible controller
//     Red tab on the protective plastic
//     UMSH-8118FD-1CS
//     U.R.T. 080109-0010
//     LM355C11-B
//     AT-A2-071227-F604-1
//     GE-12
//
// Parts with markings such as these use the Epson S1D15G10 compatible controller:
//      Green tab on the protective plastic
//      EV-LG-0298
//      73-01824
//      GMP355C0 0403
//      C-SNB6C1504.50.21
//      GE-8
//
// The controller I used in developing this code was purchased on ebay from 
// Yallstore out of Brooklyn.  It had a Red tab on the protective plastic
// and markings:  CC2ZZ 8779 - 1Z3100
//
// I found the Yallstore display pretty much follows the specification documented
// in the Philips PCF8833 datasheet, with the exception of the RGBSET Color 
// command.  Because of this, it necessary to write a 48 byte color table rather  
// the 20 byte table documented.  Also I found that the values in the table were
// than used both with the 8 bit and 12 bit color modes.
//
// I also tested this software with a display from Sparkfun (part number LCD-00569)
// having a red tab on the protective plastic.  It worked correctly with the 48 
// byte color table.
//
// The datasheet for the Philips PCF8833 can be found at:
// 		http://www.nxp.com/acrobat_download/datasheets/PCF8833_1.pdf
//
// This driver is written for the Phillips controller.  It should be easily 
// modifiable to support the Epson controller by revising the functions:
//
//		LCDDriverInitialize()
//		LCDSelectColorMode()
//		LCDSetContrast()
//		WriteCommandToLCD()
//		WriteDataByteToLCD()
//
// along with the RGB8ColorMap color table and list of #defines for the 
// controller's command set.  See James Lynch's document referenced below for 
// help with that.
//
//
// Acknowledgements:
//
//	Some of this code is based on the work of James P Lynch.  His document:
//		www.sparkfun.com/tutorial/Nokia%206100%20LCD%20Display%20Driver.pdf
//  was extremely helpful in developing this LCD driver.
//
//  The line and circle drawing routines are derived from the 1962 algorithms 
//  of the famous Jack Bresenham.
//
//
// ------------------------------------------------------------------------------
//
//
// The LCD controller can be configured for different coordinate systems.  I choose
// to mount the display with the connector tab on the top, and I setup the coordinate
// system with 0,0 in the upper left corner.  X moves down and Y moves to the right.
// With this display, the X=0 and X=131 columns, along with the Y=0 and Y = 131 rows 
// are not visible and are not used.  
//
//
//                     ----------- Y ----------->
//                                        ___
//                    _ _ _ _ _ _ _ _ _ _|_ _|_ _
//                   |                           |
//             (0,0) |---------------------------| (131,0)
//        |          |                           |
//        |          |                           |
//        |          |                           |
//        |          |                           |
//        |          |    Nokia 6100 display     |
//        X          |                           |
//        |          |                           |
//        |          |                           |
//        |          |                           |
//        |          |                           |
//       \|/         |                           |
//           (0,131)  ---------------------------  (131,131)
//
//
// The auto increment and wrap feature of the RAMWR command is configured
// to write bytes in the Y direction, going from top to bottom, then wrapping  
// left to right. As a result, bitmap data should be stored in arrays with the  
// first byte representing the pixel in the upper left corner, then advancing 
// downward and to the right.
//

/* ------------------------------------------------------------------------ */


#include <p18cxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NumericTypedefs.h"
#include "Fonts.h"
#include "HardwareIO.h"
#include "GeneralFuncs.h"
#include "LCDDriver.h"


/* ------------------------------------------------------------------------ */


//
// command set for the Philips PCF8833 LCD controller
//
#define NOP 	0x00 		// nop
#define SWRESET 0x01 		// software reset
#define BSTROFF 0x02 		// booster voltage OFF
#define BSTRON 	0x03 		// booster voltage ON
#define RDDIDIF 0x04 		// read display identification
#define RDDST 	0x09 		// read display status
#define SLEEPIN 0x10 		// sleep in
#define SLEEPOUT 0x11 		// sleep out
#define PTLON 	0x12 		// partial display mode
#define NORON 	0x13 		// display normal mode
#define INVOFF 	0x20 		// inversion OFF
#define INVON 	0x21 		// inversion ON
#define DALO 	0x22 		// all pixel OFF
#define DAL 	0x23 		// all pixel ON
#define SETCON 	0x25 		// write contrast
#define DISPOFF 0x28 		// display OFF
#define DISPON 	0x29 		// display ON
#define CASET 	0x2A 		// column address set
#define PASET 	0x2B 		// page address set
#define RAMWR 	0x2C 		// memory write
#define RGBSET 	0x2D 		// colour set
#define PTLAR 	0x30 		// partial area
#define VSCRDEF 0x33 		// vertical scrolling definition
#define TEOFF 	0x34 		// test mode
#define TEON 	0x35		// test mode
#define MADCTL 	0x36 		// memory access control
#define SEP 	0x37 		// vertical scrolling start address
#define IDMOFF 	0x38 		// idle mode OFF
#define IDMON 	0x39 		// idle mode ON
#define COLMOD 	0x3A 		// interface pixel format
#define SETVOP 	0xB0 		// set Vop
#define BRS 	0xB4 		// bottom row swap
#define TRS 	0xB6 		// top row swap
#define DISCTR 	0xB9 		// display control
#define DOR 	0xBA 		// data order
#define TCDFE 	0xBD 		// enable/disable DF temperature compensation
#define TCVOPE 	0xBF 		// enable/disable Vop temp comp
#define EC 		0xC0 		// internal or external oscillator
#define SETMUL 	0xC2 		// set multiplication factor
#define TCVOPAB 0xC3 		// set TCVOP slopes A and B
#define TCVOPCD 0xC4 		// set TCVOP slopes c and d
#define TCDF 	0xC5 		// set divider frequency
#define DF8COLOR 0xC6 		// set divider frequency 8-color mode
#define SETBS 	0xC7 		// set bias system
#define RDTEMP 	0xC8 		// temperature read back
#define NLI 	0xC9 		// n-line inversion
#define RDID1 	0xDA 		// read ID1
#define RDID2 	0xDB 		// read ID2
#define RDID3 	0xDC 		// read ID3


/* ------------------------------------------------------------------------ */


//
// color map for RGB12 (rrrrggggbbbb)
//
static rom byte RGB12ColorMap[] = {
	// number of bytes in the table excluding this one
	48,
	
	// red map: an input 4 bit rrrr color is mapped to an output 5 bit rrrrr color
	0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,0x10,0x12,0x14,0x16,0x18,0x1A,0x1C,0x1F,
	
	// green map: an input 4 bit gggg color is mapped to an output 6 bit gggggg color
	0x00,0x07,0x0B,0x0F,0x13,0x17,0x1B,0x1F,0x23,0x27,0x2B,0x2F,0x33,0x37,0x3B,0x3F,
	
	// blue map: an input 4 bit bbbb color is mapped to an output 5 bit bbbbb color
	0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,0x10,0x12,0x14,0x16,0x18,0x1A,0x1C,0x1F};



//
// color map for RGB8 (rrrgggbb).  This color table does not follow the requirements
// detailed in the Philips datasheet, but does work correctly with the displays used
// to develop this software.  I'm not sure why.
//
static rom byte RGB8ColorMap[] = {
	// number of bytes in the table excluding this one
	48,

	// red map: an input 3 bit rrr color is mapped to an output 5 bit rrrrr color
	0, 4, 9, 13, 18, 22, 27, 31, 0, 0, 0, 0, 0, 0, 0, 0,
	
	// green map: an input 3 bit ggg color is mapped to an output 6 bit gggggg color
	0, 9, 18, 27, 36, 45, 54, 63, 0, 0, 0, 0, 0, 0, 0, 0,
	
	// blue map: an input 2 bit bb color is mapped to an output 5 bit bbbbb color
	0, 10, 21, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};



//
// color map for RGB8 (rrrgggbb). This color table has not been tested.  It is
// here because it matches the required as documented in the Philips datasheet.
//
//static rom byte RGB8ColorMap[] = {
//	// number of bytes in the table excluding this one
//	20,
//
//	// red map: an input 3 bit rrr color is mapped to an output 4 bit rrrr color
//	0, 2, 5, 7, 9, 11, 14, 15, 
//	
//	// green map: an input 3 bit ggg color is mapped to an output 4 bit gggg color
//	0, 2, 4, 6, 9, 11, 14, 15,
//	
//	// blue map: an input 2 bit bb color is mapped to an output 4 bit bbbb color
//	0, 6, 11, 15};



/* ------------------------------------------------------------------------ */
/*             	    Private variables local to this module					*/
/* ------------------------------------------------------------------------ */
#pragma udata

static byte CurrentColorMode;
static rom byte *CurrentColorMap;
static byte SPIData;


/* ------------------------------------------------------------------------ */
/*						  Local function declarations  	 					*/
/* ------------------------------------------------------------------------ */

static void InitSPI(void);
static void WriteCommandToLCD(void);
static void WriteRomDataToLCD(rom byte *, unsigned int);
static void WriteDataByteToLCD(void);
static void DeselectLCD(void);


/* ------------------------------------------------------------------------ */
/*						  	Public general functions 		 				*/
/* ------------------------------------------------------------------------ */
#pragma code


//
// initialize this module and the LCD controller
//		Enter:	ColorMode = LCD_COLOR_MODE_RGB8 or LCD_COLOR_MODE_RGB8
//
void LCDDriverInitialize(byte ColorMode)
{	//
	// initialize state variables
	//
	CurrentColorMode = LCD_COLOR_MODE_UNDEFINED;
	CurrentColorMap = 0;
	
	
	//
	// initialize the SPI registers that communicate with the LCD display
	//
	InitSPI();

	
	//
	// hardware reset the LCD display
	//
	LCD_RESET = 0;
	DelayMS(30);
	LCD_RESET = 1;
	DelayMS(30);


	//
	// take the controller out of sleep (start the power booster)
	//
	SPIData = SLEEPOUT;
	WriteCommandToLCD();
	DelayMS(2);

	
	//
	// don't mirror x & y, write in Y dir, color = RGB
	// Note: The V bit is set so that writes to RAM increment in the Y direction, going
	// from top to bottom, then left to right.  I picked the Y direction to be compatible
	// with the variable pitch font.  Setting this bit also required switching PASET and 
	// CASET
	//
	SPIData = MADCTL;
	WriteCommandToLCD();
	SPIData = 0x20;			
	WriteDataByteToLCD();


	//
	// initialize the contrast
	//
	SPIData = SETCON;
	WriteCommandToLCD();
	SPIData = 0x30;
	WriteDataByteToLCD();
	DeselectLCD();

	
	//
	// turn on the display
	//
	DelayMS(4);
	SPIData = DISPON;
	WriteCommandToLCD();		


	//
	// set the default color mode (RGB8 or RGB12) and the color map
	//
	LCDSelectColorMode(ColorMode, 0);
	DeselectLCD();
}



//
// select color mode, either RGB8 or RGB12
//		Enter:	ColorMode = LCD_COLOR_MODE_RGB8 or LCD_COLOR_MODE_RGB8
//				ColorMap -> color map table, if 0 then use default table
//
void LCDSelectColorMode(byte ColorMode, rom byte *ColorMap)
{	rom byte *ColorMapTable;
	

	//
	// check if the display is already in the current mode
	//
	if ((CurrentColorMode == ColorMode) && (CurrentColorMap == ColorMap)) 
		return;
		

	//
	// set the color mode
	//
	SPIData = COLMOD;
	WriteCommandToLCD();
	
	if (ColorMode == LCD_COLOR_MODE_RGB8)
	{	SPIData = 2;
		WriteDataByteToLCD();
		ColorMapTable = RGB8ColorMap;
	}
	else
	{	SPIData = 3;
		WriteDataByteToLCD();
		ColorMapTable = RGB12ColorMap;
	}
	
	
	//
	// check if the default table should not be used
	//
	if (ColorMap != 0)
		ColorMapTable = ColorMap;
	
	
	//
	// load the color table
	//
	SPIData = RGBSET;
	WriteCommandToLCD();
	WriteRomDataToLCD(ColorMapTable + 1, ColorMapTable[0]);
	SPIData = NOP;
	WriteCommandToLCD();

	CurrentColorMode = ColorMode;
	CurrentColorMap = ColorMap;
	DeselectLCD();
}



//
// blank the display (fill with white)
//
void LCDBlankDisplay(void)
{	if (CurrentColorMode == LCD_COLOR_MODE_RGB8)
		LCDDrawFilledRectangleRGB8(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, RGB8_WHITE);
	
	else
		LCDDrawFilledRectangleRGB12(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, RGB12_WHITE);
}



//
// set the contrast level for the LCD display
//		Enter:	Value = contrast value (-64 to 63)
//
void LCDSetContrast(char Value)
{	SPIData = SETCON;
	WriteCommandToLCD();
	SPIData = (byte) Value;
	WriteDataByteToLCD();
	DeselectLCD();
}



/* ------------------------------------------------------------------------ */
/*						  	 Public RGB8 functions 		 					*/
/* ------------------------------------------------------------------------ */

//
// draw a single pixel with an 8 bit color
//		Enter:	X = x coord (1 - 130)
//				Y = y coord (1 - 130)
//				Color = pixel color (rrrgggbb)
//
void LCDDrawPixelRGB8(byte X, byte Y, byte ColorRGB8)
{	//
	// set the coords of a box including just this one pixel
	//
	SPIData = PASET;							// define the right & left 
	WriteCommandToLCD();
	SPIData = X;
	WriteDataByteToLCD();
	WriteDataByteToLCD();
	
	SPIData = CASET;							// define the top and bottom
	WriteCommandToLCD();
	SPIData = Y;
	WriteDataByteToLCD();
	WriteDataByteToLCD();
	
	//
	// set the color of the pixel
	//
	SPIData = RAMWR;							// set the pixel 
	WriteCommandToLCD();
	SPIData = ColorRGB8;
	WriteDataByteToLCD();
	
	DeselectLCD();
}



//
// draw a filled rectangle with an 8 bit color (5.2us / pixel)
//		Enter:	Left = left x coord (1 - 130)
//				Top = top y coord (1 - 130)
//				Right = right x coord (1 - 130)
//				Bottom = bottom y coord (1 - 130)
//				ColorRGB8 = pixel color (rrrgggbb)
//
void LCDDrawFilledRectangleRGB8(byte Left, byte Top, byte Right, byte Bottom, byte ColorRGB8)
{	word i;
	word PixelCount;
	
	//
	// verify rectangle makes sense
	//
	if ((Left > Right) || (Top > Bottom))
		return;

	//
	// set the coords of a rectangle
	//
	SPIData = PASET;							// define the right & left 
	WriteCommandToLCD();
	SPIData = Left;
	WriteDataByteToLCD();
	SPIData = Right;
	WriteDataByteToLCD();
	
	SPIData = CASET;							// define the top and bottom
	WriteCommandToLCD();
	SPIData = Top;
	WriteDataByteToLCD();
	SPIData = Bottom;
	WriteDataByteToLCD();


	//
	// fill the rectangle with the pixel color
	//
	SPIData = RAMWR;
	WriteCommandToLCD();
	
	PixelCount = (unsigned int) (Right - Left + 1) * (unsigned int) (Bottom - Top + 1);
	SPIData = ColorRGB8;
	for (i = 0; i < PixelCount; i++)
		WriteDataByteToLCD();

	SPIData = NOP;
	WriteCommandToLCD();

	DeselectLCD();
}



//
// draw a horizontal gradient
//		Enter:	ColorTable -> to a table in RAM of RGB8 colors
//				LeftX = left side of horizontal gradient to draw
//				RightX = right side of horizontal gradient to draw
//				TopY = Y coord of top line of horizontal gradient to draw, will draw down from there
//				LineCount = number of lines to draw
//
void DrawHorzGradientRGB8(ram byte *ColorTable, byte LeftX, byte RightX, byte TopY, byte LineCount)
{	byte i;
	
	while(LineCount)
	{	LCDDrawFilledRectangleRGB8(
		  LeftX, TopY, 
		  RightX, TopY, 
		  *ColorTable);

		LineCount--;
		TopY++;
		ColorTable++;
	}
}



//
// draw a line using an 8 bit color, algorithm by Jack Bresenham
// Note: It is MUCH faster to draw horizontal and vertical lines using LCDDrawFilledRectangleRGB8()
//		Enter:	X1, Y1 = first endpoint
//				X2, Y2 = second endpoint
//				ColorRGB8 = pixel color (rrrgggbb)
//
void LCDDrawLineRGB8(int X1, int Y1, int X2, int Y2, byte ColorRGB8) 
{	int dy;
	int dx;
	int StepX, StepY;
	int Fraction;
	
	dy = Y2 - Y1;
	dx = X2 - X1;

	if (dy < 0)
	{	dy = -dy; 
		StepY = -1;
	}
	else
		StepY = 1;
		
	if (dx < 0) 
	{	dx = -dx; 
		StepX = -1; 
	}
	else
		StepX = 1;

	dy <<= 1; 									// dy is now 2*dy
	dx <<= 1; 									// dx is now 2*dx
	LCDDrawPixelRGB8(X1, Y1, ColorRGB8);

	if (dx > dy) 
	{	Fraction = dy - (dx >> 1); 				// same as 2*dy - dx
		while (X1 != X2) 
		{	if (Fraction >= 0) 
			{	Y1 += StepY;
				Fraction -= dx; 				// same as fraction -= 2*dx
			}

			X1 += StepX;
			Fraction += dy; 					// same as fraction -= 2*dy
			LCDDrawPixelRGB8(X1, Y1, ColorRGB8);
		}
	} 
	
	else 
	{	Fraction = dx - (dy >> 1);
		while (Y1 != Y2) 
		{	if (Fraction >= 0) 
			{	X1 += StepX;
				Fraction -= dy;
			}

			Y1 += StepY;
			Fraction += dx;
			LCDDrawPixelRGB8(X1, Y1, ColorRGB8);
		}
	}
}



//
// draw a circle using an 8 bit color, algorithm by Jack Bresenham
//		Enter:	X1, Y1 = center of the circle
//				radius = radius of the circle
//				ColorRGB8 = pixel color (rrrgggbb)
//
void LCDDrawCircleRGB8(int X1, int Y1, int Radius, byte ColorRGB8) 
{	int f;
	int ddF_x;
	int ddF_y;
	int x;
	int y;
	
	f = 1 - Radius;
	ddF_x = 0;
	ddF_y = -2 * Radius;
	x = 0;
	y = Radius;

	LCDDrawPixelRGB8(X1, Y1 + Radius, ColorRGB8);
	LCDDrawPixelRGB8(X1, Y1 - Radius, ColorRGB8);
	LCDDrawPixelRGB8(X1 + Radius, Y1, ColorRGB8);
	LCDDrawPixelRGB8(X1 - Radius, Y1, ColorRGB8);

	while (x < y) 
	{	if (f >= 0) 
		{	y--;
			ddF_y += 2;
			f += ddF_y;
		}

		x++;
		ddF_x += 2;
		f += ddF_x + 1;
		
		LCDDrawPixelRGB8(X1 + x, Y1 + y, ColorRGB8);
		LCDDrawPixelRGB8(X1 - x, Y1 + y, ColorRGB8);
		LCDDrawPixelRGB8(X1 + x, Y1 - y, ColorRGB8);
		LCDDrawPixelRGB8(X1 - x, Y1 - y, ColorRGB8);
		LCDDrawPixelRGB8(X1 + y, Y1 + x, ColorRGB8);
		LCDDrawPixelRGB8(X1 - y, Y1 + x, ColorRGB8);
		LCDDrawPixelRGB8(X1 + y, Y1 - x, ColorRGB8);
		LCDDrawPixelRGB8(X1 - y, Y1 - x, ColorRGB8);
	}
}



//
// draw a RGB8 bitmap
//		Enter:	Bitmap -> RGB8 bitmap stored in ROM
//				X, Y = coord where to place bitmap (upper left corner)
//
void LCDDrawBitmapRGB8(rom byte *Bitmap, byte X, byte Y)
{	byte Width;
	byte Height;
	word ByteCount;
	
	Width = Bitmap[1];							// get the size of the bitmap
	Height = Bitmap[2];
	ByteCount = Bitmap[3] + ((word)Bitmap[4] << 8);
	
	SPIData = PASET;							// define the right & left
	WriteCommandToLCD(); 
	SPIData = X;
	WriteDataByteToLCD();
	SPIData = X + Width - 1;
	WriteDataByteToLCD();
	
	SPIData = CASET;							// define the top and bottom
	WriteCommandToLCD();
	SPIData = Y;
	WriteDataByteToLCD();
	SPIData = Y + Height - 1;
	WriteDataByteToLCD();
	
	SPIData = RAMWR;							// write the bitmap to the display
	WriteCommandToLCD();
	WriteRomDataToLCD(Bitmap + 5, ByteCount);

	SPIData = NOP;
	WriteCommandToLCD();
	DeselectLCD();
}



//
// draw a string using RGB8 colors
//		Enter:	S -> string to draw
//				StringType = ROM_STRING or RAM_STRING
//				X = x coord where to draw the string
//				Y = y coord where to draw bottom of the text (including space for the decenders)
//				Justify = JUSTIFY_LEFT, JUSTIFY_CENTER, or JUSTIFY_RIGHT
//				Font -> the font
//				ForegroundRGB8 = forground color
//				BackgroundRGB8 = background color
//		Exit:	the X coordinate right of the character just drawn is returned
//
byte LCDDrawStringRGB8(char *S, byte StringType, byte X, byte Y, byte Justify, rom byte *Font, byte ForegroundRGB8, byte BackgroundRGB8)
{	char C;
	rom char *RomStr;
	
	
	//
	// adjust the X coord if justifying right or center
	//
	switch(Justify)
	{	case JUSTIFY_CENTER:
			X -= LCDGetStringWidth(S, StringType, Font) / 2;
			break;
	
	
		case JUSTIFY_RIGHT:
			X -= (LCDGetStringWidth(S, StringType, Font) - 1);
			break;
	}
	
	//
	// determine if the string is saved in ROM or RAM, the draw it
	//
	if (StringType == ROM_STRING)
	{	RomStr = (rom char *) S;
		
		C = *RomStr++;
		while(C)
		{	X = LCDDrawCharacterRGB8(C, X, Y, Font, ForegroundRGB8, BackgroundRGB8);
			C = *RomStr++;
		}
	}
	
	else
	{	C = *S++;
		while(C)
		{	X = LCDDrawCharacterRGB8(C, X, Y, Font, ForegroundRGB8, BackgroundRGB8);
			C = *S++;
		}
	}
	
	return(X);
}



//
// draw a string between the start and stop indexes, using RGB8 colors
//		Enter:	S -> string to draw
//				StringType = ROM_STRING or RAM_STRING
//				StartIdx = index in string of first character to draw
//				StopIdx = index in string of last character to draw
//				X, Y = coord of where to draw lower left corner of char (including space 
//				  for the possible decender)
//				Justify = JUSTIFY_LEFT, JUSTIFY_CENTER, or JUSTIFY_RIGHT
//				Font -> the font
//				ForegroundRGB8 = forground color
//				BackgroundRGB8 = background color
//		Exit:	the X coordinate right of the character just drawn is returned
//
byte LCDDrawStringBetweenIndexesRGB8(char *S, byte StringType, unsigned int StartIdx, unsigned int StopIdx, byte X, byte Y, byte Justify, rom byte *Font, byte ForegroundRGB8, byte BackgroundRGB8)
{	char C;
	rom char *RomStr;
	int i;
	
	
	//
	// adjust the X coord if justifying right or center
	//
	switch(Justify)
	{	case JUSTIFY_CENTER:
			X -= LCDGetStringWidthBetweenIndexes(S, StringType, StartIdx, StopIdx, Font) / 2;
			break;
	
	
		case JUSTIFY_RIGHT:
			X -= (LCDGetStringWidthBetweenIndexes(S, StringType, StartIdx, StopIdx, Font) - 1);
			break;
	}
	
	//
	// determine if the string is saved in ROM or RAM, the draw it
	//
	if (StringType == ROM_STRING)
	{	RomStr = (rom char *) S;
		
		for (i = StartIdx; i <= StopIdx; i++)
		{	C = RomStr[i];
			if (C == 0)
				break;
			X = LCDDrawCharacterRGB8(C, X, Y, Font, ForegroundRGB8, BackgroundRGB8);
		}
	}
	
	else
	{	for (i = StartIdx; i <= StopIdx; i++)
		{	C = S[i];
			if (C == 0)
				break;
			X = LCDDrawCharacterRGB8(C, X, Y, Font, ForegroundRGB8, BackgroundRGB8);
		}
	}
	
	return(X);
}



//
// draw a character using RGB8 colors
//		Enter:	c = character to draw
//				X, Y = coord of where to draw lower left corner of char (including space 
//				  for the possible decender)
//				Font -> the font
//				ForegroundRGB8 = forground color
//				BackgroundRGB8 = background color
//		Exit:	the X coordinate right of the character just drawn is returned
//
byte LCDDrawCharacterRGB8(byte C, byte X, byte Y, rom byte *Font, byte ForegroundRGB8, byte BackgroundRGB8)
{	rom byte *TablePntr;
	byte CharacterHeight;
	byte ExtraSpaceBetweenChars;
	word IndexToCharacterIndex;
	WORD IndexToPixels;
	byte CharacterWidth;
	byte Column;
	byte Row;
	WORD ColBits;
	
	//
	// make sure not starting off screen
	//
	if (X >= LCD_WIDTH)
		return(X);
	if (Y >= LCD_HEIGHT)
		return(X);
		
	//
	// make sure char is in ASCII range
	//
	if (C < 0x20)
		return(X);
	
	if (C > 0x7f)
		return(X);
	
	
	//
	// get info about the font
	//
	CharacterHeight = Font[FONT_TABLE_HEIGHT_IDX];
	ExtraSpaceBetweenChars = Font[FONT_TABLE_PAD_AFTER_CHAR_IDX];


	//
	// get a pointer to the pixel data for the character
	//
	IndexToCharacterIndex = FONT_TABLE_CHAR_LOOKUP_IDX + (((word)(C - 0x20)) << 1);
	TablePntr = Font + IndexToCharacterIndex;
	IndexToPixels.byte0 = *TablePntr++; 
	IndexToPixels.byte1 = *TablePntr; 
	TablePntr = Font + IndexToPixels._word;
	
	
	//
	// determine the number of columns for the character
	//
	CharacterWidth = *TablePntr++;


	//
	// define the upper left and lower right corners of the character
	//
	SPIData = PASET;							// define the right & left 
	WriteCommandToLCD();
	SPIData = X;
	WriteDataByteToLCD();
	SPIData = X + CharacterWidth - 1;
	WriteDataByteToLCD();
	
	Y -= (CharacterHeight - 1);					// define the top and bottom
	SPIData = CASET;
	WriteCommandToLCD();
	SPIData = Y;
	WriteDataByteToLCD();
	SPIData = Y + CharacterHeight - 1;
	WriteDataByteToLCD();
	

	//
	// for each pixel in the font, send a forground or background pixel to the display
	//	
	SPIData = RAMWR;
	WriteCommandToLCD();						// begin writing data to the display

	for (Column = 0; Column < CharacterWidth; Column++)
	{	ColBits.byte0 = *TablePntr++;
		ColBits.byte1 = *TablePntr++;

		for (Row = 0; Row < CharacterHeight; Row++)
		{	if (ColBits.Byte0.b0) 
				SPIData = ForegroundRGB8;
			else
				SPIData = BackgroundRGB8;
			WriteDataByteToLCD();
			
			ColBits._word = ColBits._word >> 1;
		}
	}

	SPIData = NOP;
	WriteCommandToLCD();
	X += Column;


	//
	// check if drawing extra space after the character
	//
	if (ExtraSpaceBetweenChars != 0)
	{	//
		// define the upper left and lower right corners of the extra space
		//
		SPIData = PASET;						// define the right & left 
		WriteCommandToLCD();
		SPIData = X;
		WriteDataByteToLCD();
		SPIData = X + ExtraSpaceBetweenChars - 1;
		WriteDataByteToLCD();
		
		SPIData = CASET;						// define the top and bottom
		WriteCommandToLCD();
		SPIData = Y;
		WriteDataByteToLCD();
		SPIData = Y + CharacterHeight - 1;
		WriteDataByteToLCD();

		SPIData = RAMWR;						// begin writing data to the display
		WriteCommandToLCD();
	
		SPIData = BackgroundRGB8;
		for (Column = 0; Column < ExtraSpaceBetweenChars; Column++)
		{	for (Row = 0; Row < CharacterHeight; Row++)
				WriteDataByteToLCD();
		}

		SPIData = NOP;
		WriteCommandToLCD();	

		X += Column;
	}

	DeselectLCD();


	//
	// return the X coord of where the next character should be drawn
	//
	return(X);
}



//
// get the width of a string of charcters
//		Enter:	S -> string
//				StringType = ROM_STRING or RAM_STRING
//				Font -> the font
//		Exit:	the character's width returned
//
byte LCDGetStringWidth(char *S, byte StringType, rom byte *Font)
{	char C;
	rom char *RomStr;
	byte Width;
	
	//
	// determine if the string is stored in ROM or RAM, then measure it
	//
	Width = 0;
	if (StringType == ROM_STRING)
	{	RomStr = (rom char *) S;
		
		C = *RomStr++;
		while(C)
		{	Width += LCDGetCharacterWidth(C, Font);
			C = *RomStr++;
		}
	}
	
	else
	{	C = *S++;
		while(C)
		{	Width += LCDGetCharacterWidth(C, Font);
			C = *S++;
		}
	}
	
	return(Width);
}



//
// get the width of a string of charcters between the start and stop indexes
//		Enter:	S -> string
//				StringType = ROM_STRING or RAM_STRING
//				StartIdx = index in string of first character to measure
//				StopIdx = index in string of last character to measure
//				Font -> the font
//		Exit:	the character's width returned
//
byte LCDGetStringWidthBetweenIndexes(char *S, byte StringType, unsigned int StartIdx, unsigned int StopIdx, rom byte *Font)
{	char C;
	rom char *RomStr;
	byte Width;
	int i;

	//
	// determine if the string is stored in ROM or RAM, then measure it
	//
	Width = 0;
	if (StringType == ROM_STRING)
	{	RomStr = (rom char *) S;
		
		for (i = StartIdx; i <= StopIdx; i++)
		{	C = RomStr[i];
			if (C == 0)
				break;
			Width += LCDGetCharacterWidth(C, Font);
		}
	}
	
	else
	{	for (i = StartIdx; i <= StopIdx; i++)
		{	C = S[i];
			if (C == 0)
				break;
			Width += LCDGetCharacterWidth(C, Font);
		}
	}
	
	return(Width);
}



//
// get the width and height of a string of charcters
//		Enter:	S -> string
//				StringType = ROM_STRING or RAM_STRING
//				Font -> the font
//				Width -> storage to return width of string in
//				Height -> storage to return height (including decenters)
//
void LCDGetStringExtents(char *S, byte StringType, rom byte *Font, byte *Width, byte *Height)
{	char C;
	rom char *RomStr;
	byte W;
	
	//
	// determine if the string is stored in ROM or RAM, then measure it
	//
	W = 0;
	if (StringType == ROM_STRING)
	{	RomStr = (rom char *) S;
		
		C = *RomStr++;
		while(C)
		{	W += LCDGetCharacterWidth(C, Font);
			C = *RomStr++;
		}
	}
	
	else
	{	C = *S++;
		while(C)
		{	W += LCDGetCharacterWidth(C, Font);
			C = *S++;
		}
	}
	
	*Width = W;
	*Height = Font[FONT_TABLE_HEIGHT_IDX];
}



//
// get the width of a character
//		Enter:	c = character to measure
//				Font -> the font
//		Exit:	the character's width returned
//
byte LCDGetCharacterWidth(byte C, rom byte *Font)
{	rom byte *TablePntr;
	word IndexToCharacterIndex;
	WORD IndexToPixels;
	
	//
	// get a pointer to the pixel data for the character
	//
	IndexToCharacterIndex = FONT_TABLE_CHAR_LOOKUP_IDX + (((word)(C - 0x20)) << 1);
	TablePntr = Font + IndexToCharacterIndex;
	IndexToPixels.byte0 = *TablePntr++; 
	IndexToPixels.byte1 = *TablePntr; 
	TablePntr = Font + IndexToPixels._word;
	
	
	//
	// return the width of the character plus the extra space drawn after every character
	//
	return(*TablePntr + Font[FONT_TABLE_PAD_AFTER_CHAR_IDX]);
}



/* ------------------------------------------------------------------------ */
/*						  	 Public RGB12 functions 		 				*/
/* ------------------------------------------------------------------------ */


//
// draw a filled rectangle with an 12 bit color (7.5us / pixel)
//		Enter:	Left = left x coord (1 - 130)
//				Top = top y coord (1 - 130)
//				Right = right x coord (1 - 130)
//				Bottom = bottom y coord (1 - 130)
//				ColorRGB12 = pixel color (rrrrggggbbbb)
//
void LCDDrawFilledRectangleRGB12(byte Left, byte Top, byte Right, byte Bottom, word ColorRGB12)
{	word i;
	word PixelCount;
	byte Byte1, Byte2, Byte3;
	word LoopCount;
	
	//
	// verify rectangle makes sense
	//
	if ((Left > Right) || (Top > Bottom))
		return;

	//
	// set the coords of a rectangle
	//
	SPIData = PASET;							// define the right & left 
	WriteCommandToLCD();
	SPIData = Left;
	WriteDataByteToLCD();
	SPIData = Right;
	WriteDataByteToLCD();
	
	SPIData = CASET;							// define the top and bottom
	WriteCommandToLCD();
	SPIData = Top;
	WriteDataByteToLCD();
	SPIData = Bottom;
	WriteDataByteToLCD();
	
	//
	// fill the rectangle with the pixel color
	//
	SPIData = RAMWR;
	WriteCommandToLCD();
	
	Byte1 = (ColorRGB12 >> 4) & 0xff;
	Byte2 = (((ColorRGB12 & 0x0f) << 4) | ((ColorRGB12 >> 8) & 0x0f));
	Byte3 = (ColorRGB12 & 0xff);
	
	PixelCount = (unsigned int) (Right - Left + 1) * (unsigned int) (Bottom - Top + 1);
	LoopCount = (PixelCount / 2) + 1;
	for (i = 0; i < LoopCount; i++)
	{	SPIData = Byte1;
		WriteDataByteToLCD();
		
		SPIData = Byte2;
		WriteDataByteToLCD();
		
		SPIData = Byte3;
		WriteDataByteToLCD();
	}

	SPIData = NOP;
	WriteCommandToLCD();
	DeselectLCD();
}



//
// draw a RGB12 bitmap
//		Enter:	Bitmap -> RGB12 bitmap stored in ROM
//				X, Y = coord where to place bitmap (upper left corner)
//
void LCDDrawBitmapRGB12(rom byte *Bitmap, byte X, byte Y)
{	byte Width;
	byte Height;
	word ByteCount;
	
	Width = Bitmap[1];							// get the size of the bitmap
	Height = Bitmap[2];
	ByteCount = Bitmap[3] + ((word)Bitmap[4] << 8);
	
	SPIData = PASET;							// define the right & left 
	WriteCommandToLCD();
	SPIData = X;
	WriteDataByteToLCD();
	SPIData = X + Width - 1;
	WriteDataByteToLCD();
	
	SPIData = CASET;							// define the top and bottom
	WriteCommandToLCD();
	SPIData = Y;
	WriteDataByteToLCD();
	SPIData = Y + Height - 1;
	WriteDataByteToLCD();
	
	SPIData = RAMWR;							// write the bitmap to the display
	WriteCommandToLCD();
	WriteRomDataToLCD(Bitmap + 5, ByteCount);

	SPIData = NOP;
	WriteCommandToLCD();
	DeselectLCD();
}


/* ------------------------------------------------------------------------ */
/*					SPI communication to the LCD in software 				*/
/* ------------------------------------------------------------------------ */

#if 1
//
// initialize the SPI IO bits
//
static void InitSPI(void)
{	//
	// configure the IO bits that connect to the LCD
	//
	LCD_CS = 1;
	LCD_CS_TRIS = 0;
	LCD_RESET = 0;
	LCD_RESET_TRIS = 0;

	//
	// configure the SPI port for the LCD
	//
	SPI_SDO_TRIS = 0;							// set SDO as output
	SPI_SDI_TRIS = 1;							// set SDI as input 
	SPI_SCK_TRIS = 0;							// set SCK as output 
}



//
// send a command byte to the LCD display using a software SPI, this version is harware optimized
//		Enter:	SPIData = command byte to send to LCD
//
static void WriteCommandToLCD(void)
{	//
	// enable the LCD's chip select
	//
	LCD_CS = 0;

	//
	// set the 9th bit low for commands written to the LCD
	//
	SPI_SDO = 0;
	SPI_SCK = 1;
	LATC &= 0b11010111;
	
	//
	// clock out the 8 data bits
	//
	if (SPIData & 0x80) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x40) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x20) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x10) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x08) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x04) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x02) SPI_SDO = 1;
	SPI_SCK = 1;   LATC &= 0b11010111;

	if (SPIData & 0x01) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;
}



//
// send a command byte to the LCD display using a software SPI
//		Enter:	SPIData = command byte to send to LCD
//
//static void WriteCommandToLCD(void)
//{	//
//	// enable the LCD's chip select
//	//
//	LCD_CS = 0;
//
//	//
//	// set the 9th bit low for commands written to the LCD
//	//
//	SPI_SDO = 0;
//	SPI_SCK = 1;
//	SPI_SCK = 0;
//	
//	//
//	// clock out the 8 data bits
//	//
//	SPI_SDO = 0;
//	if (SPIData & 0x80) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (SPIData & 0x40) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (SPIData & 0x20) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (SPIData & 0x10) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (SPIData & 0x08) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (SPIData & 0x04) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (SPIData & 0x02) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (SPIData & 0x01) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//}



//
// send an array of data bytes located in ROM to the LCD
//		Enter:	RomData -> an array of bytes stored in ROM
//				Count = number of bytes to write to the LCD
//
static void WriteRomDataToLCD(rom byte *RomData, unsigned int Count)
{	unsigned int i;
	
	for (i = 0; i < Count; i++)
	{	SPIData = *RomData++;
		WriteDataByteToLCD();
	}
}



//
// send a data byte to the LCD display, this version is harware optimized
//		Enter:	SPIData = data byte to send to LCD
//
static void WriteDataByteToLCD(void)
{	//
	// set the 9th bit high for data written to the LCD
	//
	SPI_SDO = 1;
	SPI_SCK = 1;
	LATC &= 0b11010111;

	//
	// clock out the 8 data bits
	//
	if (SPIData & 0x80) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x40) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x20) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x10) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x08) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x04) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x02) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;

	if (SPIData & 0x01) SPI_SDO = 1;
	SPI_SCK = 1;  LATC &= 0b11010111;
}



//
// send a data byte to the LCD display
//		Enter:	SPIData = data byte to send to LCD
//
//static void WriteDataByteToLCD(byte Data)
//{	//
//	// set the 9th bit high for data written to the LCD
//	//
//	SPI_SDO = 1;
//	SPI_SCK = 1;
//	SPI_SCK = 0;
//
//	//
//	// clock out the 8 data bits
//	//
//	SPI_SDO = 0;
//	if (Data & 0x80) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (Data & 0x40) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (Data & 0x20) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (Data & 0x10) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (Data & 0x08) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (Data & 0x04) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (Data & 0x02) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//
//	SPI_SDO = 0;
//	if (Data & 0x01) SPI_SDO = 1;
//	SPI_SCK = 1; SPI_SCK = 0;
//}



//
// deselect the LCD (must be done after sending commands)
//
static void DeselectLCD(void)
{
	LCD_CS = 1;
}
#endif



/* ------------------------------------------------------------------------ */
/*					SPI communication to the LCD in hardware 				*/
/* ------------------------------------------------------------------------ */

//
// I was not able to get the SPI communication using the PICs SPI hardware to 
// work reliability.  The Nokia LCD used 9 bit serial data and the PIC only 
// supports 8 bit.  To add the extra bit, I tried manually clocking the first 
// bit, then letting the SPI do the remaining 8.  This mostly worked, however 
// I found that occasionally, I would get data errors, especially when the 
// board was cold.  In an effort to make it work, I tried adding many NOPs.
// I also added a pulldown resistor on the CLK line.  However these mods did 
// not improve reliability.  In the end, I gave up on using the SPI hardware.
//
// I may want to revisit the SPI hardware issue because it did result in a
// performance improvement:
//
//      Test		 Software SPI 		  Hardware SPI
// ---------------------------------------------------
//   12 bit bitmap		157ms				132ms
//   Text display		174ms				151ms
//   Main menu			117ms				 99ms
//
//


#if 0
//
// initialize the SPI
//
static void InitSPI(void)
{	//
	// configure the IO bits that connect to the LCD
	//
	LCD_CS = 1;
	LCD_CS_TRIS = 0;
	LCD_RESET = 0;
	LCD_RESET_TRIS = 0;

	//
	// configure the SPI port for the LCD
	//
	SPI_SDO_TRIS = 0;							// set SDO as output
	SPI_SDI_TRIS = 1;							// set SDI as input 
	SPI_SCK_TRIS = 0;							// set SCK as output 

	SSPCON1 = 0b00000001;						// clock SPI at Fosc / 16
	SSPSTATbits.SMP = 0;
	SSPSTATbits.CKE = 1;						// transmit data on rising edge of clock
	SSPCON1bits.SSPEN = 1;						// enable the SPI port
	Nop();
	SSPBUF = 0;									// send the first byte to initialize the port
}



//
// send a command byte to the LCD display
//
// Notes: 
//		The mininum clock period for the LCD is 150ns.  With a 40mhz clock and the SPI 
//		configured for Fosc/4, the clock period is 100ns.  With a 40mhz clock and 
//		SPI configured for Fosc/16, the clock period is 400ns
//
//		The data rate for transmitting commands or data (with 40Mhz clock & Fosc/16) is 5us
//
//		Enter:	SPIData = command byte to send to LCD
//
static void WriteCommandToLCD(void)
{	byte Command;
	
	//
	// enable the LCD's chip select
	//
	LCD_CS = 0;

	//
	//  wait if the SPI port is busy
	//
	while(!SSPSTATbits.BF)
		;

	//
	// send the 9th bit using the output port bit
	//
	Nop();
	SSPCON1bits.SSPEN = 0;						// disable the SPI port so 9th bit can be manually sent
	SPI_SCK_TRIS = 0;							// set SCK as output 
	Nop();
	SPI_SDO = 0;								// set the 9th bit low for commands
	SPI_SCK = 1;								// clock the 9th bit (SCK must be high for a minimum of 75ns)
	SPI_SCK = 0;
	Nop();

	//
	// re-enable the SPI port.  In order to prevent a rising spike on the SCK line,
	// change it temporairly to an input.  This hack may require a pull down on the SCK
	// line (which I have because of the 3.3v level shifter resistors).
	//
	SPI_SCK_TRIS = 1;							// set SCK as output 
	SSPCON1bits.SSPEN = 1;						// enable the SPI port
	SPI_SCK_TRIS = 0;							// set SCK as output 

	
	//
	// send the data byte using the SPI port
	//
	Command = SPIData;
	SSPBUF = Command;							// transmit the 8 bits
}



//
// send an array of data bytes located in ROM to the LCD
//		Enter:	RomData -> an array of bytes stored in ROM
//				Count = number of bytes to write to the LCD
//
static void WriteRomDataToLCD(rom byte *RomData, unsigned int Count)
{	unsigned int i;
	
	for (i = 0; i < Count; i++)
	{	SPIData = *RomData++;
		WriteDataByteToLCD();
	}
}



//
// send a data byte to the LCD display
//		Enter:	SPIData = data byte to send to LCD
//
static void WriteDataByteToLCD(void)
{	byte Data;

	//
	//  wait if the SPI port is busy
	//
	while(!SSPSTATbits.BF)
		;

	//
	// send the 9th bit using the output port bit
	//
	Nop();
	SSPCON1bits.SSPEN = 0;						// disable the SPI port so 9th bit can be manually sent
	SPI_SCK_TRIS = 0;							// set SCK as output 
	Nop();
	SPI_SDO = 1;								// set the 9th bit high for data
	SPI_SCK = 1;								// clock the 9th bit (SCK must be high for a minimum of 75ns)
	SPI_SCK = 0;
	Nop();
	
	//
	// re-enable the SPI port.  In order to prevent a rising spike on the SCK line,
	// change it temporairly to an input.  This hack may require a pull down on the SCK
	// line (which I have because of the 3.3v level shifter resistors).
	//
	SPI_SCK_TRIS = 1;							// set SCK as input 
	SSPCON1bits.SSPEN = 1;						// enable the SPI port
	SPI_SCK_TRIS = 0;							// set SCK as output 
	
	//
	// send the data byte using the SPI port
	//
	Data = SPIData;
	SSPBUF = Data;							// transmit the 8 bits
}




//
// deselect the LCD (must be done after sending commands)
//
static void DeselectLCD(void)
{	//
	//  wait if the SPI port is busy
	//
	while(!SSPSTATbits.BF)
		;

	Nop();
	LCD_CS = 1;
}
#endif


/* --------------------------- End of LCDDriver.c ------------------------- */
