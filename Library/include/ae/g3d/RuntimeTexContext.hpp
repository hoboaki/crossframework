// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RUNTIMETEXCONTEXT_HPP)
#else
#define AE_G3D_INCLUDED_RUNTIMETEXCONTEXT_HPP

#include <ae/base/Enum.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/ResTexFormat.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Util
//@{
/// RuntimeTex用コンテキスト。
class RuntimeTexContext
{
public:
    /// @name 作成関数
    //@{
    static const RuntimeTexContext Create(ResTexFormat::EnumType aFormat, int aWidth, int aHeight);
    //@}

    /// @name 取得
    //@{
    ResTexFormat::EnumType format()const; ///< フォーマット。
    u16 width()const;  ///< 横ピクセル数。
    u16 height()const; ///< 縦ピクセル数。
    //@}

private:
    RuntimeTexContext(ResTexFormat::EnumType, int aWidth, int aHeight);
    //------------------------------------------------------------------------------
    ::ae::base::Enum32< ResTexFormat::EnumType > mFormat;
    u16 mWidth;
    u16 mHeight;
};
//@}

}} // namespace
#endif
// EOF
