// 文字コード：UTF-8
#include <XG3D/ResMdlShape.hpp>

//------------------------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/ResConstant.hpp>
#include "ResMdlShapeImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResMdlShape::ResMdlShape()
{
}

//------------------------------------------------------------------------------
ResMdlShape::ResMdlShape(const ResMdlShapeImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResMdlShape::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMdlShape::equals(const ResMdlShape& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMdlShape::operator==(const ResMdlShape& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
uint ResMdlShape::index()const
{
    // チェック
    if (checkInvalid())
    {
        return ResConstant::INVALID_MDL_SHAPE_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
const char* ResMdlShape::name()const
{
    // チェック
    if (checkInvalid())
    {
        return "";
    }
    return mPtr->xdata.ref< ::XData::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
bool ResMdlShape::isSkinning()const
{
    // チェック
    if (checkInvalid())
    {
        return false;
    }
    return mPtr->binPtr->skinningTableIdx != ResConstant::INVALID_MDL_SKINNING_TABLE_INDEX;
}

//------------------------------------------------------------------------------
const ResMdlShapeImpl* ResMdlShape::impl_()const
{
    return mPtr.get();
}

//------------------------------------------------------------------------------
bool ResMdlShape::checkInvalid()const
{
    // 正しければ何もしない
    if (isValid())
    {
        return false;
    }

    // 不正なのでエラー
    XBASE_NOT_REACH_ASSERT();
    return true;
}

} // namespace
// EOF
