// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESTEXFORMAT_HPP)
#else
#define AE_G3D_INCLUDED_RESTEXFORMAT_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
/// テクスチャのフォーマット。
struct ResTexFormat
{
    enum EnumType
    {
        // ベーシックフォーマット
        RGBA8,   ///< RGBA8。
        RGB8,    ///< RGB8。

        // テクニカルフォーマット
        RGB5A1,  ///< RGB5A1。
        RGBA4,   ///< RGBA4。
        RGB565,  ///< RGB565。
        RG8,     ///< RG8。
        R8,      ///< R8。

        TERM,
    };
};
//@}

}} // namespace
#endif
// EOF
