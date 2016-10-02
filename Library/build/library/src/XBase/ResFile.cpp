// 文字コード：UTF-8
#include <XBase/ResFile.hpp>

//------------------------------------------------------------------------------
#include <XBase/AutoMemBlock.hpp>
#include <XBase/ResFileStream.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
const AutoMemBlock ResFile::Read(
    const char* aPath,
    IAllocator& aAllocator
    )
{
    // オープン
    ResFileStream stream;
    if (!stream.open(aPath)) {
        XBASE_NOT_REACH_ASSERT_MSGFMT("ResFile named '%s' is failed to open.", aPath);
        return AutoMemBlock();
    }

    // メモリ準備
    const pword_t size = stream.seek(0, ::XBase::SeekOrigin_End);
    const pword_t bufferSize = stream.calcReadBufferSize(size);
    ptr_t ptr = aAllocator.alloc(bufferSize, stream.requireReadBufferAlignment());
    if (ptr == 0) {
        XBASE_NOT_REACH_ASSERT();
        return AutoMemBlock();
    }

    // 読み込み
    stream.seek(0, ::XBase::SeekOrigin_Begin);
    stream.read(ptr, size);
    stream.close();

    // 終了
    return AutoMemBlock(MemBlock(ptr, size), aAllocator);
}

} // namespace
// EOF
