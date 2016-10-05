// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_APPLICATION_WINDOWS_HPP)
#else
#define XBASE_INCLUDED_APPLICATION_WINDOWS_HPP

#include <XBase/Bool.hpp>
#include <XBase/Time.hpp>

//------------------------------------------------------------------------------
namespace XBase {

// Windows環境でのApplicationの拡張。
class Applcation_Ext
{
public:
    //============================================================
    u64  prevUSec;
    Bool32 doQuit;

    //============================================================
    Applcation_Ext();
};
//@}

} // namespace
#endif
// EOF
