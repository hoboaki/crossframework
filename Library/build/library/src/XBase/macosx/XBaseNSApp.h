// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_XBASENSAPP_H)
#else
#define XBASE_INCLUDED_XBASENSAPP_H

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    extern void XBaseNSApp_Initialize();
    extern void XBaseNSApp_Finalize();
    extern void XBaseNSApp_PollEvent();
    extern void XBaseNSApp_Terminate();
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
// EOF
