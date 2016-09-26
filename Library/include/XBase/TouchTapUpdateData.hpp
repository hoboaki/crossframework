/**
 * @file
 * @brief TouchTapUpdateData型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_TOUCHTAPUPDATEDATA_HPP)
#else
#define XBASE_INCLUDED_TOUCHTAPUPDATEDATA_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/ScreenPos.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-HID
//@{
    /// タッチの1タップの更新データ。
    struct TouchTapUpdateData
    {
        uint32       tapCount; 
        ScreenPosPOD pos;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
