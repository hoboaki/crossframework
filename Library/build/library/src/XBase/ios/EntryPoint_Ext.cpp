// 文字コード：UTF-8
#include <XBase/EntryPoint.hpp>

//------------------------------------------------------------------------------
#include <pthread.h>
#include <XBase/Application.hpp>
#include <XBase/Argument.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/Unused.hpp>
#include "EntryPoint_Ext.h"
#include "EntryPoint_Sync.h"

//------------------------------------------------------------------------------
namespace {

// スレッドの引数
struct tThreadArg
{
    int result;
    const ::XBase::Argument* argPtr;
};

} // namespace

//------------------------------------------------------------------------------
int xmainThreadEntryPointC(void* aArg)
{
    // 変換
    tThreadArg* arg = static_cast<tThreadArg*>(aArg);

    // UIMainが立ち上がるまで待つ。
    XBaseEntryPointSync_XMainWait();

    {// 起動処理開始  
        // Application作成
        ::XBase::Application app(*arg->argPtr);

        // xmain実行
        arg->result = xmain(app);
    }

    // UIMainに終了したことを通知
    XBaseEntryPointSync_UIMainSignal();

    // スレッド終了
    return 0;
}

//------------------------------------------------------------------------------
int mainC(
    const int aArgCount,
    char* aArgValues[],
    const char* aExeFileName,
    const char* aExeDirPath
    )
{
    // 引数作成
    const int offset = 1; // Exeのパスは別で処理しているためパス。
    XBASE_ASSERT_LESS_EQUALS(offset, aArgCount);
    const ::XBase::Argument arg(
        ::XBase::uint(aArgCount - offset),
        &aArgValues[offset],
        aExeFileName,
        aExeDirPath
        );

// 同期オブジェクト作成
    XBaseEntryPointSync_Initialize();

    // xmainスレッド作成
    tThreadArg threadArg = {};
    threadArg.argPtr = &arg;
    pthread_t threadXMain;
    {
        int result = pthread_create(
            &threadXMain,
            0, // attr
            xmainThreadEntryPoint,
            &threadArg
            );
        XBASE_UNUSED(result);
        XBASE_ASSERT_EQUALS(result, 0);
    }

    // UIMain実行
    mainUI(aArgCount, aArgValues);

    // xmainスレッド終了待ち
    {
        int result = pthread_join(threadXMain, 0);
        XBASE_UNUSED(result);
        XBASE_ASSERT_EQUALS(result, 0);
    }

    // 同期オブジェクト後始末
    XBaseEntryPointSync_Finalize();

    // 終了
    return threadArg.result;
}

//------------------------------------------------------------------------------
// EOF
