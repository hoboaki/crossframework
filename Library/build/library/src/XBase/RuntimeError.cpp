/**
 * @file
 * @brief RuntimeError.hppの実装を記述する。
 * @author akino
 */
#include <XBase/RuntimeError.hpp>

//------------------------------------------------------------
#include <cassert>
#include <XBase/Compiler.hpp>
#include <XBase/Config.hpp>
#include <XBase/FunctionAttribute.hpp>
#include <XBase/IRuntimeErrorCallback.hpp>
#include <XBase/OS.hpp>

// for MessageBox
#if (defined(XBASE_OS_WIN32) && defined(XBASE_COMPILER_MSVC))
    #include <crtdbg.h>
#endif

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
namespace {
    IRuntimeErrorCallback* tCallbackPtr = 0;
#if defined(XBASE_CONFIG_ENABLE_RUNTIME_ERROR)
    IRuntimeErrorCallback& tCallbackObj()
    {
        // ここに到達するということは既に致命的な状態なはずなので
        // ポインタチェックはしない。
        return tCallbackPtr != 0
            ? *tCallbackPtr
            : RuntimeError::DefaultCallback();
    }
#endif
}


//------------------------------------------------------------
IRuntimeErrorCallback& RuntimeError::DefaultCallback()
{
    // コールバックの実装。
    class Callback : public IRuntimeErrorCallback
    {
    public:
        XBASE_OVERRIDE( void onRuntimeError() )
        {
#if defined(XBASE_CONFIG_ENABLE_RUNTIME_ERROR)
            // 標準のアサートで止めてみる。
            assert( false && "Runtime Error." );
            
            // メッセージボックスで止めてみる。
#if (defined(XBASE_OS_WIN32) && defined(XBASE_COMPILER_MSVC)) 
            MessageBox(0,L"エラーが発生しました。ログを確認してください。",L"Runtime Error",MB_OK);
#endif
#endif
        }
    };

    // コールバックを返す
    static Callback obj;
    return obj;
}

//------------------------------------------------------------
void RuntimeError::SetCallback( IRuntimeErrorCallback& aCallback )
{
    tCallbackPtr = &aCallback;
}

//------------------------------------------------------------
void RuntimeError::OnError()
{
#if defined(XBASE_CONFIG_ENABLE_RUNTIME_ERROR)
    tCallbackObj().onRuntimeError();
#endif
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
