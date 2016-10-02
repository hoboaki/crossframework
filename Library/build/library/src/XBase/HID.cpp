// 文字コード：UTF-8
#include <XBase/HID.hpp>

//------------------------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/Keyboard.hpp>
#include <XBase/Mouse.hpp>
#include <XBase/Touch.hpp>

//------------------------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------------------------
HID::HID(Display& aDisplay)
    : mDisplay(aDisplay)
    , mEXT()
{
    mDisplay.ext_().hidPtr.set(*this);
}

//------------------------------------------------------------------------------
HID::~HID()
{
    mDisplay.ext_().hidPtr.unset(*this);
}

//------------------------------------------------------------------------------
const Keyboard HID::keyboard()const
{
    if (0 < keyboardCount())
    {
        return keyboardAtIndex(0);
    }
    return Keyboard();
}

//------------------------------------------------------------------------------
const Mouse HID::mouse()const
{
    if (0 < mouseCount())
    {
        return mouseAtIndex(0);
    }
    return Mouse();
}

//------------------------------------------------------------------------------
const Touch HID::touch()const
{
    if (0 < touchCount())
    {
        return touchAtIndex(0);
    }
    return Touch(0);
}

//------------------------------------------------------------------------------
HID_EXT& HID::ext_()
{
    return mEXT;
}

} // namespace
// EOF
