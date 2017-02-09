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

    // フレームバッファのクリアカラー設定
    renderer.fbSetClearColor(::ae::base::Color4(0.5f, 0.5f, 0.5f, 0.5f));

    // 三角形の頂点バッファを作成
    ::ae::g3d::VtxBuffer vtx(1, 3);
    vtx.begin(::ae::g3d::PrimitiveKind::Triangles);
    {
        vtx.color(1, 0, 0);
        vtx.vertex(0.0f, 0.5f);

        vtx.color(0, 1, 0);
        vtx.vertex(0.5f, -0.5f);

        vtx.color(0, 0, 1);
        vtx.vertex(-0.5f, -0.5f);
    }
    vtx.end();
    vtx.flush();

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

                // フレームバッファのクリア
                renderer.fbClear();

                // シェーダー初期化
                renderer.sdReset();

                // 三角形を回転
                static float deg = 0.0f;
                deg += 1.0f;
                if (360.0f <= deg) {
                    deg = 0;
                }

                // ビュー行列指定
                renderer.sdSetMtxView(::ae::base::Matrix34::Rotate(::ae::base::Degree(deg).toAngle(), ::ae::base::Vector3::UnitZ()));

                // 三角形を描画
                vtx.draw();

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
