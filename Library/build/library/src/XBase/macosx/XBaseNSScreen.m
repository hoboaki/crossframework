/**
 * @file
 * @brief XBaseNSScreen.hの実装を記述する。
 * @author akino
 */
#include "XBaseNSScreen.h"

//-----------------------------------------------------------
#import <Cocoa/Cocoa.h>

//-----------------------------------------------------------
void XBaseNSScreen_GetMainScreenFrame( struct XBaseNSRect* aRect )
{ 
    NSRect rect = [[NSScreen mainScreen] frame];
    aRect->originX = rect.origin.x;
    aRect->originY = rect.origin.y;
    aRect->sizeW   = rect.size.width;
    aRect->sizeH   = rect.size.height;
}

//-----------------------------------------------------------
void XBaseNSScreen_GetMainScreenVisibleFrame( struct XBaseNSRect* aRect )
{ 
    NSRect rect = [[NSScreen mainScreen] visibleFrame];
    aRect->originX = rect.origin.x;
    aRect->originY = rect.origin.y;
    aRect->sizeW   = rect.size.width;
    aRect->sizeH   = rect.size.height;
}

//-----------------------------------------------------------
// EOF
