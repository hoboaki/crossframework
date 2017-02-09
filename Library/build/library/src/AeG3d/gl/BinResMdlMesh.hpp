// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESMDLMESH_HPP)
#else
#define AE_G3D_INCLUDED_BINRESMDLMESH_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：モデルメッシュ。
struct BinResMdlMesh
{
    ::ae::xdata::UInt16    index;
    ::ae::xdata::UInt16    flags;
    ::ae::xdata::Reference name;
    ::ae::xdata::UInt16    subMeshesCount;
    ::ae::xdata::UInt16    padding;
    ::ae::xdata::Reference subMeshes;
};

}} // namespace
#endif
// EOF
