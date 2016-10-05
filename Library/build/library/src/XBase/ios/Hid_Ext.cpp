// 文字コード：UTF-8
#include <XBase/Hid.hpp>

//------------------------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/Keyboard.hpp>
#include <XBase/Mouse.hpp>
#include "XBaseUIWindow.h"

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
int Hid::keyboardCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
const Keyboard Hid::keyboardAtIndex(const int)const
{
    XBASE_ASSERT_NOT_REACHED();
    return Keyboard();
}

//------------------------------------------------------------------------------
int Hid::mouseCount()const
{
    return 0;
}

//------------------------------------------------------------------------------
const Mouse Hid::mouseAtIndex(const int)const
{
    XBASE_ASSERT_NOT_REACHED();
    return Mouse();
}

//------------------------------------------------------------------------------
int Hid::supportedTouchTapCount()const
{
    return XBASE_UITOUCHSET_TOUCH_COUNT_MAX;
}

//------------------------------------------------------------------------------
int Hid::touchCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Touch Hid::touchAtIndex(const int aIndex)const
{
    if (touchCount() <= aIndex) {
        XBASE_ERROR_INVALID_VALUE(aIndex);
        return Touch(XBASE_UITOUCHSET_TOUCH_COUNT_MAX);
    }
    return mExt.touch;
}

//------------------------------------------------------------------------------
Hid_Ext::Hid_Ext()
: touch(XBASE_UITOUCHSET_TOUCH_COUNT_MAX)
{
}

} // namespace
// EOF
