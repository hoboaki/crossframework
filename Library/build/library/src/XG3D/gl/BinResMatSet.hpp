/**
 * @file
 * @brief BinResMatSet型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_BINRESMATSET_HPP)
#else
#define XG3D_INCLUDED_BINRESMATSET_HPP

//------------------------------------------------------------
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XG3D {
    // バイナリデータ：マテリアルセット。
    struct BinResMatSet
    {
        ::XData::UInt16    index;
        ::XData::UInt16    flags;
        ::XData::Reference name;
        ::XData::Reference mats;
    };
}
//------------------------------------------------------------
#endif
// EOF
