		/************************************************************/
		/*															*/
		/*		     	     The User Interface						*/
		/*				  											*/
		/************************************************************/

//
// This user interface is used with embedded applications having a graphical
// LCD display and 4 push buttons.  The display is divided into three sections, 
// each section is the full width of the screen.  
//
// Along the top, is the "TitleBar".  It displays things like the name of the 
// menu that is selected, or the name of the application.  
//
// Along the bottom of the screen is the "ButtonBar".  Mounted below the LCD
// display are two of the push buttons.  The function of these buttons change, 
// so the ButtonBar is used to label what the buttons do.  Typically the left 
// button will be labeled "Select" and the right "Back".
//
// The middle section of the display is the "DisplaySpace".  Here is where menus,
// message boxes, configuration screens, along with the application's main 
// display is shown.
//
// Mounted along the right side of the LCD display are the other two buttons, 
// one to go up, the other down.
//
//
// Below are the functions that define this user interface.  The function 
// UIDrawTitleBar() is called to draw the TitleBar along the top of the LCD.  The 
// function UIDrawButtonBar() draws the ButtonBar at the bottom.
//
// In between the TitleBar and the ButtonBar is the DisplaySpace.  An application 
// typically draws its custom displays here.  This user interface also defines 
// several functions that draw in the DisplaySpace.
//
//
// UISelectMenuDisplay() presents a menu in the DisplaySpace.  This function is 
// called with a pointer to a table that defines the contents of the menu.  Each 
// menu item includes the menu text, along with what to do when the menu item is 
// selected by the user.  There are three types of menu items: Commands, Alternates, 
// and Sub Menus.
//
// A typical main menu table might look like this:
//
//	MENU_ITEM MainMenu[] = {
//    {MENU_ITEM_TYPE_MAIN_MENU_HEADER, "Main menu", SelectApplication},
//	  {MENU_ITEM_TYPE_COMMAND, "About", ShowAboutCommand},
//	  {MENU_ITEM_TYPE_ALTERNATE, "Enable sound", SetEnableSoundCallback},	
//	  {MENU_ITEM_TYPE_SUB_MENU, "Settings", SettingsMenu},
//	  {MENU_ITEM_TYPE_END_OF_MENU, "", 0}};
//
// The first line in the table always defines what type of menu it is, either a 
// Main Menu, or a Sub Menu.  The table's last line marks the end of the table.  
// In between are menu items.
//
// A MENU_ITEM_TYPE_COMMAND entry indicates that a function will be executed when 
// this menu item is selected.  A pointer to the function is third field in the
// entry.
//
// A MENU_ITEM_TYPE_ALTERNATE is used somewhat like a Radio Button in a dialog 
// box.  It allows the user to select one of a fixed number of choices (such as  
// On / Off,   or   Red / Green / Blue).  Each time the user clicks on this type
// of menu item, it alternates the selection (i.e. toggles between On and Off, or 
// rotates between Red, Green and Blue).  The third field in this entry points 
// to a callback function that alternates the value.
//
// A MENU_ITEM_TYPE_SUB_MENU entry is used to select a different menu.  For 
// example, a main menu might reference a "Settings" sub menu. The third field in 
// this entry points to the new menu table that defines the sub menu.
//
// As described above, the first line in a menu table indicates the type of menu:
//
// A MENU_ITEM_TYPE_MAIN_MENU_HEADER specifies the main menu.  The second field 
// is the text displayed on the TitleBar when the menu is shown.  The third  
// field is a pointer to a callback function executed when the user presses the 
// "Back" button below the menu, indicating that they are done with the menu.
// Typically this callback function would reselect the device's main application.
// Note: If the third field is 0, then the "Back" button is not displayed.
//
// A MENU_ITEM_TYPE_SUB_MENU_HEADER is used in the first line of a sub menu table. 
// (Sub menus that are menus that are called from a main menu, or another sub 
// menu)  The second field is the sub menu's title (which is displayed on the 
// TitleBar).  The third field is a pointer back to the parent menu table 
// (typically this would be the main menu).  This is used to reselect the parent 
// menu when the user presses the "Back" button, indicating that they are done 
// with the sub menu.
//
//
// In addition to menus, there are a few other things that can be shown in the 
// DisplaySpace.  A Slider allows the users to select a numeric value (such as 
// 0 to 255,  or  -1000 to 1000).  In addition to printing the number on the LCD, 
// a Slider shows a graphical representation of the value. The user sets the 
// number by pressing the Up and Down buttons.  Sliders are displayed by calling 
// UISelectSliderDisplay().
//
//
// A MessageDisplay presents a text message in the center of the DisplaySpace.  
// The function UISelectMessageDisplay() is called with the string to display.  
// The source string can be located in ROM or RAM, as indicated by the "StringType"
// argument.  If the string is too wide to fit on one line of the LCD, it will 
// automatically be broken into multiple lines.  The string can also contain '\r'
// characters to break the line.  The "Justify" argument specifies left, right 
// or centered alignment.  A pointer to a callback function must be given in the 
// "CallbackFunc" argument.  The callback function is executed when the user  
// presses one of the two bottom buttons.  These buttons are labeled with names   
// such as:  OK / Back   or   Yes / No.
//

/* ------------------------------------------------------------------------ */

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



/* ------------------------------------------------------------------------ */
/*             	    Private variables local to this module					*/
/* ------------------------------------------------------------------------ */
#pragma udata


//
// Menu Display static variables
//
static MENU_ITEM *CurrentMenuTable;
static byte CurrentMenuItemIdx;


//
// Slider Display static variables
//
static int SliderDisplayMinValue;
static int SliderDisplayMaxValue;
static int SliderDisplayStep;
static int SliderDisplayStepAutoRepeat;
static int SliderDisplayValue;
static byte SliderDisplayShowNumericValueFlg;
static rom void (*SliderDisplayCallbackFunc)(byte, int);


//
// Message Display static variables
//
static rom void (*MessageDisplayCallbackFunc)(byte);
static byte MessageDisplayType;


//
// pointer to the current event handler
//
static rom void (*PointerToCurrentEventHandler)(byte);


/* ------------------------------------------------------------------------ */
/*						   Local function declarations   					*/
/* ------------------------------------------------------------------------ */

static void SelectMenuDisplay(MENU_ITEM *, byte);
static void DrawMenuItem(byte);
static void MenuDisplayEventHandler(byte Event);
static void MenuChangeSelection(byte);
static void SliderEventDisplayHandler(byte);
static void SliderDrawValue(void);
static void MessageDisplayEventHandler(byte);
static void DrawButtonOnButtonBar(rom char *, byte, byte *, byte *);


/* ------------------------------------------------------------------------ */
/*						  	 Main event functions 		 				*/
/* ------------------------------------------------------------------------ */
#pragma code


//
// set the current event handler
//
void UISetEventHandler(rom void (*PntrToNewEventHandler)())
{	PointerToCurrentEventHandler = PntrToNewEventHandler;
}



//
// direct events to the current event handler
//
void UIExecuteEvent(byte Event)
{	(*PointerToCurrentEventHandler)(Event);
}



/* ------------------------------------------------------------------------ */
/*						   		   Menu Display  							*/
/* ------------------------------------------------------------------------ */

//
// constants used to draw the Menu Display
//
#define UI_MENU_FONT				Font_MediumBold	

#define UI_MENU_TOP_LINE_Y			(UI_DISPLAY_SPACE_TOP_Y + 1)
#define UI_MENU_LINE_SPACING_Y		16
#define UI_MENU_LEFT_MARGIN			4
#define UI_MENU_TEXT_HEIGHT_Y		11


//
// colors for a blue menu with white text
//
#define UI_MENU_ITEM_FOREGROUND_RGB8			RGB8_BLACK
#define UI_MENU_ITEM_BACKGROUND_RGB8			UI_DISPLAY_SPACE_BACKGROUND_RGB8
#define UI_MENU_SELECT_ITEM_FOREGROUND_RGB8		RGB8_WHITE
#define UI_MENU_SELECT_ITEM_BACKGROUND_1_RGB8	RGB8_BLUE2
#define UI_MENU_SELECT_ITEM_BACKGROUND_2_RGB8	RGB8_BLUE6
#define UI_MENU_SELECT_ITEM_BACKGROUND_RGB8		RGB8_BLUE5
#define UI_MENU_SELECT_ITEM_BACKGROUND_8_RGB8	RGB8_BLUE6
#define UI_MENU_SELECT_ITEM_BACKGROUND_9_RGB8	RGB8_BLACK


/* ------------------------------------------------------------------------ */


//
// the select the Menu Display
//		Enter:	Menu -> menu table (in ROM)
//
void UISelectMenuDisplay(MENU_ITEM *Menu)
{	//
	// select the Menu Display, using the give menu with the first item highlighted
	//
	SelectMenuDisplay(Menu, 1);
}



//
// the reselect the Menu Display, using the previous menu and item selected 
//
void UISelectPreviousMenuDisplay(void)
{	//
	// select the Menu Display, using the give menu with the first item highlighted
	//
	SelectMenuDisplay(CurrentMenuTable, CurrentMenuItemIdx);
}



//
// the select parent menu of the currentley selected menu 
//		Enter:	Menu -> menu table (in ROM)
//
void UISelectParentMenu(void)
{	rom MENU_ITEM *Menu;
		
	//
	// get the handle of the parent menu
	//
	Menu = (rom MENU_ITEM *)CurrentMenuTable[0].MenuItemPntr;
	
	if (Menu != 0)
		SelectMenuDisplay(Menu, 1);
}



//
// select the Menu Display and draw it
//		Enter:	Menu -> menu table (in ROM)
//
static void SelectMenuDisplay(MENU_ITEM *Menu, byte MenuItemIdxToSelect)
{	rom char *RightButtonText;
	byte MenuIdx;
	byte Y;

	//
	// remember this menu and select the first item in the menu
	//
	CurrentMenuTable = Menu;
	CurrentMenuItemIdx = MenuItemIdxToSelect;
	
	
	//
	// display menu name in title bar
	//
	UIDrawTitleBar(Menu[0].MenuItemText, ROM_STRING);


	//
	// blank the top line of the display not used by the menu
	//
	LCDDrawFilledRectangleRGB8(
	  UI_DISPLAY_SPACE_LEFT_X, 	UI_DISPLAY_SPACE_TOP_Y, 
	  UI_DISPLAY_SPACE_RIGHT_X, UI_MENU_TOP_LINE_Y - 1, 
	  UI_DISPLAY_SPACE_BACKGROUND_RGB8);


	//
	// draw each of the menu items
	//
	MenuIdx = 1;
	while(CurrentMenuTable[MenuIdx].MenuItemType != MENU_ITEM_TYPE_END_OF_MENU)
	{	DrawMenuItem(MenuIdx);
		MenuIdx++;
	}


	//
	// blank remain part of the display space not used by the menu
	//
	Y = UI_MENU_TOP_LINE_Y + ((MenuIdx - 1) * UI_MENU_LINE_SPACING_Y);
	LCDDrawFilledRectangleRGB8(
	  UI_DISPLAY_SPACE_LEFT_X, 	Y, 
	  UI_DISPLAY_SPACE_RIGHT_X, UI_DISPLAY_SPACE_BOTTOM_Y, 
	  UI_DISPLAY_SPACE_BACKGROUND_RGB8);
	
	
	//
	// draw the ButtonBar, don't show the "Back" button if there is no back function
	//
	if (Menu[0].MenuItemPntr == 0)
		RightButtonText = "";
	else
		RightButtonText = "Back";

	UIDrawButtonBar("Select", RightButtonText);
	
	
	//
	// set the event handler
	//
	UISetEventHandler(MenuDisplayEventHandler);
}



//
// draw one menu item
//
static void DrawMenuItem(byte MenuIdx)
{	byte ColorTableAbove[3];
	byte ColorTableBelow[2];
	byte ForegroundRGB8;
	byte BackgroundRGB8;
	byte BottomOfTextY;
	byte X, Y;
	byte X2;
	byte Width;
	rom char *RightText;
	char * (*CallbackFunc)(byte);


	//
	// determine the color to draw the menu item
	//
	if (MenuIdx != CurrentMenuItemIdx)
	{	ForegroundRGB8 = UI_MENU_ITEM_FOREGROUND_RGB8;
		BackgroundRGB8 = UI_MENU_ITEM_BACKGROUND_RGB8;

		ColorTableAbove[0] = UI_MENU_ITEM_BACKGROUND_RGB8;
		ColorTableAbove[1] = UI_MENU_ITEM_BACKGROUND_RGB8;
		ColorTableAbove[2] = UI_MENU_ITEM_BACKGROUND_RGB8;

		ColorTableBelow[0] = UI_MENU_ITEM_BACKGROUND_RGB8;
		ColorTableBelow[1] = UI_MENU_ITEM_BACKGROUND_RGB8;
	}
	
	else
	{	ForegroundRGB8 = UI_MENU_SELECT_ITEM_FOREGROUND_RGB8;
		BackgroundRGB8 = UI_MENU_SELECT_ITEM_BACKGROUND_RGB8;

		ColorTableAbove[0] = UI_MENU_SELECT_ITEM_BACKGROUND_1_RGB8;
		ColorTableAbove[1] = UI_MENU_SELECT_ITEM_BACKGROUND_2_RGB8;
		ColorTableAbove[2] = UI_MENU_SELECT_ITEM_BACKGROUND_RGB8;

		ColorTableBelow[0] = UI_MENU_SELECT_ITEM_BACKGROUND_8_RGB8;
		ColorTableBelow[1] = UI_MENU_SELECT_ITEM_BACKGROUND_9_RGB8;
	}
	
	
	//
	// determine if there is text to be right justified on the menu line
	//
	switch(CurrentMenuTable[MenuIdx].MenuItemType)
	{	case MENU_ITEM_TYPE_SUB_MENU:
			RightText = ">";
			break;

		case MENU_ITEM_TYPE_ALTERNATE:
			//
			// use the callback function to get the right text
			//
			CallbackFunc = (char* (*)(byte)) CurrentMenuTable[MenuIdx].MenuItemPntr;
			RightText = (*CallbackFunc)(MENU_ACTION_ALTERNATE_GET_TEXT); 
			break;

		default:
			RightText = "";
	}


	//
	// determine the top line of this menu item
	//
	Y = UI_MENU_TOP_LINE_Y + ((MenuIdx - 1) * UI_MENU_LINE_SPACING_Y);


	//
	// draw 3 lines above the text
	//
	DrawHorzGradientRGB8(ColorTableAbove, UI_DISPLAY_SPACE_LEFT_X, UI_DISPLAY_SPACE_RIGHT_X, Y, 3);
	Y += 3;
	

	//
	// fill in the menu line left of the text with the background color
	//
	BottomOfTextY = Y + UI_MENU_TEXT_HEIGHT_Y - 1;
	
	LCDDrawFilledRectangleRGB8(
	  UI_DISPLAY_SPACE_LEFT_X, 	Y, 
	  UI_MENU_LEFT_MARGIN - 1, BottomOfTextY, 
	  BackgroundRGB8);

	
	//
	// draw the text of the menu item
	//	
	X = LCDDrawStringRGB8(CurrentMenuTable[MenuIdx].MenuItemText, ROM_STRING, 
	  UI_MENU_LEFT_MARGIN, BottomOfTextY, JUSTIFY_LEFT, UI_MENU_FONT, 
	  ForegroundRGB8, BackgroundRGB8);


	//
	// check if there is right justified text
	//
	if (RightText[0] != 0)
	{	//
		// there is text on the right, determine the width of the text
		//
		Width = LCDGetStringWidth(RightText, ROM_STRING, UI_MENU_FONT);
		X2 = UI_DISPLAY_SPACE_RIGHT_X - UI_MENU_LEFT_MARGIN - (Width - 1) + 0;
	
		//
		// file the space between the left and right text with the background color
		//
		LCDDrawFilledRectangleRGB8(
		  X, Y, 
		  X2 - 1, BottomOfTextY, 
		  BackgroundRGB8);
	
		//
		// draw the right justified text of the menu item
		//	
		X = LCDDrawStringRGB8(RightText, ROM_STRING, 
		  X2, BottomOfTextY, 
		  JUSTIFY_LEFT, UI_MENU_FONT, 
		  ForegroundRGB8, BackgroundRGB8);
	}


	//
	// fill in the remainder of the menu line with the background color
	//
	LCDDrawFilledRectangleRGB8(
	  X, Y, 
	  UI_DISPLAY_SPACE_RIGHT_X, BottomOfTextY, 
	  BackgroundRGB8);
	Y = BottomOfTextY + 1;

	  
	//
	// draw 2 lines below the text
	//
	DrawHorzGradientRGB8(ColorTableBelow, UI_DISPLAY_SPACE_LEFT_X, UI_DISPLAY_SPACE_RIGHT_X, Y, 2);
}



//
// event handler for the Menu Display
//
static void MenuDisplayEventHandler(byte Event)
{	int NewValue;
	rom void (*CommandPntr)(void);
	rom void (*Callback)(byte);
	rom MENU_ITEM *SubMenuTable;

	//
	// determine the event type
	//
	switch(Event)
	{	//
		// check for a push of the Up button, causing the menu item above to be selected
		//
		case EVENT_UP_BUTTON_PUSHED:
			MenuChangeSelection(CurrentMenuItemIdx - 1);
			break;

		//
		// check for a push of the Down button, causing the menu item below to be selected
		//
		case EVENT_DOWN_BUTTON_PUSHED:
			MenuChangeSelection(CurrentMenuItemIdx + 1);
			break;

		//
		// check for a push of the Left button
		//
		case EVENT_LEFT_BUTTON_PUSHED:
			//
			// left button pushed, determine the menu item type
			//
			switch(CurrentMenuTable[CurrentMenuItemIdx].MenuItemType)
			{	case MENU_ITEM_TYPE_COMMAND:
					//
					// left button pressed on a "Command" menu item
					//
					CommandPntr = (rom void (*)(void))CurrentMenuTable[CurrentMenuItemIdx].MenuItemPntr;
					if (CommandPntr != 0)
						(*CommandPntr)(); 
					break;

				case MENU_ITEM_TYPE_ALTERNATE:
					//
					// left button pressed on a "Alternate" menu item
					//
					Callback = (rom void (*)(byte))CurrentMenuTable[CurrentMenuItemIdx].MenuItemPntr;
					if (Callback != 0)
					{	(*Callback)(MENU_ACTION_ALTERNATE_SELECTION); 
						DrawMenuItem(CurrentMenuItemIdx);
					}
					break;

				case MENU_ITEM_TYPE_SUB_MENU:
					//
					// left button pressed on a "Sub menu" menu item, select that menu
					//
					SubMenuTable = (rom MENU_ITEM *)CurrentMenuTable[CurrentMenuItemIdx].MenuItemPntr;
					UISelectMenuDisplay(SubMenuTable);
					break;
			}
			break;


		//
		// check for a push of the Right button
		//
		case EVENT_RIGHT_BUTTON_PUSHED:
			//
			// right button pushed, determine the menu type
			//
			switch(CurrentMenuTable[0].MenuItemType)
			{	case MENU_ITEM_TYPE_MAIN_MENU_HEADER:
					//
					// run the callback function to select the parent display
					//
					CommandPntr = (rom void (*)(void))CurrentMenuTable[0].MenuItemPntr;
					if (CommandPntr != 0)
						(*CommandPntr)(); 
					break;


				case MENU_ITEM_TYPE_SUB_MENU_HEADER:
					//
					// select the parent menu for this submenu
					//
					if (CurrentMenuTable[0].MenuItemPntr != 0)
						UISelectParentMenu();
					break;
			}
			break;
	}
}



//
// change the selected menu item
//
static void MenuChangeSelection(byte NewMenuItemIdx)
{	byte PreviousMenuItemIdx;
	
	if ((NewMenuItemIdx >= 1) && 
	  (CurrentMenuTable[NewMenuItemIdx].MenuItemType != MENU_ITEM_TYPE_END_OF_MENU) &&
	  (NewMenuItemIdx != CurrentMenuItemIdx))
	{	//
		// select the new menu item
		//
		PreviousMenuItemIdx = CurrentMenuItemIdx;
		CurrentMenuItemIdx = NewMenuItemIdx;
		
		//
		// undraw the previously selected menu item, then draw the new one
		//
		DrawMenuItem(PreviousMenuItemIdx);
		DrawMenuItem(NewMenuItemIdx);
	}	  
}



/* ------------------------------------------------------------------------ */
/*						   		 Slider Display  							*/
/* ------------------------------------------------------------------------ */

//
// constants used to draw the Slider Display
//
#define UI_SLIDER_HEIGHT 				7
#define UI_SLIDER_WIDTH 				110
#define UI_SLIDER_PERIMETER_HEIGHT 		(UI_SLIDER_HEIGHT + 2)
#define UI_SLIDER_PERIMETER_WIDTH 		(UI_SLIDER_WIDTH + 2)

#define UI_SLIDER_CENTER_X				(((UI_DISPLAY_SPACE_LEFT_X + UI_DISPLAY_SPACE_RIGHT_X) / 2) + 1)
#define UI_SLIDER_TOP_Y					78

#define UI_SLIDER_LABEL_CENTER_Y		(UI_DISPLAY_SPACE_TOP_Y + 46)
#define UI_SLIDER_LABEL_FONT			Font_MediumBold	
#define UI_SLIDER_LABEL_FOREGROUND_RGB8	RGB8_BLACK	


#define UI_SLIDER_MINMAX_VALUES_Y		(UI_SLIDER_TOP_Y + UI_SLIDER_PERIMETER_HEIGHT + 11)
#define UI_SLIDER_MINMAX_VALUES_FONT	Font_SmallBold	

#define UI_SLIDER_NUMERIC_VALUE_Y		(UI_SLIDER_TOP_Y + UI_SLIDER_PERIMETER_HEIGHT + 20)
#define UI_SLIDER_NUMERIC_VALUE_FONT	Font_MediumBold	

#define UI_SLIDER_PERIMETER_RGB8			RGB8_GRAY1

// blue needle
//#define UI_SLIDER_NEEDLE_BB_RGB8			RGB8_BLUE8
//#define UI_SLIDER_NEEDLE_B_RGB8			RGB8_BLUE6
//#define UI_SLIDER_NEEDLE_RGB8				RGB8_BLUE5

// green needle
#define UI_SLIDER_NEEDLE_BB_RGB8			RGB8_GREEN7
#define UI_SLIDER_NEEDLE_B_RGB8				RGB8_GREEN5
#define UI_SLIDER_NEEDLE_RGB8				RGB8_GREEN4

#define UI_SLIDER_NEEDLE_BACKGROUND_BB_RGB8	RGB8_WHITE
#define UI_SLIDER_NEEDLE_BACKGROUND_B_RGB8	RGB8_GRAY6
#define UI_SLIDER_NEEDLE_BACKGROUND_RGB8	RGB8_GRAY5


/* ------------------------------------------------------------------------ */


//
// the Slider Display
//		Enter:	TitleBarText -> ROM string to display on the title bar
//				MinValue = the minimum value for the slider
//				MaxValue = the max value for the slider
//				Step = amount added/subtracted to the value with each button press
//				StepAutoRepeat = amount added/subtracted to the value when button his held down
//					0 to disable auto repeat
//				InitialValue = initial value to display on the slider
//				Label -> text (ROM string) printed above the slider
//				ShowMinMaxValuesFlg = TRUE if should display the MinValue & MaxValue below the slider
//				ShowNumericValueFlg = TRUE if should display the numerical value below the slider
//				CallbackFunc -> the callback function
//
void UISelectSliderDisplay(char *TitleBarText, int MinValue, int MaxValue, int Step, int StepAutoRepeat, int InitialValue, rom char *Label, byte ShowMinMaxValuesFlg, byte ShowNumericValueFlg, rom void (*CallbackFunc)())
{	byte PerimeterLeft;
	byte PerimeterRight;
	byte PerimeterTop;
	byte PerimeterBottom;
	byte SBuf[8];
	byte MaxLineWidth;
	byte LineSpacing;
	byte LineCount;
	byte Y;
	
	//
	// remember the slider values
	//
	SliderDisplayMinValue = MinValue;
	SliderDisplayMaxValue = MaxValue;
	SliderDisplayStep = Step;
	SliderDisplayStepAutoRepeat = StepAutoRepeat;
	SliderDisplayShowNumericValueFlg = ShowNumericValueFlg; 
	SliderDisplayCallbackFunc = CallbackFunc;

	
	//
	// set the title bar label and blank the DisplaySpace
	//
	UIDrawTitleBar(TitleBarText, ROM_STRING);
	UIBlankDisplaySpace();

	
	//
	// determine the starting Y coord for drawing the multi line label above the slider
	//
	MaxLineWidth = UI_DISPLAY_SPACE_WIDTH_WITH_BORDERS;
	LineSpacing = UI_SLIDER_LABEL_FONT[FONT_TABLE_LINE_SPACING_IDX];
	LineCount = GetTextLineCountAfterBreakingText(Label, ROM_STRING, MaxLineWidth, UI_SLIDER_LABEL_FONT);
	Y = UI_SLIDER_LABEL_CENTER_Y - ((LineCount * LineSpacing) / 2);
	

	//
	// draw the label text centered above the slider
	//
	DrawTextBrokenIntoMultipleLines(Label, ROM_STRING, 
	  UI_SLIDER_CENTER_X, Y, LineSpacing,
	  JUSTIFY_CENTER, MaxLineWidth, UI_SLIDER_LABEL_FONT, 
	  UI_SLIDER_LABEL_FOREGROUND_RGB8, UI_DISPLAY_SPACE_BACKGROUND_RGB8);
	
	//
	// draw the slider's perimeter box 
	//
	PerimeterLeft = UI_SLIDER_CENTER_X - (UI_SLIDER_PERIMETER_WIDTH / 2);
	PerimeterRight = PerimeterLeft + UI_SLIDER_PERIMETER_WIDTH - 1;
	PerimeterTop = UI_SLIDER_TOP_Y;
	PerimeterBottom = UI_SLIDER_TOP_Y + UI_SLIDER_PERIMETER_HEIGHT - 1;

	LCDDrawFilledRectangleRGB8(PerimeterLeft, PerimeterTop, PerimeterRight, PerimeterTop, UI_SLIDER_PERIMETER_RGB8);
	LCDDrawFilledRectangleRGB8(PerimeterLeft, PerimeterBottom, PerimeterRight, PerimeterBottom, UI_SLIDER_PERIMETER_RGB8);
	LCDDrawFilledRectangleRGB8(PerimeterLeft, PerimeterTop, PerimeterLeft, PerimeterBottom, UI_SLIDER_PERIMETER_RGB8);
	LCDDrawFilledRectangleRGB8(PerimeterRight, PerimeterTop, PerimeterRight, PerimeterBottom, UI_SLIDER_PERIMETER_RGB8);


	//
	// draw the text showing the Min / Max values
	//
	if (ShowMinMaxValuesFlg)
	{	ConvertSignedIntToString(MinValue, SBuf);	
		LCDDrawStringRGB8(SBuf, RAM_STRING, 
		  PerimeterLeft + 2, UI_SLIDER_MINMAX_VALUES_Y, 
		  JUSTIFY_LEFT, UI_SLIDER_MINMAX_VALUES_FONT, 
		  UI_SLIDER_LABEL_FOREGROUND_RGB8, UI_DISPLAY_SPACE_BACKGROUND_RGB8);
	
		ConvertSignedIntToString(MaxValue, SBuf);	
		LCDDrawStringRGB8(SBuf, RAM_STRING, 
		  PerimeterRight - 2, UI_SLIDER_MINMAX_VALUES_Y, 
		  JUSTIFY_RIGHT, UI_SLIDER_MINMAX_VALUES_FONT, 
		  UI_SLIDER_LABEL_FOREGROUND_RGB8, UI_DISPLAY_SPACE_BACKGROUND_RGB8);
	}

	
	//
	// update the slider, displaying the initial value
	//
	SliderDisplayValue = InitialValue;
	SliderDrawValue();
	
	
	//
	// draw the ButtonBar and set the event handler
	//
	UIDrawButtonBar("Set", "Cancel");
	UISetEventHandler(SliderEventDisplayHandler);
}



//
// event handler for the Slider Display
//
static void SliderEventDisplayHandler(byte Event)
{	int NewValue;
	
	switch(Event)
	{	//
		// check for a push of the UP button, causing slider to move right
		//
		case EVENT_UP_BUTTON_PUSHED:
		case EVENT_UP_BUTTON_REPEAT:
			if (Event == EVENT_UP_BUTTON_PUSHED)
				NewValue = SliderDisplayValue + SliderDisplayStep;
			else
				NewValue = SliderDisplayValue + SliderDisplayStepAutoRepeat;
			
			if (NewValue > SliderDisplayMaxValue)
				 NewValue = SliderDisplayMaxValue;

			if (NewValue != SliderDisplayValue)
			{	//
				// update the display with the new value
				//
				SliderDisplayValue = NewValue;
				SliderDrawValue();
				
				//
				// send the user's callback function a "value changed" action
				//
				(*SliderDisplayCallbackFunc)(SLIDER_DISPLAY_ACTION_VALUE_CHANGED, NewValue);
			}
			break;

		case EVENT_DOWN_BUTTON_PUSHED:
		case EVENT_DOWN_BUTTON_REPEAT:
			if (Event == EVENT_DOWN_BUTTON_PUSHED)
				NewValue = SliderDisplayValue - SliderDisplayStep;
			else
				NewValue = SliderDisplayValue - SliderDisplayStepAutoRepeat;

			if (NewValue < SliderDisplayMinValue)
				 NewValue = SliderDisplayMinValue;

			if (NewValue != SliderDisplayValue)
			{	//
				// update the display with the new value
				//
				SliderDisplayValue = NewValue;
				SliderDrawValue();
				
				//
				// send the user's callback function a "value changed" action
				//
				(*SliderDisplayCallbackFunc)(SLIDER_DISPLAY_ACTION_VALUE_CHANGED, NewValue);
			}
			break;

		case EVENT_LEFT_BUTTON_PUSHED:
			//
			// send the user's callback function a "value set" action
			//
			(*SliderDisplayCallbackFunc)(SLIDER_DISPLAY_ACTION_VALUE_SET, SliderDisplayValue);
			break;

		case EVENT_RIGHT_BUTTON_PUSHED:
			//
			// send the user's callback function a "cancelled" action
			//
			(*SliderDisplayCallbackFunc)(SLIDER_DISPLAY_ACTION_CANCELED, SliderDisplayValue);
			break;
	}
}



//
// update the value of the slider
//		Enter:	Value = new value for the slider
//
static void SliderDrawValue(void)
{	byte ColorTable[8];
	byte LineCount;
	byte Left;
	byte Right;
	byte Top;
	byte Bottom;
	byte NeedleLength;
	byte BlankLeft;
	byte SBuf[20];
	char ram *SBufPntr;

	
	//
	// determine how long to draw the slider
	//
	if (SliderDisplayValue <= SliderDisplayMinValue) 
		NeedleLength = 0;
	else if (SliderDisplayValue >= SliderDisplayMaxValue)
		NeedleLength = UI_SLIDER_WIDTH - 1;
	else
		NeedleLength = ((short long)(SliderDisplayValue - SliderDisplayMinValue) * (short long)UI_SLIDER_WIDTH) / (short long)(SliderDisplayMaxValue - (SliderDisplayMinValue - 1));

	//
	// determine the dimensions of the needle
	//
	Left = UI_SLIDER_CENTER_X - (UI_SLIDER_WIDTH / 2);
	Right = Left + NeedleLength;
	Top = UI_SLIDER_TOP_Y + 1;
	Bottom = UI_SLIDER_TOP_Y + 1 + UI_SLIDER_HEIGHT - 1;
	
	//
	// draw the needle of the slider
	//
	if (NeedleLength != 0)
	{	LineCount = 7;
		ColorTable[0] = UI_SLIDER_NEEDLE_BB_RGB8;
		ColorTable[1] = UI_SLIDER_NEEDLE_BB_RGB8;
		ColorTable[2] = UI_SLIDER_NEEDLE_B_RGB8;
		ColorTable[3] = UI_SLIDER_NEEDLE_RGB8;
		ColorTable[4] = UI_SLIDER_NEEDLE_RGB8;
		ColorTable[5] = UI_SLIDER_NEEDLE_RGB8;
		ColorTable[6] = UI_SLIDER_NEEDLE_B_RGB8;

		DrawHorzGradientRGB8(ColorTable, Left, Right, Top, LineCount);
	}
	
	//
	// fill in after the needle
	//
	if (NeedleLength != UI_SLIDER_WIDTH - 1)
	{	LineCount = 7;
		ColorTable[0] = UI_SLIDER_NEEDLE_BACKGROUND_BB_RGB8;
		ColorTable[1] = UI_SLIDER_NEEDLE_BACKGROUND_BB_RGB8;
		ColorTable[2] = UI_SLIDER_NEEDLE_BACKGROUND_B_RGB8;
		ColorTable[3] = UI_SLIDER_NEEDLE_BACKGROUND_RGB8;
		ColorTable[4] = UI_SLIDER_NEEDLE_BACKGROUND_RGB8;
		ColorTable[5] = UI_SLIDER_NEEDLE_BACKGROUND_RGB8;
		ColorTable[6] = UI_SLIDER_NEEDLE_BACKGROUND_B_RGB8;
		
		BlankLeft = Right + 1;
		Right = Left + UI_SLIDER_WIDTH - 1;
		DrawHorzGradientRGB8(ColorTable, BlankLeft, Right, Top, LineCount);
	}


	//
	// display the numeric value of the slider
	//
	if (SliderDisplayShowNumericValueFlg)
	{	//
		// convert number to string, add padding left and right of the number
		//
		SBufPntr = StringToRam("      ", SBuf);
		SBufPntr = ConvertSignedIntToString(SliderDisplayValue, SBufPntr);	
		StringToRam("      ", SBufPntr);

		LCDDrawStringRGB8(SBuf, RAM_STRING, 
		  UI_SLIDER_CENTER_X, UI_SLIDER_NUMERIC_VALUE_Y, 
		  JUSTIFY_CENTER, UI_SLIDER_NUMERIC_VALUE_FONT, 
		  UI_SLIDER_LABEL_FOREGROUND_RGB8, UI_DISPLAY_SPACE_BACKGROUND_RGB8);
	}
}



/* ------------------------------------------------------------------------ */
/*						   		 Message Display  							*/
/* ------------------------------------------------------------------------ */

//
// constants used to draw the Slider Display
//
#define UI_MESSAGE_DISPLAY_CENTER_Y		((UI_DISPLAY_SPACE_TOP_Y + UI_DISPLAY_SPACE_BOTTOM_Y) / 2)
#define UI_MESSAGE_DISPLAY_FOREGROUND_RGB8	RGB8_BLACK	


/* ------------------------------------------------------------------------ */


//
// the Message Display
//		Enter:	TitleBarText -> ROM string to display on the title bar
//				Message -> text to display
//				StringType = ROM_STRING or RAM_STRING
//				Justify = JUSTIFY_LEFT, JUSTIFY_CENTER, or JUSTIFY_RIGHT
//				MessageType = MESSAGE_DISPLAY_BACK, MESSAGE_DISPLAY_OK_BACK, MESSAGE_DISPLAY_YES_NO, ...
//				Font -> the font used to display the message
//				CallbackFunc -> the callback function
//
void UISelectMessageDisplay(char *TitleBarText, char *Message, byte StringType, byte Justify, byte MessageType, rom byte *Font, rom void (*CallbackFunc)())
{	byte MaxLineWidth;
	byte LineSpacing;
	byte LineCount;
	byte X, Y;

	//
	// remember the values
	//
	MessageDisplayCallbackFunc = CallbackFunc;
	MessageDisplayType = MessageType;


	//
	// set the title bar label and blank the DisplaySpace
	//
	UIDrawTitleBar(TitleBarText, ROM_STRING);
	UIBlankDisplaySpace();
	
	
	//
	// determine how the message is justified
	//
	switch (Justify)
	{	case JUSTIFY_LEFT:
			X = 6;
			MaxLineWidth = (UI_DISPLAY_SPACE_RIGHT_X - UI_DISPLAY_SPACE_LEFT_X + 1) - X - X;
			break;
	
		case JUSTIFY_CENTER:
			X = (UI_DISPLAY_SPACE_RIGHT_X + UI_DISPLAY_SPACE_LEFT_X) / 2;
			MaxLineWidth = UI_DISPLAY_SPACE_WIDTH_WITH_BORDERS;
			break;

		case JUSTIFY_RIGHT:
			X = UI_DISPLAY_SPACE_RIGHT_X - 6;
			MaxLineWidth = (UI_DISPLAY_SPACE_RIGHT_X - UI_DISPLAY_SPACE_LEFT_X + 1) - 12;
			break;
	}
	
	//
	// determine the starting Y coord for drawing the multi line label above the slider
	//
	LineSpacing = Font[FONT_TABLE_LINE_SPACING_IDX];
	LineCount = GetTextLineCountAfterBreakingText(Message, StringType, MaxLineWidth, Font);
	Y = UI_MESSAGE_DISPLAY_CENTER_Y - 2 + (LineSpacing / 2) - (((LineCount - 1) * LineSpacing) / 2);
	

	//
	// draw the message text centered in the Display Space
	//
	DrawTextBrokenIntoMultipleLines(Message, StringType, 
	  X, Y, LineSpacing, Justify, MaxLineWidth, Font, 
	  UI_MESSAGE_DISPLAY_FOREGROUND_RGB8, UI_DISPLAY_SPACE_BACKGROUND_RGB8);
		
	
	//
	// draw the ButtonBar and set the event handler
	//
	switch(MessageDisplayType)
	{	case MESSAGE_DISPLAY_OK_BACK:
			UIDrawButtonBar("OK", "Cancel");
			break;
		
		case MESSAGE_DISPLAY_YES_NO:
			UIDrawButtonBar("Yes", "No");
			break;
		
		default:
			UIDrawButtonBar("Back", "");
	}

	
	//
	// set the event handler
	//
	UISetEventHandler(MessageDisplayEventHandler);
}



//
// event handler for the Message Display
//
static void MessageDisplayEventHandler(byte Event)
{	byte LeftButtonAction;
	byte RightButtonAction;

	//
	// determine the possible actions to send the callback func based on the MessageDisplay type 
	//
	switch(MessageDisplayType)
	{	case MESSAGE_DISPLAY_OK_BACK:
			LeftButtonAction = MESSAGE_DISPLAY_ACTION_OK;
			RightButtonAction = MESSAGE_DISPLAY_ACTION_BACK;
			break;

		case MESSAGE_DISPLAY_YES_NO:
			LeftButtonAction = MESSAGE_DISPLAY_ACTION_YES;
			RightButtonAction = MESSAGE_DISPLAY_ACTION_NO;
			break;
		
		default:
			LeftButtonAction = MESSAGE_DISPLAY_ACTION_BACK;
			RightButtonAction = MESSAGE_DISPLAY_ACTION_BACK;
	}


	//
	// send the action to the callback based on the button pressed
	//
	switch(Event)
	{	case EVENT_LEFT_BUTTON_PUSHED:
			(*MessageDisplayCallbackFunc)(LeftButtonAction);
			break;

		case EVENT_RIGHT_BUTTON_PUSHED:
			(*MessageDisplayCallbackFunc)(RightButtonAction);
			break;
			
		default:
			return;
	}
}



/* ------------------------------------------------------------------------ */
/*						  General DisplaySpace functions	 				*/
/* ------------------------------------------------------------------------ */

//
// blank the DisplaySpace
//
void UIBlankDisplaySpace(void)
{	LCDDrawFilledRectangleRGB8(
	  UI_DISPLAY_SPACE_LEFT_X, UI_DISPLAY_SPACE_TOP_Y, 
	  UI_DISPLAY_SPACE_RIGHT_X, UI_DISPLAY_SPACE_BOTTOM_Y,
	  UI_DISPLAY_SPACE_BACKGROUND_RGB8);
}


/* ------------------------------------------------------------------------ */
/*							  TitleBar functions			   				*/
/* ------------------------------------------------------------------------ */

//
// constants used to draw the TitleBar
//
#define UI_TITLE_BAR_FONT 				Font_MediumBold


//
// colors for dark blue background with white text
//
#define UI_TITLE_BAR_FOREGROUND_RGB8	RGB8_WHITE
#define UI_TITLE_BAR_BACKGROUND_BB_RGB8	RGB8_BLUE4
#define UI_TITLE_BAR_BACKGROUND_B_RGB8	RGB8_BLUE2
#define UI_TITLE_BAR_BACKGROUND_RGB8	RGB8_BLUE2
#define UI_TITLE_BAR_BACKGROUND_D_RGB8	RGB8_BLUE1


/* ------------------------------------------------------------------------ */


//
// blank the TitleBar
//		Enter:	TitleBarText -> ROM or RAM string to display on the title bar
//				StringType = ROM_STRING or RAM_STRING
//
void UIDrawTitleBar(rom char *TitleBarText, byte StringType)
{	byte ColorTable[3];
	byte TextWidth;
	byte TextHeight;
	byte TitleTextLeftX;
	byte TitleTextRightX;
	byte TitleTextTopY;
	byte TitleTextBottomY;
	byte Y;
		
	//
	// draw 3 lines above the text
	//
	ColorTable[0] = UI_TITLE_BAR_BACKGROUND_BB_RGB8;
	ColorTable[1] = UI_TITLE_BAR_BACKGROUND_B_RGB8;
	ColorTable[2] = UI_TITLE_BAR_BACKGROUND_RGB8;
	DrawHorzGradientRGB8(ColorTable, UI_TITLE_BAR_LEFT_X, UI_TITLE_BAR_RIGHT_X, UI_TITLE_BAR_TOP_Y, 3);
	Y = UI_TITLE_BAR_TOP_Y + 3;


	//
	// determine the size and location of the title text
	//
	LCDGetStringExtents(TitleBarText, StringType, UI_TITLE_BAR_FONT, &TextWidth, &TextHeight);
	TitleTextLeftX = UI_TITLE_BAR_CENTER_X - TextWidth/2;
	TitleTextRightX = TitleTextLeftX + TextWidth - 1;
	TitleTextTopY = Y;
	TitleTextBottomY = TitleTextTopY + TextHeight - 1;


	//
	// fill in the TitleBar left of the text
	//
	LCDDrawFilledRectangleRGB8(
	  UI_TITLE_BAR_LEFT_X, 	TitleTextTopY, 
	  TitleTextLeftX - 1, 	TitleTextBottomY, 
	  UI_TITLE_BAR_BACKGROUND_RGB8);


	//
	// fill in the TitleBar right of the text
	//
	LCDDrawFilledRectangleRGB8(
	  TitleTextRightX + 1, 	 TitleTextTopY, 
	  UI_TITLE_BAR_RIGHT_X,  TitleTextBottomY, 
	  UI_TITLE_BAR_BACKGROUND_RGB8);


	//
	// draw the text in the TitleBar
	//
	LCDDrawStringRGB8(
	  TitleBarText, StringType, 
	  TitleTextLeftX, TitleTextBottomY, 
	  JUSTIFY_LEFT, UI_TITLE_BAR_FONT, 
	  UI_TITLE_BAR_FOREGROUND_RGB8, UI_TITLE_BAR_BACKGROUND_RGB8);
	  
	  
	//
	// draw 2 lines below the text
	//
	ColorTable[0] = UI_TITLE_BAR_BACKGROUND_RGB8;
	ColorTable[1] = UI_TITLE_BAR_BACKGROUND_D_RGB8;
	DrawHorzGradientRGB8(ColorTable, UI_TITLE_BAR_LEFT_X, UI_TITLE_BAR_RIGHT_X, TitleTextBottomY + 1, 2);
}



/* ------------------------------------------------------------------------ */
/*							 ButtonBar functions			   				*/
/* ------------------------------------------------------------------------ */

//
// constants used to draw the ButtonBar
//
#define UI_BUTTON_BAR_FONT 					Font_MediumBold
#define UI_BUTTON_BAR_BUTTON_MIN_WIDTH		47


//
// colors for light blue bar, darker blue buttons with white text
//
#define UI_BUTTON_BAR_BACKGROUND_RGB8			RGB8_BLUE7
#define UI_BUTTON_BAR_BUTTON_BACKGROUND_B_RGB8	RGB8_BLUE6
#define UI_BUTTON_BAR_BUTTON_BACKGROUND_RGB8	RGB8_BLUE5
#define UI_BUTTON_BAR_BUTTON_FOREGROUND_RGB8	RGB8_WHITE


/* ------------------------------------------------------------------------ */


//
// blank the ButtonBar
//
void UIDrawButtonBar(rom char *LeftButtonText, rom char *RightButtonText)
{	byte ButtonLeftX;
	byte ButtonRightX;
	byte X;


	X = UI_BUTTON_BAR_LEFT_X;

	//
	// draw the left button, if the text is not blank
	//
	if (LeftButtonText[0] != 0)
	{	DrawButtonOnButtonBar(LeftButtonText, UI_BOTTON_BAR_LEFT_BUTTON_X, &ButtonLeftX, &ButtonRightX);
		
		//
		// blank the ButtonBar on the left side of the button
		//
		LCDDrawFilledRectangleRGB8(
		  X, 				UI_BUTTON_BAR_TOP_Y, 
		  ButtonLeftX - 1, 	UI_BUTTON_BAR_BOTTOM_Y, 
		  UI_BUTTON_BAR_BACKGROUND_RGB8);
		  
		X = ButtonRightX + 1;
	}


	//
	// draw the right button, if the text is not blank
	//
	if (RightButtonText[0] != 0)
	{	DrawButtonOnButtonBar(RightButtonText, UI_BOTTON_BAR_RIGHT_BUTTON_X, &ButtonLeftX, &ButtonRightX);
		
		//
		// blank the ButtonBar on the left side of the button
		//
		LCDDrawFilledRectangleRGB8(
		  X, 				UI_BUTTON_BAR_TOP_Y, 
		  ButtonLeftX - 1, 	UI_BUTTON_BAR_BOTTOM_Y, 
		  UI_BUTTON_BAR_BACKGROUND_RGB8);
		  
		X = ButtonRightX + 1;
	}
	
	
	//
	// blank the remaining ButtonBar, right of the buttons drawn
	//
	LCDDrawFilledRectangleRGB8(
	  X, 						UI_BUTTON_BAR_TOP_Y, 
	  UI_BUTTON_BAR_RIGHT_X, 	UI_BUTTON_BAR_BOTTOM_Y, 
	  UI_BUTTON_BAR_BACKGROUND_RGB8);
}



//
// draw a button on the button bar
//		Enter:	ButtonText -> text to display on the button
//				ButtonCenterX = X coord for the center of the button
//				DrawnLeftX -> storage to return the left coord where the button was drawn
//				DrawnRightX -> storage to return the right coord where the button was drawn
//
static void DrawButtonOnButtonBar(rom char *ButtonText, byte ButtonCenterX, byte *DrawnLeftX, byte *DrawnRightX)
{	byte ColorTable[4];
	byte LineCount;
	byte TextWidth;
	byte TextHeight;
	byte TextLeftX;
	byte TextRightX;
	byte TextTopY;
	byte TextBottomY;
	byte ExtraWidth;
	byte PadOnLeft;
	byte ButtonLeftX;
	byte ButtonRightX;
	
	
	//
	// determine the size and position of the button's text
	//
	LCDGetStringExtents(ButtonText, ROM_STRING, UI_BUTTON_BAR_FONT, &TextWidth, &TextHeight);
	TextLeftX = ButtonCenterX - TextWidth/2;
	TextRightX = TextLeftX + TextWidth - 1;
	TextTopY = UI_BUTTON_BAR_TOP_Y + 4;
	TextBottomY = TextTopY + TextHeight - 1;

	//
	// determine how much to grow the button beyond the text on the right and left
	//
	if(UI_BUTTON_BAR_BUTTON_MIN_WIDTH > TextWidth)
		ExtraWidth = UI_BUTTON_BAR_BUTTON_MIN_WIDTH - TextWidth;
	else
		ExtraWidth = 0;
	
	PadOnLeft = ExtraWidth >> 1;
	ButtonLeftX = TextLeftX - PadOnLeft;
	ButtonRightX = TextRightX + (ExtraWidth - PadOnLeft);
	

	//
	// draw several lines above the text
	//
	LineCount = 4;
	ColorTable[0] = UI_BUTTON_BAR_BACKGROUND_RGB8;
	ColorTable[1] = UI_BUTTON_BAR_BACKGROUND_RGB8;
	ColorTable[2] = UI_BUTTON_BAR_BUTTON_BACKGROUND_B_RGB8;
	ColorTable[3] = UI_BUTTON_BAR_BUTTON_BACKGROUND_RGB8;
	DrawHorzGradientRGB8(ColorTable, ButtonLeftX, ButtonRightX, UI_BUTTON_BAR_TOP_Y, LineCount);


	//
	// draw the text in the button
	//
	LCDDrawStringRGB8(
	  ButtonText, ROM_STRING, 
	  TextLeftX, TextBottomY, 
	  JUSTIFY_LEFT, UI_BUTTON_BAR_FONT, 
	  UI_BUTTON_BAR_BUTTON_FOREGROUND_RGB8, UI_BUTTON_BAR_BUTTON_BACKGROUND_RGB8);
	
	
	//
	// fill in the button left of the text
	//
	if(ButtonLeftX < TextLeftX)
	{	LCDDrawFilledRectangleRGB8(
		  ButtonLeftX, 		TextTopY, 
		  TextLeftX - 1, 	TextBottomY, 
		  UI_BUTTON_BAR_BUTTON_BACKGROUND_RGB8);
	}
	
	
	//
	// fill in the button right of the text
	//
	if(ButtonRightX > TextRightX)
	{	LCDDrawFilledRectangleRGB8(
		  TextRightX + 1,	TextTopY, 
		  ButtonRightX,		TextBottomY, 
		  UI_BUTTON_BAR_BUTTON_BACKGROUND_RGB8);
	}


	//
	// round the button by blanking the pixels in the corners
	//		
	LCDDrawPixelRGB8(ButtonLeftX, UI_BUTTON_BAR_TOP_Y + 2, UI_BUTTON_BAR_BACKGROUND_RGB8);
	LCDDrawPixelRGB8(ButtonLeftX, TextBottomY, UI_BUTTON_BAR_BACKGROUND_RGB8);
	LCDDrawPixelRGB8(ButtonRightX, UI_BUTTON_BAR_TOP_Y + 2, UI_BUTTON_BAR_BACKGROUND_RGB8);
	LCDDrawPixelRGB8(ButtonRightX, TextBottomY, UI_BUTTON_BAR_BACKGROUND_RGB8);


	//
	// draw a line below the text
	//
	LCDDrawFilledRectangleRGB8(
	  ButtonLeftX, 		UI_BUTTON_BAR_BOTTOM_Y, 
	  ButtonRightX, 	UI_BUTTON_BAR_BOTTOM_Y, 
	  UI_BUTTON_BAR_BACKGROUND_RGB8);


	//
	// return where the button was drawn
	//
	*DrawnLeftX = ButtonLeftX;
	*DrawnRightX = ButtonRightX;
}



/* ------------------------------------------------------------------------ */
/*						  	Public general functions 		 				*/
/* ------------------------------------------------------------------------ */

//
// draw a string of text, if the line is wider than the display, break into multiple lines
//		Enter:	S -> string to draw
//				StringType = ROM_STRING or RAM_STRING
//				X = x coord where to draw the string
//				Y = y coord of the middle line
//				LineSpacing = spacing in pixels between each line
//				Justify = JUSTIFY_LEFT, JUSTIFY_CENTER, or JUSTIFY_RIGHT
//				MaxLineWidth = the max width in pixels the line can be
//				Font -> the font
//				ForegroundRGB8 = forground color
//				BackgroundRGB8 = background color
//
void DrawTextBrokenIntoMultipleLines(char *S, byte StringType, byte X, byte Y, byte LineSpacing, byte Justify, byte MaxLineWidth, rom byte *Font, byte ForegroundRGB8, byte BackgroundRGB8)
{	unsigned int StartIdx;
	unsigned int StopIdx;
	unsigned int NextStartIdx;
	byte LineCount;
	char C;
	
	StartIdx = 0;
	while(1)
	{	C = GetCharFromString(S, StringType, StartIdx);

		if (C == 0)
			break;
			
		if (C == '\r')
		{	StartIdx = EatSpaceChars(S, StringType, StartIdx + 1);
			Y += 16;
			continue;
		}
		
		BreakLineAtMaxWidth(S, StringType, StartIdx, MaxLineWidth, Font, &StopIdx, &NextStartIdx);
		LCDDrawStringBetweenIndexesRGB8(S, StringType, StartIdx, StopIdx, X, Y, Justify, Font, ForegroundRGB8, BackgroundRGB8);
		StartIdx = EatSpaceChars(S, StringType, NextStartIdx);
		Y += LineSpacing;
	}
}



//
// determine the number of lines the given text will be after breaking into multiple lines of a max width
//		Enter:	S -> string to measure
//				StringType = ROM_STRING or RAM_STRING
//				MaxLineWidth = the max width in pixels the line can be
//				Font -> the font
//		Exit:	Line count returned
//
byte GetTextLineCountAfterBreakingText(char *S, byte StringType, byte MaxLineWidth, rom byte *Font)
{	unsigned int StartIdx;
	unsigned int StopIdx;
	unsigned int NextStartIdx;
	byte LineCount;
	char C;

	//
	// loop through the text, counting the line breaks
	//
	LineCount = 0;
	StartIdx = 0;
	while(1)
	{	//
		// check if found the end of the string
		//
		C = GetCharFromString(S, StringType, StartIdx);
		if (C == 0)
			return(LineCount);
			
		if (C == '\r')
		{	StartIdx = EatSpaceChars(S, StringType, StartIdx + 1);
			LineCount++;
			continue;
		}
		
		BreakLineAtMaxWidth(S, StringType, StartIdx, MaxLineWidth, Font, &StopIdx, &NextStartIdx);
		StartIdx = EatSpaceChars(S, StringType, NextStartIdx);
		LineCount++;
	}
}



//
// scan through a line of text to find where to break it such that it fits within a 
// pixel line width
//		Enter:	S -> string to find line break
//				StringType = ROM_STRING or RAM_STRING
//				StartIdx = index of starting point in string
//				MaxLineWidth = the max width in pixels the line can be
//				Font -> the font
//				StopIdx -> storage to return the index of the last char in string to draw
//				NextStartIdx -> storage to return the index in the string of the next char
//
void BreakLineAtMaxWidth(char *S, byte StringType, unsigned int StartIdx, byte MaxLineWidth, rom byte *Font, unsigned int *StopIdx, unsigned int *NextStartIdx)
{	unsigned int Idx;
	unsigned int LastBreakIdx;
	byte RunningTextLength;
	char C;
	
	
	//
	// find the first none space character in the line of text
	//
	Idx = StartIdx;
	RunningTextLength = 0;
	LastBreakIdx = Idx;

	
	//
	// loop to find the first place where the line can be broken
	//
	while(1)
	{	if (StringType == ROM_STRING)			// get the next char in the string
			C = ((rom char *)S)[Idx];
		else
			C = ((ram char *)S)[Idx];

		switch(C)
		{	case 0:
				*StopIdx = LastBreakIdx;		// found the end of the string, so return
				*NextStartIdx = Idx;
				return;
		
			case '\r':		
				*StopIdx = LastBreakIdx;		// found a line break character, so return
				*NextStartIdx = Idx + 1;
				return;
		}
												// add char to running pixel length of string
		RunningTextLength += LCDGetCharacterWidth(C, Font);

		if (C == ' ')							// check if the line can be broken here
		{	Idx++;
			break;
		}
				
		if (RunningTextLength > MaxLineWidth)	// check if line is longer than max length
		{	*StopIdx = LastBreakIdx;			// line too long, return last break
			*NextStartIdx = LastBreakIdx + 1;
			return;
		}

		LastBreakIdx = Idx++;					// length still OK, try adding next char
	}
	

	//
	// loop to find the last place where the line can be broken
	//
	while(1)
	{	if (StringType == ROM_STRING)			// get the next char in the string
			C = ((rom char *)S)[Idx];
		else
			C = ((ram char *)S)[Idx];

		switch(C)
		{	case 0:
				*StopIdx = Idx - 1;				// found the end of the string, so return
				*NextStartIdx = Idx;
				return;
				
			case '\r':		
				*StopIdx = Idx - 1;				// found a line break character, so return
				*NextStartIdx = Idx + 1;
				return;

			case ' ':
				LastBreakIdx = Idx - 1;			// found a space, the line can be broken here
				break;
		}
												// add char to running pixel length of string
		RunningTextLength += LCDGetCharacterWidth(C, Font);
											
		if (RunningTextLength > MaxLineWidth)	// check if line is longer than max length
		{	*StopIdx = LastBreakIdx;			// line too long, return last break
			*NextStartIdx = EatSpaceChars(S, StringType, LastBreakIdx + 1);
			return;
		}			

		 Idx++;									// length still OK, try adding next char
	}
}


/* ------------------------- End of UserInterface.c ----------------------- */
