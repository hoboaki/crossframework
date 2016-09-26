/**
 * @file
 * @brief HID.hppの実装を記述する。
 * @author akino
 */
#include <XBase/HID.hpp>

//------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/Mouse.hpp>
#include <XBase/Touch.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
uint HID::keyboardCount()const
{
    return 1;
}

//------------------------------------------------------------
const Keyboard HID::keyboardAtIndex( const uint aIndex )const
{
    XBASE_RANGE_ASSERT_MAX( aIndex , keyboardCount() );
    return mEXT.keyboard;
}
    
//------------------------------------------------------------
uint HID::mouseCount()const
{
    return 1;
}

//------------------------------------------------------------
const Mouse HID::mouseAtIndex( const uint aIndex )const
{
    XBASE_RANGE_ASSERT_MAX( aIndex , mouseCount() );
    return mEXT.mouse;
}
    
//-----------------------------------------------------------
uint HID::supportedTouchTapCount()const
{
    return 0;
}

//-----------------------------------------------------------
uint HID::touchCount()const
{
    return 0;
}
    
//-----------------------------------------------------------
const Touch HID::touchAtIndex( const uint )const
{
    XBASE_NOT_REACH_ASSERT();
    return Touch( 1 );
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
