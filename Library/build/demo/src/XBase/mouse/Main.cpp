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

        // マウスの値を見てコンソールに出力
        const ::ae::base::Mouse mouse = hid.mouse();
        if (mouse.isHold(::ae::base::MouseBtnKind::L)) {
            AE_BASE_COUTFMT_LINE("LBtn Hold (%d,%d)", mouse.pos().x, mouse.pos().y);
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
