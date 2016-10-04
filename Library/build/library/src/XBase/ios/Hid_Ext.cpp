// 文字コード：UTF-8
#include <XBase/HID.hpp>

//------------------------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/Keyboard.hpp>
#include <XBase/Mouse.hpp>
#include "XBaseUIWindow.h"

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
int HID::keyboardCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
const Keyboard HID::keyboardAtIndex(const int)const
{
    XBASE_ASSERT_NOT_REACHED();
    return Keyboard();
}

//------------------------------------------------------------------------------
int HID::mouseCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
const Mouse HID::mouseAtIndex(const int)const
{
    XBASE_ASSERT_NOT_REACHED();
    return Mouse();
}

//------------------------------------------------------------------------------
int HID::supportedTouchTapCount()const
{
    return XBASE_UITOUCHSET_TOUCH_COUNT_MAX;
}

//------------------------------------------------------------------------------
int HID::touchCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Touch HID::touchAtIndex(const int aIndex)const
{
    if (touchCount() <= aIndex) {
        XBASE_ERROR_INVALID_VALUE(aIndex);
        return Touch(XBASE_UITOUCHSET_TOUCH_COUNT_MAX);
    }
    return mEXT.touch;
}

//------------------------------------------------------------------------------
HID_EXT::HID_EXT()
: touch(XBASE_UITOUCHSET_TOUCH_COUNT_MAX)
{
}

} // namespace
// EOF
