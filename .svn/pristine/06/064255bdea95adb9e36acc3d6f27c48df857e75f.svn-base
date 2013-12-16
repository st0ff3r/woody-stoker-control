// KS0108
// http://www.piclist.com/techref/microchip/language/c/ks0107.htm

#include <pic18fregs.h>

#include "pillefyrsstyring.h"
#include "glcd.h"
#include "menu_system.h"

unsigned char lcd_buffer;
//unsigned char _sides;	// for caching
//unsigned char _page;
//unsigned char _y;

void lcd_init(void) {
	LCD_TRIS = 0x00;
	ENABLE_TRIS = 0;
	RW_TRIS	= 0;
	DI_TRIS = 0;
	RESET_TRIS = 0;
	CS1_TRIS = 0;
	CS2_TRIS = 0;
	
	CS1 = 1;
	CS2 = 1;
	
//	_sides = LCD_NONE;
//	_page = 0;
//	_y = 0;

	lcd_reset();
	lcd_screenon(1);
	lcd_cls();
}

void lcd_enable(void) {
	ENABLE = 1;
	delay_2us();
	ENABLE = 0;
	delay_2us();
}


unsigned char lcd_status(void) {
	// returns the lcd status & maintains the TRIS state of the
	// lcd data port

	unsigned char _lcd_tris, _status;
	
	// save the tris value
	_lcd_tris = LCD_TRIS;
	
	// read the status
	LCD_TRIS = 0xFF;	// all inputs
	DI = 0; RW = 1;		// command/read
	
	lcd_enable();
	_status = LCD_DATA;
	
	// restore the tris value
	LCD_TRIS = _lcd_tris;
	
	return _status;
}


void lcd_reset(void) {
	// reset the lcd module
	// datasheet says reset must be low for minimum of 1us
	// after Vdd clears 4.5v. 
	// from experimentation, this is bullshit. this seems to
	// work though.
	
	sleep_ms(1);
	RESET = 1;
	sleep_ms(1);
    RESET = 0;

    // check status, and wait if necessary
	while (lcd_status() & 0b00010000) {
		sleep_ms(1);
	}
}


void lcd_screenon(unsigned char on) {
	// turn the display on or off
	CS1 = 0;
	CS2 = 0;
	RW = 0;
	DI = 0;
	LCD_TRIS = 0;	// all outputs	
	LATD = 0b00111110 | (on & 0b00000001);	// main screen turn on!
	lcd_enable();
}


void lcd_cls(void) {
	unsigned char x,y;
	
	// clear both sides
	lcd_selectside(LCD_BOTH);
	for (x = 0; x < 8; x++) {
		// set the page (x)
		lcd_setpage(x);
		
		// set the y address to 0
		lcd_setyaddr(0);
	
		// setup for data
		LCD_DATA = 0; RW = 0; DI = 1;
	
		// clear the row
		for (y = 0; y < 64; y++) {
			lcd_enable(); 
			delay_2us();
		}
	}
	
	// go back
	lcd_selectside(LCD_LEFT);
}


// sets the x address of the x address register
void lcd_setpage(unsigned char page) {
//	if (page != _page) {	// need to update...
		lcd_waitbusy();
		DI = 0; RW = 0; 
		LCD_DATA = 0b10111000 | page;
		lcd_enable();
		//_page = page;
//	}
}


// sets the y address of the y address register
void lcd_setyaddr(unsigned char y) {
//	if (y != _y) {	// need to update...
		lcd_waitbusy();
		DI = 0; RW = 0;
		LCD_DATA = 0b01000000 | (y & 0b00111111);
		lcd_enable();
		//_y = y;
//	}
}


void lcd_waitbusy(void) {
	while (lcd_status() & 0b10000000) {
		delay_2us();
	}
}


void lcd_write (unsigned char d) {
	lcd_waitbusy();
	DI = 1;	// data
	RW = 0;	// write
	LCD_TRIS = 0; 
	LCD_DATA = d;
	lcd_enable();
}


void lcd_selectside(unsigned char sides) {
	// set a CS pin low to enable it
//	if (sides != _sides) {	// only call lcd_selectside if needed. Keep local state
		if (sides & LCD_LEFT) {
			CS1 = 0;
		}
		else {
			CS1 = 1;
		}
	
		if (sides & LCD_RIGHT) {
			CS2 = 0;
		}
		else {
			CS2 = 1;
		}
//		_sides = sides;		// update local copy
//	}
}


unsigned char lcd_read (void) {
	unsigned char d;
	
	LCD_TRIS = 0xFF;
	RW = 1;	// read
	DI = 1;	// data
	
	lcd_enable();
	d = LCD_DATA;
	LCD_TRIS = 0x00;
	
	return d;
}


void lcd_plot_pixel(unsigned char rx, unsigned char ry) {
	unsigned char d;
	
	//lcd_waitbusy();
	// select the correct side
	if (rx & 64) {
		lcd_selectside(LCD_RIGHT);
	}
	else {
		lcd_selectside(LCD_LEFT);
	}
	
	lcd_setpage( ry >> 3);		// fast /8
	lcd_setyaddr( rx & 0b00111111);
	d = lcd_read();				// read to move data to GLCD buffer,
	d = lcd_read();				// read again to transfer to pic
	lcd_setyaddr( rx & 0b00111111); 
	lcd_write (d | (1 << (ry & 0b111)));
}

