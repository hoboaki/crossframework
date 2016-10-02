// 文字コード：UTF-8
#include "ResMatVtxAttrImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResMatVtxAttrImpl::ResMatVtxAttrImpl(
    const ::XData::XData& aXData,
    const BinResMatVtxAttr* aBinPtr,
    ::XBase::IAllocator&
    )
: xdata(aXData.ptr())
, binPtr(aBinPtr)
{
}

//------------------------------------------------------------------------------
ResMatVtxAttrImpl::~ResMatVtxAttrImpl()
{
}

} // namespace
// EOF
