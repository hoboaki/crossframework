// 文字コード：UTF-8
#include <ae/g3d/ResMdlMatRefer.hpp>

#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/ResConstant.hpp>
#include "ResMdlMatReferImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMdlMatRefer::ResMdlMatRefer()
{
}

//------------------------------------------------------------------------------
ResMdlMatRefer::ResMdlMatRefer(const ResMdlMatReferImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResMdlMatRefer::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMdlMatRefer::equals(const ResMdlMatRefer& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMdlMatRefer::operator==(const ResMdlMatRefer& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
int ResMdlMatRefer::index()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_MAT_REFER_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
const char* ResMdlMatRefer::name()const
{
    // チェック
    if (checkInvalid()) {
        return "";
    }
    return mPtr->xdata.ref< ::ae::xdata::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
bool ResMdlMatRefer::checkInvalid()const
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
