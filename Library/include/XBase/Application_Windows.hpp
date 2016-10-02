// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_APPLICATION_WINDOWS_HPP)
#else
#define XBASE_INCLUDED_APPLICATION_WINDOWS_HPP

#include <XBase/Bool.hpp>
#include <XBase/Time.hpp>

//------------------------------------------------------------------------------
namespace XBase {

// Windows環境でのApplicationの拡張。
class Application_EXT
{
public:
    //============================================================
    u64  prevUSec;
    Bool32 doQuit;

    //============================================================
    Application_EXT();
};
//@}

} // namespace
#endif
// EOF
