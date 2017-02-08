// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_DISPLAY_IOS_HPP)
#else
#define XBASE_INCLUDED_DISPLAY_IOS_HPP

#include <XBase/DisplayContext.hpp>
#include <XBase/Placement.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Screen.hpp>

struct XBaseUIWindow;
namespace XBase {
class Hid;
}

//------------------------------------------------------------------------------
namespace XBase {

// MacOSX環境でのDisplayの拡張。
class Display_Ext
{
public:
    //============================================================
    XBaseUIWindow* windowPtr;
    Placement< Screen > mainScreen;
    Pointer< Hid > hidPtr;

    //============================================================
    Display_Ext(const DisplayContext&);
    ~Display_Ext();
};

} // namespace
#endif
// EOF
