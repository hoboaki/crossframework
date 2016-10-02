// 文字コード：UTF-8
#include "ResMdlSubMeshImpl.hpp"

//------------------------------------------------------------------------------
#include <XG3D/ResMdl.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResMdlSubMeshImpl::ResMdlSubMeshImpl(
    const ::XData::XData& aXData,
    const BinResMdlSubMesh* aBinPtr,
    ::XBase::IAllocator&,
    const ResMdl& aResMdl
    )
: xdata(aXData.ptr())
, binPtr(aBinPtr)
, resMdlShape(aResMdl.shape(binPtr->shapeIdx))
{
}

//------------------------------------------------------------------------------
ResMdlSubMeshImpl::~ResMdlSubMeshImpl()
{
}

} // namespace
// EOF
