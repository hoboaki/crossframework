// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLMESHIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMDLMESHIMPL_HPP

#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/Placement.hpp>
#include <XBase/RuntimeAutoArray.hpp>
#include "BinResMdlMesh.hpp"
#include "ResMdlSubMeshImpl.hpp"
#include "XDataPlus.hpp"

namespace XG3D {
class ResMdl;
}

//------------------------------------------------------------------------------
namespace XG3D {

    // BinResMdlMeshとResMdlMeshの間にかますクラス。
class ResMdlMeshImpl : public ::XBase::NonCopyable
{
public:
    typedef ::XBase::RuntimeAutoArray< ResMdlSubMeshImpl >  SubMeshArray;

    //============================================================
    const XDataPlus  xdata;
    const BinResMdlMesh* binPtr;
    ::XBase::Placement< SubMeshArray > subMeshImpls;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMdlMeshImpl(const ::XData::XData& aXData, const BinResMdlMesh* aBinPtr, ::XBase::IAllocator& aAllocator, const ResMdl& aResMdl);
    ~ResMdlMeshImpl();
};

} // namespace
#endif
// EOF
