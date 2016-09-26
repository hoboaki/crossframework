﻿/**
 * @file
 * @brief BinResMdlMatRefer型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_BINRESMDLMATREFER_HPP)
#else
#define XG3D_INCLUDED_BINRESMDLMATREFER_HPP

//------------------------------------------------------------
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XG3D {
    // バイナリデータ：モデルマテリアル参照。
    struct BinResMdlMatRefer
    {
        ::XData::UInt16    index;
        ::XData::UInt16    flags;
        ::XData::Reference name;
    };
}
//------------------------------------------------------------
#endif
// EOF
