/**
 * @file
 * @brief Enumの値をチェックするマクロを記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_ENUMCHECK_HPP)
#else
#define XBASE_INCLUDED_ENUMCHECK_HPP

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Debug
//@{

/**
 * @brief Enumの値がMIN以上MAX以下であることをチェックするマクロ。
 * @return bool値。範囲内ならtrue。
 * @details
 * 調査するEnumにMINとMAXが定義されている必要があります。
 */
#define XBASE_ENUM_IS_VALID( aEnumType , aEnumValue ) ( aEnumType##_MIN <= int( aEnumValue ) && int( aEnumValue ) <= aEnumType##_MAX )
    
/**
 * @brief Enumの値がMIN未満 or MAXより大きいことをチェックするマクロ。
 * @return bool値。範囲外ならtrue。
 * @details
 * 調査するEnumにMINとMAXが定義されている必要があります。
 */
#define XBASE_ENUM_IS_INVALID( aEnumType , aEnumValue ) ( XBASE_ENUM_IS_VALID( aEnumType , aEnumValue ) == false )
//@}
}
//------------------------------------------------------------
#endif
// EOF
