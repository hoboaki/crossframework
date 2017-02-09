// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESMATPARAM_HPP)
#else
#define AE_G3D_INCLUDED_BINRESMATPARAM_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：マテリアルパラメータ。
struct BinResMatParam
{
    ::ae::xdata::UInt16    index;
    ::ae::xdata::UInt16    flags;
    ::ae::xdata::Reference name;
    ::ae::xdata::Reference symbolName; // Stringではなくcharの配列の先頭アドレスなので注意
    ::ae::xdata::UInt32    type;
    ::ae::xdata::Reference valueRef;
};

}} // namespace
#endif
// EOF
