﻿/**
 * @file
 * @brief Display_EXT型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_DISPLAY_DEFAULT_HPP)
#else
#define XBASE_INCLUDED_DISPLAY_DEFAULT_HPP

//------------------------------------------------------------
#include <XBase/DisplayContext.hpp>

//------------------------------------------------------------
namespace XBase {
    // デフォルト環境でのDisplayの拡張。
    class Display_EXT
    {
    public:    
        //============================================================
        Display_EXT( const DisplayContext& ) {}
    };
}
//------------------------------------------------------------
#endif
// EOF
