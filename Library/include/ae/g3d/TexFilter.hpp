// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_TEXFILTER_HPP)
#else
#define AE_G3D_INCLUDED_TEXFILTER_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Enum
//@{
/// テクスチャ補間の種類。
struct TexFilter
{
    enum EnumType
    {
        Nearest, ///< 近い値。
        Linear,  ///< 線形補間。
        // , NearestMipMapNearest ///< 近い値。MipMapは１つ使う。
        // , NearestMipMapLinear ///< 近い値。MipMapで２つ使い線形補間。
        // , LinearMipMapNearest ///< 線形補間。MipMapは１つ使う。
        // , LinearMipMapLinear ///< 線形補間。MipMapは２つ使い線形補間。
        
        TERM,
    };
};
//@}

}} // namespace
#endif
// EOF
