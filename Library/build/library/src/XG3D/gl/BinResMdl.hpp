/**
 * @file
 * @brief BinResMdl型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_BINRESMDL_HPP)
#else
#define XG3D_INCLUDED_BINRESMDL_HPP

//------------------------------------------------------------
#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XG3D {
    // バイナリデータ：モデル。
    struct BinResMdl
    {
        ::XData::UInt16    index;
        ::XData::UInt16    flags;
        ::XData::Reference name;
        ::XData::Reference matRefers;
        ::XData::Reference meshes;
        ::XData::Reference nodes;
        ::XData::Reference shapes;
    };
}
//------------------------------------------------------------
#endif
// EOF
