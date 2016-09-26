/**
 * @file
 * @brief PrimitiveKind型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_PRIMITIVEKIND_HPP)
#else
#define XG3D_INCLUDED_PRIMITIVEKIND_HPP

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Enum
//@{
    /// プリミティブの種類。
    enum PrimitiveKind
    {
        PrimitiveKind_Triangles ///< 連続した三角形。
        , PrimitiveKind_Quads   ///< 連続した矩形。
        // term
        , PrimitiveKind_TERMINATE
        , PrimitiveKind_MIN = 0
        , PrimitiveKind_MAX = PrimitiveKind_TERMINATE-1
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
