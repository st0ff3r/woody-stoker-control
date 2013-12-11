		/************************************************************/
		/*															*/
		/*			    Header file for UserInterface.c				*/
		/*															*/
		/************************************************************/


/* ------------------------------------------------------------------------ */
/*						  General XY layout constants		   				*/
/* ------------------------------------------------------------------------ */

//
// TitleBar constants that define it's size and position
//
#define UI_TITLE_BAR_HEIGHT		16
#define UI_TITLE_BAR_TOP_Y 		1

#define UI_TITLE_BAR_LEFT_X 	1
#define UI_TITLE_BAR_RIGHT_X 	130
#define UI_TITLE_BAR_CENTER_X	((UI_TITLE_BAR_RIGHT_X - UI_TITLE_BAR_LEFT_X) / 2)

#define UI_TITLE_BAR_BOTTOM_Y 	(UI_TITLE_BAR_TOP_Y + UI_TITLE_BAR_HEIGHT - 1)



//
// ButtonBar constants that define it's size and position
//
#define UI_BUTTON_BAR_HEIGHT				16
#define UI_BUTTON_BAR_BOTTOM_Y 				130

#define UI_BUTTON_BAR_LEFT_X 				1
#define UI_BUTTON_BAR_RIGHT_X 				130
#define UI_BOTTON_BAR_LEFT_BUTTON_X			33
#define UI_BOTTON_BAR_RIGHT_BUTTON_X		99
#define UI_BUTTON_BAR_TOP_Y 				(UI_BUTTON_BAR_BOTTOM_Y - (UI_BUTTON_BAR_HEIGHT - 1))



//
// DisplaySpace constants that define it's size and position
//
#define UI_DISPLAY_SPACE_LEFT_X				1
#define UI_DISPLAY_SPACE_RIGHT_X			130
#define UI_DISPLAY_SPACE_WIDTH_WITH_BORDERS	((UI_DISPLAY_SPACE_RIGHT_X - UI_DISPLAY_SPACE_LEFT_X + 1) - 6)
#define UI_DISPLAY_SPACE_TOP_Y 				(UI_TITLE_BAR_BOTTOM_Y + 1)
#define UI_DISPLAY_SPACE_BOTTOM_Y 			(UI_BUTTON_BAR_TOP_Y - 1)

#define UI_DISPLAY_SPACE_HEIGHT				(UI_DISPLAY_SPACE_BOTTOM_Y - UI_DISPLAY_SPACE_TOP_Y + 1)

#define UI_DISPLAY_SPACE_BACKGROUND_RGB8	RGB8_WHITE



/* ------------------------------------------------------------------------ */
/*						   Menu Display declarations		   				*/
/* ------------------------------------------------------------------------ */

//
// menu table item typedef
//
typedef struct _MENU_ITEM
{	byte MenuItemType;
	rom char *MenuItemText;
	rom char *MenuItemPntr;
} MENU_ITEM;


//
// menu item types
//
#define MENU_ITEM_TYPE_MAIN_MENU_HEADER		0
#define MENU_ITEM_TYPE_SUB_MENU_HEADER		1
#define MENU_ITEM_TYPE_SUB_MENU				2
#define MENU_ITEM_TYPE_COMMAND				3
#define MENU_ITEM_TYPE_ALTERNATE			4
#define MENU_ITEM_TYPE_END_OF_MENU			5


//
// "Alternate" menu item callback actions
//
#define MENU_ACTION_ALTERNATE_GET_TEXT	0
#define MENU_ACTION_ALTERNATE_SELECTION	1



/* ------------------------------------------------------------------------ */
/*						  Slider Display declarations		   				*/
/* ------------------------------------------------------------------------ */

//
// Slider Display callback actions
//
#define SLIDER_DISPLAY_ACTION_VALUE_CHANGED		1
#define SLIDER_DISPLAY_ACTION_VALUE_SET			2
#define SLIDER_DISPLAY_ACTION_CANCELED			3



/* ------------------------------------------------------------------------ */
/*						 Message Display declarations		   				*/
/* ------------------------------------------------------------------------ */

//
// Message Display types
//
#define MESSAGE_DISPLAY_BACK					1
#define MESSAGE_DISPLAY_OK_BACK					2
#define MESSAGE_DISPLAY_YES_NO					3


//
// Message Display callback actions
//
#define MESSAGE_DISPLAY_ACTION_BACK				1
#define MESSAGE_DISPLAY_ACTION_OK				2
#define MESSAGE_DISPLAY_ACTION_YES				3
#define MESSAGE_DISPLAY_ACTION_NO				4



/* ------------------------------------------------------------------------ */
/*						  Public function declarations			  			*/
/* ------------------------------------------------------------------------ */

void UISetEventHandler(rom void (*)());
void UIExecuteEvent(byte);
void UISelectMenuDisplay(MENU_ITEM *);
void UISelectPreviousMenuDisplay(void);
void UISelectParentMenu(void);
void UISelectSliderDisplay(char *, int, int, int, int, int, rom char *, byte, byte, rom void (*)());
void UISelectMessageDisplay(char *, char *, byte, byte, byte, rom byte *, rom void (*)());
void UIBlankDisplaySpace(void);
void UIDrawTitleBar(rom char *, byte);
void UIDrawButtonBar(rom char *, rom char *);
void DrawTextBrokenIntoMultipleLines(char *, byte, byte, byte, byte, byte, byte, rom byte *, byte, byte);
byte GetTextLineCountAfterBreakingText(char *, byte, byte, rom byte *);
void BreakLineAtMaxWidth(char *, byte, unsigned int, byte, rom byte *, unsigned int *, unsigned int *);


/* ------------------------- End of UserInterface.h ----------------------- */
