/**
 * @file
 * @brief コンパイラ環境に関する定数を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_COMPILER_HPP)
#else
#define XBASE_INCLUDED_COMPILER_HPP

//------------------------------------------------------------
/// @addtogroup XBase-Env
//@{
/// @name コンパイラ
//@{

/// MicrosoftVisualC使用時に定義されるプリプロセッサ。
#define XBASE_COMPILER_MSVC
#undef  XBASE_COMPILER_MSVC

/// GNUC使用時に定義されるプリプロセッサ。
#define XBASE_COMPILER_GNUC
#undef  XBASE_COMPILER_GNUC

// 選択
#if defined(_MSC_VER)
    #define XBASE_COMPILER_MSVC
#elif defined(__GNUC__)
    #define XBASE_COMPILER_GNUC
#else
    #error Unknown Compiler.
#endif

//@}
//@}
//------------------------------------------------------------
#endif
// EOF
