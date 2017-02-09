// 文字コード：UTF-8
#include <ae/base/Application.hpp>

#include <ae/base/Display.hpp>
#include <ae/base/Hid.hpp>
#include "EntryPoint_Sync.h"
#include "AeBaseUIWindow.h"

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
void Application::quit()
{
    // iOSにはquitするという概念がないので何もしない
}

//------------------------------------------------------------------------------
AppEvent::EnumType Application::receiveEventCore()
{
    // まずUIMainにシグナル送信して同期する
    XBaseEntryPointSync_UIMainSignal();
    XBaseEntryPointSync_XMainWait();

    // 新しいイベントを取得
    switch (XBaseEntryPointSync_GetAppEvent()) {
        case XBaseAppEvent_Quit:
            return AppEvent::Quit;

        case XBaseAppEvent_Update:
        {// Hidの更新
            if (mDisplayPtr.isValid()) {
                // タッチ入力ポーリング
                const XBaseUITouchSet* touchSet = XBaseUIWindow_PollTouch(mDisplayPtr->ext_().windowPtr);
                if (mDisplayPtr->ext_().hidPtr.isValid()) {
                    const int screenHeight = mDisplayPtr->mainScreen().height();
                    TouchUpdateData data = {};
                    for (int i = 0; i < AE_BASE_UITOUCHSET_TOUCH_COUNT_MAX; ++i) {
                        const XBaseUITouch& src = touchSet->touches[i];
                        TouchTapUpdateData& dst = data.taps[i];
                        dst.tapCount = src.tapCount;
                        dst.pos.x = s16(src.tapPosX);
                        dst.pos.y = s16(screenHeight - 1 - src.tapPosY); // 左下原点に変換
                    }
                    mDisplayPtr->ext_().hidPtr->ext_().touch.update(data);
                }
            }
        }
        return AppEvent::Update;

        default:
            AE_BASE_ASSERT_NOT_REACHED();
            return AppEvent::EnumType(0);
    }
}

}} // namespace
// EOF
