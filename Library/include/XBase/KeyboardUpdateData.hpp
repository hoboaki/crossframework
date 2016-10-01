/**
 * @file
 * @brief KeyboardUpdateData型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_KEYBOARDUPDATEDATA_HPP)
#else
#define XBASE_INCLUDED_KEYBOARDUPDATEDATA_HPP

//------------------------------------------------------------
#include <XBase/KeyBitSet.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-HID
//@{
    /// キーボードの更新データ。
    struct KeyboardUpdateData
    {
        KeyBitSet hold;
        KeyBitSet pulse;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
