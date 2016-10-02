// 文字コード：UTF-8
#include <XBase/XBase.hpp>

//------------------------------------------------------------------------------
int xmain(::XBase::Application& aApp)
{
    // 読み込み
    const ::XBase::AutoMemBlock data = ::XBase::ResFile::Read("res/Simple.txt");

    // データサイズを出力
    XBASE_COUTFMT_LINE("size: %d", int(data->size()));

    // 終端文字を入れるためのバッファを作成
    char* buffer = new char[data->size() + 1];
    for (::XBase::pword_t i = 0; i < data->size(); ++i)
    {
        buffer[i] = reinterpret_cast<const char*>(data->head())[i];
    }
    buffer[data->size()] = '\0';

    // テキストファイルの内容を出力
    XBASE_COUT_LINE(buffer);

    // バッファ解放
    delete[] buffer;
    buffer = 0;

    // 終了イベントがくるまでループ
    while (aApp.receiveEvent() != ::XBase::AppEvent_Quit)
    {
    }

    // 終了
    return 0;
}

// EOF
