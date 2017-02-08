// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLSUBMESHIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMDLSUBMESHIMPL_HPP

#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XG3D/ResMdlShape.hpp>
#include "BinResMdlSubMesh.hpp"
#include "XDataPlus.hpp"

namespace XG3D {
class ResMdl;
}

//------------------------------------------------------------------------------
namespace XG3D {

// BinResMdlSubMeshとResMdlSubMeshの間にかますクラス。
class ResMdlSubMeshImpl : public ::XBase::NonCopyable
{
public:
    const XDataPlus         xdata;
    const BinResMdlSubMesh* binPtr;
    ResMdlShape             resMdlShape;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMdlSubMeshImpl(const ::XData::XData& aXData, const BinResMdlSubMesh* aBinPtr, ::XBase::IAllocator& aAllocator, const ResMdl& aResMdl);
    ~ResMdlSubMeshImpl();
};

} // namespace
#endif
// EOF
