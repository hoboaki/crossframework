// 文字コード：UTF-8
#include <XBase/Display.hpp>

//------------------------------------------------------------------------------
#include <XBase/Application.hpp>
#include <XBase/Ref.hpp>
#include "XBaseUIScreen.h"
#include "XBaseUIWindow.h"

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
uint Display::screenCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
Screen& Display::screenAtIndex(const uint aIndex)
{
    XBASE_RANGE_ASSERT_MAX(aIndex, screenCount());
    return mainScreen();
}

//------------------------------------------------------------------------------
Screen& Display::mainScreen()
{
    return *mEXT.mainScreen;
}

//------------------------------------------------------------------------------
void Display::show()
{
    XBaseUIWindow_Show(mEXT.windowPtr);
}

//------------------------------------------------------------------------------
bool Display::isClosed()const
{
    // iOSではWindowが閉じることはないので常にfalse
    return false;
}

//------------------------------------------------------------------------------
Display_EXT::Display_EXT(const DisplayContext& aContext)
: windowPtr(0)
, mainScreen()
, hidPtr()
{
    // Window作成
    windowPtr = XBaseUIWindow_Create();

    // メインスクリーンの作成
    XBaseUIRect rect = {};
    XBaseUIScreen_GetMainScreenBounds(&rect);
    mainScreen.init(Ref(*this), uint(rect.sizeW), uint(rect.sizeH));
}

//------------------------------------------------------------------------------
Display_EXT::~Display_EXT()
{
    // メインスクリーンの削除
    mainScreen.reset();

    // Window解放
    XBaseUIWindow* ptr = windowPtr;
    windowPtr = 0;
    XBaseUIWindow_Destroy(ptr);
}

} // namespace
// EOF
