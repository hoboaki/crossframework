/**
 * @file
 * @brief Main関数を記述する。
 * @author akino
 */

//------------------------------------------------------------
#include <XBase/XBase.hpp>

//------------------------------------------------------------
int xmain( ::XBase::Application& aApp )
{
    // ディスプレイの作成
    ::XBase::Display display = ::XBase::Display( ::XBase::DisplayContext() );

    // HIDの作成
    ::XBase::HID hid( display );

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

        // キーボードの値を見てコンソールに出力
        const ::XBase::Keyboard kbd = hid.keyboard();
        // 例えばReturn(Enter)
        if ( kbd.isPulse( ::XBase::KeyKind_Return ) )
        {
            XBASE_COUT_LINE_WITH_TIME( "Pulse: Return" );
        }
        // 例えばA
        if ( kbd.isTrigger( ::XBase::KeyKind_A ) )
        {
            XBASE_COUT_LINE_WITH_TIME( "KeyDown: A" );
        }
        if ( kbd.isRelease( ::XBase::KeyKind_A ) )
        {
            XBASE_COUT_LINE_WITH_TIME( "KeyUp  : A" );
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

//------------------------------------------------------------
// EOF
