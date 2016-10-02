// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_MOUSEBTNBITSET_HPP)
#else
#define XBASE_INCLUDED_MOUSEBTNBITSET_HPP

#include <XBase/BitSet.hpp>
#include <XBase/MouseBtnKind.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-HID
//@{
    /// @brief マウスのボタンのビットセット。
    /// @details
    /// ビットのインデックスは MouseBtnKind を使用しています。
typedef BitSet< MouseBtnKind_TERMINATE > MouseBtnBitSet;
//@}

} // namespace
#endif
// EOF
