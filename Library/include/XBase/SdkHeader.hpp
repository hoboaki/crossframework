// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_SDKHEADER_HPP)
#else
#define XBASE_INCLUDED_SDKHEADER_HPP

#include <XBase/OS.hpp>

#if defined(XBASE_OS_WINDOWS)
    #include <windows.h>
    #undef min
    #undef max
#endif

#endif
// EOF