//
// This file is part of Airmac.
//
// This version of Airmac is a continuation of Airmac version 0.4
// developed by Arend Jan Kramer, which was available at the time of
// writing from <http://code.google.com/p/airmac/>.
//
// Airmac is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Airmac is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Airmac.  If not, see <http://www.gnu.org/licenses/>.
//

#import <Cocoa/Cocoa.h>
#import "HTTPServer.h"
#import <QTKit/QTKit.h>

@interface AirmacAppDelegate : NSObject <NSApplicationDelegate,AirplayDelegate,NSWindowDelegate> {
    NSPanel *aboutWindow;
	
	// Image slideshow
	NSPanel *imageWindow;
	NSImageView *fullScreenbg;
	NSImageView *imageView1;
	NSImageView *imageView2;
	int CurrentImageView;
	NSTrackingArea *imageHoverTracker;
	NSView *hoverControls;
	NSButton *fullScreenBtn;
	CGPoint windowedModeLocation;
	BOOL imageFullscreen;
	BOOL videoFullscreen;
	int hideCounter;
	
	// Voorkeuren paneel
	NSWindow *prefWindow;
	NSButton *_startVideoFullScreenCheckBox;
	NSButton *_startImageSlideshowFullScreenCheckBox;
	
	// Error paneel
	NSPanel *errorWindow;
	NSTextField *errorTextField;
	
	HTTPServer *server;
	BOOL _serverIsStarted;
	// Menu icoontje
	NSStatusItem *myStatusItem;
	IBOutlet NSMenu *myStatusMenu;
	IBOutlet NSMenuItem *serverStatus;
	IBOutlet NSMenuItem *toggleServer;
	
	
}
- (void) checkForUpdates;

- (void) startServer;
- (void) toggleServerStatusMenuItem:(BOOL)started;
- (void)setImageWindowHoverActions;
- (IBAction) toggleFullScreen:(id)sender;
- (IBAction) toggleServer:(id)sender;
- (IBAction) about:(id)sender;
- (IBAction) quit:(id)sender;
- (IBAction) errorOk:(id)sender;
- (IBAction) preferences:(id)sender;

@property (assign) IBOutlet NSPanel *aboutWindow;
@property (assign) IBOutlet NSPanel *imageWindow;
@property (assign) IBOutlet NSView *hoverControls;
@property (assign) IBOutlet NSButton *fullScreenBtn;
@property (assign) IBOutlet NSWindow *prefWindow;
@property (assign) IBOutlet NSPanel *errorWindow;
@property (assign) IBOutlet NSTextField *errorTextField;
@property (assign) IBOutlet NSImageView *imageView1;
@property (assign) IBOutlet NSImageView *imageView2;
@property (assign) IBOutlet NSImageView *fullScreenbg;
@property (assign) IBOutlet NSButton *_startVideoFullScreenCheckBox;
@property (assign) IBOutlet NSButton *_startImageSlideshowFullScreenCheckBox;

@end
