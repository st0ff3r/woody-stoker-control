//
//  AppDelegate.h
//  OpenStoker Simulator
//
//  Created by stoffer on 17/12/12.
//  Copyright (c) 2012 stoffer. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "LCDDisplay.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet LCDDisplay *lcd;

@end
