/**
 * @file
 * @brief BinResTex型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_BINRESTEX_HPP)
#else
#define XG3D_INCLUDED_BINRESTEX_HPP

//------------------------------------------------------------
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XG3D {
    // バイナリデータ：テクスチャ。
    struct BinResTex
    {
        ::XData::UInt16    index;
        ::XData::UInt16    flags;
        ::XData::Reference name;
        ::XData::UInt16 width;
        ::XData::UInt16 height;
        ::XData::UInt8 format;
        ::XData::UInt8 padding[3];
        ::XData::Reference pixels;
    };
}
//------------------------------------------------------------
#endif
// EOF
