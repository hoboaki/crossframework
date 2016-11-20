// 文字コード：UTF-8
#include <XG3D/StateMdlTransform.hpp>

#include <XG3D/MdlLocalMtx.hpp>
#include <XG3D/ResConstant.hpp>
#include <XG3D/ResMdl.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
namespace {
    const int fBonePosMtxVecCount = 3;
    const int fBoneNrmMtxVecCount = 3;
}

//------------------------------------------------------------------------------
StateMdlTransform::StateMdlTransform(
    const ResMdl& aResMdl,
    ::XBase::IAllocator& aAllocator
    )
: mResMdl(aResMdl)
, mLocalMtxs(aResMdl.nodeCount(), aAllocator)
, mWorldMtxs(aResMdl.nodeCount(), aAllocator)
, mBonePosMtxs(aResMdl.nodeCount() * fBonePosMtxVecCount, aAllocator)
, mBoneNrmMtxs(aResMdl.nodeCount() * fBoneNrmMtxVecCount, aAllocator)
{
    resetLocalMtx();

    for (int i = 0; i < mBonePosMtxs.count(); ++i) {
        mBonePosMtxs[i] = ::XBase::Vec4::Zero();
    }
    for (int i = 0; i < mBoneNrmMtxs.count(); ++i) {
        mBoneNrmMtxs[i] = ::XBase::Vec4::Zero();
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
            const int baseIndexPos = i * fBonePosMtxVecCount;
            const ::XBase::Mtx34 boneMtx = mWorldMtxs[i] * (*invBindPoseMtx);
            mBonePosMtxs[baseIndexPos] = ::XBase::Vector4(
                boneMtx.v[::XBase::Mtx34::Index00], 
                boneMtx.v[::XBase::Mtx34::Index01], 
                boneMtx.v[::XBase::Mtx34::Index02], 
                boneMtx.v[::XBase::Mtx34::Index03]
                );
            mBonePosMtxs[baseIndexPos + 1] = ::XBase::Vector4(
                boneMtx.v[::XBase::Mtx34::Index10],
                boneMtx.v[::XBase::Mtx34::Index11],
                boneMtx.v[::XBase::Mtx34::Index12],
                boneMtx.v[::XBase::Mtx34::Index13]
                );
            mBonePosMtxs[baseIndexPos + 2] = ::XBase::Vector4(
                boneMtx.v[::XBase::Mtx34::Index20],
                boneMtx.v[::XBase::Mtx34::Index21],
                boneMtx.v[::XBase::Mtx34::Index22],
                boneMtx.v[::XBase::Mtx34::Index23]
                );

            const int baseIndexNrm = i * fBoneNrmMtxVecCount;
            const ::XBase::Mtx34 boneMtxIt = boneMtx.invert().transpose();
            mBoneNrmMtxs[baseIndexNrm] = ::XBase::Vector4(
                boneMtxIt.v[::XBase::Mtx34::Index00],
                boneMtxIt.v[::XBase::Mtx34::Index01],
                boneMtxIt.v[::XBase::Mtx34::Index02],
                0.0f
            );
            mBoneNrmMtxs[baseIndexNrm + 1] = ::XBase::Vector4(
                boneMtxIt.v[::XBase::Mtx34::Index10],
                boneMtxIt.v[::XBase::Mtx34::Index11],
                boneMtxIt.v[::XBase::Mtx34::Index12],
                0.0f
            );
            mBoneNrmMtxs[baseIndexNrm + 2] = ::XBase::Vector4(
                boneMtxIt.v[::XBase::Mtx34::Index20],
                boneMtxIt.v[::XBase::Mtx34::Index21],
                boneMtxIt.v[::XBase::Mtx34::Index22],
                0.0f
            );
        }
    }
}

//------------------------------------------------------------------------------
const ::XBase::Mtx34 StateMdlTransform::worldMtx(const int aNodeIndex)const
{
    return mWorldMtxs[aNodeIndex];
}

//------------------------------------------------------------------------------
const ::XBase::Vec4* StateMdlTransform::bonePosMtxData()const
{
    return &mBonePosMtxs[0];
}

//------------------------------------------------------------------------------
const ::XBase::Vec4* StateMdlTransform::boneNrmMtxData()const
{
    return &mBoneNrmMtxs[0];
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
