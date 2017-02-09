// 文字コード：UTF-8
#include <ae/base/ResFileStream.hpp>

#include <ae/base/Application.hpp>
#include <ae/base/Argument.hpp>
#include <ae/base/Compiler.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/StringTraits.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
#if defined(AE_BASE_OS_WINDOWS)
    // 260は最大パス長
    fopen_s(&mExt.fp, ::ae::base::FixedString< char, 260 >::FromFormat("%s/%s", Application::Instance().argument().exeDirPath(), aPath).readPtr(), "rb");
#elif defined(AE_BASE_OS_MACOSX)
    // 256は適当なパス長
    mExt.fp = std::fopen(::ae::base::FixedString< char, 256 >::FromFormat("Contents/Resources/%s", aPath).readPtr(), "rb");
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
            AE_BASE_ERROR_INVALID_VALUE(int(aOrigin));
            return 0; // fail safe code
    }

    // seek
    {
        const bool result = std::fseek(mExt.fp, aOffset, whence) == 0;
        if (!result) {
            AE_BASE_ASSERT_NOT_REACHED();
            return 0; // fail safe code
        }
    }

    // tell
    {
        long pos = ftell(mExt.fp);
        if (pos < 0) {
            AE_BASE_ASSERT_NOT_REACHED();
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
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    const bool result = std::fclose(mExt.fp) == 0;
    AE_BASE_UNUSED(result);
    AE_BASE_ASSERT(result);
    mExt.fp = 0;
}

//------------------------------------------------------------------------------
ResFileStream_EXT::ResFileStream_EXT()
: fp(0)
{
}

}} // namespace
// EOF
