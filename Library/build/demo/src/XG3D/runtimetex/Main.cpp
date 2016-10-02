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

    // 矩形の頂点バッファを準備
    ::XG3D::VtxBuffer vtx(1, 4);
    {// 頂点を作成
        vtx.begin(::XG3D::PrimitiveKind_Quads);
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

    // 実行時テクスチャのイメージを作成
    ::XG3D::RuntimeTex runtimeTex(::XG3D::RuntimeTexContext::Create(
        ::XG3D::ResTexFormat_RGBA8,
        256,
        256
        ));
    runtimeTex.beginEdit();
    {
        ::XBase::Color4b color;
        color.a = 0xFF;
        for (::XBase::uint y = 0; y < runtimeTex.context().height(); ++y)
        {
            // 縦方向にRのグラデーション
            color.r = ::XBase::u8(y);
            for (::XBase::uint x = 0; x < runtimeTex.context().width(); ++x)
            {
                // 横方向にGのグラデーション
                color.g = ::XBase::u8(x);

                // 設定
                runtimeTex.setPixel(x, y, color);
            }
        }
    }
    runtimeTex.endEdit();

    // テクスチャの準備
    ::XG3D::TexBuffer texBuffer(runtimeTex.texResData());
    ::XG3D::TexSetting texSetting;
    {// 設定を作成
        texSetting.setIsActive(true);
        texSetting.bindBuffer(texBuffer);
    }

    // ディスプレイ表示
    display.show();

    // イベントループ
    bool doExit = false;
    while (!doExit)
    {
        // イベントの取得
        ::XBase::AppEvent event = aApp.receiveEvent();

        // イベントによって分岐
        switch (event)
        {
            case ::XBase::AppEvent_Quit:
                doExit = true;
                break;

            case ::XBase::AppEvent_Update:
            {
                // ディスプレイが閉じてたら終了
                if (display.isClosed())
                {
                    aApp.quit();
                    continue;
                }

                // フレームバッファのクリア
                renderer.fbClear();

                // テクスチャを設定
                renderer.sdReset();
                renderer.sdSetTex(::XG3D::TexId_0, texSetting);

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
