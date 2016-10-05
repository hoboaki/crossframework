// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_APPLICATION_MACOSX_HPP)
#else
#define XBASE_INCLUDED_APPLICATION_MACOSX_HPP

#include <XBase/Bool.hpp>

//------------------------------------------------------------------------------
namespace XBase {

// MacOSX環境でのApplicationの拡張。
class Applcation_Ext
{
public:
    //============================================================
    s64 prevUpdateTicks;
    Bool32 doQuit;

    //============================================================
    Applcation_Ext();
    ~Applcation_Ext();
};
//@}

} // namespace
#endif
// EOF
