// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_DISPLAYCONTEXT_HPP)
#else
#define XBASE_INCLUDED_DISPLAYCONTEXT_HPP

#include <XBase/Bool.hpp>
#include <XBase/BuiltInTypes.hpp>
#include <XBase/OsType.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-System
//@{
/// Display クラスのコンテキスト。
class DisplayContext
{
public:
    /// デフォルトの設定で作成する。
    DisplayContext();

#if defined(XBASE_OSTYPE_WINDOWSYSTEM)
        /// @name WindowSystem環境でのカスタマイズ
        //@{
    void setLocationToCenter(); ///< 現在のwidthとheightの値を見て画面の中央にウィンドウがくるようにlocationX,Yを設定する。
    int locationX()const;
    int locationY()const;
    int width()const;
    int height()const;
    bool isScreenDoubleBuffer()const;
    //@}
#endif

private:
#if defined(XBASE_OSTYPE_WINDOWSYSTEM)
    int mLocationX;
    int mLocationY;
    int mWidth;
    int mHeight;
    Bool32 mIsScreenDoubleBuffer;
#endif
};
//@}

} // namespace
#endif
// EOF
