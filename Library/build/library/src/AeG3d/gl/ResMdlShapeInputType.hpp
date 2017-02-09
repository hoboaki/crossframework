// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLSHAPEINPUTTYPE_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLSHAPEINPUTTYPE_HPP

#include <ae/xdata/Xdata.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

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

}} // namespace
#endif
// EOF
