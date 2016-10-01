/**
 * @file
 * @brief PointerCheck.hppの実装を記述する。
 * @author akino
 */
#include <XBase/PointerCheck.hpp>

//------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
bool PointerCheck::IsValid( const_anyptr_t aPtr )
{
    return aPtr != 0;
}

//------------------------------------------------------------
bool PointerCheck::InvalidCheck( const_anyptr_t aPtr )
{
    if ( !IsValid( aPtr ) )
    {
        XBASE_INVALID_VALUE_ERROR( aPtr );
        return true;
    }
    return false;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
