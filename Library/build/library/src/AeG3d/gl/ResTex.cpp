// 文字コード：UTF-8
#include <ae/g3d/ResTex.hpp>

#include <ae/base/EnumCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/ResConstant.hpp>
#include <ae/g3d/TexResData.hpp>
#include "ResTexImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

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
    return mPtr->xdata.ref< ::ae::xdata::String >(mPtr->binPtr->name)->toCStr();
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
ResTexFormat::EnumType ResTex::format()const
{
    // チェック
    if (checkInvalid()) {
        return ResTexFormat::EnumType(0);
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
    AE_BASE_ASSERT_NOT_REACHED();
    return true;
}

}} // namespace
// EOF
