/**
 * @file
 * @brief HID.hppの実装を記述する。
 * @author akino
 */
#include <XBase/HID.hpp>

//------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/Keyboard.hpp>
#include <XBase/Mouse.hpp>
#include "XBaseUIWindow.h"

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
uint HID::keyboardCount()const
{
    return 0;
}

//------------------------------------------------------------
const Keyboard HID::keyboardAtIndex( const uint )const
{
    XBASE_NOT_REACH_ASSERT();
    return Keyboard();
}
    
//------------------------------------------------------------
uint HID::mouseCount()const
{
    return 0;
}

//------------------------------------------------------------
const Mouse HID::mouseAtIndex( const uint )const
{
    XBASE_NOT_REACH_ASSERT();
    return Mouse();
}

//-----------------------------------------------------------
uint HID::supportedTouchTapCount()const
{
    return XBASE_UITOUCHSET_TOUCH_COUNT_MAX;
}

//-----------------------------------------------------------
uint HID::touchCount()const
{
    return 1;
}
    
//-----------------------------------------------------------
const Touch HID::touchAtIndex( const uint aIndex )const
{
    if ( touchCount() <= aIndex )
    {
        XBASE_INVALID_VALUE_ERROR( aIndex );
        return Touch( XBASE_UITOUCHSET_TOUCH_COUNT_MAX );
    }
    return mEXT.touch;
}
 
//-----------------------------------------------------------
HID_EXT::HID_EXT()
: touch( XBASE_UITOUCHSET_TOUCH_COUNT_MAX )
{
}
    
//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
