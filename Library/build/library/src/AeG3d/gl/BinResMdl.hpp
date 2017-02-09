// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESMDL_HPP)
#else
#define AE_G3D_INCLUDED_BINRESMDL_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：モデル。
struct BinResMdl
{
    ::ae::xdata::UInt16    index;
    ::ae::xdata::UInt16    flags;
    ::ae::xdata::Reference name;
    ::ae::xdata::Reference matRefers;
    ::ae::xdata::Reference meshes;
    ::ae::xdata::Reference nodes;
    ::ae::xdata::Reference shapes;
};

}} // namespace
#endif
// EOF
