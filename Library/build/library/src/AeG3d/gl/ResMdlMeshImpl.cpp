// 文字コード：UTF-8
#include "ResMdlMeshImpl.hpp"

#include <ae/base/Ref.hpp>
#include <ae/g3d/ResMdl.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMdlMeshImpl::ResMdlMeshImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMdlMesh* aBinPtr,
    ::ae::base::IAllocator& aAllocator,
    const ResMdl& aResMdl
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
, subMeshImpls()
{
    // subMesh
    {
        const BinResMdlSubMesh* binArray = xdata.ref< BinResMdlSubMesh >(binPtr->subMeshes);
        subMeshImpls.init(binPtr->subMeshesCount, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < binPtr->subMeshesCount; ++i) {
            subMeshImpls->add(
                ::ae::base::Ref(xdata),
                &binArray[i],
                ::ae::base::Ref(aAllocator),
                ::ae::base::Ref(aResMdl)
                );
        }
    }
}

//------------------------------------------------------------------------------
ResMdlMeshImpl::~ResMdlMeshImpl()
{
}

}} // namespace
// EOF
