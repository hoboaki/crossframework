// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_APPEVENT_HPP)
#else
#define XBASE_INCLUDED_APPEVENT_HPP

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-System
//@{
/// アプリケーションイベントの種類。
enum AppEvent
{
    AppEvent_Quit     ///< 終了する。
    , AppEvent_Update ///< 状態を更新する。
    // term
    , AppEvent_TERMINATE
    , AppEvent_MIN = 0
    , AppEvent_MAX = AppEvent_TERMINATE - 1
    // alias
    , AppEvent_INVALID = AppEvent_TERMINATE ///< 無効なイベント。
};
//@}

} // namespace
#endif
// EOF
