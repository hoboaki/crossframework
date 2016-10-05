// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_DISPLAY_WINDOWS_HPP)
#else
#define XBASE_INCLUDED_DISPLAY_WINDOWS_HPP

#include <XBase/Bool.hpp>
#include <XBase/DisplayContext.hpp>
#include <XBase/KeyboardUpdateData.hpp>
#include <XBase/MouseUpdateData.hpp>
#include <XBase/Placement.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Screen.hpp>
#include <XBase/SdkHeader.hpp>

namespace XBase {
class Application;
class Hid;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-System
//@{
// Windows環境でのDisplayの拡張。
class Display_Ext
{
public:
    //============================================================
    enum { KEY_NUM = 256 };

    //============================================================
    static LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);

    //============================================================
    HWND window;
    WNDCLASSEX windowClass;
    MSG  message;
    Placement< Screen > mainScreen;
    Pointer< Hid > hidPtr;
    Bool32 isClosed;
    KeyboardUpdateData keyboardUpdateData;
    MouseUpdateData mouseUpdateData;

    //============================================================
    Display_Ext(const DisplayContext&);

    //============================================================
    void    pollEvent(Application&);
    LRESULT windowProcess(HWND, UINT, WPARAM, LPARAM);
};
//@}

} // namespace
#endif
// EOF
