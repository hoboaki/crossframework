/**
 * @file
 * @brief TexAddress型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_TEXADDRESS_HPP)
#else
#define XG3D_INCLUDED_TEXADDRESS_HPP

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Enum
//@{
    /// テクスチャのアドレッシングモードの種類。
    enum TexAddress
    {
        TexAddress_Wrap,   ///< 繰り返し。
        TexAddress_Mirror, ///< ミラー。
        TexAddress_Clamp,  ///< クランプ。
        // term
        TexAddress_TERMINATE,
        TexAddress_MIN = 0,
        TexAddress_MAX = TexAddress_TERMINATE-1
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
