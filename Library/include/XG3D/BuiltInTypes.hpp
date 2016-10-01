// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_BUILTINTYPES_HPP)
#else
#define XG3D_INCLUDED_BUILTINTYPES_HPP

//------------------------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D
{
/// @addtogroup XG3D-Types
//@{
    //=================================================
    /// @name 符号無し整数型
    //@{
    using ::XBase::u8;     ///< 8bit符号無し整数型。
    using ::XBase::uint8;  ///< 8bit符号無し整数型。
    using ::XBase::u16;    ///< 16bit符号無し整数型。
    using ::XBase::uint16; ///< 16bit符号無し整数型。
    using ::XBase::u32;    ///< 32bit符号無し整数型。
    using ::XBase::uint;   ///< 32bit符号無し整数型。
    using ::XBase::uint32; ///< 32bit符号無し整数型。
    using ::XBase::u64;    ///< 64bit符号無し整数型。
    using ::XBase::uint64; ///< 64bit符号無し整数型。
    //@}

    //=================================================
    /// @name 符号有り整数型
    //@{
    using ::XBase::int8;   ///< 8bit符号有り整数型。
    using ::XBase::s8;     ///< 8bit符号有り整数型。
    using ::XBase::sint8;  ///< 8bit符号有り整数型。
    using ::XBase::int16;  ///< 16bit符号有り整数型。
    using ::XBase::s16;    ///< 16bit符号有り整数型。
    using ::XBase::sint16; ///< 16bit符号有り整数型。
    using ::XBase::int32;  ///< 32bit符号有り整数型。
    using ::XBase::s32;    ///< 32bit符号有り整数型。
    using ::XBase::sint;   ///< 32bit符号有り整数型。
    using ::XBase::sint32; ///< 32bit符号有り整数型。
    using ::XBase::int64;  ///< 64bit符号有り整数型。
    using ::XBase::s64;    ///< 64bit符号有り整数型。
    using ::XBase::sint64; ///< 64bit符号有り整数型。
    //@}

    //=================================================
    /// @name 浮動小数型
    //@{
    using ::XBase::f32;     ///< 32bit浮動小数型。
    using ::XBase::float32; ///< 32bit浮動小数型。
    using ::XBase::single;  ///< 32bit浮動小数型。
    using ::XBase::f64;     ///< 64bit浮動小数型。
    using ::XBase::float64; ///< 64bit浮動小数型。
    //@}

    //============================================================
    /// @name データ型
    //@{
    using ::XBase::byte_t;  ///< 1バイトデータ型。
    using ::XBase::word_t;  ///< 2バイトデータ型。
    using ::XBase::dword_t; ///< 4バイトデータ型。
    using ::XBase::qword_t; ///< 8バイトデータ型。    
    using ::XBase::pword_t; ///< アドレスサイズを表すデータ型。
    //@}
    
    //============================================================
    /// @name アドレス型 
    //@{
    using ::XBase::ptr_t;          ///< ポインタ型。void** -> void*に変換できてしまう事故を防ぐため基本はこちらを使用。
    using ::XBase::const_ptr_t;    ///< ptr_tのconst版。
    using ::XBase::anyptr_t;       ///< 何でもいけるポインタ型。
    using ::XBase::const_anyptr_t; ///< any_ptr_tのconst版。
    //@}    
//@}

} // namespace
#endif
// EOF
