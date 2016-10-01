/**
 * @file
 * @brief 動作OSに関する定数を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_OS_HPP)
#else
#define XBASE_INCLUDED_OS_HPP

//------------------------------------------------------------
/// @addtogroup XBase-Env 
//@{
/// @name オペレーティングシステム 
//@{

/// Windows使用時に定義されるプリプロセッサ。
#define XBASE_OS_WINDOWS
#undef  XBASE_OS_WINDOWS

/// MacOSX使用時に定義されるプリプロセッサ。
#define XBASE_OS_MACOSX
#undef  XBASE_OS_MACOSX

/// iPhone使用時に定義されるプリプロセッサ。
#define XBASE_OS_IPHONE
#undef  XBASE_OS_IPHONE

/// iPad使用時に定義されるプリプロセッサ。
#define XBASE_OS_IPAD
#undef  XBASE_OS_IPAD

/// iOS使用時に定義されるプリプロセッサ。
#define XBASE_OS_IOS
#undef  XBASE_OS_IOS

// 選択
#if defined(_WIN32)
    #define XBASE_OS_WINDOWS
#elif defined(__APPLE__)
    #if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
        #define XBASE_OS_MACOSX
    #elif defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
        #define XBASE_OS_IOS
        #define XBASE_OS_IPHONE
    #else
        #define XBASE_OS_IOS
        #define XBASE_OS_IPAD
    #endif
#else
    #error Unkonwn OS.
#endif

//@}
//@}
//------------------------------------------------------------
#endif
// EOF
