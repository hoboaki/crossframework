// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_SCREEN_HPP)
#else
#define XBASE_INCLUDED_SCREEN_HPP

#include <XBase/BuiltInTypes.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/Os.hpp>

#if defined(XBASE_OS_MACOSX)
    #include <XBase/Screen_MacOSX.hpp>
#elif defined(XBASE_OS_IOS)
    #include <XBase/Screen_iOs.hpp>
#else
    #include <XBase/Screen_Default.hpp>
#endif

namespace XBase {
class Display_Ext;
struct ScreenPosPod;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @name addtogroup XBase-System
//@{
    /// @brief Displayが所持する描画領域。
    /// @details
    /// WindowsやMacOSXなどのWindowSystem環境では１つの Display に１つの Screen が存在します。 @n
/// NintendoDSなど2枚の描画領域を持つ環境では１つの Display に２つの Screen が存在します。 @n
class Screen : public ::XBase::NonCopyable
{
public:
    // コンストラクタ。システムが呼ぶ。
    Screen(Display_Ext& aOwner, int aWidth, int aHeight);

    /// @name 解像度
    //@{
    /// 横ピクセル数。
    int width()const;

    /// 縦ピクセル数。
    int height()const;

    /// @brief 指定の位置がスクリーン内かどうか判定する。
    /// @return 0 <= aPos.x < width() && 0 <= aPos.y < height()
    bool isContains(const ScreenPosPod& aPos)const;
    //@}

    //============================================================
    // 内部実装用関数群。
    Display_Ext& display_();
    Screen_Ext& ext_();

private:
    Display_Ext& mOwner;
    Screen_Ext mExt;
    int mWidth;
    int mHeight;
};
//@}

} // namespace
#endif
// EOF
