// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_MOUSEBTNKIND_HPP)
#else
#define XBASE_INCLUDED_MOUSEBTNKIND_HPP

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Hid
//@{
/// マウスのボタンの種類。
enum MouseBtnKind
{
    MouseBtnKind_L, ///< 左。
    MouseBtnKind_R, ///< 右。(副ボタン)
    MouseBtnKind_M, ///< 中。(3ボタン)

    // term
    MouseBtnKind_TERMINATE,
    MouseBtnKind_MIN = 0,
    MouseBtnKind_MAX = MouseBtnKind_TERMINATE - 1
};
//@}

} // namespace
#endif
// EOF
