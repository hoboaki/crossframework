// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_SEEKORIGIN_HPP)
#else
#define XBASE_INCLUDED_SEEKORIGIN_HPP

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-IO
//@{
/// Seek関数の基準。
struct SeekOrigin
{
    enum EnumType
    {
        Begin,   ///< 先頭。
        Current, ///< 現在位置。
        End,     ///< 末尾。
        
        TERM,
    };
};
//@}

} // namespace
#endif
// EOF
