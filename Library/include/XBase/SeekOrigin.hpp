// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_SEEKORIGIN_HPP)
#else
#define XBASE_INCLUDED_SEEKORIGIN_HPP

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-IO
//@{
    /// Seek関数の基準。
    enum SeekOrigin
    {
        SeekOrigin_Begin,   ///< 先頭。
        SeekOrigin_Current, ///< 現在位置。
        SeekOrigin_End,     ///< 末尾。
        // term
        SeekOrigin_TERMINATE,
        SeekOrigin_MIN = 0,
        SeekOrigin_MAX = SeekOrigin_TERMINATE-1
    };
//@}

} // namespace
#endif
// EOF
