// 文字コード：UTF-8
#if defined(XDATA_INCLUDED_PODTYPES_HPP)
#else
#define XDATA_INCLUDED_PODTYPES_HPP

#include <XBase/BuiltInTypes.hpp>
#include <XBase/ScalerClass.hpp>

//------------------------------------------------------------------------------
namespace XBase

{
/// @addtogroup XBase-Types
//@{
    //=================================================
    /// @name struct化された符号無し型
    //@{
typedef PODStruct< u8 >   U8POD;     ///< 8bit符号有り整数型。
typedef PODStruct< u8 >   UInt8POD;  ///< 8bit符号有り整数型。
typedef PODStruct< u16 >  U16POD;    ///< 16bit符号有り整数型。
typedef PODStruct< u16 >  UInt16POD; ///< 16bit符号有り整数型。
typedef PODStruct< u32 >  U32POD;    ///< 32bit符号有り整数型。
typedef PODStruct< u32 >  UIntPOD;   ///< 32bit符号有り整数型。
typedef PODStruct< u32 >  UInt32POD; ///< 32bit符号有り整数型。
typedef PODStruct< u64 >  U64POD;    ///< 64bit符号有り整数型。
typedef PODStruct< u64 >  UInt64POD; ///< 64bit符号有り整数型。
//@}

//=================================================
/// @name struct化された符号有り型
//@{
typedef PODStruct< s8 >   Int8POD;   ///< 8bit符号有り整数型。
typedef PODStruct< s8 >   S8POD;     ///< 8bit符号有り整数型。
typedef PODStruct< s8 >   SInt8POD;  ///< 8bit符号有り整数型。
typedef PODStruct< s16 >  Int16POD;  ///< 16bit符号有り整数型。
typedef PODStruct< s16 >  S16POD;    ///< 16bit符号有り整数型。
typedef PODStruct< s16 >  SInt16POD; ///< 16bit符号有り整数型。
typedef PODStruct< s32 >  Int32POD;  ///< 32bit符号有り整数型。
typedef PODStruct< s32 >  S32POD;    ///< 32bit符号有り整数型。
typedef PODStruct< s32 >  SIntPOD;   ///< 32bit符号有り整数型。
typedef PODStruct< s32 >  SInt32POD; ///< 32bit符号有り整数型。
typedef PODStruct< s64 >  Int64POD;  ///< 64bit符号有り整数型。
typedef PODStruct< s64 >  S64POD;    ///< 64bit符号有り整数型。
typedef PODStruct< s64 >  SInt64POD; ///< 64bit符号有り整数型。
//@}

//=================================================
/// @name struct化された浮動小数型
//@{
typedef PODStruct< f32 > F32POD;     ///< 32bit浮動小数型。
typedef PODStruct< f32 > Float32POD; ///< 32bit浮動小数型。
typedef PODStruct< f32 > SinglePOD;  ///< 32bit浮動小数型。
typedef PODStruct< f64 > F64POD;     ///< 64bit浮動小数型。
typedef PODStruct< f64 > Float64POD; ///< 64bit浮動小数型。
//@}

//============================================================
/// @name struct化されたデータ型
//@{
typedef PODStruct<  byte_t > BytePOD;  ///< 1バイトデータ型。
typedef PODStruct<  word_t > WordPOD;  ///< 2バイトデータ型。
typedef PODStruct< dword_t > DWordPOD; ///< 4バイトデータ型。
typedef PODStruct< qword_t > QWordPOD; ///< 8バイトデータ型。
typedef PODStruct< pword_t > PWordPOD; ///< アドレスサイズを表すデータ型。
typedef PODStruct<  size_t>  SizePOD;  ///< アドレスサイズを表すデータ型。
//@}

//============================================================
/// @name struct化されたアドレス型
//@{
typedef PODStruct< ptr_t >          PtrPOD;         ///< ポインタ型。void** -> void*に変換できてしまう事故を防ぐため基本はこちらを使用。
typedef PODStruct< const_ptr_t >    ConstPtrPOD;    ///< ptr_tのconst版。
typedef PODStruct< anyptr_t >       AnyPtrPOD;      ///< 何でもいけるポインタ型。
typedef PODStruct< const_anyptr_t > ConstAnyPtrPOD; ///< any_ptr_tのconst版。
//@}

//@}

} // namespace
#endif
// EOF
