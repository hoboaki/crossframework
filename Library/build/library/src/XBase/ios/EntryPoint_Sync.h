// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_ENTRYPOINT_SYNC_H)
#else
#define XBASE_INCLUDED_ENTRYPOINT_SYNC_H

//------------------------------------------------------------------------------
#include "XBaseAppEvent.h"

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    extern void XBaseEntryPointSync_Initialize();
    extern void XBaseEntryPointSync_Finalize();
    extern void XBaseEntryPointSync_XMainWait();
    extern void XBaseEntryPointSync_XMainSignal();
    extern void XBaseEntryPointSync_UIMainWait();
    extern void XBaseEntryPointSync_UIMainSignal();
    extern void XBaseEntryPointSync_SetAppEvent( XBaseAppEvent );
    extern XBaseAppEvent XBaseEntryPointSync_GetAppEvent();
    extern void XBaseEntryPointSync_CATransactionFlush();
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
// EOF
