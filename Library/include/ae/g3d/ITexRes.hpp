// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_ITEXRES_HPP)
#else
#define AE_G3D_INCLUDED_ITEXRES_HPP

namespace ae {
namespace g3d {
struct TexResData;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Util
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

}} // namespace
#endif
// EOF
