// 文字コード：UTF-8
#include <XG3D/ResMatSet.hpp>

//------------------------------------------------------------------------------
#include <XBase/EnumCheck.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/StringTraits.hpp>
#include <XG3D/ResConstant.hpp>
#include "ResMatSetImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResMatSet::ResMatSet()
{
}

//------------------------------------------------------------------------------
ResMatSet::ResMatSet(const ResMatSetImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResMatSet::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMatSet::equals(const ResMatSet& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMatSet::operator==(const ResMatSet& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
int ResMatSet::index()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MAT_SET_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
const char* ResMatSet::name()const
{
    // チェック
    if (checkInvalid()) {
        return "";
    }
    return mPtr->xdata.ref< ::XData::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
int ResMatSet::matCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->matImpls->count();
}

//------------------------------------------------------------------------------
ResMat ResMatSet::mat(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResMat();
    }
    return ResMat(mPtr->matImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResMat ResMatSet::mat(const char* aName)const
{
    // チェック
    if (checkInvalid()) {
        return ResMat();
    }

    // 検索
    for (int i = 0; i < mPtr->matImpls->count(); ++i) {
        ResMatImpl& impl = mPtr->matImpls->at(i);
        if (::XBase::StringTraits< char >::Equals(ResMat(impl).name(), aName)) {
            return ResMat(impl);
        }
    }
    return ResMat();
}

//------------------------------------------------------------------------------
bool ResMatSet::checkInvalid()const
{
    // 正しければ何もしない
    if (isValid()) {
        return false;
    }

    // 不正なのでエラー
    XBASE_NOT_REACH_ASSERT();
    return true;
}

} // namespace
// EOF
