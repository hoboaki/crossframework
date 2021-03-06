// 文字コード：UTF-8
#include <ae/g3d/ResMdl.hpp>

#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/ResConstant.hpp>
#include "ResMdlImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMdl::ResMdl()
{
}

//------------------------------------------------------------------------------
ResMdl::ResMdl(const ResMdlImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResMdl::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMdl::equals(const ResMdl& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMdl::operator==(const ResMdl& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
int ResMdl::index()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
const char* ResMdl::name()const
{
    // チェック
    if (checkInvalid()) {
        return "";
    }
    return mPtr->xdata.ref< ::ae::xdata::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
int ResMdl::matReferCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->matReferImpls->count();
}

//------------------------------------------------------------------------------
ResMdlMatRefer ResMdl::matRefer(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdlMatRefer();
    }
    return ResMdlMatRefer(mPtr->matReferImpls->at(aIndex));
}

//------------------------------------------------------------------------------
int ResMdl::meshCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->meshImpls->count();
}

//------------------------------------------------------------------------------
ResMdlMesh ResMdl::mesh(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdlMesh();
    }
    return ResMdlMesh(mPtr->meshImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResMdlMesh ResMdl::mesh(const char* aName)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdlMesh();
    }

    // 検索
    for (int i = 0; i < mPtr->meshImpls->count(); ++i) {
        ResMdlMeshImpl& impl = mPtr->meshImpls->at(i);
        if (::ae::base::StringTraits< char >::Equals(ResMdlMesh(impl).name(), aName)) {
            return ResMdlMesh(impl);
        }
    }
    return ResMdlMesh();
}

//------------------------------------------------------------------------------
int ResMdl::nodeCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->nodeImpls->count();
}

//------------------------------------------------------------------------------
ResMdlNode ResMdl::node(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdlNode();
    }
    return ResMdlNode(mPtr->nodeImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResMdlNode ResMdl::node(const char* aName)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdlNode();
    }

    // 検索
    for (int i = 0; i < mPtr->nodeImpls->count(); ++i) {
        ResMdlNodeImpl& impl = mPtr->nodeImpls->at(i);
        if (::ae::base::StringTraits< char >::Equals(ResMdlNode(impl).name(), aName)) {
            return ResMdlNode(impl);
        }
    }
    return ResMdlNode();
}

//------------------------------------------------------------------------------
int ResMdl::shapeCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->shapeImpls->count();
}

//------------------------------------------------------------------------------
ResMdlShape ResMdl::shape(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdlShape();
    }
    return ResMdlShape(mPtr->shapeImpls->at(aIndex));
}

//------------------------------------------------------------------------------
ResMdlShape ResMdl::shape(const char* aName)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdlShape();
    }

    // 検索
    for (int i = 0; i < mPtr->shapeImpls->count(); ++i) {
        ResMdlShapeImpl& impl = mPtr->shapeImpls->at(i);
        if (::ae::base::StringTraits< char >::Equals(ResMdlShape(impl).name(), aName)) {
            return ResMdlShape(impl);
        }
    }
    return ResMdlShape();
}

//------------------------------------------------------------------------------
bool ResMdl::checkInvalid()const
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
