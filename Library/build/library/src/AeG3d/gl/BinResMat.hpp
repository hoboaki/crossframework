// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESMAT_HPP)
#else
#define AE_G3D_INCLUDED_BINRESMAT_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// バイナリデータ：マテリアル。
struct BinResMat
{
    ::ae::xdata::UInt16    index;
    ::ae::xdata::UInt16    flags;
    ::ae::xdata::Reference name;
    ::ae::xdata::Reference params;     // パラメータ
    ::ae::xdata::Reference vtxAttrs;   // 頂点属性
    ::ae::xdata::Reference vshSrcText; // 頂点シェーダーソースコード
    ::ae::xdata::Reference pshSrcText; // ピクセルシェーダーソースコード
};

}} // namespace
#endif
// EOF
