// 文字コード：UTF-8
#include <XBase/ResFileStream.hpp>

//------------------------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>
#include <XBase/Unused.hpp>

//------------------------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------------------------
ResFileStream::ResFileStream()
    : mEXT()
{
}

//------------------------------------------------------------------------------
ResFileStream::ResFileStream(const char* aPath)
    : mEXT()
{
    const bool result = open(aPath);
    XBASE_UNUSED(result);
    XBASE_ASSERT_MSGFMT(result, "Can't open resource file '%s'.", aPath);
}

//------------------------------------------------------------------------------
pword_t ResFileStream::requireReadBufferAlignment()const
{
    return ReadBufferAlignment;
}

//------------------------------------------------------------------------------
pword_t ResFileStream::calcReadBufferSize(const pword_t aSize)const
{
    return CalcReadBufferSize(aSize);
}

} // namespace
// EOF
