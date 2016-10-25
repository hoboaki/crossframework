// 文字コード：UTF-8
#include <XG3D/StateMdlTransform.hpp>

#include <XG3D/MdlLocalMtx.hpp>
#include <XG3D/ResConstant.hpp>
#include <XG3D/ResMdl.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
StateMdlTransform::StateMdlTransform(
    const ResMdl& aResMdl,
    ::XBase::IAllocator& aAllocator
    )
: mResMdl(aResMdl)
, mLocalMtxs(aResMdl.nodeCount(), aAllocator)
, mWorldMtxs(aResMdl.nodeCount(), aAllocator)
, mBoneMtxs(aResMdl.nodeCount(), aAllocator)
{
    resetLocalMtx();

    for (int i = 0; i < mBoneMtxs.count(); ++i) {
        mBoneMtxs[i] = ::XBase::Mtx34::Identity();
    }
}

//------------------------------------------------------------------------------
StateMdlTransform::~StateMdlTransform()
{
}

//------------------------------------------------------------------------------
void StateMdlTransform::updateWorldMtx(const ::XBase::Mtx34& aMdlMtx)
{
    for (int i = 0; i < mLocalMtxs.count(); ++i) {
        ResMdlNode node = mResMdl.node(i);
        MdlLocalMtx& localMtx = mLocalMtxs[i];

        // 自身の行列を作成
        ::XBase::Mtx34 mtx;
        mtx.setX(localMtx.rtMtx.x() * localMtx.scale.x);
        mtx.setY(localMtx.rtMtx.y() * localMtx.scale.y);
        mtx.setZ(localMtx.rtMtx.z() * localMtx.scale.z);
        mtx.setW(localMtx.rtMtx.w());

        // ワールド行列
        if (node.parentNodeIndex() == ResConstant::INVALID_MDL_NODE_INDEX) {
            // ルートノード
            mWorldMtxs[i] = aMdlMtx * mtx;
        }
        else
        {// ぶらさがっているノード
            mWorldMtxs[i] = mWorldMtxs[node.parentNodeIndex()] * mtx;
        }

        // ボーン用行列
        const ::XBase::Mtx34* invBindPoseMtx = node.bindPoseMtxPtr();
        if (invBindPoseMtx != NULL) {
            mBoneMtxs[i] = (mWorldMtxs[i] * (*invBindPoseMtx));
        }
    }
}

//------------------------------------------------------------------------------
const ::XBase::Mtx34 StateMdlTransform::worldMtx(const int aNodeIndex)const
{
    return mWorldMtxs[aNodeIndex];
}

//------------------------------------------------------------------------------
const ::XBase::Mtx34* StateMdlTransform::boneMtxArray()const
{
    return &mBoneMtxs[0];
}

//------------------------------------------------------------------------------
void StateMdlTransform::resetLocalMtx()
{
    for (int i = 0; i < mLocalMtxs.count(); ++i) {
        ResMdlNode node = mResMdl.node(i);
        MdlLocalMtx& localMtx = mLocalMtxs[i];
        localMtx.rtMtx = node.rtMtx();
        localMtx.scale = node.scale();
    }
}

} // namespace
// EOF
