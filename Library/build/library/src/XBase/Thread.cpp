// 文字コード：UTF-8
#include <XBase/Thread.hpp>

//------------------------------------------------------------------------------
#include <XBase/Math.hpp>
#include <XBase/Os.hpp>
#include <XBase/TimeSpan.hpp>

#if defined(XBASE_OS_WINDOWS)
    #include <XBase/SdkHeader.hpp>
#else
    #include <unistd.h>
#endif

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
void Thread::Sleep(const TimeSpanPod& aTimeSpan)
{
#if defined(XBASE_OS_WINDOWS)
    ::Sleep(DWORD(::XBase::Math::Max(s64(1), aTimeSpan.milliseconds())));
#else    
    usleep(useconds_t(::XBase::Math::Max(s64(1), aTimeSpan.microseconds())));
#endif
}

} // namespace
// EOF
