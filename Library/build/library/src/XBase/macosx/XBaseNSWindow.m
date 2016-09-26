/**
 * @file
 * @brief XBaseNSWindow.hの実装を記述する。
 * @author akino
 */
#include "XBaseNSWindow.h"

//-----------------------------------------------------------
#import <Cocoa/Cocoa.h>

//-----------------------------------------------------------
@interface XBaseOpenGLWindow : NSWindow
{
@private
    void* mOwnerPtr;
    int* mIsClosedPtr;
    XBaseNSWindow_CBKeyEvent mCBKeyEvent;
    XBaseNSWindow_CBModKeyEvent mCBModKeyEvent;
    XBaseNSWindow_CBMouseEvent mCBMouseEvent;
}
- (void**) ownerPtr;
- (int**) isClosedPtr;
- (XBaseNSWindow_CBKeyEvent*) cbKeyEventPtr;
- (XBaseNSWindow_CBModKeyEvent*) cbModKeyEventPtr;
- (XBaseNSWindow_CBMouseEvent*) cbMouseEventPtr;
@end

//-----------------------------------------------------------
@implementation XBaseOpenGLWindow
- (id) initWithContentRect: (NSRect)rect styleMask:(NSUInteger)wndStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)deferFlg
{
	id result = [super initWithContentRect:rect styleMask:wndStyle backing:bufferingType defer:deferFlg];
            
	[[NSNotificationCenter defaultCenter] 
     addObserver:self
     selector:@selector(windowDidResize:)
     name:NSWindowDidResizeNotification
     object:self];
    
	[[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(windowWillClose:)
     name:NSWindowWillCloseNotification
     object:self];
    
	[self setAcceptsMouseMovedEvents:YES];
    
	return result;
}

- (void) windowDidResize: (NSNotification *)notification
{
}

- (void) windowWillClose: (NSNotification *)notification
{
    *mIsClosedPtr = 1;
}

- (void) flagsChanged: (NSEvent *)aEvent
{
    // 変数準備
	unsigned int flags;
    
    // フラグ取得
	flags = [aEvent modifierFlags];
    
    // コールバック
    mCBModKeyEvent(
        mOwnerPtr
        , ( flags & NSShiftKeyMask )
        , ( flags & NSControlKeyMask )
        , ( flags & NSAlternateKeyMask )
        );
}

- (void) keyDown:(NSEvent *)aEvent
{
    NSString* chrsNoMod;
    chrsNoMod = [aEvent charactersIgnoringModifiers];
    if ( 0 < [chrsNoMod length] )
    {
        mCBKeyEvent( mOwnerPtr , [chrsNoMod characterAtIndex:0] , 1 );
    }
}

- (void) keyUp:(NSEvent *)aEvent
{
    NSString* chrsNoMod;
    chrsNoMod = [aEvent charactersIgnoringModifiers];
    if ( 0 < [chrsNoMod length] )
    {
        mCBKeyEvent( mOwnerPtr , [chrsNoMod characterAtIndex:0] , 0 );
    }
}

- (void) mouseEventFunc:(NSEvent *)theEvent
{
    NSPoint pos = [theEvent locationInWindow];
    mCBMouseEvent( mOwnerPtr , [NSEvent pressedMouseButtons] , pos.x , pos.y );
}

- (void) mouseEntered:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseExited:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseMoved:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseDown:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseDragged:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseUp:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) rightMouseDown:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) rightMouseDragged:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) rightMouseUp:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) otherMouseDown:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) otherMouseDragged:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) otherMouseUp:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void**) ownerPtr
{
    return &mOwnerPtr;
}

- (int**) isClosedPtr
{
    return &mIsClosedPtr;
}

- (XBaseNSWindow_CBKeyEvent*) cbKeyEventPtr
{
    return &mCBKeyEvent;
}

- (XBaseNSWindow_CBModKeyEvent*) cbModKeyEventPtr
{
    return &mCBModKeyEvent;
}

- (XBaseNSWindow_CBMouseEvent*) cbMouseEventPtr
{
    return &mCBMouseEvent;
}
@end
//-----------------------------------------------------------
struct XBaseNSWindow* XBaseNSWindow_Create(
    const float aPosX
    , const float aPosY
    , const float aWidth
    , const float aHeight
    , void* aOwnerPtr
    , int* aIsClosedPtr 
    , XBaseNSWindow_CBKeyEvent aCBKeyEvent
    , XBaseNSWindow_CBModKeyEvent aCBModKeyEvent
    , XBaseNSWindow_CBMouseEvent aCBMouseEvent
    )
{    
    NSAutoreleasePool* pool=[[NSAutoreleasePool alloc] init];
    
	NSRect contRect;
	contRect = NSMakeRect( aPosX , aPosY , aWidth , aHeight );	
	unsigned int winStyle=
    NSTitledWindowMask|
    NSClosableWindowMask|
    NSMiniaturizableWindowMask;
	
	XBaseOpenGLWindow* window =[XBaseOpenGLWindow alloc];
    *[window ownerPtr] = aOwnerPtr;
    *[window isClosedPtr] = aIsClosedPtr;
    *[window cbKeyEventPtr] = aCBKeyEvent;
    *[window cbModKeyEventPtr] = aCBModKeyEvent;
    *[window cbMouseEventPtr] = aCBMouseEvent;
    
	[window
     initWithContentRect:contRect
     styleMask:winStyle
     backing:NSBackingStoreBuffered 
		defer:NO];
    
    [pool release];
    
    return (struct XBaseNSWindow*)window;
}

//-----------------------------------------------------------
void XBaseNSWindow_Destroy( struct XBaseNSWindow* aWindow )
{
}

//-----------------------------------------------------------
void XBaseNSWindow_Show( struct XBaseNSWindow* aWindow )
{   
    NSAutoreleasePool* pool=[[NSAutoreleasePool alloc] init];
    
    XBaseOpenGLWindow* window = (XBaseOpenGLWindow*)aWindow;
    
    **[window isClosedPtr] = 0;
	[window makeKeyAndOrderFront:nil];
	[window makeMainWindow];
    
	[NSApp activateIgnoringOtherApps:YES];
    
    [pool release];
}

//-----------------------------------------------------------
// EOF
