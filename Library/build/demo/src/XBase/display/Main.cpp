// 文字コード：UTF-8

//------------------------------------------------------------------------------
#include <XBase/XBase.hpp>

//------------------------------------------------------------------------------
int xmain( ::XBase::Application& aApp )
{
    // ディスプレイの作成
    ::XBase::Display display = ::XBase::Display( ::XBase::DisplayContext() );

    // ディスプレイの表示
    display.show();

    // メインループ
    while ( aApp.receiveEvent() != ::XBase::AppEvent_Quit )
    {
        // 更新以外は何もしない
        if ( aApp.lastEvent() != ::XBase::AppEvent_Update )
        {
            continue;
        }

        // ディスプレイが閉じられたら終了する
        if ( display.isClosed() )
        {
            aApp.quit();
        }
    }

    // 終了
    return 0;
}

//------------------------------------------------------------------------------
// EOF
