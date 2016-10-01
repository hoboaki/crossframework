// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_DIVIDECHECK_HPP)
#else
#define XBASE_INCLUDED_DIVIDECHECK_HPP

//------------------------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    // 割り算チェックで使うモノたち用空間。
    struct DivideCheck
    {
        // Assert用メッセージ文字列。
        static const char* const AssertionMessage;

        // アサートで止めつつ引数の値をそのまま返す。
        template< typename T >
        static T Error( const T& aRetVal )
        {
            XBASE_NOT_REACH_ASSERT_MSG(AssertionMessage);
            return aRetVal;
        }
    };
}
/// @addtogroup XBase-Debug
//@{
/// @name 0除算チェック
//@{

/// @brief lhs /= rhs, operator /=の0除算チェック。
/// @details 0除算しようとした場合はエラー。エラーが無効なときは除算をせずに続行する。
#define XBASE_DIV_ASSIGN( lhs , rhs ) \
    do \
    { \
        if ( rhs == 0 ) \
        { \
            XBASE_NOT_REACH_ASSERT_MSG( ::XBase::DivideCheck::AssertionMessage ); \
        } \
        else \
        { \
            lhs /= rhs; \
        } \
    } while(0)

/// @brief lhs / rhsの0除算チェック。
/// @details 0除算しようとした場合はエラー。エラーが無効なときは除算をせずに左辺を返す。
#define XBASE_DIV( aLHS , aRHS ) ( aRHS != 0 ? ( aLHS / aRHS ) : ::XBase::DivideCheck::Error( aLHS ) )

//@}
//@}
//------------------------------------------------------------------------------
#endif
// EOF
