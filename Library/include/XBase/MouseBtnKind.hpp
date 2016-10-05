// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_MOUSEBTNKIND_HPP)
#else
#define XBASE_INCLUDED_MOUSEBTNKIND_HPP

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Hid
//@{
/// マウスのボタンの種類。
struct MouseBtnKind
{
    enum EnumType
    {
        L, ///< 左。
        R, ///< 右。(副ボタン)
        M, ///< 中。(3ボタン)

        TERM,
    };
};
//@}

} // namespace
#endif
// EOF
