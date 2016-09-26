/**
 * @file
 * @brief HID_EXT型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_HID_WINDOWS_HPP)
#else
#define XBASE_INCLUDED_HID_WINDOWS_HPP

//------------------------------------------------------------
#include <XBase/Keyboard.hpp>
#include <XBase/Mouse.hpp>
#include <XBase/NonCopyable.hpp>

//------------------------------------------------------------
namespace XBase {
    // WindowsのHID拡張。
    class HID_EXT : public NonCopyable
    {
    public:
        Keyboard keyboard;
        Mouse mouse;
    };
}
//------------------------------------------------------------
#endif
// EOF
