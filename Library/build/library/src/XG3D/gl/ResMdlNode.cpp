// 文字コード：UTF-8
#include <XG3D/ResMdlNode.hpp>

//------------------------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/ResConstant.hpp>
#include "ResMdlNodeImpl.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
ResMdlNode::ResMdlNode()
{
}

//------------------------------------------------------------------------------
ResMdlNode::ResMdlNode(const ResMdlNodeImpl& aImpl)
: mPtr(aImpl)
{
}

//------------------------------------------------------------------------------
bool ResMdlNode::isValid()const
{
    return mPtr.isValid();
}

//------------------------------------------------------------------------------
bool ResMdlNode::equals(const ResMdlNode& aRHS)const
{
    return mPtr == aRHS.mPtr;
}

//------------------------------------------------------------------------------
bool ResMdlNode::operator==(const ResMdlNode& aRHS)const
{
    return equals(aRHS);
}

//------------------------------------------------------------------------------
const char* ResMdlNode::name()const
{
    // チェック
    if (checkInvalid()) {
        return "";
    }
    return mPtr->xdata.ref< ::XData::String >(mPtr->binPtr->name)->toCStr();
}

//------------------------------------------------------------------------------
int ResMdlNode::index()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_NODE_INDEX;
    }
    return mPtr->binPtr->index;
}

//------------------------------------------------------------------------------
int ResMdlNode::parentNodeIndex()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_NODE_INDEX;
    }
    return mPtr->binPtr->parentNodeIdx;
}

//------------------------------------------------------------------------------
int ResMdlNode::firstChildNodeIndex()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_NODE_INDEX;
    }
    return mPtr->binPtr->firstChildNodeIdx;
}

//------------------------------------------------------------------------------
int ResMdlNode::nextSiblingNodeIndex()const
{
    // チェック
    if (checkInvalid()) {
        return ResConstant::INVALID_MDL_NODE_INDEX;
    }
    return mPtr->binPtr->nextSiblingNodeIdx;
}

//------------------------------------------------------------------------------
::XBase::Mtx34 ResMdlNode::rtMtx()const
{
    // チェック
    if (checkInvalid()) {
        return ::XBase::Mtx34::Identity();
    }
    return mPtr->binPtr->rtMtx;;
}

//------------------------------------------------------------------------------
::XBase::Vec3 ResMdlNode::scale()const
{
    // チェック
    if (checkInvalid()) {
        return ::XBase::Vec3::One();
    }
    return mPtr->binPtr->scale;
}

//------------------------------------------------------------------------------
const ::XBase::Mtx34* ResMdlNode::bindPoseMtxPtr()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->xdata.safeRef< ::XBase::Mtx34 >(mPtr->binPtr->bindPoseMtxRef);
}

//------------------------------------------------------------------------------
bool ResMdlNode::checkInvalid()const
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
