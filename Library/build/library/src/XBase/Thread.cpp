/**
 * @file
 * @brief Thread.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Thread.hpp>

//------------------------------------------------------------
#include <XBase/Math.hpp>
#include <XBase/OS.hpp>
#include <XBase/TimeSpan.hpp>

#if defined(XBASE_OS_WINDOWS)
    #include <XBase/SDKHeader.hpp>
#else
    #include <unistd.h>
#endif

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
void Thread::Sleep( const TimeSpanPOD& aTimeSpan )
{
#if defined(XBASE_OS_WINDOWS)
    ::Sleep( DWORD( ::XBase::Math::Max( s64( 1 ) , aTimeSpan.milliseconds() ) ) );
#else    
    usleep( useconds_t(::XBase::Math::Max( s64( 1 ) , aTimeSpan.microseconds() )) );
#endif
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
