// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_HID_IOS_HPP)
#else
#define XBASE_INCLUDED_HID_IOS_HPP

#include <XBase/NonCopyable.hpp>
#include <XBase/Touch.hpp>

//------------------------------------------------------------------------------
namespace XBase {

// iOSのHid拡張。
class Hid_Ext : public NonCopyable
{
public:
    Touch touch;

    //------------------------------------------------------------------------------
    Hid_Ext();
};

} // namespace
#endif
// EOF
