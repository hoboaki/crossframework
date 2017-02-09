// 文字コード：UTF-8
#include <ae/base/All.hpp>

//------------------------------------------------------------------------------
int xmain(::ae::base::Application& aApp)
{
    // ディスプレイの作成
    ::ae::base::Display display = ::ae::base::Display(::ae::base::DisplayContext());

    // ディスプレイの表示
    display.show();

    // メインループ
    while (aApp.receiveEvent() != ::ae::base::AppEvent::Quit) {
        // 更新以外は何もしない
        if (aApp.lastEvent() != ::ae::base::AppEvent::Update) {
            continue;
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
