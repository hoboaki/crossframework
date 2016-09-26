/**
 * @file
 * @brief Main関数を記述する。
 * @author akino
 */

//------------------------------------------------------------
#include <XBase/XBase.hpp>
#include <XG3D/XG3D.hpp>

//------------------------------------------------------------
int xmain( ::XBase::Application& aApp )
{
    // ディスプレイ作成
    ::XBase::Display display = ::XBase::Display( ::XBase::DisplayContext() );
    
    // レンダラー作成
    ::XG3D::Renderer renderer( display );

    // フレームバッファのクリアカラー設定
    renderer.fbSetClearColor( ::XBase::Color4( 0.5f , 0.5f , 0.5f , 0.5f ) );

    // 矩形の頂点バッファを準備
    ::XG3D::VtxBuffer vtx( 1 , 4 );
    {// 頂点を作成
        vtx.begin( ::XG3D::PrimitiveKind_Quads );
        {
            vtx.texCoord( 1.0f , 1.0f );
            vtx.vertex( 0.5f , 0.5f );
    
            vtx.texCoord( 1.0f , 0.0f );
            vtx.vertex( 0.5f , -0.5f );

            vtx.texCoord( 0.0f , 0.0f );
            vtx.vertex( -0.5f , -0.5f );    
        
            vtx.texCoord( 0.0f , 1.0f );
            vtx.vertex( -0.5f , 0.5f );    
        }
        vtx.end();
        vtx.flush();
    }

    // テクスチャの準備
    ::XBase::AutoMemBlock resData = XBase::ResFile::Read( "res/RGBA8.bin" );
    ::XG3D::ResBin resBin( resData->head() );
    resBin.setup(); // TextureBufferの準備
    ::XG3D::TexSetting texSetting;    
    {// 設定を作成
        const ::XG3D::uint texIndex = 0; // 先頭のテクスチャを使用
        texSetting.setIsActive( true );
        texSetting.bindBuffer( *resBin.tex( texIndex ).texBufferPtr() );
    }

    // ディスプレイ表示
    display.show();

    // イベントループ
    bool doExit = false;
    while( !doExit )
    {
        // イベントの取得
        ::XBase::AppEvent event = aApp.receiveEvent();
        
        // イベントによって分岐
        switch ( event )
        {
        case ::XBase::AppEvent_Quit:
            doExit = true;
            break;

        case ::XBase::AppEvent_Update:
            {        
                // ディスプレイが閉じてたら終了
                if ( display.isClosed() )
                {
                    aApp.quit();
                    continue;
                }

                // フレームバッファのクリア
                renderer.fbClear();
                
                // テクスチャを設定
                renderer.sdReset();
                renderer.sdSetTex( ::XG3D::TexId_0 , texSetting );

                // 矩形を描画
                vtx.draw();

                // 描画の完了を待つ
                renderer.waitDrawDone();

                // 転送
                renderer.copyToDisplay( display );
            }
            break;

        default:
            break;
        }
    }


    // 終了
    return 0;
}

//------------------------------------------------------------
// EOF
