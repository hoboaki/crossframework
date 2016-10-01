/**
 * @file
 * @brief Argument.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Argument.hpp>

//------------------------------------------------------------
#include <XBase/PointerCheck.hpp>
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
Argument::Argument( 
    const uint aArgCount
    , const char* const* aArgValues
    , const char* aExeFileName
    , const char* aExeDirPath
    )
: mArgCount( aArgCount )
, mArgValues( aArgValues )
, mExeFileName( aExeFileName )
, mExeDirPath( aExeDirPath )
{
}

//------------------------------------------------------------
uint Argument::argCount()const
{
    return mArgCount;
}

//------------------------------------------------------------
const char* Argument::argValue( const uint aIndex )const
{
    // 範囲外チェック
    if ( mArgCount <= aIndex )
    {
        XBASE_INVALID_VALUE_ERROR( aIndex );
        return "";
    }

    // 配列ポインタチェック
    if ( PointerCheck::InvalidCheck( mArgValues ) )
    {
        return "";
    }
    
    // 文字列ポインタチェック
    const char* value = mArgValues[ aIndex ];
    if ( PointerCheck::InvalidCheck( value ) )
    {
        return "";
    }
    
    // 結果を返す
    return value;
}

//------------------------------------------------------------
const char* Argument::exeFileName()const
{
    if ( PointerCheck::InvalidCheck( mExeFileName ) )
    {
        return "";
    }
    return mExeFileName;
}

//------------------------------------------------------------
const char* Argument::exeDirPath()const
{
    if ( PointerCheck::InvalidCheck( mExeDirPath ) )
    {
        return "";
    }
    return mExeDirPath;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
