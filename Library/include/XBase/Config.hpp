// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_CONFIG_HPP)
#else
#define XBASE_INCLUDED_CONFIG_HPP

//------------------------------------------------------------------------------
/// @addtogroup XBase-Env
//@{

/* ビルドバージョンレベルの定義。
 * FINAL版に向けて1ずつ大きくなる。
 * ・DEBUG     = 0
 * ・DEVELOP   = 1
 * ・SEMIFINAL = 2
 * ・FINAL     = 3
 */
#define XBASE_BUILD_VERSION_LEVEL_DEBUG     (0)
#define XBASE_BUILD_VERSION_LEVEL_DEVELOP   (1)
#define XBASE_BUILD_VERSION_LEVEL_SEMIFINAL (2)
#define XBASE_BUILD_VERSION_LEVEL_FINAL     (3)

/*
 * 現在のビルドバージョンレベルの指定。
 * XBASE_BUILD_VERSION_LEVELにビルドバージョンレベルが定義される。
 */
// debug
#if defined(XLIBRARY_DEBUG)
    #if defined(XBASE_BUILD_VERSION_LEVEL)
        #error Already defined 'XBASE_BUILD_VERSION_LEVEL'.
    #endif
    #define XBASE_BUILD_VERSION_LEVEL (XBASE_BUILD_VERSION_LEVEL_DEBUG)
#endif
// develop
#if defined(XLIBRARY_DEVELOP)
    #if defined(XBASE_BUILD_VERSION_LEVEL)
        #error Already defined 'XBASE_BUILD_VERSION_LEVEL'.
    #endif
    #define XBASE_BUILD_VERSION_LEVEL (XBASE_BUILD_VERSION_LEVEL_DEVELOP)
#endif
// semifinal
#if defined(XLIBRARY_SEMIFINAL)
    #if defined(XBASE_BUILD_VERSION_LEVEL)
        #error Already defined 'XBASE_BUILD_VERSION_LEVEL'.
    #endif
    #define XBASE_BUILD_VERSION_LEVEL (XBASE_BUILD_VERSION_LEVEL_SEMIFINAL)
#endif
// final
#if defined(XLIBRARY_FINAL)
    #if defined(XBASE_BUILD_VERSION_LEVEL)
        #error Already defined 'XBASE_BUILD_VERSION_LEVEL'.
    #endif
    #define XBASE_BUILD_VERSION_LEVEL (XBASE_BUILD_VERSION_LEVEL_FINAL)
#endif
// 未定義は警告しDEBUGに設定。
#if !defined(XBASE_BUILD_VERSION_LEVEL)
    #warning "Not defined build version. Please defined 'XLIBRARY_DEBUG','XLIBRARY_DEVELOP','XLIBRARY_SEMIFINAL','XLIBRARY_FINAL'."
    #define XBASE_BUILD_VERSION_LEVEL (XBASE_BUILD_VERSION_LEVEL_DEBUG)
#endif

/// @name ビルド環境
//@{

// 実行時エラーの有効・無効。DEVELOPまでなら有効。
#if (XBASE_BUILD_VERSION_LEVEL <= XBASE_BUILD_VERSION_LEVEL_DEVELOP)
    /// 実行時エラーが有効なときに定義されるプリプロセッサ。
    #define XBASE_CONFIG_ENABLE_RUNTIME_ERROR
#endif

// ログ文字列の有効・無効。SEMIFINALまでなら有効。
#if (XBASE_BUILD_VERSION_LEVEL <= XBASE_BUILD_VERSION_LEVEL_SEMIFINAL)
    /// ログ文字列が有効なときに定義されるプリプロセッサ。
    #define XBASE_CONFIG_ENABLE_LOGSTR
#endif

//@}
//@}
//------------------------------------------------------------------------------
#endif
// EOF
