// 文字コード：UTF-8
#include "ResMatParamImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResMatParamImpl::ResMatParamImpl(
    const ::XData::XData& aXData,
    const BinResMatParam* aBinPtr,
    ::XBase::IAllocator&
    )
: xdata(aXData.ptr())
, binPtr(aBinPtr)
{
}

//------------------------------------------------------------------------------
ResMatParamImpl::~ResMatParamImpl()
{
}

} // namespace
// EOF
