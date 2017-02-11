// 文字コード：UTF-8
#include <ae/g3d/ResMdlNode.hpp>

#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/ResConstant.hpp>
#include "ResMdlNodeImpl.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

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
    return mPtr->xdata.ref< ::ae::xdata::String >(mPtr->binPtr->name)->toCStr();
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
::ae::base::Mtx34 ResMdlNode::rtMtx()const
{
    // チェック
    if (checkInvalid()) {
        return ::ae::base::Mtx34::Identity();
    }
    return mPtr->binPtr->rtMtx;;
}

//------------------------------------------------------------------------------
::ae::base::Vec3 ResMdlNode::scale()const
{
    // チェック
    if (checkInvalid()) {
        return ::ae::base::Vec3::One();
    }
    return mPtr->binPtr->scale;
}

//------------------------------------------------------------------------------
const ::ae::base::Mtx34* ResMdlNode::bindPoseMtxPtr()const
{
    // チェック
    if (checkInvalid()) {
        return 0;
    }
    return mPtr->xdata.safeRef< ::ae::base::Mtx34 >(mPtr->binPtr->bindPoseMtxRef);
}

//------------------------------------------------------------------------------
bool ResMdlNode::checkInvalid()const
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
