// KS0108
// http://www.piclist.com/techref/microchip/language/c/ks0107.htm

#include <pic18fregs.h>

#include "pillefyrsstyring.h"
#include "glcd.h"
//#include "menu_system.h"

unsigned char _latch_3_data;

unsigned char lcd_buffer;
//unsigned char _sides;	// for caching
//unsigned char _page;
//unsigned char _y;

void lcd_init(void) {
	latched_lcd_power(1);
//	LCD_TRIS = 0x00;
//	ENABLE_TRIS = 0;
//	RW_TRIS	= 0;
//	DI_TRIS = 0;
//	RESET_TRIS = 0;
//	CS1_TRIS = 0;
//	CS2_TRIS = 0;
	_latch_3_data = 0x00;
	
//	CS1 = 1;
	latched_lcd_cs1(1);
//	CS2 = 1;
	latched_lcd_cs2(1);
	
//	_sides = LCD_NONE;
//	_page = 0;
//	_y = 0;

	lcd_reset();
	lcd_screenon(1);
	lcd_cls();
}

void lcd_enable(void) {
	//ENABLE = 1;
	latched_lcd_enable(1);
	delay_2us();
	//ENABLE = 0;
	latched_lcd_enable(0);
	delay_2us();
}


unsigned char lcd_status(void) {
	// returns the lcd status & maintains the TRIS state of the
	// lcd data port

	/*
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
	*/
	sleep_ms(10);	
	return 1;	// no hardware support for reading from latch 4
}


void lcd_reset(void) {
	// reset the lcd module
	// datasheet says reset must be low for minimum of 1us
	// after Vdd clears 4.5v. 
	// from experimentation, this is bullshit. this seems to
	// work though.
	
	sleep_ms(1);
	//RESET = 1;
	latched_lcd_rst(1);
	sleep_ms(1);
    //RESET = 0;
	latched_lcd_rst(0);

    // check status, and wait if necessary
//	while (lcd_status() & 0b00010000) {
//		sleep_ms(1);
//	}
}


void lcd_screenon(unsigned char on) {
	// turn the display on or off
	//CS1 = 0;
	latched_lcd_cs1(0);
	//CS2 = 0;
	latched_lcd_cs2(0);
	//RW = 0;
	latched_lcd_rw(0);
	//DI = 0;
	latched_lcd_di(0);
	//LCD_TRIS = 0;	// all outputs	
	//LATD = 0b00111110 | (on & 0b00000001);	// main screen turn on!
	latched_lcd_data(0b00111110 | (on & 0b00000001));
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
		//LCD_DATA = 0; RW = 0; DI = 1;
		latched_lcd_data(0);
		latched_lcd_rw(0);
		latched_lcd_di(1);
	
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
		//DI = 0; RW = 0; 
		latched_lcd_di(0);
		latched_lcd_rw(0);
		//LCD_DATA = 0b10111000 | page;
		latched_lcd_data(0b10111000 | page);
		lcd_enable();
		//_page = page;
//	}
}


// sets the y address of the y address register
void lcd_setyaddr(unsigned char y) {
//	if (y != _y) {	// need to update...
		lcd_waitbusy();
		//DI = 0; RW = 0;
		latched_lcd_di(0);
		latched_lcd_rw(0);
		//LCD_DATA = 0b01000000 | (y & 0b00111111);
		latched_lcd_data(0b01000000 | (y & 0b00111111));
		lcd_enable();
		//_y = y;
//	}
}


void lcd_waitbusy(void) {
//	while (lcd_status() & 0b10000000) {
		delay_2us();
//	}
}


void lcd_write (unsigned char d) {
	lcd_waitbusy();
	//DI = 1;	// data
	latched_lcd_di(1);
	//RW = 0;	// write
	latched_lcd_rw(0);
	//LCD_TRIS = 0; 
	//LCD_DATA = d;
	latched_lcd_data(d);
	lcd_enable();
}


void lcd_selectside(unsigned char sides) {
	// set a CS pin low to enable it
//	if (sides != _sides) {	// only call lcd_selectside if needed. Keep local state
		if (sides & LCD_LEFT) {
			//CS1 = 0;
			latched_lcd_cs1(0);
		}
		else {
			//CS1 = 1;
			latched_lcd_cs1(1);
		}
	
		if (sides & LCD_RIGHT) {
			//CS2 = 0;
			latched_lcd_cs2(0);
		}
		else {
			//CS2 = 1;
			latched_lcd_cs2(1);
		}
//		_sides = sides;		// update local copy
//	}
}


unsigned char lcd_read (void) {
	unsigned char d;

/*	
	LCD_TRIS = 0xFF;
	RW = 1;	// read
	DI = 1;	// data
	
	lcd_enable();
	d = LCD_DATA;
	LCD_TRIS = 0x00;
	
	return d;
*/
	lcd_enable();
	return 0;
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

void latched_lcd_power(unsigned char value) {
	LATCH_DATA_TRIS = 0x00;		// outputs
	if (value) {	// set it
		_latch_3_data |= 0b10000000;
		LATCH_DATA = _latch_3_data;
	}
	else {			// clear it
		_latch_3_data &= 0b01111111;
		LATCH_DATA = _latch_3_data;
	}
	LATCH_3 = LATCH_3_ENABLED;
	LATCH_3 = LATCH_3_DISABLED;
	LATCH_DATA = 0x00;
}

void latched_lcd_enable(unsigned char value) {
	LATCH_DATA_TRIS = 0x00;		// outputs
	if (value) {	// set it
		_latch_3_data |= 0b00000001;
		LATCH_DATA = _latch_3_data;
	}
	else {			// clear it
		_latch_3_data &= 0b11111110;
		LATCH_DATA = _latch_3_data;
	}
	LATCH_3 = LATCH_3_ENABLED;
	LATCH_3 = LATCH_3_DISABLED;
	LATCH_DATA = 0x00;
}

void latched_lcd_di(unsigned char value) {
	LATCH_DATA_TRIS = 0x00;		// outputs
	if (value) {	// set it
		_latch_3_data |= 0b00000010;
		LATCH_DATA = _latch_3_data;
	}
	else {			// clear it
		_latch_3_data &= 0b11111101;
		LATCH_DATA = _latch_3_data;
	}
	LATCH_3 = LATCH_3_ENABLED;
	LATCH_3 = LATCH_3_DISABLED;
	LATCH_DATA = 0x00;
}

void latched_lcd_rw(unsigned char value) {
	LATCH_DATA_TRIS = 0x00;		// outputs
	if (value) {	// set it
		_latch_3_data |= 0b00000100;
		LATCH_DATA = _latch_3_data;
	}
	else {			// clear it
		_latch_3_data &= 0b11111011;
		LATCH_DATA = _latch_3_data;
	}
	LATCH_3 = LATCH_3_ENABLED;
	LATCH_3 = LATCH_3_DISABLED;
	LATCH_DATA = 0x00;
}

void latched_lcd_rst(unsigned char value) {
	LATCH_DATA_TRIS = 0x00;		// outputs
	if (value) {	// set it
		_latch_3_data |= 0b00001000;
		LATCH_DATA = _latch_3_data;
	}
	else {			// clear it
		_latch_3_data &= 0b11110111;
		LATCH_DATA = _latch_3_data;
	}
	LATCH_3 = LATCH_3_ENABLED;
	LATCH_3 = LATCH_3_DISABLED;
	LATCH_DATA = 0x00;
}

void latched_lcd_cs2(unsigned char value) {
	LATCH_DATA_TRIS = 0x00;		// outputs
	if (value) {	// set it
		_latch_3_data |= 0b00010000;
		LATCH_DATA = _latch_3_data;
	}
	else {			// clear it
		_latch_3_data &= 0b11101111;
		LATCH_DATA = _latch_3_data;
	}
	LATCH_3 = LATCH_3_ENABLED;
	LATCH_3 = LATCH_3_DISABLED;
	LATCH_DATA = 0x00;
}

void latched_lcd_cs1(unsigned char value) {
	LATCH_DATA_TRIS = 0x00;		// outputs
	if (value) {	// set it
		_latch_3_data |= 0b00100000;
		LATCH_DATA = _latch_3_data;
	}
	else {			// clear it
		_latch_3_data &= 0b11011111;
		LATCH_DATA = _latch_3_data;
	}
	LATCH_3 = LATCH_3_ENABLED;
	LATCH_3 = LATCH_3_DISABLED;
	LATCH_DATA = 0x00;
}

void latched_lcd_data(unsigned char value) {
	LATCH_DATA_TRIS = 0x00;		// outputs
	LATCH_DATA = value;
	LATCH_4 = LATCH_4_ENABLED;
	LATCH_4 = LATCH_4_DISABLED;
	LATCH_DATA = 0x00;
}

/*
unsigned char latched_lcd_data_read() {
	unsigned char value;
	LATCH_DATA_TRIS = 0xff;		// inputs
	LATCH_4 = LATCH_4_ENABLED;
	LATCH_4 = LATCH_4_DISABLED;
	LATCH_DATA = 0x00;
}
*/