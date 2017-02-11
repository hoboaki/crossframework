// 文字コード：UTF-8
#include "ResMdlSubMeshImpl.hpp"

#include <ae/g3d/ResMdl.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMdlSubMeshImpl::ResMdlSubMeshImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMdlSubMesh* aBinPtr,
    ::ae::base::IAllocator&,
    const ResMdl& aResMdl
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
, resMdlShape(aResMdl.shape(binPtr->shapeIdx))
{
}

//------------------------------------------------------------------------------
ResMdlSubMeshImpl::~ResMdlSubMeshImpl()
{
}

}} // namespace
// EOF
