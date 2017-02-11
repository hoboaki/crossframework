// 文字コード：UTF-8
#include "ResMdlMatReferImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMdlMatReferImpl::ResMdlMatReferImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMdlMatRefer* aBinPtr,
    ::ae::base::IAllocator&
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
{
}

//------------------------------------------------------------------------------
ResMdlMatReferImpl::~ResMdlMatReferImpl()
{
}

}} // namespace
// EOF
