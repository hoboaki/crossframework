// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_RESFILESTREAM_HPP)
#else
#define XBASE_INCLUDED_RESFILESTREAM_HPP

#include <XBase/FunctionAttribute.hpp>
#include <XBase/IAllocator.hpp>
#include <XBase/IReadStream.hpp>

// EXT
#include <XBase/ResFileStream_STDC.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-IO
//@{
    /// @brief アプリケーションのリソースファイルを読み込むクラス。
    /// @details
    /// リソースファイルは読み込み専用です。書き込むことはできません。
    /// @n
    /// ルートディレクトリはOSによって異なります。 @n
    /// Windowsだと ".exeファイルがあるディレクトリ" がルートになります。 @n
    /// MacOSXだと ".app/Contents/Resources" がルートになります。@n
    /// iOSだと ".app/" がルートになります。@n
    /// @n
    /// OSによっては想定しないファイルがリソースファイルと同じ場所に置かれることもあります。@n
/// そのため "data" や "resource" といった名前のフォルダを１つほりそれ以下に全てのリソースファイルを配置することをおすすめします。@n
class ResFileStream : public IReadStream
{
public:
    /// @name 定数
    //@{
    /// ファイル読み込み先アドレスに求められるアライメント値。
    static const pword_t ReadBufferAlignment = IAllocator::DefaultAlignment;
    //@}

    /// @name 関数
    //@{
    /// @brief  指定のデータサイズを読み込む時に必要なバッファサイズを求める。
    /// @param aSize 読み込みデータサイズ。
    /// @details
    /// 実行環境によっては実際のデータサイズよりも大きいバッファサイズを要求することがあるため、
    /// バッファ領域は必ずこの関数で求められたサイズを確保してください。
    static pword_t CalcReadBufferSize(pword_t aSize);
    //@}

    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief 何もせず作成する。
    /// @details ファイルオープンは open() を使用してください。
    ResFileStream();

    /// @brief 指定のファイルをオープンしつつ作成する。
    /// @param aPath オープンするファイルパス。
    /// @details オープンに失敗したらエラーになります。
    ResFileStream(const char* aPath);

    /// @brief デストラクタ
    /// @details オープン中なら自動で close() を呼びます。
    virtual ~ResFileStream();
    //@}

    /// @name オープン
    //@{
    /// @brief 指定のファイルをオープンする。
    /// @return オープンに成功したらtrue。
    /// @param aPath オープンするファイルパス。
    /// @details 既にオープンしている場合は自動で close() してからオープンします。
    bool open(const char* aPath);
    //@}

    // IReadStreamの実装。
    XBASE_OVERRIDE(pword_t requireReadBufferAlignment()const);
    XBASE_OVERRIDE(pword_t calcReadBufferSize(pword_t aSize)const);
    XBASE_OVERRIDE(pword_t seek(int aOffset, SeekOrigin aOrigin));
    XBASE_OVERRIDE(pword_t read(ptr_t aBuffer, pword_t aSize));
    XBASE_OVERRIDE(void close());

private:
    ResFileStream_EXT mExt;
};

//@}

} // namespace
#endif
// EOF
