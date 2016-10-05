// 文字コード：UTF-8
#include <XBase/Hid.hpp>

#include <XBase/Display.hpp>
#include <XBase/Touch.hpp>
#include <XBase/Unused.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
int Hid::keyboardCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Keyboard Hid::keyboardAtIndex(const int aIndex)const
{
    XBASE_ASSERT_LESS(aIndex, keyboardCount());
    XBASE_UNUSED(aIndex);
    return mExt.keyboard;
}

//------------------------------------------------------------------------------
int Hid::mouseCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
const Mouse Hid::mouseAtIndex(const int aIndex)const
{
    XBASE_ASSERT_LESS(aIndex, mouseCount());
    XBASE_UNUSED(aIndex);
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
const Touch Hid::touchAtIndex(const int)const
{
    XBASE_ASSERT_NOT_REACHED();
    return Touch(1);
}

} // namespace
// EOF
