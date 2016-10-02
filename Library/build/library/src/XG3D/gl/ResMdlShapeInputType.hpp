// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLSHAPEINPUTTYPE_HPP)
#else
#define XG3D_INCLUDED_RESMDLSHAPEINPUTTYPE_HPP

#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

    // シェイプ入力データのデータ型。
enum ResMdlShapeInputType
{
    ResMdlShapeInputType_Float,
    ResMdlShapeInputType_Int8,
    ResMdlShapeInputType_Int16,
    ResMdlShapeInputType_Int32,
    ResMdlShapeInputType_UInt8,
    ResMdlShapeInputType_UInt16,
    ResMdlShapeInputType_UInt32,
    // term        
    ResMdlShapeInputType_TERMINATE,
    ResMdlShapeInputType_MIN = 0,
    ResMdlShapeInputType_MAX = ResMdlShapeInputType_TERMINATE - 1
};

} // namespace
#endif
// EOF
