/**
 * @file
 * @brief BinResMat型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_BINRESMAT_HPP)
#else
#define XG3D_INCLUDED_BINRESMAT_HPP

//------------------------------------------------------------
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XG3D {
    // バイナリデータ：マテリアル。
    struct BinResMat
    {    
        ::XData::UInt16    index;
        ::XData::UInt16    flags;
        ::XData::Reference name;
        ::XData::Reference params;     // パラメータ
        ::XData::Reference vtxAttrs;   // 頂点属性
        ::XData::Reference vshSrcText; // 頂点シェーダーソースコード
        ::XData::Reference pshSrcText; // ピクセルシェーダーソースコード
    };
}
//------------------------------------------------------------
#endif
// EOF
