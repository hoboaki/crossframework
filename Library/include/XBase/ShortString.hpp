/**
 * @file
 * @brief ShortString型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_SHORTSTRING_HPP)
#else
#define XBASE_INCLUDED_SHORTSTRING_HPP

//------------------------------------------------------------
#include <XBase/FixedString.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-String
//@{
    typedef FixedString< char    , 64 > ShortString;  ///< char版ShortString。短い固定長文字列。
    typedef FixedString< wchar_t , 64 > ShortWString; ///< wchar_t版ShortString。短い固定長文字列。
//@}
}
//------------------------------------------------------------
#endif
// EOF
