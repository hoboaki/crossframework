// 文字コード：UTF-8
#include <XBase/Screen.hpp>

//------------------------------------------------------------------------------
#include <XBase/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
Screen::Screen(
    Display_EXT& aOwner,
    const int aWidth,
    const int aHeight
    )
: mOwner(aOwner)
, mEXT()
, mWidth(aWidth)
, mHeight(aHeight)
{
}

//------------------------------------------------------------------------------
int Screen::width()const
{
    return mWidth;
}

//------------------------------------------------------------------------------
int Screen::height()const
{
    return mHeight;
}

//------------------------------------------------------------------------------
bool Screen::isContains(const ScreenPosPOD& aPos)const
{
    return 0 <= aPos.x && aPos.x < int(mWidth)
        && 0 <= aPos.y && aPos.y < int(mHeight);
}

//------------------------------------------------------------------------------
Display_EXT& Screen::display_()
{
    return mOwner;
}

//------------------------------------------------------------------------------
Screen_EXT& Screen::ext_()
{
    return mEXT;
}

} // namespace
// EOF
