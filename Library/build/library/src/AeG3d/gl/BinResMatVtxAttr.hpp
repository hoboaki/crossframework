// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESMATVTXATTR_HPP)
#else
#define AE_G3D_INCLUDED_BINRESMATVTXATTR_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：マテリアル頂点属性。
struct BinResMatVtxAttr
{
    ::ae::xdata::Reference symbolName; // Stringではなくchar配列の先頭アドレスなので注意。
    ::ae::xdata::UInt32    bindInputKind; // ResMdlShapeInputKind
};

}} // namespace
#endif
// EOF
