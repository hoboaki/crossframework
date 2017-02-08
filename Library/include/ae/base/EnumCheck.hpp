// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_ENUMCHECK_HPP)
#else
#define XBASE_INCLUDED_ENUMCHECK_HPP

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Debug
//@{

/// @brief Enumの値が 0以上 TERM　未満であることをチェックするマクロ。
/// @return bool値。範囲内ならtrue。
/// @details
/// 調査するEnumにTERMが定義されている必要があります。
#define XBASE_ENUM_IS_VALID( aEnumType , aEnumValue ) ( 0 <= int( aEnumValue ) && int( aEnumValue ) <= aEnumType::TERM )

/// @brief Enumの値が 0以上 TERM　未満であることをチェックするマクロ。
/// @return bool値。範囲外ならtrue。
/// @details
/// 調査するEnumにTERMが定義されている必要があります。
#define XBASE_ENUM_IS_INVALID( aEnumType , aEnumValue ) ( XBASE_ENUM_IS_VALID( aEnumType , aEnumValue ) == false )
//@}

} // namespace
#endif
// EOF
