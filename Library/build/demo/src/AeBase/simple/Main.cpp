// 文字コード：UTF-8
#include <ae/base/All.hpp>

//------------------------------------------------------------------------------
int xmain(::ae::base::Application& aApp)
{
    // 開始
    AE_BASE_COUT_LINE("xmain started.");

    // 終了イベントがくるまでループ
    int count = 0;
    while (aApp.receiveEvent() != ::ae::base::AppEvent::Quit) {
        // 更新以外は何もしない
        if (aApp.lastEvent() != ::ae::base::AppEvent::Update) {
            continue;
        }

        // 60フレごとにprintf
        ++count;
        if (count % 60 == 0) {
            AE_BASE_COUTFMT_LINE("count is %d.", count);
        }
    }

    // 終了
    AE_BASE_COUT_LINE("xmain finished.");
    return 0;
}

// EOF
