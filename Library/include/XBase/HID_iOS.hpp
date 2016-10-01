// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_HID_IOS_HPP)
#else
#define XBASE_INCLUDED_HID_IOS_HPP

//------------------------------------------------------------------------------
#include <XBase/NonCopyable.hpp>
#include <XBase/Touch.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    // iOSのHID拡張。
    class HID_EXT : public NonCopyable
    {
    public:
        Touch touch;
        
        //------------------------------------------------------------------------------
        HID_EXT();
    };

} // namespace
#endif
// EOF
