// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_SCREENPOS_HPP)
#else
#define XBASE_INCLUDED_SCREENPOS_HPP

#include <XBase/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @name XBase-Util
//@{
    /// @brief スクリーン上の位置。
    /// @details
    /// スクリーンの左下が原点になります。@n
    /// 符号有りにしているのはマウスのドラッグ操作でウィンドウ外の座標を扱うことがあるためです。@n
struct ScreenPosPOD
{
    s16 x; ///< x位置。
    s16 y; ///< y位置。
};

/// ScreenPosPODのクラス版。
class ScreenPos : public ScreenPosPOD
{
public:
    /// @name コンストラクタ。
    //@{
    ScreenPos(); ///< (0,0)で作成。
    ScreenPos(s16 aX, s16 aY); ///< x,yを指定して作成。
    ScreenPos(const ScreenPosPOD&); ///< コピーして作成。
    //@}
};
//@}

} // namespace
#endif
// EOF
