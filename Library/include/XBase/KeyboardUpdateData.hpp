// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_KEYBOARDUPDATEDATA_HPP)
#else
#define XBASE_INCLUDED_KEYBOARDUPDATEDATA_HPP

//------------------------------------------------------------------------------
#include <XBase/KeyBitSet.hpp>

//------------------------------------------------------------------------------
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

} // namespace
#endif
// EOF
