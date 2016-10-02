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
        enum SysUniform
        {
            SysUniform_MtxProj,
            SysUniform_MtxView,
            SysUniform_MtxWorld,
            // term
            SysUniform_TERMINATE,
            SysUniform_MIN = 0,
            SysUniform_MAX = SysUniform_TERMINATE-1
        };

        //============================================================
        // 以下、古い情報。
        // Attribute。
        enum Attribute
        {
            Attribute_Position
            , Attribute_Normal
            , Attribute_TexCoord
            , Attribute_Color
            // term
            , Attribute_TERMINATE
            , Attribute_MIN = 0
            , Attribute_MAX = Attribute_TERMINATE-1
        };

        // Uniform。
        enum Uniform
        {
            Uniform_PREV_ = SysUniform_MAX
            , Uniform_TexActive
            , Uniform_TexSampler
            // term
            , Uniform_TERMINATE
            , Uniform_MIN = 0
            , Uniform_MAX = Uniform_TERMINATE-1
        };
    };

} // namespace
#endif
// EOF
