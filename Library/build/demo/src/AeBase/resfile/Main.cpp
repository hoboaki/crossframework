// 文字コード：UTF-8
#include <ae/base/All.hpp>

//------------------------------------------------------------------------------
int xmain(::ae::base::Application& aApp)
{
    // 読み込み
    const ::ae::base::AutoMemBlock data = ::ae::base::ResFile::Read("res/Simple.txt");

    // データサイズを出力
    AE_BASE_COUTFMT_LINE("size: %d", int(data->size()));

    // 終端文字を入れるためのバッファを作成
    char* buffer = new char[data->size() + 1];
    for (::ae::base::pword_t i = 0; i < data->size(); ++i) {
        buffer[i] = reinterpret_cast<const char*>(data->head())[i];
    }
    buffer[data->size()] = '\0';

    // テキストファイルの内容を出力
    AE_BASE_COUT_LINE(buffer);

    // バッファ解放
    delete[] buffer;
    buffer = 0;

    // 終了イベントがくるまでループ
    while (aApp.receiveEvent() != ::ae::base::AppEvent::Quit) {
    }

    // 終了
    return 0;
}

// EOF
