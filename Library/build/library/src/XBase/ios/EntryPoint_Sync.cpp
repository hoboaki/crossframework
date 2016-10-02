// 文字コード：UTF-8
#include "EntryPoint_Sync.h"

//------------------------------------------------------------------------------
#include <pthread.h>
#include <XBase/Placement.hpp>
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace {

// condのラッパークラス。
class tSynbObj
{
public:
    tSynbObj()
        : mMutex(),
        mCond(),
        mValue(1)
    {
        int result = int();
        result = pthread_mutex_init(&mMutex, 0);
        XBASE_EQUALS_ASSERT(result, 0);
        result = pthread_cond_init(&mCond, 0);
        XBASE_EQUALS_ASSERT(result, 0);
    }

    ~tSynbObj()
    {
        int result = int();
        result = pthread_cond_destroy(&mCond);
        XBASE_EQUALS_ASSERT(result, 0);
        result = pthread_mutex_destroy(&mMutex);
        XBASE_EQUALS_ASSERT(result, 0);
    }

    void signal()
    {
        int result = int();
        result = pthread_mutex_lock(&mMutex);
        XBASE_EQUALS_ASSERT(result, 0);

        XBASE_EQUALS_ASSERT(mValue, 1);
        mValue = 0;

        result = pthread_cond_broadcast(&mCond);
        XBASE_EQUALS_ASSERT(result, 0);

        result = pthread_mutex_unlock(&mMutex);
        XBASE_EQUALS_ASSERT(result, 0);
    }

    void wait()
    {
        int result = int();
        result = pthread_mutex_lock(&mMutex);
        XBASE_EQUALS_ASSERT(result, 0);

        while (0 < mValue) {
            result = pthread_cond_wait(&mCond, &mMutex);
            XBASE_EQUALS_ASSERT(result, 0);
        }
        mValue = 1;

        result = pthread_cond_broadcast(&mCond);
        XBASE_EQUALS_ASSERT(result, 0);

        result = pthread_mutex_unlock(&mMutex);
        XBASE_EQUALS_ASSERT(result, 0);
    }
private:
    pthread_mutex_t mMutex;
    pthread_cond_t  mCond;
    volatile int mValue;
};

// 複数のCondをまとめたもの。
class tSyncObjSet
{
public:
    tSynbObj syncXMain;
    tSynbObj syncUIMain;
};

// 同期オブジェクトの変数。
::XBase::Placement< tSyncObjSet > tSyncObjSetInstance;
XBaseAppEvent tAppEvent = XBaseAppEvent_INVALID;

} // namespace

//------------------------------------------------------------------------------
void XBaseEntryPointSync_Initialize()
{
    tSyncObjSetInstance.init();
}

//------------------------------------------------------------------------------
void XBaseEntryPointSync_Finalize()
{
    tSyncObjSetInstance.reset();
}

//------------------------------------------------------------------------------
void XBaseEntryPointSync_XMainWait()
{
    XBaseEntryPointSync_CATransactionFlush();
    tSyncObjSetInstance->syncXMain.wait();
}

//------------------------------------------------------------------------------
void XBaseEntryPointSync_XMainSignal()
{
    tSyncObjSetInstance->syncXMain.signal();
}

//------------------------------------------------------------------------------
void XBaseEntryPointSync_UIMainWait()
{
    XBaseEntryPointSync_CATransactionFlush();
    tSyncObjSetInstance->syncUIMain.wait();
}

//------------------------------------------------------------------------------
void XBaseEntryPointSync_UIMainSignal()
{
    tSyncObjSetInstance->syncUIMain.signal();
}

//------------------------------------------------------------------------------
void XBaseEntryPointSync_SetAppEvent(const XBaseAppEvent aEvent)
{
    tAppEvent = aEvent;
}

//------------------------------------------------------------------------------
XBaseAppEvent XBaseEntryPointSync_GetAppEvent()
{
    return tAppEvent;
}

//------------------------------------------------------------------------------
// EOF
