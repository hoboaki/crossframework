// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_APPLICATION_HPP)
#else
#define XBASE_INCLUDED_APPLICATION_HPP

#include <XBase/AppEvent.hpp>
#include <XBase/Enum.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/Os.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/SdkHeader.hpp>

#if defined(XBASE_OS_WINDOWS)
#include <XBase/Application_Windows.hpp>
#elif defined(XBASE_OS_MACOSX)
#include <XBase/Application_MacOSX.hpp>
#else
#include <XBase/Application_Default.hpp>
#endif

namespace XBase {
class Argument;
class Display;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-System
//@{
    /// @brief アプリケーションの全体を扱うクラス。
    /// @details
    /// このクラスのインスタンスはフレームワークによって生成されます。@n
/// xmain 関数が呼ばれた時点でこのクラスは生成されているため Instance() を使ってアクセスできます。@n
class Application : public ::XBase::NonCopyable
{
public:
    /// インスタンスにアクセス。
    static Application& Instance();

    // コンストラクタと
    Application(const Argument&);
    ~Application();

    /// コマンドライン引数を取得する。
    const Argument& argument()const;

    /// @brief アプリケーションの終了を要求する。
    /// @details 
    /// 任意のタイミングでアプリケーションを終了したい場合にこの関数を呼びます。@n
    /// そうすると receiveEvent() は次の呼び出しで AppEvent_Quit を返します。 @n
    void quit();

    /// @name  イベント
    //@{
    AppEvent receiveEvent();   ///< 新しいイベントを受け取る。
    AppEvent lastEvent()const; ///< 最後に受け取ったイベントを取得する。
    //@}

    //============================================================
    // 内部処理用関数。
    void registerDisplay_(Display&);
    void unregisterDisplay_(Display&);

private:
    const Argument& mArgument;
    Enum32< AppEvent > mLastEvent;
    Pointer< Display > mDisplayPtr;
    Application_Ext mExt;
    //------------------------------------------------------------------------------
    AppEvent receiveEventCore();
};
//@}

} // namespace
#endif
// EOF
