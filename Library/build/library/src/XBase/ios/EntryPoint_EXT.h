/**
 * @file
 * @brief Main関数に関する関数郡を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_ENTRYPOINT_EXT_H)
#else
#define XBASE_INCLUDED_ENTRYPOINT_EXT_H

//-----------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif    
    // main関数スレッド
    extern int mainUI( int aArgCount , char* aArgValues[] );
    extern int mainC( int aArgCount , char* aArgValues[] , const char* aExeFileName , const char* aExeDirPath );    
    // xmain関数スレッド
    extern void* xmainThreadEntryPoint( void* );
    extern int xmainThreadEntryPointC( void* );
#ifdef __cplusplus
}
#endif
//-----------------------------------------------------------
#endif
// EOF
