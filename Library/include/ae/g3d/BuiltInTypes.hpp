// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BUILTINTYPES_HPP)
#else
#define AE_G3D_INCLUDED_BUILTINTYPES_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Types
//@{
//=================================================
/// @name 符号無し整数型
//@{
using ::ae::base::u8;     ///< 8bit符号無し整数型。
using ::ae::base::uint8;  ///< 8bit符号無し整数型。
using ::ae::base::u16;    ///< 16bit符号無し整数型。
using ::ae::base::uint16; ///< 16bit符号無し整数型。
using ::ae::base::u32;    ///< 32bit符号無し整数型。
using ::ae::base::uint;   ///< 32bit符号無し整数型。
using ::ae::base::uint32; ///< 32bit符号無し整数型。
using ::ae::base::u64;    ///< 64bit符号無し整数型。
using ::ae::base::uint64; ///< 64bit符号無し整数型。
//@}

//=================================================
/// @name 符号有り整数型
//@{
using ::ae::base::int8;   ///< 8bit符号有り整数型。
using ::ae::base::s8;     ///< 8bit符号有り整数型。
using ::ae::base::sint8;  ///< 8bit符号有り整数型。
using ::ae::base::int16;  ///< 16bit符号有り整数型。
using ::ae::base::s16;    ///< 16bit符号有り整数型。
using ::ae::base::sint16; ///< 16bit符号有り整数型。
using ::ae::base::int32;  ///< 32bit符号有り整数型。
using ::ae::base::s32;    ///< 32bit符号有り整数型。
using ::ae::base::sint;   ///< 32bit符号有り整数型。
using ::ae::base::sint32; ///< 32bit符号有り整数型。
using ::ae::base::int64;  ///< 64bit符号有り整数型。
using ::ae::base::s64;    ///< 64bit符号有り整数型。
using ::ae::base::sint64; ///< 64bit符号有り整数型。
//@}

//=================================================
/// @name 浮動小数型
//@{
using ::ae::base::f32;     ///< 32bit浮動小数型。
using ::ae::base::float32; ///< 32bit浮動小数型。
using ::ae::base::single;  ///< 32bit浮動小数型。
using ::ae::base::f64;     ///< 64bit浮動小数型。
using ::ae::base::float64; ///< 64bit浮動小数型。
//@}

//============================================================
/// @name データ型
//@{
using ::ae::base::byte_t;  ///< 1バイトデータ型。
using ::ae::base::word_t;  ///< 2バイトデータ型。
using ::ae::base::dword_t; ///< 4バイトデータ型。
using ::ae::base::qword_t; ///< 8バイトデータ型。    
using ::ae::base::pword_t; ///< アドレスサイズを表すデータ型。
//@}

//============================================================
/// @name アドレス型 
//@{
using ::ae::base::ptr_t;          ///< ポインタ型。void** -> void*に変換できてしまう事故を防ぐため基本はこちらを使用。
using ::ae::base::const_ptr_t;    ///< ptr_tのconst版。
using ::ae::base::anyptr_t;       ///< 何でもいけるポインタ型。
using ::ae::base::const_anyptr_t; ///< any_ptr_tのconst版。
//@}    
//@}

}} // namespace
#endif
// EOF
