// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_NEWLINE_HPP)
#else
#define XBASE_INCLUDED_NEWLINE_HPP

//------------------------------------------------------------------------------
#include <XBase/OS.hpp>

//------------------------------------------------------------------------------
/// @addtogroup XBase-Env
//@{

/// @def XBASE_NEWLINE
/// @brief 環境に合った改行コード文字列を定義するマクロ。
#if defined(XBASE_OS_WINDOWS)
    #define XBASE_NEWLINE ("\r\n")
#else
    // デフォルトは\n
    #define XBASE_NEWLINE ("\n")
#endif

//@}
//------------------------------------------------------------------------------
#endif
// EOF
