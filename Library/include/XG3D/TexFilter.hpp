// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_TEXFILTER_HPP)
#else
#define XG3D_INCLUDED_TEXFILTER_HPP

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Enum
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

} // namespace
#endif
// EOF
