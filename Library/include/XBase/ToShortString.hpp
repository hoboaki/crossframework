// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_TOSHORTSTRING_HPP)
#else
#define XBASE_INCLUDED_TOSHORTSTRING_HPP

#include <XBase/ShortStringFactory.hpp>

/// @addtogroup XBase-String
//@{

/// @brief 引数の値をShortStringに変換するマクロ。
/// @return 変換された文字列。
#define XBASE_TO_SHORT_STRING( aVal ) (::XBase::ShortStringFactory::Create( aVal ))

//@}
#endif
// EOF
