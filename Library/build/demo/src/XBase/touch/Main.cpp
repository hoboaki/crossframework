// 文字コード：UTF-8
#include <XBase/XBase.hpp>

//------------------------------------------------------------------------------
int xmain(::XBase::Application& aApp)
{
    // ディスプレイの作成
    ::XBase::Display display = ::XBase::Display(::XBase::DisplayContext());

    // Hidの作成
    ::XBase::Hid hid(display);

    // ディスプレイの表示
    display.show();

    // メインループ
    while (aApp.receiveEvent() != ::XBase::AppEvent_Quit) {
        // 更新以外は何もしない
        if (aApp.lastEvent() != ::XBase::AppEvent_Update) {
            continue;
        }

        // タッチの値を見てコンソールに出力
        const ::XBase::Touch touch = hid.touch();
        for (int i = 0; i < touch.tapCount(); ++i) {
            const ::XBase::TouchTap tap = touch.tapAtIndex(i);
            if (tap.isTrigger()) {
                XBASE_COUTFMT_LINE_WITH_TIME(
                    "[%lu] trigger(%lu) : (%d,%d)",
                    i,
                    tap.tapCount(),
                    int(tap.pos().x),
                    int(tap.pos().y)
                    );
            }
            if (tap.isRelease()) {
                XBASE_COUTFMT_LINE_WITH_TIME(
                    "[%lu] release(%lu) : (%d,%d)",
                    i,
                    tap.tapCount(),
                    int(tap.pos().x),
                    int(tap.pos().y)
                    );
            }
        }

        // ディスプレイが閉じられたら終了する
        if (display.isClosed()) {
            aApp.quit();
        }
    }

    // 終了
    return 0;
}

// EOF
