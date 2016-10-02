// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_TOUCHUPDATEDATA_HPP)
#else
#define XBASE_INCLUDED_TOUCHUPDATEDATA_HPP

#include <XBase/TouchTapUpdateData.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-HID
//@{
/// タッチ入力の更新データ。
struct TouchUpdateData
{
    enum
    {
        /// サポートしている最大タップ数。
        TAP_COUNT_MAX = 8
    };
    TouchTapUpdateData taps[TAP_COUNT_MAX];
};
//@}

} // namespace
#endif
// EOF
