// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESTEXFORMAT_HPP)
#else
#define XG3D_INCLUDED_RESTEXFORMAT_HPP

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Res
//@{
/// テクスチャのフォーマット。
struct ResTexFormat
{
    enum EnumType
    {
        RGBA8,   ///< RGBA8。
        RGB8,    ///< RGB8。
        RGB5A1,  ///< RGB5A1。
        RGBA4,   ///< RGBA4。
        RGB565,  ///< RGB565。
        R8,      ///< R8。
        RG8,     ///< RG8。

        TERM,
    };
};
//@}

} // namespace
#endif
// EOF
