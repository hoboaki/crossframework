// 文字コード：UTF-8
#include <XBase/ResFileStream.hpp>

#include <XBase/Application.hpp>
#include <XBase/Argument.hpp>
#include <XBase/Compiler.hpp>
#include <XBase/Os.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/StringTraits.hpp>
#include <XBase/Unused.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
pword_t ResFileStream::CalcReadBufferSize(const pword_t aSize)
{
    return aSize; // そのままの値で大丈夫。
}

//------------------------------------------------------------------------------
ResFileStream::~ResFileStream()
{
    if (mExt.fp != 0) {
        close();
    }
}

//------------------------------------------------------------------------------
bool ResFileStream::open(const char* aPath)
{
#if defined(XBASE_OS_WINDOWS)
    // 260は最大パス長
    fopen_s(&mExt.fp, ::XBase::FixedString< char, 260 >::FromFormat("%s/%s", Application::Instance().argument().exeDirPath(), aPath).readPtr(), "rb");
#elif defined(XBASE_OS_MACOSX)
    // 256は適当なパス長
    mExt.fp = std::fopen(::XBase::FixedString< char, 256 >::FromFormat("Contents/Resources/%s", aPath).readPtr(), "rb");
#else
    mExt.fp = std::fopen(aPath, "rb");
#endif
    return mExt.fp != 0;
}

//------------------------------------------------------------------------------
pword_t ResFileStream::seek(const int aOffset, const SeekOrigin::EnumType aOrigin)
{
    // whence選択
    int whence = int();
    switch (aOrigin) {
        case SeekOrigin::Begin:
            whence = SEEK_SET;
            break;

        case SeekOrigin::Current:
            whence = SEEK_CUR;
            break;

        case SeekOrigin::End:
            whence = SEEK_END;
            break;

        default:
            XBASE_ERROR_INVALID_VALUE(int(aOrigin));
            return 0; // fail safe code
    }

    // seek
    {
        const bool result = std::fseek(mExt.fp, aOffset, whence) == 0;
        if (!result) {
            XBASE_ASSERT_NOT_REACHED();
            return 0; // fail safe code
        }
    }

    // tell
    {
        long pos = ftell(mExt.fp);
        if (pos < 0) {
            XBASE_ASSERT_NOT_REACHED();
            return 0; // fail safe code
        }
        return pword_t(pos);
    }
}

//------------------------------------------------------------------------------
pword_t ResFileStream::read(const ptr_t aBuffer, const pword_t aSize)
{
    return std::fread(aBuffer, 1, aSize, mExt.fp);
}

//------------------------------------------------------------------------------
void ResFileStream::close()
{
    if (mExt.fp == 0) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }
    const bool result = std::fclose(mExt.fp) == 0;
    XBASE_UNUSED(result);
    XBASE_ASSERT(result);
    mExt.fp = 0;
}

//------------------------------------------------------------------------------
ResFileStream_EXT::ResFileStream_EXT()
: fp(0)
{
}

} // namespace
// EOF
