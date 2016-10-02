// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_TEXFILTER_HPP)
#else
#define XG3D_INCLUDED_TEXFILTER_HPP

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Enum
//@{
/// テクスチャ補間の種類。
enum TexFilter
{
    TexFilter_Nearest, ///< 近い値。
    TexFilter_Linear,  ///< 線形補間。
    // , TexFilter_NearestMipMapNearest ///< 近い値。MipMapは１つ使う。
    // , TexFilter_NearestMipMapLinear ///< 近い値。MipMapで２つ使い線形補間。
    // , TexFilter_LinearMipMapNearest ///< 線形補間。MipMapは１つ使う。
    // , TexFilter_LinearMipMapLinear ///< 線形補間。MipMapは２つ使い線形補間。
    // term
    TexFilter_TERMINATE,
    TexFilter_MIN = 0,
    TexFilter_MAX = TexFilter_TERMINATE - 1
};
//@}

} // namespace
#endif
// EOF
