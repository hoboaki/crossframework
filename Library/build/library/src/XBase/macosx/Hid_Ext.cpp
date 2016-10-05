// 文字コード：UTF-8
#include <XBase/Hid.hpp>

#include <XBase/Display.hpp>
#include <XBase/Mouse.hpp>
#include <XBase/Touch.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
int Hid::keyboardCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Keyboard Hid::keyboardAtIndex( const int aIndex )const
{
    XBASE_ASSERT_LESS( aIndex , keyboardCount() );
    return mExt.keyboard;
}
    
//------------------------------------------------------------------------------
int Hid::mouseCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Mouse Hid::mouseAtIndex( const int aIndex )const
{
    XBASE_ASSERT_LESS( aIndex , mouseCount() );
    return mExt.mouse;
}
    
//------------------------------------------------------------------------------
int Hid::supportedTouchTapCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
int Hid::touchCount()const
{
    return 0;
}
    
//------------------------------------------------------------------------------
const Touch Hid::touchAtIndex( const int )const
{
    XBASE_ASSERT_NOT_REACHED();
    return Touch( 1 );
}

} // namespace
// EOF
