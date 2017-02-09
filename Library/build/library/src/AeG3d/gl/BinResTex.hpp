// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESTEX_HPP)
#else
#define AE_G3D_INCLUDED_BINRESTEX_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：テクスチャ。
struct BinResTex
{
    ::ae::xdata::UInt16    index;
    ::ae::xdata::UInt16    flags;
    ::ae::xdata::Reference name;
    ::ae::xdata::UInt16 width;
    ::ae::xdata::UInt16 height;
    ::ae::xdata::UInt8 format;
    ::ae::xdata::UInt8 padding[3];
    ::ae::xdata::Reference pixels;
};

}} // namespace
#endif
// EOF
