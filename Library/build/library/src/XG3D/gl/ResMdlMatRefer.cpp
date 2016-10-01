// 文字コード：UTF-8
#include <XG3D/ResMdlMatRefer.hpp>

//------------------------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/ResConstant.hpp>
#include "ResMdlMatReferImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------------------------
ResMdlMatRefer::ResMdlMatRefer()
{
}

//------------------------------------------------------------------------------
ResMdlMatRefer::ResMdlMatRefer( const ResMdlMatReferImpl& aImpl )
: mPtr( aImpl )
{
}

//------------------------------------------------------------------------------
bool ResMdlMatRefer::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMdlMatRefer::equals( const ResMdlMatRefer& aRHS )const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMdlMatRefer::operator==( const ResMdlMatRefer& aRHS )const
{
    return equals( aRHS );
}

//------------------------------------------------------------------------------
uint ResMdlMatRefer::index()const
{
    // チェック
    if ( checkInvalid() )
    {
        return ResConstant::INVALID_MDL_MAT_REFER_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
const char* ResMdlMatRefer::name()const
{
    // チェック
    if ( checkInvalid() )
    {
        return "";
    }
    return mPtr->xdata.ref< ::XData::String >( mPtr->binPtr->name )->toCStr();
}

//------------------------------------------------------------------------------
bool ResMdlMatRefer::checkInvalid()const
{
    // 正しければ何もしない
    if ( isValid() )
    {
        return false;
    }

    // 不正なのでエラー
    XBASE_NOT_REACH_ASSERT();
    return true;
}

} // namespace
// EOF
