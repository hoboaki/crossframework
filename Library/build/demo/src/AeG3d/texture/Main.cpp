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

    // 矩形の頂点バッファを準備
    ::ae::g3d::VtxBuffer vtx(1, 4);
    {// 頂点を作成
        vtx.begin(::ae::g3d::PrimitiveKind::Quads);
        {
            vtx.texCoord(1.0f, 1.0f);
            vtx.vertex(0.5f, 0.5f);

            vtx.texCoord(1.0f, 0.0f);
            vtx.vertex(0.5f, -0.5f);

            vtx.texCoord(0.0f, 0.0f);
            vtx.vertex(-0.5f, -0.5f);

            vtx.texCoord(0.0f, 1.0f);
            vtx.vertex(-0.5f, 0.5f);
        }
        vtx.end();
        vtx.flush();
    }

    // テクスチャの準備
    ::ae::base::AutoMemBlock resData = ae::base::ResFile::Read("res/RGBA8.bin");
    ::ae::g3d::ResBin resBin(resData->head());
    resBin.setup(); // TextureBufferの準備
    ::ae::g3d::TexSetting texSetting;
    {// 設定を作成
        const int texIndex = 0; // 先頭のテクスチャを使用
        texSetting.setIsActive(true);
        texSetting.bindBuffer(*resBin.tex(texIndex).texBufferPtr());
    }

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

                // テクスチャを設定
                renderer.sdReset();
                renderer.sdSetTex(::ae::g3d::TexId::No0, texSetting);

                // 矩形を描画
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
