/**
 * @file
 * @brief ResMat.hppの実装を記述する。
 * @author akino
 */
#include <XG3D/ResMat.hpp>

//------------------------------------------------------------
#include <XBase/EnumCheck.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/StringTraits.hpp>
#include <XG3D/ResConstant.hpp>
#include "ResMatImpl.hpp"

//------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------
ResMat::ResMat()
{
}

//------------------------------------------------------------
ResMat::ResMat( const ResMatImpl& aImpl )
: mPtr( aImpl )
{
}

//------------------------------------------------------------
bool ResMat::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------
bool ResMat::equals( const ResMat& aRHS )const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------
bool ResMat::operator==( const ResMat& aRHS )const
{
    return equals( aRHS );
}

//------------------------------------------------------------
uint ResMat::index()const
{
    // チェック
    if ( checkInvalid() )
    {
        return ResConstant::INVALID_MAT_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------
const char* ResMat::name()const
{
    // チェック
    if ( checkInvalid() )
    {
        return "";
    }
    return mPtr->xdata.ref< ::XData::String >( mPtr->binPtr->name )->toCStr();
}

//------------------------------------------------------------
uint ResMat::paramCount()const
{
    // チェック
    if ( checkInvalid() )
    {
        return 0;
    }
    return mPtr->paramImpls->count();
}

//------------------------------------------------------------
ResMatParam ResMat::param( const uint aIndex )const
{
    // チェック
    if ( checkInvalid() )
    {
        return ResMatParam();
    }
    return ResMatParam( mPtr->paramImpls->at( aIndex ) );
}

//------------------------------------------------------------
ResMatParam ResMat::param( const char* aName )const
{
    // チェック
    if ( checkInvalid() )
    {
        return ResMatParam();
    }    

    // 検索
    for ( uint i = 0; i < mPtr->paramImpls->count(); ++i )
    {
        ResMatParamImpl& impl = mPtr->paramImpls->at(i);
        if ( ::XBase::StringTraits< char >::Equals( ResMatParam( impl ).name() , aName ) )
        {
            return ResMatParam( impl );
        }
    }
    return ResMatParam();
}

//------------------------------------------------------------
const ResMatImpl* ResMat::impl_()const
{
    return mPtr.get();
}

//------------------------------------------------------------
bool ResMat::checkInvalid()const
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

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
