// 文字コード：UTF-8
#include <XBase/Application.hpp>

//------------------------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/HID.hpp>
#include <XBase/Thread.hpp>
#include <XBase/Time.hpp>
#include <XBase/TimeSpan.hpp>
#include "XBaseNSApp.h"

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
void Application::quit()
{
    // フラグを立てる
    mEXT.doQuit = true;

    // 終了処理
    XBaseNSApp_Terminate();
}

//------------------------------------------------------------------------------
AppEvent Application::receiveEventCore()
{
    // HIDのフラグをおろしておく
    if (mDisplayPtr.isValid())
    {
        mDisplayPtr->ext_().keyboardUpdateData.pulse.clear();
        mDisplayPtr->ext_().mouseUpdateData.posUpdated = false;
    }

    // イベント処理
    XBaseNSApp_PollEvent();

    // 終了要求が来たら終了
    if (mEXT.doQuit)
    {
        return AppEvent_Quit;
    }

    // HID更新
    if (mDisplayPtr.isValid()
        && mDisplayPtr->ext_().hidPtr.isValid()
        )
    {
        // 更新の前の設定
        if (mDisplayPtr->ext_().mouseUpdateData.hold.isAnyOn())
        {
            mDisplayPtr->ext_().mouseUpdateData.posUpdated = true;
        }

        // 更新
        HID_EXT& hidExt = mDisplayPtr->ext_().hidPtr->ext_();
        hidExt.keyboard.update(mDisplayPtr->ext_().keyboardUpdateData);
        hidExt.mouse.update(mDisplayPtr->ext_().mouseUpdateData);
    }

    {// 60フレ同期
        s64 currentTicks = s64();
        while (true)
        {
            currentTicks = Time::LocalTime().ticks();
            if ((currentTicks - mEXT.prevUpdateTicks) < 166666)
            {
                Thread::Sleep(TimeSpan::FromMilliseconds(1));
                continue;
            }
            break;
        }
        mEXT.prevUpdateTicks = currentTicks;
    }

    // 通常は更新
    return AppEvent_Update;
}

//------------------------------------------------------------------------------
Application_EXT::Application_EXT()
: prevUpdateTicks(Time::LocalTime().ticks())
, doQuit(false)
{
    XBaseNSApp_Initialize();
}

//------------------------------------------------------------------------------
Application_EXT::~Application_EXT()
{
    XBaseNSApp_Finalize();
}

} // namespace
// EOF
