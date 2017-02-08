// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_PRIMITIVEKIND_HPP)
#else
#define XG3D_INCLUDED_PRIMITIVEKIND_HPP

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Enum
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

} // namespace
#endif
// EOF
