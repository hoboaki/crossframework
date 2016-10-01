/**
 * @file
 * @brief ResMatVtxAttrImpl.hppの実装を記述する。
 * @author akino
 */
#include "ResMatVtxAttrImpl.hpp"

//------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------
ResMatVtxAttrImpl::ResMatVtxAttrImpl(
    const ::XData::XData& aXData
    , const BinResMatVtxAttr* aBinPtr
    , ::XBase::IAllocator& 
    )
: xdata( aXData.ptr() )
, binPtr( aBinPtr )
{
}

//------------------------------------------------------------
ResMatVtxAttrImpl::~ResMatVtxAttrImpl()
{
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
