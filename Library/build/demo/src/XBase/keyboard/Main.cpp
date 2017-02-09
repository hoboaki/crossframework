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

        // キーボードの値を見てコンソールに出力
        const ::ae::base::Keyboard kbd = hid.keyboard();
        // 例えばReturn(Enter)
        if (kbd.isPulse(::ae::base::KeyKind::Return)) {
            AE_BASE_COUT_LINE_WITH_TIME("Pulse: Return");
        }
        // 例えばA
        if (kbd.isTrigger(::ae::base::KeyKind::A)) {
            AE_BASE_COUT_LINE_WITH_TIME("KeyDown: A");
        }
        if (kbd.isRelease(::ae::base::KeyKind::A)) {
            AE_BASE_COUT_LINE_WITH_TIME("KeyUp  : A");
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
