// 文字コード：UTF-8
#include "ResMatParamImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMatParamImpl::ResMatParamImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMatParam* aBinPtr,
    ::ae::base::IAllocator&
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
{
}

//------------------------------------------------------------------------------
ResMatParamImpl::~ResMatParamImpl()
{
}

}} // namespace
// EOF
