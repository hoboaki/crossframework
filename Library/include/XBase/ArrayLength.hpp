/**
 * @file
 * @brief 配列の長さに関するマクロを記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_ARRAYLENGTH_HPP)
#else
#define XBASE_INCLUDED_ARRAYLENGTH_HPP

//------------------------------------------------------------
#include <XBase/StaticAssert.hpp>

//------------------------------------------------------------
/// @addtogroup XBase-Util
//@{
/// @name 配列長
//@{

/**
 * @brief 配列の長さを取得するマクロ。
 * @return 配列長。
 */
#define XBASE_ARRAY_LENGTH( obj ) ( sizeof(obj)/sizeof(obj[0]) )

/// 指定の配列の長さが指定の長さかチェックする。
#define XBASE_ARRAY_LENGTH_CHECK( arr , len ) XBASE_STATIC_ASSERT( XBASE_ARRAY_LENGTH( arr ) == len )

//@}
//@}
//------------------------------------------------------------
#endif
// EOF
