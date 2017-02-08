// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_TEXADDRESS_HPP)
#else
#define XG3D_INCLUDED_TEXADDRESS_HPP

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Enum
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

} // namespace
#endif
// EOF
