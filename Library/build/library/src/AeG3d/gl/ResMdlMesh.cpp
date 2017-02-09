// 文字コード：UTF-8
#include <ae/g3d/ResMdlMesh.hpp>

#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/ResConstant.hpp>
#include "ResMdlMeshImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResMdlMesh::ResMdlMesh()
{
}

//------------------------------------------------------------------------------
ResMdlMesh::ResMdlMesh(const ResMdlMeshImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResMdlMesh::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMdlMesh::equals(const ResMdlMesh& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMdlMesh::operator==(const ResMdlMesh& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
int ResMdlMesh::index()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_MESH_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
const char* ResMdlMesh::name()const
{
    // チェック
    if (checkInvalid()) {
        return "";
    }
    return mPtr->xdata.ref< ::ae::xdata::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
int ResMdlMesh::subMeshCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->subMeshImpls->count();
}

//------------------------------------------------------------------------------
ResMdlSubMesh ResMdlMesh::subMesh(const int aIndex)const
{
    // チェック
    if (checkInvalid()) {
        return ResMdlSubMesh();
    }
    return ResMdlSubMesh(mPtr->subMeshImpls->at(aIndex));
}

//------------------------------------------------------------------------------
bool ResMdlMesh::checkInvalid()const
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
