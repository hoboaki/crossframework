/**
 * @file
 * @brief ResMdlNodeImpl.hppの実装を記述する。
 * @author akino
 */
#include "ResMdlNodeImpl.hpp"

//------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------
ResMdlNodeImpl::ResMdlNodeImpl(
    const ::XData::XData& aXData
    , const BinResMdlNode* aBinPtr
    , ::XBase::IAllocator& 
    )
: xdata( aXData.ptr() )
, binPtr( aBinPtr )
, bindPoseMtxPtr( xdata.safeRef< ::XBase::Mtx34 >( binPtr->bindPoseMtxRef ) )
{
}

//------------------------------------------------------------
ResMdlNodeImpl::~ResMdlNodeImpl()
{
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
