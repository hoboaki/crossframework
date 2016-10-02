// 文字コード：UTF-8
#include "ResMdlMatReferImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResMdlMatReferImpl::ResMdlMatReferImpl(
    const ::XData::XData& aXData,
    const BinResMdlMatRefer* aBinPtr,
    ::XBase::IAllocator&
    )
: xdata(aXData.ptr())
, binPtr(aBinPtr)
{
}

//------------------------------------------------------------------------------
ResMdlMatReferImpl::~ResMdlMatReferImpl()
{
}

} // namespace
// EOF
