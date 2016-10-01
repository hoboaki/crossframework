/**
 * @file
 * @brief TexId型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_TEXMAPID_HPP)
#else
#define XG3D_INCLUDED_TEXMAPID_HPP

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Enum
//@{
    /// テクスチャのID。
    enum TexId
    {
        TexId_0, ///< 0番。
        // term
        TexId_TERMINATE,
        TexId_MIN = 0,
        TexId_MAX = TexId_TERMINATE
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
