// 文字コード：UTF-8
#include <XBase/HID.hpp>

//------------------------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/Touch.hpp>
#include <XBase/Unused.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
int HID::keyboardCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Keyboard HID::keyboardAtIndex(const int aIndex)const
{
    XBASE_ASSERT_LESS(aIndex, keyboardCount());
    XBASE_UNUSED(aIndex);
    return mEXT.keyboard;
}

//------------------------------------------------------------------------------
int HID::mouseCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Mouse HID::mouseAtIndex(const int aIndex)const
{
    XBASE_ASSERT_LESS(aIndex, mouseCount());
    XBASE_UNUSED(aIndex);
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
const Touch HID::touchAtIndex(const int)const
{
    XBASE_ASSERT_NOT_REACHED();
    return Touch(1);
}

} // namespace
// EOF