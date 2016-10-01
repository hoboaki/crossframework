/**
 * @file
 * @brief BinResMatParam型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_BINRESMATPARAM_HPP)
#else
#define XG3D_INCLUDED_BINRESMATPARAM_HPP

//------------------------------------------------------------
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XG3D {
    // バイナリデータ：マテリアルパラメータ。
    struct BinResMatParam
    {   
        ::XData::UInt16    index;
        ::XData::UInt16    flags;
        ::XData::Reference name;
        ::XData::Reference symbolName; // Stringではなくcharの配列の先頭アドレスなので注意
        ::XData::UInt32    type;
        ::XData::Reference valueRef;
    };
}
//------------------------------------------------------------
#endif
// EOF
