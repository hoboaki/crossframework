/**
 * @file
 * @brief ResTexImpl.hppの実装を記述する。
 * @author akino
 */
#include "ResTexImpl.hpp"

//------------------------------------------------------------
#include <XBase/EnumCheck.hpp>
#include <XBase/FunctionAttribute.hpp>
#include <XBase/Ref.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/TexResData.hpp>
#include <XG3D/ResTexFormat.hpp>

//------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------
ResTexImpl::ResTexImpl(
    const ::XData::XData& aXData
    , const BinResTex* aBinPtr
    , ::XBase::IAllocator& 
    )
: xdata( aXData.ptr() )
, binPtr( aBinPtr )
, texBufferPtr( 0 )
, mTexBuffer()
{
}

//------------------------------------------------------------
ResTexImpl::~ResTexImpl()
{
}

//------------------------------------------------------------
void ResTexImpl::setup()
{
    // セットアップ済みなら何もしない
    if ( texBufferPtr != 0 )
    {
        return;
    }
    
    // 変数用意
    TexResData data = {};
    data.format = format();
    data.width  = binPtr->width;;
    data.height = binPtr->height;
    data.pixels = pixels();
    
    // 作成
    mTexBuffer.init( ::XBase::Ref( data ) );
    texBufferPtr = mTexBuffer.ptr();
}

//------------------------------------------------------------
ResTexFormat ResTexImpl::format()const
{
    ResTexFormat fmt = ResTexFormat( binPtr->format );
    if ( XBASE_ENUM_IS_INVALID( ResTexFormat , fmt ) )
    {
        XBASE_NOT_REACH_ASSERT();
        return ResTexFormat_MIN;
    }
    return ResTexFormat( fmt );
}

//------------------------------------------------------------
const byte_t* ResTexImpl::pixels()const
{
    return xdata.ref< byte_t >( binPtr->pixels );
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
