/**
 * @file
 * @brief HID_EXT�^���L�q����B
 * @author akino
 */
#if defined(XBASE_INCLUDED_HID_IOS_HPP)
#else
#define XBASE_INCLUDED_HID_IOS_HPP

//------------------------------------------------------------
#include <XBase/NonCopyable.hpp>
#include <XBase/Touch.hpp>

//------------------------------------------------------------
namespace XBase {
    // iOS��HID�g���B
    class HID_EXT : public NonCopyable
    {
    public:
        Touch touch;
        
        //-----------------------------------------------------------
        HID_EXT();
    };
}
//------------------------------------------------------------
#endif
// EOF
