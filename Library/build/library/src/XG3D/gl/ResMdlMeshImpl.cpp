// 文字コード：UTF-8
#include "ResMdlMeshImpl.hpp"

//------------------------------------------------------------------------------
#include <XBase/Ref.hpp>
#include <XG3D/ResMdl.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResMdlMeshImpl::ResMdlMeshImpl(
    const ::XData::XData& aXData,
    const BinResMdlMesh* aBinPtr,
    ::XBase::IAllocator& aAllocator,
    const ResMdl& aResMdl
    )
: xdata(aXData.ptr())
, binPtr(aBinPtr)
, subMeshImpls()
{
    // subMesh
    {
        const BinResMdlSubMesh* binArray = xdata.ref< BinResMdlSubMesh >(binPtr->subMeshes);
        subMeshImpls.init(binPtr->subMeshesCount, ::XBase::Ref(aAllocator));
        for (uint i = 0; i < binPtr->subMeshesCount; ++i) {
            subMeshImpls->add(
                ::XBase::Ref(xdata),
                &binArray[i],
                ::XBase::Ref(aAllocator),
                ::XBase::Ref(aResMdl)
                );
        }
    }
}

//------------------------------------------------------------------------------
ResMdlMeshImpl::~ResMdlMeshImpl()
{
}

} // namespace
// EOF
