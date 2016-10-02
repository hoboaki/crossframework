// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_MEMBLOCK_HPP)
#else
#define XBASE_INCLUDED_MEMBLOCK_HPP

#include <XBase/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Memory
//@{
/// メモリブロック。
class MemBlock
{
public:
    /// @name コンストラクタ。
    //@{
    /// サイズ0のメモリブロックを作成。
    MemBlock();

    /// アドレス・サイズを指定して作成。
    MemBlock(ptr_t aAddr, pword_t aSize);
    //@}

    /// @name プロパティの取得。
    //@{
    bool    isNull()const; ///< 先頭アドレスが0か。
    ptr_t   head()const; ///< 先頭アドレスを取得。
    ptr_t   tail()const; ///< 終端アドレス( head() + size() )を取得。
    pword_t size()const; ///< ブロックのバイト数を取得。
    //@}

private:
    ptr_t   mAddr;
    pword_t mSize;
};
//@}

} // namespace
#endif
// EOF
