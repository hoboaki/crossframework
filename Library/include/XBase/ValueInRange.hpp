/**
 * @file
 * @brief 値が範囲内か調べるマクロを記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_VALUEINRANGE_HPP)
#else
#define XBASE_INCLUDED_VALUEINRANGE_HPP

//------------------------------------------------------------
/// @addtogroup XBase-Util
//@{
/// @name 値範囲チェック
//@{

/**
 * @brief aMin < aVal < aMaxな値か調べる。
 * @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
 */
#define XBASE_IS_VALUE_IN_RANGE_MIN_MAX( aMinVal , aVal , aMaxVal ) ( aMinVal < aVal && aVal < aMaxVal )

/**
 * @brief aMin <= aVal < aMaxな値か調べる。
 * @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
 */
#define XBASE_IS_VALUE_IN_RANGE_EMIN_MAX( aMinVal , aVal , aMaxVal ) ( aMinVal <= aVal && aVal < aMaxVal )

/**
 * @brief aMin <= aVal <= aMaxな値か調べる。
 * @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
 */
#define XBASE_IS_VALUE_IN_RANGE_EMIN_EMAX( aMinVal , aVal , aMaxVal ) ( aMinVal <= aVal && aVal <= aMaxVal )

/**
 * @brief aVal < aMaxな値か調べる。
 * @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
 */
#define XBASE_IS_VALUE_IN_RANGE_MAX( aVal , aMaxVal ) ( aVal < aMaxVal )

/**
 * @brief aVal <= aMaxな値か調べる。
 * @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
 */
#define XBASE_IS_VALUE_IN_RANGE_EMAX( aVal , aMaxVal ) ( aVal <= aMaxVal )

/**
 * @brief aMin < aValな値か調べる。
 * @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
 */
#define XBASE_IS_VALUE_IN_RANGE_MIN( aMinVal , aVal ) ( aMinVal < aVal )

/**
 * @brief aMin <= aValな値か調べる。
 * @return 条件に当てはまればtrueを返し、そうでなければfalseを返す。
 */
#define XBASE_IS_VALUE_IN_RANGE_EMIN( aMinVal , aVal ) ( aMinVal <= aVal )

//@}
//@}
//------------------------------------------------------------
#endif
// EOF
