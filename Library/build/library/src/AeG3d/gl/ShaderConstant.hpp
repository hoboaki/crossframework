// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_SHADERCONSTANT_HPP)
#else
#define AE_G3D_INCLUDED_SHADERCONSTANT_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

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
            MtxBonePosArray,
            MtxBoneNrmArray,

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

}} // namespace
#endif
// EOF
