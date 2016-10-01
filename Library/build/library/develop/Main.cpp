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

    // 表示
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
                // フレームバッファのクリア
                renderer.fbClear();

                // 描画の完了を待つ
                renderer.waitDrawDone();

                // 転送
                renderer.copyToDisplay( display );
            }
            break;

        default:
            break;
        }
        
        // ディスプレイが閉じてたら終了
        if ( display.isClosed() )
        {
            aApp.quit();
            continue;
        }
    }

    return 0;
}

//------------------------------------------------------------
// EOF
