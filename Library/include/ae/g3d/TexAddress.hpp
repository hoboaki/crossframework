// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_TEXADDRESS_HPP)
#else
#define AE_G3D_INCLUDED_TEXADDRESS_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Enum
//@{
/// テクスチャのアドレッシングモードの種類。
struct TexAddress
{
    enum EnumType
    {
        Wrap,   ///< 繰り返し。
        Mirror, ///< ミラー。
        Clamp,  ///< クランプ。
        
        TERM,
    };
};
//@}

}} // namespace
#endif
// EOF
