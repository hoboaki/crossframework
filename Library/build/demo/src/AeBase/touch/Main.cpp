// 文字コード：UTF-8
#include <ae/base/All.hpp>

//------------------------------------------------------------------------------
int xmain(::ae::base::Application& aApp)
{
    // ディスプレイの作成
    ::ae::base::Display display = ::ae::base::Display(::ae::base::DisplayContext());

    // Hidの作成
    ::ae::base::Hid hid(display);

    // ディスプレイの表示
    display.show();

    // メインループ
    while (aApp.receiveEvent() != ::ae::base::AppEvent::Quit) {
        // 更新以外は何もしない
        if (aApp.lastEvent() != ::ae::base::AppEvent::Update) {
            continue;
        }

        // タッチの値を見てコンソールに出力
        const ::ae::base::Touch touch = hid.touch();
        for (int i = 0; i < touch.tapCount(); ++i) {
            const ::ae::base::TouchTap tap = touch.tapAtIndex(i);
            if (tap.isTrigger()) {
                AE_BASE_COUTFMT_LINE_WITH_TIME(
                    "[%lu] trigger(%lu) : (%d,%d)",
                    i,
                    tap.tapCount(),
                    int(tap.pos().x),
                    int(tap.pos().y)
                    );
            }
            if (tap.isRelease()) {
                AE_BASE_COUTFMT_LINE_WITH_TIME(
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
