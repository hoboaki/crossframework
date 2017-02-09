// 文字コード：UTF-8

#include <ae/base/All.hpp>
#include <ae/g3d/All.hpp>

//------------------------------------------------------------------------------
int xmain( ::ae::base::Application& aApp)
{
    // ディスプレイ作成
    ::ae::base::Display display = ::ae::base::Display( ::ae::base::DisplayContext() );

    // レンダラー作成
    ::ae::g3d::Renderer renderer( display );

    // 表示
    display.show();

    // イベントループ
    bool doExit = false;
    while( !doExit )
    {
        // イベントの取得
        ::ae::base::AppEvent::EnumType event = aApp.receiveEvent();
        
        // イベントによって分岐
        switch ( event ) {
        case ::ae::base::AppEvent::Quit:
            doExit = true;
            break;

        case ::ae::base::AppEvent::Update:
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
        if ( display.isClosed() ) {
            aApp.quit();
            continue;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
// EOF
