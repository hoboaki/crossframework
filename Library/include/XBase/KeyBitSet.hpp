// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_KEYBITSET_HPP)
#else
#define XBASE_INCLUDED_KEYBITSET_HPP

#include <XBase/BitSet.hpp>
#include <XBase/KeyKind.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-HID
//@{
    /// @brief キーボードのキーのビットセット。
    /// @details
    /// ビットのインデックスは KeyKind を使用しています。
typedef BitSet< KeyKind_TERMINATE > KeyBitSet;
//@}

} // namespace
#endif
// EOF
