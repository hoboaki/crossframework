// 文字コード：UTF-8
#include <XBase/XBase.hpp>
#include <XG3D/XG3D.hpp>

//------------------------------------------------------------------------------
int xmain(::XBase::Application& aApp)
{
    // ディスプレイ作成
    ::XBase::Display display = ::XBase::Display(::XBase::DisplayContext());

    // レンダラー作成
    ::XG3D::Renderer renderer(display);

    // フレームバッファのクリアカラー設定
    renderer.fbSetClearColor(::XBase::Color4(0.5f, 0.5f, 0.5f, 0.5f));

    // 三角形の頂点バッファを作成
    ::XG3D::VtxBuffer vtx(1, 3);
    vtx.begin(::XG3D::PrimitiveKind::Triangles);
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
        ::XBase::AppEvent::EnumType event = aApp.receiveEvent();

        // イベントによって分岐
        switch (event) {
            case ::XBase::AppEvent::Quit:
                doExit = true;
                break;

            case ::XBase::AppEvent::Update:
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
                renderer.sdSetMtxView(::XBase::Matrix34::Rotate(::XBase::Degree(deg).toAngle(), ::XBase::Vector3::UnitZ()));

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
