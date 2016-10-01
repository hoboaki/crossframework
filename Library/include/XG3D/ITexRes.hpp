/**
 * @file
 * @brief ITexRes型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_ITEXRES_HPP)
#else
#define XG3D_INCLUDED_ITEXRES_HPP

//------------------------------------------------------------
namespace XG3D {
    struct TexResData;
}

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Util
//@{
    /// テクスチャリソースのデータを返すインターフェースクラス。
    class ITexRes
    {
    public:
        virtual ~ITexRes();
        
        /// データを取得する。
        virtual const TexResData texResData()const = 0;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
