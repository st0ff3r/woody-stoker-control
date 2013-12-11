//
//  LCDDisplay.m
//  OpenStoker Simulator
//
//  Created by stoffer on 17/12/12.
//  Copyright (c) 2012 stoffer. All rights reserved.
//

#import "LCDDisplay.h"
#include "menu_system.h"

@implementation LCDDisplay

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (BOOL)isFlipped {
    return YES;
}

- (void)keyDown:(NSEvent *)theEvent {
    /*
    NSString *characters;
    characters = [theEvent characters];
    
    unichar character;
    character = [characters characterAtIndex: 0];
    
    if (character == NSRightArrowFunctionKey) {
        button_pressed(MENU);
    }
    else if (character == NSLeftArrowFunctionKey) {
        button_pressed(MENU);
    }
    else if (character == NSUpArrowFunctionKey) {
        button_pressed(UP);
    }
    else if (character == NSDownArrowFunctionKey) {
        button_pressed(DOWN);
    }
        
     */
}

- (void)drawRect:(NSRect)dirtyRect
{
    unsigned char x;
    unsigned char y;
    
    NSColor *black  = [NSColor blackColor];
    NSColor *white  = [NSColor whiteColor];
	
    for (x = 0; x < LCD_WIDTH; x++) {
        for (y = 0; y < LCD_HEIGHT; y++) {
            if (get_pixel(x, y)) {
                NSRect pixel = NSMakeRect(x * SCALE, y * SCALE, SCALE, SCALE);
                [black set];
                NSRectFill (pixel);
            }
            else {
                NSRect pixel = NSMakeRect(x * SCALE, y * SCALE, SCALE, SCALE);
                [white set];
                NSRectFill (pixel);
            }
        }
    }
}

@end
