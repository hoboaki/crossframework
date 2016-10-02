// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESTEXFORMAT_HPP)
#else
#define XG3D_INCLUDED_RESTEXFORMAT_HPP

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Res
//@{
    /// テクスチャのフォーマット。
enum ResTexFormat
{
    ResTexFormat_RGBA8,   ///< RGBA8。
    ResTexFormat_RGB8,    ///< RGB8。
    ResTexFormat_RGB5A1,  ///< RGB5A1。
    ResTexFormat_RGBA4,   ///< RGBA4。
    ResTexFormat_RGB565,  ///< RGB565。
    ResTexFormat_A8,      ///< A8。
    ResTexFormat_LA8,     ///< LA8。
    ResTexFormat_L8,      ///< L8。
    // term
    ResTexFormat_TERMINATE,
    ResTexFormat_MIN = 0,
    ResTexFormat_MAX = ResTexFormat_TERMINATE - 1
};
//@}

} // namespace
#endif
// EOF
