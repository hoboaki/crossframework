// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLSHAPEINPUTKIND_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLSHAPEINPUTKIND_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

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

}} // namespace
#endif
// EOF
