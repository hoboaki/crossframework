// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLSHAPEINPUTTYPE_HPP)
#else
#define XG3D_INCLUDED_RESMDLSHAPEINPUTTYPE_HPP

#include <XData/XData.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

// シェイプ入力データのデータ型。
struct ResMdlShapeInputType
{
    enum EnumType
    {
        Float,
        Int8,
        Int16,
        Int32,
        UInt8,
        UInt16,
        UInt32,
        
        TERM,
    };
};

} // namespace
#endif
// EOF
