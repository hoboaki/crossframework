/**
 * @file
 * @brief ResMatParamImpl.hppの実装を記述する。
 * @author akino
 */
#include "ResMatParamImpl.hpp"

//------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------
ResMatParamImpl::ResMatParamImpl(
    const ::XData::XData& aXData
    , const BinResMatParam* aBinPtr
    , ::XBase::IAllocator& 
    )
: xdata( aXData.ptr() )
, binPtr( aBinPtr )
{
}

//------------------------------------------------------------
ResMatParamImpl::~ResMatParamImpl()
{
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
