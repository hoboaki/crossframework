/**
 * @file
 * @brief ResMdlMatReferImpl.hppの実装を記述する。
 * @author akino
 */
#include "ResMdlMatReferImpl.hpp"

//------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------
ResMdlMatReferImpl::ResMdlMatReferImpl(
    const ::XData::XData& aXData
    , const BinResMdlMatRefer* aBinPtr
    , ::XBase::IAllocator& 
    )
: xdata( aXData.ptr() )
, binPtr( aBinPtr )
{
}

//------------------------------------------------------------
ResMdlMatReferImpl::~ResMdlMatReferImpl()
{
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
