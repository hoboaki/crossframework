// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_DISPLAY_MACOSX_HPP)
#else
#define XBASE_INCLUDED_DISPLAY_MACOSX_HPP

#include <XBase/DisplayContext.hpp>
#include <XBase/KeyboardUpdateData.hpp>
#include <XBase/MouseUpdateData.hpp>
#include <XBase/Placement.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Screen.hpp>

struct XBaseNSWindow;
namespace XBase {
class HID;
}

//------------------------------------------------------------------------------
namespace XBase {

// MacOSX環境でのDisplayの拡張。
class Display_EXT
{
public:
    //============================================================
    static void CBKeyEvent(void* aEXT, int aUnicode, int aIsDown);
    static void CBModKeyEvent(void* aEXT, int aIsShift, int aIsCtrl, int aIsAlt);
    static void CBMouseEvent(void* aEXT, int aPressedButtons, float aX, float aY);

    //============================================================
    XBaseNSWindow* windowPtr;
    Placement< Screen > mainScreen;
    Pointer< HID > hidPtr;
    int isClosed;
    KeyboardUpdateData keyboardUpdateData;
    MouseUpdateData mouseUpdateData;

    //============================================================
    Display_EXT(const DisplayContext&);
    ~Display_EXT();
};

} // namespace
#endif
// EOF
