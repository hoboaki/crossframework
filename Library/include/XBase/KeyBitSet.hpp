/**
 * @file
 * @brief KeyBitSet型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_KEYBITSET_HPP)
#else
#define XBASE_INCLUDED_KEYBITSET_HPP

//------------------------------------------------------------
#include <XBase/BitSet.hpp>
#include <XBase/KeyKind.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-HID
//@{
    /**
     * @brief キーボードのキーのビットセット。
     * @details
     * ビットのインデックスは KeyKind を使用しています。
     */
    typedef BitSet< KeyKind_TERMINATE > KeyBitSet;
//@}
}
//------------------------------------------------------------
#endif
// EOF
