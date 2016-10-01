// 文字コード：UTF-8

//------------------------------------------------------------------------------
#include <XBase/XBase.hpp>

//------------------------------------------------------------------------------
int xmain( ::XBase::Application& aApp )
{
    // 開始
    XBASE_COUT_LINE( "xmain started." );
    
    // 終了イベントがくるまでループ
    int count = 0;
    while ( aApp.receiveEvent() != ::XBase::AppEvent_Quit )
    {      
        // 更新以外は何もしない
        if ( aApp.lastEvent() != ::XBase::AppEvent_Update )
        {
            continue;
        }

        // 60フレごとにprintf
        ++count;
        if ( count % 60 == 0 )
        {
            XBASE_COUTFMT_LINE( "count is %d." , count );
        }
    }
    
    // 終了
    XBASE_COUT_LINE( "xmain finished." );
    return 0;
}

//------------------------------------------------------------------------------
// EOF
