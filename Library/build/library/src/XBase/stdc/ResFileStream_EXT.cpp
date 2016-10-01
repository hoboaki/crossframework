/**
 * @file
 * @brief ResFileStream.hppの実装を記述する。
 * @author akino
 */
#include <XBase/ResFileStream.hpp>

//------------------------------------------------------------
#include <XBase/Application.hpp>
#include <XBase/Argument.hpp>
#include <XBase/Compiler.hpp>
#include <XBase/OS.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/StringTraits.hpp>
#include <XBase/Unused.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
pword_t ResFileStream::CalcReadBufferSize( const pword_t aSize )
{
    return aSize; // そのままの値で大丈夫。
}

//------------------------------------------------------------
ResFileStream::~ResFileStream()
{
    if ( mEXT.fp != 0 )
    {
        close();
    }
}

//------------------------------------------------------------
bool ResFileStream::open( const char* aPath )
{   
#if defined(XBASE_OS_WINDOWS)
    // 260は最大パス長
    fopen_s( &mEXT.fp , ::XBase::FixedString< char , 260 >::FromFormat( "%s/%s" , Application::Instance().argument().exeDirPath() , aPath ).readPtr() , "rb" );
#elif defined(XBASE_OS_MACOSX)
    // 256は適当なパス長
    mEXT.fp = std::fopen( ::XBase::FixedString< char , 256 >::FromFormat( "Contents/Resources/%s" , aPath ).readPtr() , "rb" );
#else
    mEXT.fp = std::fopen( aPath , "rb" );
#endif
    return mEXT.fp != 0;
}

//------------------------------------------------------------
pword_t ResFileStream::seek( const int aOffset , const SeekOrigin aOrigin )
{
    // whence選択
    int whence = int();
    switch ( aOrigin )
    {
    case SeekOrigin_Begin:
        whence = SEEK_SET;
        break;

    case SeekOrigin_Current:
        whence = SEEK_CUR;
        break;

    case SeekOrigin_End:
        whence = SEEK_END;
        break;

    default:
        XBASE_INVALID_VALUE_ERROR( int( aOrigin ) );
        return 0; // fail safe code
    }

    // seek
    {
        const bool result = std::fseek( mEXT.fp , aOffset , whence ) == 0;
        if ( !result )
        {
            XBASE_NOT_REACH_ASSERT();
            return 0; // fail safe code
        }
    }

    // tell
    {
        long pos = ftell( mEXT.fp );
        if ( pos < 0 )
        {
            XBASE_NOT_REACH_ASSERT();
            return 0; // fail safe code
        }
        return pword_t( pos );
    }
}

//------------------------------------------------------------
pword_t ResFileStream::read( const ptr_t aBuffer , const pword_t aSize )
{
    return std::fread( aBuffer , 1 , aSize , mEXT.fp );
}

//------------------------------------------------------------
void ResFileStream::close()
{
    if ( mEXT.fp == 0 )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    const bool result = std::fclose( mEXT.fp ) == 0;
    XBASE_UNUSED( result );
    XBASE_ASSERT( result );
    mEXT.fp = 0;
}

//------------------------------------------------------------
ResFileStream_EXT::ResFileStream_EXT()
: fp( 0 )
{
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
