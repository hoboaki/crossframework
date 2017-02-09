// 文字コード：UTF-8
#include <ae/g3d/ResMat.hpp>

#include <ae/base/EnumCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/StringTraits.hpp>
#include <ae/g3d/ResConstant.hpp>
#include "ResMatImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMat::ResMat()
{
}

//------------------------------------------------------------------------------
ResMat::ResMat(const ResMatImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResMat::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMat::equals(const ResMat& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMat::operator==(const ResMat& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
int ResMat::index()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MAT_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
const char* ResMat::name()const
{
    // チェック
    if (checkInvalid()) {
        return "";
    }
    return mPtr->xdata.ref< ::ae::xdata::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
int ResMat::paramCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->paramImpls->count();
}

//------------------------------------------------------------------------------
ResMatParam ResMat::param(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResMatParam();
    }
    return ResMatParam(mPtr->paramImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResMatParam ResMat::param(const char* aName)const
{
    // チェック
    if (checkInvalid()) {
        return ResMatParam();
    }

    // 検索
    for (int i = 0; i < mPtr->paramImpls->count(); ++i) {
        ResMatParamImpl& impl = mPtr->paramImpls->at(i);
        if (::ae::base::StringTraits< char >::Equals(ResMatParam(impl).name(), aName)) {
            return ResMatParam(impl);
        }
    }
    return ResMatParam();
}

//------------------------------------------------------------------------------
const ResMatImpl* ResMat::impl_()const
{
    return mPtr.get();
}

//------------------------------------------------------------------------------
bool ResMat::checkInvalid()const
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
