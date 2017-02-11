// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESMDLNODE_HPP)
#else
#define AE_G3D_INCLUDED_BINRESMDLNODE_HPP

#include <ae/base/Matrix34.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：モデルノード。
struct BinResMdlNode
{
    ::ae::xdata::UInt16     index;
    ::ae::xdata::UInt16     flags;
    ::ae::xdata::Reference  name;
    ::ae::xdata::UInt16     parentNodeIdx;
    ::ae::xdata::UInt16     firstChildNodeIdx;
    ::ae::xdata::UInt16     nextSiblingNodeIdx;
    ::ae::xdata::UInt16     padding;
    ::ae::base::Mtx34      rtMtx;
    ::ae::base::Vec3       scale;
    ::ae::xdata::Reference  bindPoseMtxRef; // バインドポーズ行列が必要なときのみMtx34への参照
};

}} // namespace
#endif
// EOF
