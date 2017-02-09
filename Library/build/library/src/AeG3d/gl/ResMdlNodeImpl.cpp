// 文字コード：UTF-8
#include "ResMdlNodeImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMdlNodeImpl::ResMdlNodeImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMdlNode* aBinPtr,
    ::ae::base::IAllocator&
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
, bindPoseMtxPtr(xdata.safeRef< ::ae::base::Mtx34 >(binPtr->bindPoseMtxRef))
{
}

//------------------------------------------------------------------------------
ResMdlNodeImpl::~ResMdlNodeImpl()
{
}

}} // namespace
// EOF
