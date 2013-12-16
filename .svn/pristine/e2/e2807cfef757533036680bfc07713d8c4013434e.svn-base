//
//  menu_system.c
//  OpenStoker Simulator
//
//  Created by stoffer on 17/12/12.
//  Copyright (c) 2012 stoffer. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_system.h"
#include "font8x5.h"
#ifdef __pic16
// on pic
    #include "glcd.h"
#else
#endif

typedef struct menu_item_t {
    unsigned char id;
    char name[22];
} menu_item;

static struct menu_item_t menu[7] = { { 0, "Selected item"},
                                      { 1, "Item 2"},
                                      { 2, "Option"},
                                      { 3, "Setting"},
                                      { 4, "Wood"},
                                      { 5, "Oxygen"},
                                      { 6, "Manual control"}};


char buffer[LCD_WIDTH][LCD_HEIGHT];

void do_menu_update() {
    unsigned char i;
    char menu_item[22];
    
    for (i = 0; i < (sizeof(menu)/sizeof(struct menu_item_t)); i++) {
        strcpy(menu_item, " ");
        strcat(menu_item, menu[i].name);
        lcd_print(menu_item, i, NON_INVERTED);
    }
}

void lcd_print(char *s, unsigned char line, unsigned char inverted) {
	unsigned char x;
	unsigned char y;
	unsigned char n;
    
    //	lcd_cls();
    for (n = 0; s[n]; n++) {
        for (x = 0; x < FONT_WIDTH; x++) {
            for (y = 0; y < FONT_HEIGHT; y++) {
                if (inverted) {
                    if (!((font8x5[ s[n] ][x] & (1 << y)) >> y)) {
                        lcd_plotpixel(x + n * FONT_WIDTH, y + line * FONT_HEIGHT);
                    }
                }
                else {
                    if ((font8x5[ s[n] ][x] & (1 << y)) >> y) {
                        lcd_plotpixel(x + n * FONT_WIDTH, y + line * FONT_HEIGHT);
                    }
                }
            }
        }
    }
}

void button_pressed(unsigned char button) {
    
}

void button_released(unsigned char button) {
    
}


void lcd_plotpixel(unsigned char x, unsigned char y) {
#ifdef __pic16
    // on pic
#else
    if ((x < (LCD_WIDTH)) && (y < (LCD_HEIGHT))) {  // clipping
        buffer[x][y] = 1;
    }
#endif
}

#ifdef __pic16
// on pic
#else
// support function for simulator
unsigned char get_pixel(unsigned char x, unsigned char y) {
    return buffer[x][y];
}
#endif