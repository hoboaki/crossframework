// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESMDLSUBMESH_HPP)
#else
#define AE_G3D_INCLUDED_BINRESMDLSUBMESH_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：モデルサブメッシュ。
struct BinResMdlSubMesh
{
    ::ae::xdata::UInt16 index;
    ::ae::xdata::UInt16 flags;
    ::ae::xdata::UInt16 nodeIdx;        // スキニングの場合はINVALID_NODE_INDEX
    ::ae::xdata::UInt16 shapeIdx;
    ::ae::xdata::UInt16 matReferIdx;
    ::ae::xdata::UInt16 padding;
};

}} // namespace
#endif
// EOF
