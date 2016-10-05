// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_SHADERCONSTANT_HPP)
#else
#define XG3D_INCLUDED_SHADERCONSTANT_HPP

//------------------------------------------------------------------------------
namespace XG3D {

// シェーダーに関する定数群。
struct ShaderConstant
{
    // システムが用意したユニフォーム。
    struct SysUniform
    {
        enum EnumType
        {
            MtxProj,
            MtxView,
            MtxWorld,

            TERM,
        };
    };

    //============================================================
    // 以下、古い情報。
    // Attribute。
    struct Attribute
    {
        enum EnumType
        {
            Position,
            Normal,
            TexCoord,
            Color,
            
            // term
            TERM,
        };
    };

    // Uniform。
    struct Uniform
    {
        enum EnumType
        {
            PREV_ = Attribute::TERM - 1,
            TexActive,
            TexSampler,
            
            // term
            TERM,
        };
    };
};

} // namespace
#endif
// EOF
