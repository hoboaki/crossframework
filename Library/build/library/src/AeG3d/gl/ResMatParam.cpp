// 文字コード：UTF-8
#include <ae/g3d/ResMatParam.hpp>

#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/ResConstant.hpp>
#include "ResMatParamImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMatParam::ResMatParam()
{
}

//------------------------------------------------------------------------------
ResMatParam::ResMatParam(const ResMatParamImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResMatParam::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMatParam::equals(const ResMatParam& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMatParam::operator==(const ResMatParam& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
int ResMatParam::index()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MAT_PARAM_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
const char* ResMatParam::name()const
{
    // チェック
    if (checkInvalid()) {
        return "";
    }
    return mPtr->xdata.ref< ::ae::xdata::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
bool ResMatParam::checkInvalid()const
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
