// 文字コード：UTF-8
#include <XBase/Application.hpp>

//------------------------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/Hid.hpp>
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
    mExt.doQuit = true;

    // 終了処理
    XBaseNSApp_Terminate();
}

//------------------------------------------------------------------------------
AppEvent Application::receiveEventCore()
{
    // Hidのフラグをおろしておく
    if (mDisplayPtr.isValid()) {
        mDisplayPtr->ext_().keyboardUpdateData.pulse.clear();
        mDisplayPtr->ext_().mouseUpdateData.posUpdated = false;
    }

    // イベント処理
    XBaseNSApp_PollEvent();

    // 終了要求が来たら終了
    if (mExt.doQuit) {
        return AppEvent_Quit;
    }

    // Hid更新
    if (mDisplayPtr.isValid()
        && mDisplayPtr->ext_().hidPtr.isValid()
        )
    {
        // 更新の前の設定
        if (mDisplayPtr->ext_().mouseUpdateData.hold.isAnyOn()) {
            mDisplayPtr->ext_().mouseUpdateData.posUpdated = true;
        }

        // 更新
        Hid_Ext& hidExt = mDisplayPtr->ext_().hidPtr->ext_();
        hidExt.keyboard.update(mDisplayPtr->ext_().keyboardUpdateData);
        hidExt.mouse.update(mDisplayPtr->ext_().mouseUpdateData);
    }

    {// 60フレ同期
        s64 currentTicks = s64();
        while (true) {
            currentTicks = Time::LocalTime().ticks();
            if ((currentTicks - mExt.prevUpdateTicks) < 166666) {
                Thread::Sleep(TimeSpan::FromMilliseconds(1));
                continue;
            }
            break;
        }
        mExt.prevUpdateTicks = currentTicks;
    }

    // 通常は更新
    return AppEvent_Update;
}

//------------------------------------------------------------------------------
Applcation_Ext::Applcation_Ext()
: prevUpdateTicks(Time::LocalTime().ticks())
, doQuit(false)
{
    XBaseNSApp_Initialize();
}

//------------------------------------------------------------------------------
Applcation_Ext::~Applcation_Ext()
{
    XBaseNSApp_Finalize();
}

} // namespace
// EOF
