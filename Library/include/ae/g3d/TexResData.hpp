// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_TEXRESDATA_HPP)
#else
#define AE_G3D_INCLUDED_TEXRESDATA_HPP

#include <ae/base/Enum.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/ResTexFormat.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Util
//@{
/// テクスチャリソースのデータ。
struct TexResData
{
    ::ae::base::EnumPodTmpl< ResTexFormat::EnumType, s32 > format; ///< フォーマット。
    u16 width;  ///< 横ピクセル数。
    u16 height; ///< 縦ピクセル数。。
    const byte_t* pixels; ///< ピクセルデータの先頭アドレス。
};
//@}

}} // namespace
#endif
// EOF
