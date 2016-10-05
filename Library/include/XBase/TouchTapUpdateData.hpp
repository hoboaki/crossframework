// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_TOUCHTAPUPDATEDATA_HPP)
#else
#define XBASE_INCLUDED_TOUCHTAPUPDATEDATA_HPP

#include <XBase/BuiltInTypes.hpp>
#include <XBase/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Hid
//@{
/// タッチの1タップの更新データ。
struct TouchTapUpdateData
{
    uint32       tapCount;
    ScreenPosPod pos;
};
//@}

} // namespace
#endif
// EOF
