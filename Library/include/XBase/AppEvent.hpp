// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_APPEVENT_HPP)
#else
#define XBASE_INCLUDED_APPEVENT_HPP

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-System
//@{
/// アプリケーションイベントの種類。
struct AppEvent
{
    enum EnumType
    {
        Quit,     ///< 終了する。
        Update, ///< 状態を更新する。
        
        TERM,

        // alias
        INVALID, ///< 無効なイベント。
    };
};
//@}

} // namespace
#endif
// EOF
