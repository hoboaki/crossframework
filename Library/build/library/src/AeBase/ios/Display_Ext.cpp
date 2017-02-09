// 文字コード：UTF-8
#include <ae/base/Display.hpp>

#include <ae/base/Application.hpp>
#include <ae/base/Ref.hpp>
#include "XBaseUIScreen.h"
#include "XBaseUIWindow.h"

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
int Display::screenCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
Screen& Display::screenAtIndex(const int aIndex)
{
    AE_BASE_ASSERT_LESS(aIndex, screenCount());
    return mainScreen();
}

//------------------------------------------------------------------------------
Screen& Display::mainScreen()
{
    return *mExt.mainScreen;
}

//------------------------------------------------------------------------------
void Display::show()
{
    XBaseUIWindow_Show(mExt.windowPtr);
}

//------------------------------------------------------------------------------
bool Display::isClosed()const
{
    // iOSではWindowが閉じることはないので常にfalse
    return false;
}

//------------------------------------------------------------------------------
Display_Ext::Display_Ext(const DisplayContext& aContext)
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
Display_Ext::~Display_Ext()
{
    // メインスクリーンの削除
    mainScreen.reset();

    // Window解放
    XBaseUIWindow* ptr = windowPtr;
    windowPtr = 0;
    XBaseUIWindow_Destroy(ptr);
}

}} // namespace
// EOF
