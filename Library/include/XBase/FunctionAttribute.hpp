/**
 * @file
 * @brief 関数属性のマクロを記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_FUNCTIONATTRIBUTE_HPP)
#else
#define XBASE_INCLUDED_FUNCTIONATTRIBUTE_HPP

//------------------------------------------------------------
#include <XBase/Compiler.hpp>

//-----------------------------------------------------------
/// @addtogroup XBase-Debug
//@{
/// @name 関数属性
//@{

/**
 * @def XBASE_OVERRIDE
 * @brief オーバーライドチェック。
 * @details 指定の関数がオーバーライドしていなければコンパイルエラーにします。
 * @code
 // [例]
 // 継承元。
 class Base
 {
 public:
     virtual void func();
 };
 // 派生クラス。
 class Inherit : public Base
 {
 public:
     XBASE_OVERRIDE( void func() ); // オーバーライドしているのでOK。
     XBASE_OVERRIDE( void foo() );  // オーバーライドしていないのでエラー。
 };
 * @endcode
 */
#if defined(XBASE_COMPILER_MSVC)
    #define XBASE_OVERRIDE( ... ) virtual __VA_ARGS__ override
#else
    #define XBASE_OVERRIDE( ... ) __VA_ARGS__
#endif

/**
 * @def XBASE_FINAL
 * @brief オーバーライド禁止チェック。
 * @details 指定の関数が派生クラスでオーバーライドしていればコンパイルエラーにします。
 * @code
 // [例]
 // 継承元。
 class Base
 {
 public:
     XBASE_FINAL( void func() );
 };
 // 派生クラス。
 class Inherit : public Base
 {
 public:
     virtual void func(); // オーバーライドしようとしたのでエラー。
 };
 * @endcode
 */
#if defined(XBASE_COMPILER_MSVC)
    #define XBASE_FINAL( ... ) virtual __VA_ARGS__ sealed
#else
    #define XBASE_FINAL( ... ) __VA_ARGS__
#endif

//@}
//@}
//-----------------------------------------------------------
#endif
// EOF
