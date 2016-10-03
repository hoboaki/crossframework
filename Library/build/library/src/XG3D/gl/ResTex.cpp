// 文字コード：UTF-8
#include <XG3D/ResTex.hpp>

//------------------------------------------------------------------------------
#include <XBase/EnumCheck.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/ResConstant.hpp>
#include <XG3D/TexResData.hpp>
#include "ResTexImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResTex::ResTex()
{
}

//------------------------------------------------------------------------------
ResTex::ResTex(const ResTexImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResTex::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResTex::equals(const ResTex& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResTex::operator==(const ResTex& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
int ResTex::index()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_TEX_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
const char* ResTex::name()const
{
    // チェック
    if (checkInvalid()) {
        return "";
    }
    return mPtr->xdata.ref< ::XData::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
u16 ResTex::width()const
{
    // チェック
    if (checkInvalid()) {
        return u16();
    }
    return mPtr->binPtr->width;
}

//------------------------------------------------------------------------------
u16 ResTex::height()const
{
    // チェック
    if (checkInvalid()) {
        return u16();
    }
    return mPtr->binPtr->height;
}

//------------------------------------------------------------------------------
ResTexFormat ResTex::format()const
{
    // チェック
    if (checkInvalid()) {
        return ResTexFormat_MIN;
    }
    return mPtr->format();
}

//------------------------------------------------------------------------------
const byte_t* ResTex::pixels()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->pixels();
}

//------------------------------------------------------------------------------
const TexBuffer* ResTex::texBufferPtr()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->texBufferPtr;
}

//------------------------------------------------------------------------------
bool ResTex::checkInvalid()const
{
    // 正しければ何もしない
    if (isValid()) {
        return false;
    }

    // 不正なのでエラー
    XBASE_ASSERT_NOT_REACHED();
    return true;
}

} // namespace
// EOF
