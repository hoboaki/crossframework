// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_TEXRESDATA_HPP)
#else
#define XG3D_INCLUDED_TEXRESDATA_HPP

#include <XBase/Enum.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/ResTexFormat.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Util
//@{
/// テクスチャリソースのデータ。
struct TexResData
{
    ::XBase::EnumPODTmpl< ResTexFormat, s32 > format; ///< フォーマット。
    u16 width;  ///< 横ピクセル数。
    u16 height; ///< 縦ピクセル数。。
    const byte_t* pixels; ///< ピクセルデータの先頭アドレス。
};
//@}

} // namespace
#endif
// EOF
