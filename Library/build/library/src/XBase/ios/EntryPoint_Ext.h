// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_ENTRYPOINT_EXT_H)
#else
#define XBASE_INCLUDED_ENTRYPOINT_EXT_H

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif    

// main関数スレッド
extern int mainUI(int aArgCount, char* aArgValues[]);
extern int mainC(int aArgCount, char* aArgValues[], const char* aExeFileName, const char* aExeDirPath);
// xmain関数スレッド
extern void* xmainThreadEntryPoint(void*);
extern int xmainThreadEntryPointC(void*);

#ifdef __cplusplus
} // extern "C"
#endif
//------------------------------------------------------------------------------
#endif
// EOF
