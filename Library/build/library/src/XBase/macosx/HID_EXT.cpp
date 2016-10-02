// 文字コード：UTF-8
#include <XBase/HID.hpp>

#include <XBase/Display.hpp>
#include <XBase/Mouse.hpp>
#include <XBase/Touch.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
int HID::keyboardCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Keyboard HID::keyboardAtIndex( const int aIndex )const
{
    XBASE_RANGE_ASSERT_MAX( aIndex , keyboardCount() );
    return mEXT.keyboard;
}
    
//------------------------------------------------------------------------------
int HID::mouseCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Mouse HID::mouseAtIndex( const int aIndex )const
{
    XBASE_RANGE_ASSERT_MAX( aIndex , mouseCount() );
    return mEXT.mouse;
}
    
//------------------------------------------------------------------------------
int HID::supportedTouchTapCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
int HID::touchCount()const
{
    return 0;
}
    
//------------------------------------------------------------------------------
const Touch HID::touchAtIndex( const int )const
{
    XBASE_NOT_REACH_ASSERT();
    return Touch( 1 );
}

} // namespace
// EOF
