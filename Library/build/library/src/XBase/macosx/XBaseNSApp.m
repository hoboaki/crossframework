// 文字コード：UTF-8
#include "XBaseNSApp.h"

//------------------------------------------------------------------------------
#import <Cocoa/Cocoa.h>

//------------------------------------------------------------------------------
@interface XBaseApp_Delegate : NSObject <NSApplicationDelegate>
/* Example: Fire has the same problem no explanation */
{
}
/* - (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication; */

@end

//------------------------------------------------------------------------------
@implementation XBaseApp_Delegate
- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return NO;
}
@end

//------------------------------------------------------------------------------
void XBaseNSApp_Initialize()
{        
    {// Application起動
        [NSApplication sharedApplication];
        
        XBaseApp_Delegate* delegate = [[[XBaseApp_Delegate alloc] init]autorelease];
        [NSApp setDelegate: delegate];
        
        [NSApp finishLaunching];
    }
    
    {// .app に移動
        NSString *path;
        path=[[NSBundle mainBundle] bundlePath];   
        [[NSFileManager defaultManager] changeCurrentDirectoryPath:path];
    }
}

//------------------------------------------------------------------------------
void XBaseNSApp_Finalize()
{
	//[NSApp terminate:nil];	// This can also be exit(0);    
}

//------------------------------------------------------------------------------
void XBaseNSApp_PollEvent()
{    
 	NSAutoreleasePool *pool=[[NSAutoreleasePool alloc] init];
    
	while(1)
	{
	 	[pool release];
	 	pool=[[NSAutoreleasePool alloc] init];
        
		NSEvent *event;
		event=[NSApp
			   nextEventMatchingMask:NSAnyEventMask
			   untilDate: [NSDate distantPast]
			   inMode: NSDefaultRunLoopMode
			   dequeue:YES];
		if(event!=nil)
		{
			[NSApp sendEvent:event];
			[NSApp updateWindows];
		}
		else
		{
			break;
		}
	}
    
	[pool release];	
}

//------------------------------------------------------------------------------
void XBaseNSApp_Terminate()
{
    [NSApp terminate:nil];
}

//------------------------------------------------------------------------------
// EOF
