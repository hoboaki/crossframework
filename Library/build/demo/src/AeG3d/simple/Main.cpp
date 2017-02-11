// 文字コード：UTF-8
#include <ae/base/All.hpp>
#include <ae/g3d/All.hpp>

//------------------------------------------------------------------------------
int xmain(::ae::base::Application& aApp)
{
    // ディスプレイ作成
    ::ae::base::Display display = ::ae::base::Display(::ae::base::DisplayContext());

    // レンダラー作成
    ::ae::g3d::Renderer renderer(display);

    // ディスプレイ表示
    display.show();

    // イベントループ
    bool doExit = false;
    while (!doExit) {
        // イベントの取得
        ::ae::base::AppEvent::EnumType event = aApp.receiveEvent();

        // イベントによって分岐
        switch (event) {
            case ::ae::base::AppEvent::Quit:
                doExit = true;
                break;

            case ::ae::base::AppEvent::Update:
            {
                // ディスプレイが閉じてたら終了
                if (display.isClosed()) {
                    aApp.quit();
                    continue;
                }

                // クリアカラー
                static float red = 0.0f;
                red += 0.01f;
                if (1 < red) {
                    red = 0;
                }

                // フレームバッファのクリア
                renderer.fbSetClearColor(::ae::base::Color4(red, 0.9f, 0.9f, 1.0f));
                renderer.fbClear();

                // 描画の完了を待つ
                renderer.waitDrawDone();

                // 転送
                renderer.copyToDisplay(display);
            }
            break;

            default:
                break;
        }
    }


    // 終了
    return 0;
}

// EOF
