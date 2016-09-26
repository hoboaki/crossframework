/**
 * @file
 * @brief OSの種類に関する定数を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_OSTYPE_HPP)
#else
#define XBASE_INCLUDED_OSTYPE_HPP

//------------------------------------------------------------
#include <XBase/OS.hpp>

//------------------------------------------------------------
/// @addtogroup XBase-Env 
//@{

/// @name オペレーティングシステムの種類
//@{

/// WindowSystem型OS使用時に定義されるプリプロセッサ。
#define XBASE_OSTYPE_WINDOWSYSTEM
#undef  XBASE_OSTYPE_WINDOWSYSTEM

/// 組み込み型OS使用時に定義されるプリプロセッサ。
#define XBASE_OSTYPE_EMBEDDEDSYSTEM
#undef  XBASE_OSTYPE_EMBEDDEDSYSTEM

// 選択
#if defined(XBASE_OS_WINDOWS) || defined(XBASE_OS_MACOSX)
    #define XBASE_OSTYPE_WINDOWSYSTEM
#elif defined(XBASE_OS_IOS)
    #define XBASE_OSTYPE_EMBEDDEDSYSTEM
#endif

//@}
//@}
//------------------------------------------------------------
#endif
// EOF
