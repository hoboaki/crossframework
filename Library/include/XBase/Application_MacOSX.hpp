/**
 * @file
 * @brief Application_EXT型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_APPLICATION_MACOSX_HPP)
#else
#define XBASE_INCLUDED_APPLICATION_MACOSX_HPP

//------------------------------------------------------------
#include <XBase/Bool.hpp>

//------------------------------------------------------------
namespace XBase {
    // MacOSX環境でのApplicationの拡張。
    class Application_EXT
    {
    public:     
        //============================================================
        s64 prevUpdateTicks;
        Bool32 doQuit;
        
        //============================================================
        Application_EXT();
        ~Application_EXT();
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
