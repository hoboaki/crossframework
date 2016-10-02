// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_BINRESMDLSUBMESH_HPP)
#else
#define XG3D_INCLUDED_BINRESMDLSUBMESH_HPP

#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

    // バイナリデータ：モデルサブメッシュ。
    struct BinResMdlSubMesh
    {
        ::XData::UInt16 index;
        ::XData::UInt16 flags;
        ::XData::UInt16 nodeIdx;        // スキニングの場合はINVALID_NODE_INDEX
        ::XData::UInt16 shapeIdx;
        ::XData::UInt16 matReferIdx;
        ::XData::UInt16 padding;
    };

} // namespace
#endif
// EOF
