// 文字コード：UTF-8
#include <XG3D/ResMdlSubMesh.hpp>

//------------------------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/ResConstant.hpp>
#include "ResMdlSubMeshImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResMdlSubMesh::ResMdlSubMesh()
{
}

//------------------------------------------------------------------------------
ResMdlSubMesh::ResMdlSubMesh(const ResMdlSubMeshImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResMdlSubMesh::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMdlSubMesh::equals(const ResMdlSubMesh& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMdlSubMesh::operator==(const ResMdlSubMesh& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
int ResMdlSubMesh::index()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_SUB_MESH_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
int ResMdlSubMesh::nodeIndex()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_NODE_INDEX;
    }
    return mPtr->binPtr->nodeIdx;
}

//------------------------------------------------------------------------------
int ResMdlSubMesh::matReferIndex()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_MAT_REFER_INDEX;
    }
    return mPtr->binPtr->matReferIdx;
}

//------------------------------------------------------------------------------
ResMdlShape ResMdlSubMesh::shape()const
{
    // チェック
    if (checkInvalid()) {
        return ResMdlShape();
    }
    return mPtr->resMdlShape;
}

//------------------------------------------------------------------------------
bool ResMdlSubMesh::checkInvalid()const
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
