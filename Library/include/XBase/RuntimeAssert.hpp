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
#define XBASE_ASSERT_SHOULD_NULL( aVal ) \
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
#define XBASE_ASSERT_NOT_NULL( aVal ) XBASE_ASSERT_MSG( (aVal)!=0 , "Value is Null\n" )

/// @briefポインタとして有効な値であることをチェックする。
/// @param aVal チェックする値。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_POINTER( aVal ) do { if ( !::XBase::PointerCheck::IsValid( aVal ) ) { XBASE_ERROR_INVALID_VALUE( reinterpret_cast< ::XBase::pword_t >( aVal ) ); } } while(false)

/// @brief 到達したらエラーにする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// 第1引数以降にprintfの書式でメッセージを指定してください。@n
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_NOT_REACHED_MSGFMT( aFormat , ... ) XBASE_ASSERT_MSGFMT( false , aFormat , __VA_ARGS__ )
#define XBASE_ASSERT_NOT_REACHED_MSG( aMsg ) XBASE_ASSERT_MSG( false , aMsg )

/// @brief 到達したらエラーにする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_NOT_REACHED() XBASE_ASSERT_NOT_REACHED_MSG( "Should nod reach here.\n" )
 
/// @brief 不正な値としてその値をコンソールにダンプしつつエラーにする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ERROR_INVALID_VALUE( aVal ) \
    XBASE_ASSERT_NOT_REACHED_MSGFMT( \
        "%s is invalid value(%s)\n" \
        , #aVal \
        , XBASE_TO_SHORT_STRING(aVal).readPtr() \
        )

/// @brief XBASE_ERROR_INVALID_VALUE のenum版。
/// @see XBASE_ERROR_INVALID_VALUE
#define XBASE_ERROR_INVALID_ENUM( aVal ) XBASE_ERROR_INVALID_VALUE( int( aVal ) )

/// @brief ２つの値が等しいことをチェックする。
/// @param aVal1 チェックする値。
/// @param aVal2 チェックする値。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_EQUALS( aVal1 , aVal2 ) \
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
#define XBASE_ASSERT_NOT_EQUALS( aVal1 , aVal2 ) \
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

/// @brief aVal < aTermValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_LESS(aVal, aTermVal) XBASE_ASSERT_RANGE_CORE2(XBASE_VALUE_IN_RANGE_LESS, aVal, aTermVal)

/// @brief aVal <= aMaxValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @copydetails XBASE_ASSERT_MSG
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_LESS_EQUALS(aVal, aMaxVal) XBASE_ASSERT_RANGE_CORE2(XBASE_VALUE_IN_RANGE_LESS_EQUALS, aVal, aMaxVal)

/// @brief aMinVal <= aVal <= aMaxValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_MIN_MAX(aMinVal, aVal, aMaxVal) XBASE_ASSERT_RANGE_CORE3(XBASE_VALUE_IN_RANGE_MIN_MAX, aMinVal ,aVal ,aMaxVal)

/// @brief aMinVal <= aVal < aTermValであることをチェックする。
/// @see XBase::RuntimeError
/// @see XBASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define XBASE_ASSERT_MIN_TERM(aMinVal, aVal, aTermVal) XBASE_ASSERT_RANGE_CORE3(XBASE_VALUE_IN_RANGE_MIN_TERM, aMinVal, aVal, aTermVal)

/// @brief aEnumValueがMIN <= aEnumValue <= MAXであることをチェックする。
/// @details
/// 調査するEnumにMINとMAXが定義されている必要があります。
#define XBASE_ASSERT_ENUM(aEnumType , aEnumValue) XBASE_ASSERT_MIN_MAX(int(aEnumType##_MIN), int(aEnumValue), int(aEnumType##_MAX))

//@}
//@}
    
// 範囲チェックアサートの実装。
#define XBASE_ASSERT_RANGE_CORE2(func, aVal1, aVal2) \
    XBASE_ASSERT_MSGFMT(func(aVal1 , aVal2) \
    , "Value is not in range.\n" \
      "aVal1 : %s \naVal2 : %s\n" \
    , XBASE_TO_SHORT_STRING(aVal1).readPtr() \
    , XBASE_TO_SHORT_STRING(aVal2).readPtr() \
    )
#define XBASE_ASSERT_RANGE_CORE3(func, aVal1, aVal2, aVal3) \
    XBASE_ASSERT_MSGFMT(func(aVal1, aVal2, aVal3)  \
    , "Value is not in range.\n" \
    "aVal1 : %s \naVal2 : %s \naVal3 : %s\n" \
    , XBASE_TO_SHORT_STRING(aVal1).readPtr() \
    , XBASE_TO_SHORT_STRING(aVal2).readPtr() \
    , XBASE_TO_SHORT_STRING(aVal3).readPtr() \
    )

#endif
// EOF
