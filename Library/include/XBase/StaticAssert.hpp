// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_STATICASSERT_HPP)
#else
#define XBASE_INCLUDED_STATICASSERT_HPP

#include <XBase/Compiler.hpp>

/// @addtogroup XBase-Debug
//@{
/// @name コンパイル時アサート
//@{

/// @brief メッセージ付きコンパイル時アサート。
/// @param aCond チェックする条件。これがfalseならコンパイルエラー。
/// @param aMsg エラー時に出力するメッセージ。
#if defined(XBASE_COMPILER_MSVC)
    #define XBASE_STATIC_ASSERT_MSG( aCond , aMsg )  static_assert( aCond , aMsg )
#else
    #define XBASE_STATIC_ASSERT_MSG( aCond , aMsg )
#endif

/// @brief コンパイル時アサート。
/// @param aCond チェックする条件。これがfalseならコンパイルエラー。
#define XBASE_STATIC_ASSERT( aCond )  XBASE_STATIC_ASSERT_MSG( aCond , "Static assert failure." )

/// コンパイルを止めるアサート。
#define XBASE_STATIC_ASSERT_FAILURE   XBASE_STATIC_ASSERT_MSG( false )

//@}
//@}
#endif
// EOF

