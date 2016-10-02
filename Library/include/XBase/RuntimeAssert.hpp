// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_RUNTIMEASSERT_HPP)
#else
#define XBASE_INCLUDED_RUNTIMEASSERT_HPP

#include <XBase/BuiltInTypes.hpp>
#include <XBase/Console.hpp>
#include <XBase/PointerCheck.hpp>
#include <XBase/RuntimeError.hpp>
#include <XBase/ShortString.hpp>
#include <XBase/ToShortString.hpp>
#include <XBase/ValueInRange.hpp>

//------------------------------------------------------------------------------
namespace XBase {

// 実行時Assertを扱う空間。
struct RuntimeAssert
{
    static const char* const Separator;      // 分離する文字列。
    static const char* const Header;         // ヘッダ。
    static const char* const FileLineFmt;    // ファイルと行数。
    static const char* const LabelCondition; // ラベル:Condition。
    static const char* const LabelMessage;   // ラベル:Message。
};

} // namespace

// 実行時Assertの本体。XBASE_CONFIG_ENABLE_RUNTIME_ERRORが定義されているときに動作。
#if defined(XBASE_CONFIG_ENABLE_RUNTIME_ERROR)
#define XBASE_RUNTIME_ASSERT( aCond , ... ) \
    do \
    { \
        if( !(aCond) ) \
        { \
            XBASE_COUT_LINE( ::XBase::RuntimeAssert::Separator ); \
            XBASE_COUT_LINE_WITH_TIME( ::XBase::RuntimeAssert::Header ); \
            XBASE_COUTFMT_LINE( ::XBase::RuntimeAssert::FileLineFmt , __FILE__ , __LINE__ ); \
            XBASE_COUT( ::XBase::RuntimeAssert::LabelCondition ); \
            XBASE_COUT_LINE( #aCond ); \
            XBASE_COUT( ::XBase::RuntimeAssert::LabelMessage ); \
            XBASE_COUTFMT_LINE( __VA_ARGS__ , #aCond ); \
            XBASE_COUT_LINE( ::XBase::RuntimeAssert::Separator ); \
            ::XBase::RuntimeError::OnError(); \
            while(1){} \
        } \
    }while(0)

#else
#define XBASE_RUNTIME_ASSERT( aCond , ... ) do{}while(false)
#endif
//@}

/// @addtogroup XBase-Debug
//@{
/// @name 実行時アサート
//@{

/// @brief メッセージ付きアサート。指定の条件式がtrueであることをチェックする。
/// @param aCond 条件式。
/// @param aMsg メッセージ文字列。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_MSG( aCond , aMsg ) XBASE_RUNTIME_ASSERT( aCond , "%s" , aMsg )

/// @brief printfフォーマットのメッセージ付きアサート。指定の条件式がtrueであることをチェックする。
/// @param aCond 条件式。
/// @param aFormat printfフォーマット文字列。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_MSGFMT( aCond , aFormat , ... ) XBASE_RUNTIME_ASSERT( aCond , aFormat , __VA_ARGS__ )

/// @brief 指定の条件式がtrueであることをチェックする。
/// @param aCond 条件式。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT( aCond ) XBASE_ASSERT_MSG( aCond , #aCond )

/// @brief NULLであるべき値をチェックする。
/// @param aVal チェックする値。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_SHOULD_NULL_ASSERT( aVal ) \
    XBASE_ASSERT_MSG( (aVal)==0 \
    , "Value is not Null (%s)\n" \
    , XBASE_TO_SHORT_STRING( aVal ).readPtr() \
    ) 

/// @brief NULLじゃない値をさしているかチェックする。
/// @param aVal チェックする値。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_NOT_NULL_ASSERT( aVal ) XBASE_ASSERT_MSG( (aVal)!=0 , "Value is Null\n" )

/// @briefポインタとして有効な値であることをチェックする。
/// @param aVal チェックする値。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_POINTER_ASSERT( aVal ) do { if ( !::XBase::PointerCheck::IsValid( aVal ) ) { XBASE_INVALID_VALUE_ERROR( reinterpret_cast< ::XBase::pword_t >( aVal ) ); } } while(false)

/// @brief 到達したらエラーにする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// 第1引数以降にprintfの書式でメッセージを指定してください。@n
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_NOT_REACH_ASSERT_MSGFMT( aFormat , ... ) XBASE_ASSERT_MSGFMT( false , aFormat , __VA_ARGS__ )
#define XBASE_NOT_REACH_ASSERT_MSG( aMsg ) XBASE_ASSERT_MSG( false , aMsg )

/// @brief 到達したらエラーにする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_NOT_REACH_ASSERT() XBASE_NOT_REACH_ASSERT_MSG( "Should nod reach here.\n" )
 
/// @brief 不正な値としてその値をコンソールにダンプしつつエラーにする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_INVALID_VALUE_ERROR( aVal ) \
    XBASE_NOT_REACH_ASSERT_MSGFMT( \
        "%s is invalid value(%s)\n" \
        , #aVal \
        , XBASE_TO_SHORT_STRING(aVal).readPtr() \
        )

/// @brief XBASE_INVALID_VALUE_ERROR のenum版。
/// @see XBASE_INVALID_VALUE_ERROR
#define XBASE_INVALID_ENUM_ERROR( aVal ) XBASE_INVALID_VALUE_ERROR( int( aVal ) )

/// @brief ２つの値が等しいことをチェックする。
/// @param aVal1 チェックする値。
/// @param aVal2 チェックする値。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_EQUALS_ASSERT( aVal1 , aVal2 ) \
    XBASE_ASSERT_MSGFMT( aVal1 == aVal2 \
    , "%s(%s) is not equals %s(%s).\n" \
    , #aVal1 , XBASE_TO_SHORT_STRING( aVal1 ).readPtr() \
    , #aVal2 , XBASE_TO_SHORT_STRING( aVal2 ).readPtr() \
    )

/// @brief ２つの値が等しくないことをチェックする。
/// @param aVal1 チェックする値。
/// @param aVal2 チェックする値。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_NOT_EQUALS_ASSERT( aVal1 , aVal2 ) \
    XBASE_ASSERT_MSGFMT( aVal1 != aVal2 \
    , "%s(%s) is quals %s(%s).\n" \
    , #aVal1 , XBASE_TO_SHORT_STRING( aVal1 ).readPtr() \
    , #aVal2 , XBASE_TO_SHORT_STRING( aVal2 ).readPtr() \
    )

/// @def XBASE_TEST
/// @brief テストコマンドを実行する。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#if defined(XBASE_CONFIG_ENABLE_RUNTIME_ERROR)
    #define XBASE_TEST( aCond ) (aCond)
#else
    #define XBASE_TEST( aCond ) do{}while(false)
#endif

/// @brief aVal <= aMaxValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @copydetails XBASE_ASSERT_MSG
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_RANGE_ASSERT_EMAX( aVal , aMaxVal ) XBASE_RANGE_ASSERT_CORE_FVM( XBASE_IS_VALUE_IN_RANGE_EMAX , aVal , aMaxVal )

/// @brief aVal <= aMaxValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_RANGE_ASSERT_EMIN( aMinVal , aVal ) XBASE_RANGE_ASSERT_CORE_FMV( XBASE_IS_VALUE_IN_RANGE_EMIN , aMinVal , aVal )

/// @brief aMinVal <= aVal <= aMaxValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_RANGE_ASSERT_EMIN_EMAX( aMinVal , aVal , aMaxVal ) XBASE_RANGE_ASSERT_CORE_FMVM( XBASE_IS_VALUE_IN_RANGE_EMIN_EMAX , aMinVal , aVal , aMaxVal )

/// @brief aMinVal <= aVal < aMaxValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_RANGE_ASSERT_EMIN_MAX( aMinVal , aVal , aMaxVal ) XBASE_RANGE_ASSERT_CORE_FMVM( XBASE_IS_VALUE_IN_RANGE_EMIN_MAX , aMinVal , aVal , aMaxVal )

/// @brief aVal < aMaxValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_RANGE_ASSERT_MAX( aVal , aMaxVal ) XBASE_RANGE_ASSERT_CORE_FVM( XBASE_IS_VALUE_IN_RANGE_MAX , aVal , aMaxVal )


/// @brief aMinVal < aVal であることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_RANGE_ASSERT_MIN( aMinVal , aVal ) XBASE_RANGE_ASSERT_CORE_FMV( XBASE_IS_VALUE_IN_RANGE_MIN , aMinVal , aVal )

/// @brief aMinVal < aVal <= aMaxValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_RANGE_ASSERT_MIN_EMAX( aMinVal , aVal , aMaxVal ) XBASE_RANGE_ASSERT_CORE_FMVM( XBASE_IS_VALUE_IN_RANGE_MIN_EMAX , aMinVal , aVal , aMaxVal )
 
/// @brief aEnumValueがMIN <= aEnumValue <= MAXであることをチェックする。
/// @details
/// 調査するEnumにMINとMAXが定義されている必要があります。
#define XBASE_ENUM_ASSERT( aEnumType , aEnumValue ) XBASE_RANGE_ASSERT_EMIN_EMAX( int( aEnumType##_MIN ) , int( aEnumValue ) , int( aEnumType##_MAX ) )

//@}
//@}
    
// 範囲チェックアサートの実装。
#define XBASE_RANGE_ASSERT_CORE_FVM( func , aVal , aMaxVal ) \
    XBASE_ASSERT_MSGFMT( func( aVal , aMaxVal ) \
    , "Value is not in range.\n" \
      "aVal : %s \naMaxVal : %s\n" \
    , XBASE_TO_SHORT_STRING( aVal ).readPtr() \
    , XBASE_TO_SHORT_STRING( aMaxVal ).readPtr() \
    )
#define XBASE_RANGE_ASSERT_CORE_FMV( func , aMinVal , aVal ) \
    XBASE_ASSERT_MSGFMT( func( aMinVal , aVal ) \
    , "Value is not in range.\n" \
      "aMinVal : %s \naVal : %s\n" \
    , XBASE_TO_SHORT_STRING( aMinVal ).readPtr() \
    , XBASE_TO_SHORT_STRING( aVal ).readPtr() \
    )
#define XBASE_RANGE_ASSERT_CORE_FMVM( func , aMinVal , aVal , aMaxVal ) \
    XBASE_ASSERT_MSGFMT( func( aMinVal , aVal , aMaxVal )  \
    , "Value is not in range.\n" \
    "aMinVal : %s \naVal : %s \naMaxVal : %s\n" \
    , XBASE_TO_SHORT_STRING( aVal ).readPtr() \
    , XBASE_TO_SHORT_STRING( aMaxVal ).readPtr() \
    , XBASE_TO_SHORT_STRING( aMinVal ).readPtr() \
    )

#endif
// EOF
