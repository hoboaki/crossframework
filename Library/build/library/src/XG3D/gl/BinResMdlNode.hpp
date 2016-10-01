// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_BINRESMDLNODE_HPP)
#else
#define XG3D_INCLUDED_BINRESMDLNODE_HPP

//------------------------------------------------------------------------------
#include <XBase/Matrix34.hpp>
#include <XBase/Vector3.hpp>
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
    // バイナリデータ：モデルノード。
    struct BinResMdlNode
    {
        ::XData::UInt16     index;
        ::XData::UInt16     flags;
        ::XData::Reference  name;
        ::XData::UInt16     parentNodeIdx;
        ::XData::UInt16     firstChildNodeIdx;
        ::XData::UInt16     nextSiblingNodeIdx;
        ::XData::UInt16     padding;
        ::XBase::Mtx34      rtMtx;
        ::XBase::Vec3       scale;
        ::XData::Reference  bindPoseMtxRef; // バインドポーズ行列が必要なときのみMtx34への参照
    };

} // namespace
#endif
// EOF
