// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_HASH_HPP)
#else
#define XBASE_INCLUDED_HASH_HPP

#include <XBase/BuiltInTypes.hpp>

namespace XBase {
class MemBlock;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Util
//@{
    /// ハッシュ値を求める関数群。
struct Hash
{
    /// CRC16の値を求める。
    static uint16 CRC16(const MemBlock&);

    /// CRC32(Castagnoli)の値を求める。
    static uint32 CRC32(const MemBlock&);
};
//@}

} // namespace
#endif
// EOF
