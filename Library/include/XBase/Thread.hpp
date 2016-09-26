/**
 * @file
 * @brief Thread型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_THREAD_HPP)
#else
#define XBASE_INCLUDED_THREAD_HPP

//------------------------------------------------------------
namespace XBase {
    struct TimeSpanPOD;
}

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Thread
//@{
    /// スレッド。
    class Thread
    {
    public:
        /// 指定時間スリープする。
        static void Sleep( const TimeSpanPOD& );
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
