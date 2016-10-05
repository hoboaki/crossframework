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
    while (aApp.receiveEvent() != ::XBase::AppEvent::Quit) {
        // 更新以外は何もしない
        if (aApp.lastEvent() != ::XBase::AppEvent::Update) {
            continue;
        }

        // キーボードの値を見てコンソールに出力
        const ::XBase::Keyboard kbd = hid.keyboard();
        // 例えばReturn(Enter)
        if (kbd.isPulse(::XBase::KeyKind::Return)) {
            XBASE_COUT_LINE_WITH_TIME("Pulse: Return");
        }
        // 例えばA
        if (kbd.isTrigger(::XBase::KeyKind::A)) {
            XBASE_COUT_LINE_WITH_TIME("KeyDown: A");
        }
        if (kbd.isRelease(::XBase::KeyKind::A)) {
            XBASE_COUT_LINE_WITH_TIME("KeyUp  : A");
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
