// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLSHAPEINPUTKIND_HPP)
#else
#define XG3D_INCLUDED_RESMDLSHAPEINPUTKIND_HPP

#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

// シェイプ入力データの種類。
struct ResMdlShapeInputKind
{
    enum EnumType
    {
        Position,
        Normal,
        Tangent,
        SkinMtxIndex,
        SkinWeight,
        Color0,
        Color1,
        Color2,
        Color3,
        Color4,
        Color5,
        Color6,
        Color7,
        TexCoord0,
        TexCoord1,
        TexCoord2,
        TexCoord3,
        TexCoord4,
        TexCoord5,
        TexCoord6,
        TexCoord7,
        
        TERM,
    };
};

} // namespace
#endif
// EOF
