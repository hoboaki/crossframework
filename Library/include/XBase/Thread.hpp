// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_THREAD_HPP)
#else
#define XBASE_INCLUDED_THREAD_HPP

namespace XBase {
struct TimeSpanPOD;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Thread
//@{
/// スレッド。
class Thread
{
public:
    /// 指定時間スリープする。
    static void Sleep(const TimeSpanPOD&);
};
//@}

} // namespace
#endif
// EOF
