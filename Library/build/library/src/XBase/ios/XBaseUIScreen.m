// 文字コード：UTF-8
#include "XBaseUIScreen.h"

//------------------------------------------------------------------------------
#import <UIKit/UIKit.h>

//------------------------------------------------------------------------------
void XBaseUIScreen_GetMainScreenBounds( struct XBaseUIRect* aRect )
{ 
    CGRect rect = [[UIScreen mainScreen] bounds];
    aRect->originX = rect.origin.x;
    aRect->originY = rect.origin.y;
    aRect->sizeW   = rect.size.width;
    aRect->sizeH   = rect.size.height;
}

//------------------------------------------------------------------------------
// EOF
