// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_PRIMITIVEKIND_HPP)
#else
#define AE_G3D_INCLUDED_PRIMITIVEKIND_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Enum
//@{
/// プリミティブの種類。
struct PrimitiveKind
{
    enum EnumType
    {
        Triangles, ///< 連続した三角形。
        Quads,   ///< 連続した矩形。
        // term
        TERM,
    };
};
//@}

}} // namespace
#endif
// EOF
