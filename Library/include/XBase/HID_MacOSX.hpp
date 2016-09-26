/**
 * @file
 * @brief HID_EXT�^���L�q����B
 * @author akino
 */
#if defined(XBASE_INCLUDED_HID_MACOSX_HPP)
#else
#define XBASE_INCLUDED_HID_MACOSX_HPP

//------------------------------------------------------------
#include <XBase/Keyboard.hpp>
#include <XBase/Mouse.hpp>
#include <XBase/NonCopyable.hpp>

//------------------------------------------------------------
namespace XBase {
    // MacOSX��HID�g���B
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
