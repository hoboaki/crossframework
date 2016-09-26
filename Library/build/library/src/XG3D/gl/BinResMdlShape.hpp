/**
 * @file
 * @brief BinResMdlShape型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_BINRESMDLSHAPE_HPP)
#else
#define XG3D_INCLUDED_BINRESMDLSHAPE_HPP

//------------------------------------------------------------
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include "ResMdlShapeInputKind.hpp"
#include "ResMdlShapeInputType.hpp"

//------------------------------------------------------------
namespace XG3D {
    // バイナリデータ：モデルシェイプ。
    struct BinResMdlShape
    {
        struct VtxAttrInfo
        {
            ::XData::UInt8      inputKind; // ResMdlShapeInputKind
            ::XData::UInt8      dataType;  // ResMdlShapeInputType
            ::XData::UInt8      elemCount; // 要素数1～4
            ::XData::UInt8      offset;
        };
        //============================================================
        ::XData::UInt16     index;
        ::XData::UInt16     flags;
        ::XData::Reference  name;
        ::XData::UInt16     skinningTableIdx;
        ::XData::UInt8      indexArrayDataType; // ResMdlShapeInputType
        ::XData::UInt8      vtxAttrInfoCount;
        ::XData::UInt32     indexArrayDataCount;// indexArrayDataRefの配列要素数。バイト数ではない。
        ::XData::Reference  indexArrayDataRef;
        ::XData::Reference  vtxAttrInfosRef;    // vtxAttrInfoCount数、VtxAttrInfoが並んでいる
        ::XData::UInt32     vtxAttrDataSize;
        ::XData::UInt32     vtxAttrDataStride;  // 1頂点あたりにかかるバイト数。
        ::XData::Reference  vtxAttrDataRef;     // vtxAttrDataSize長のバイト配列。
    };
}
//------------------------------------------------------------
#endif
// EOF
