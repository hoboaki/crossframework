// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLSHAPEINPUTKIND_HPP)
#else
#define XG3D_INCLUDED_RESMDLSHAPEINPUTKIND_HPP

//------------------------------------------------------------------------------
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
    // シェイプ入力データの種類。
    enum ResMdlShapeInputKind
    {
        ResMdlShapeInputKind_Position,
        ResMdlShapeInputKind_Normal,
        ResMdlShapeInputKind_WeightPaletteIndex,
        ResMdlShapeInputKind_Color0,
        ResMdlShapeInputKind_Color1,
        ResMdlShapeInputKind_Color2,
        ResMdlShapeInputKind_Color3,
        ResMdlShapeInputKind_Color4,
        ResMdlShapeInputKind_Color5,
        ResMdlShapeInputKind_Color6,
        ResMdlShapeInputKind_Color7,
        ResMdlShapeInputKind_TexCoord0,
        ResMdlShapeInputKind_TexCoord1,
        ResMdlShapeInputKind_TexCoord2,
        ResMdlShapeInputKind_TexCoord3,
        ResMdlShapeInputKind_TexCoord4,
        ResMdlShapeInputKind_TexCoord5,
        ResMdlShapeInputKind_TexCoord6,
        ResMdlShapeInputKind_TexCoord7,
        // term        
        ResMdlShapeInputKind_TERMINATE,
        ResMdlShapeInputKind_MIN = 0,
        ResMdlShapeInputKind_MAX = ResMdlShapeInputKind_TERMINATE-1
    };

} // namespace
#endif
// EOF
