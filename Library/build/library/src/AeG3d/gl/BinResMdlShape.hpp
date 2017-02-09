// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESMDLSHAPE_HPP)
#else
#define AE_G3D_INCLUDED_BINRESMDLSHAPE_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include "ResMdlShapeInputKind.hpp"
#include "ResMdlShapeInputType.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：モデルシェイプ。
struct BinResMdlShape
{
    struct VtxAttrInfo
    {
        ::ae::xdata::UInt8      inputKind; // ResMdlShapeInputKind
        ::ae::xdata::UInt8      dataType;  // ResMdlShapeInputType
        ::ae::xdata::UInt8      elemCount; // 要素数1～4
        ::ae::xdata::UInt8      offset;
    };
    //============================================================
    ::ae::xdata::UInt16     index;
    ::ae::xdata::UInt16     flags;
    ::ae::xdata::Reference  name;
    ::ae::xdata::UInt8      indexArrayDataType; // ResMdlShapeInputType
    ::ae::xdata::UInt8      vtxAttrInfoCount;
    ::ae::xdata::UInt8      padding0;
    ::ae::xdata::UInt8      padding1;
    ::ae::xdata::UInt32     indexArrayDataCount;// indexArrayDataRefの配列要素数。バイト数ではない。
    ::ae::xdata::Reference  indexArrayDataRef;
    ::ae::xdata::Reference  vtxAttrInfosRef;    // vtxAttrInfoCount数、VtxAttrInfoが並んでいる
    ::ae::xdata::UInt32     vtxAttrDataSize;
    ::ae::xdata::UInt32     vtxAttrDataStride;  // 1頂点あたりにかかるバイト数。
    ::ae::xdata::Reference  vtxAttrDataRef;     // vtxAttrDataSize長のバイト配列。
};

}} // namespace
#endif
// EOF
