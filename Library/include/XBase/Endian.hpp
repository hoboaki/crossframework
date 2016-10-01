// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_ENDIAN_HPP)
#else
#define XBASE_INCLUDED_ENDIAN_HPP

//------------------------------------------------------------------------------
#include <XBase/OS.hpp>

//------------------------------------------------------------------------------
/// @addtogroup XBase-Env
//@{
/// @name エンディアン
//@{

/// BigEndian環境時に定義されるプリプロセッサ。
#define XBASE_BIG_ENDIAN
#undef  XBASE_BIG_ENDIAN

/// LittleEndian環境時に定義されるプリプロセッサ。
#define XBASE_LITTLE_ENDIAN
#undef  XBASE_LITTLE_ENDIAN

// 選択
#if defined(XBASE_OS_MACOSX) && defined(__BIG_ENDIAN__)
    #define XBASE_BIG_ENDIAN
#else
    #define XBASE_LITTLE_ENDIAN
#endif

/// @def XBASE_IS_BIG_ENDIAN
/// @brief BigEndianならtrue。LittleEndianならfalseが入る。
#if defined(XBASE_BIG_ENDIAN)
    #define XBASE_IS_BIG_ENDIAN (true)
#else
    #define XBASE_IS_BIG_ENDIAN (false)
#endif

/// @def XBASE_IS_LITTLE_ENDIAN
/// @brief LittleEndianならtrue。BigEndianならfalseが入る。
#if defined(XBASE_LITTLE_ENDIAN)
    #define XBASE_IS_LITTLE_ENDIAN (true)
#else
    #define XBASE_IS_LITTLE_ENDIAN (false)
#endif

//@}
//@}
//------------------------------------------------------------------------------
#endif
// EOF
