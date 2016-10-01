// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_BINRESMATVTXATTR_HPP)
#else
#define XG3D_INCLUDED_BINRESMATVTXATTR_HPP

//------------------------------------------------------------------------------
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
    // バイナリデータ：マテリアル頂点属性。
    struct BinResMatVtxAttr
    {    
        ::XData::Reference symbolName; // Stringではなくchar配列の先頭アドレスなので注意。
        ::XData::UInt32    bindInputKind; // ResMdlShapeInputKind
    };

} // namespace
#endif
// EOF
