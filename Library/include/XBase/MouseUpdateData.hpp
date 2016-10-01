// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_MOUSEUPDATEDATA_HPP)
#else
#define XBASE_INCLUDED_MOUSEUPDATEDATA_HPP

//------------------------------------------------------------------------------
#include <XBase/Bool.hpp>
#include <XBase/MouseBtnBitSet.hpp>
#include <XBase/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-HID
//@{
    /// マウスの更新データ。
    struct MouseUpdateData
    {
        ScreenPos pos;
        MouseBtnBitSet hold;
        BoolPOD32 posUpdated; // trueならposは最新の値が入っている。falseならウィンドウ外でキャプチャに失敗している可能性がある。
    };
//@}

} // namespace
#endif
// EOF
