// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESMATSET_HPP)
#else
#define AE_G3D_INCLUDED_BINRESMATSET_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：マテリアルセット。
struct BinResMatSet
{
    ::ae::xdata::UInt16    index;
    ::ae::xdata::UInt16    flags;
    ::ae::xdata::Reference name;
    ::ae::xdata::Reference mats;
};

}} // namespace
#endif
// EOF
