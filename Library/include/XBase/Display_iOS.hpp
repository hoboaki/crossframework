/**
 * @file
 * @brief Display_EXT型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_DISPLAY_IOS_HPP)
#else
#define XBASE_INCLUDED_DISPLAY_IOS_HPP

//------------------------------------------------------------
#include <XBase/DisplayContext.hpp>
#include <XBase/Placement.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Screen.hpp>

//-----------------------------------------------------------
struct XBaseUIWindow;
namespace XBase {
    class HID;
}

//------------------------------------------------------------
namespace XBase {
    // MacOSX環境でのDisplayの拡張。
    class Display_EXT
    {
    public:        
        //============================================================
        XBaseUIWindow* windowPtr;
        Placement< Screen > mainScreen;
        Pointer< HID > hidPtr;
        
        //============================================================
        Display_EXT( const DisplayContext& );
        ~Display_EXT();
    };
}
//------------------------------------------------------------
#endif
// EOF
