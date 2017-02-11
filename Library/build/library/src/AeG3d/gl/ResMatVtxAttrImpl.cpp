// 文字コード：UTF-8
#include "ResMatVtxAttrImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMatVtxAttrImpl::ResMatVtxAttrImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMatVtxAttr* aBinPtr,
    ::ae::base::IAllocator&
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
{
}

//------------------------------------------------------------------------------
ResMatVtxAttrImpl::~ResMatVtxAttrImpl()
{
}

}} // namespace
// EOF
