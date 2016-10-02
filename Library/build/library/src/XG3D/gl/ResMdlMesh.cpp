// 文字コード：UTF-8
#include <XG3D/ResMdlMesh.hpp>

//------------------------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/ResConstant.hpp>
#include "ResMdlMeshImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

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
uint ResMdlMesh::index()const
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
    return mPtr->xdata.ref< ::XData::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
uint ResMdlMesh::subMeshCount()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->subMeshImpls->count();
}

//------------------------------------------------------------------------------
ResMdlSubMesh ResMdlMesh::subMesh(const uint aIndex)const
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
    XBASE_NOT_REACH_ASSERT();
    return true;
}

} // namespace
// EOF
