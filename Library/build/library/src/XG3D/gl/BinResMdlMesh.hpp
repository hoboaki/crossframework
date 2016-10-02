// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_BINRESMDLMESH_HPP)
#else
#define XG3D_INCLUDED_BINRESMDLMESH_HPP

#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

    // バイナリデータ：モデルメッシュ。
struct BinResMdlMesh
{
    ::XData::UInt16    index;
    ::XData::UInt16    flags;
    ::XData::Reference name;
    ::XData::UInt16    subMeshesCount;
    ::XData::UInt16    padding;
    ::XData::Reference subMeshes;
};

} // namespace
#endif
// EOF
