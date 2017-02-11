// 文字コード：UTF-8
#include <ae/g3d/StateMdlTransform.hpp>

#include <ae/g3d/MdlLocalMtx.hpp>
#include <ae/g3d/ResConstant.hpp>
#include <ae/g3d/ResMdl.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
namespace {
    const int fBonePosMtxVecCount = 3;
    const int fBoneNrmMtxVecCount = 3;
}

//------------------------------------------------------------------------------
StateMdlTransform::StateMdlTransform(
    const ResMdl& aResMdl,
    ::ae::base::IAllocator& aAllocator
    )
: mResMdl(aResMdl)
, mLocalMtxs(aResMdl.nodeCount(), aAllocator)
, mWorldMtxs(aResMdl.nodeCount(), aAllocator)
, mBonePosMtxs(aResMdl.nodeCount() * fBonePosMtxVecCount, aAllocator)
, mBoneNrmMtxs(aResMdl.nodeCount() * fBoneNrmMtxVecCount, aAllocator)
{
    resetLocalMtx();

    for (int i = 0; i < mBonePosMtxs.count(); ++i) {
        mBonePosMtxs[i] = ::ae::base::Vec4::Zero();
    }
    for (int i = 0; i < mBoneNrmMtxs.count(); ++i) {
        mBoneNrmMtxs[i] = ::ae::base::Vec4::Zero();
    }
}

//------------------------------------------------------------------------------
StateMdlTransform::~StateMdlTransform()
{
}

//------------------------------------------------------------------------------
void StateMdlTransform::updateWorldMtx(const ::ae::base::Mtx34& aMdlMtx)
{
    for (int i = 0; i < mLocalMtxs.count(); ++i) {
        ResMdlNode node = mResMdl.node(i);
        MdlLocalMtx& localMtx = mLocalMtxs[i];

        // 自身の行列を作成
        ::ae::base::Mtx34 mtx;
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
        const ::ae::base::Mtx34* invBindPoseMtx = node.bindPoseMtxPtr();
        if (invBindPoseMtx != NULL) {
            const int baseIndexPos = i * fBonePosMtxVecCount;
            const ::ae::base::Mtx34 boneMtx = mWorldMtxs[i] * (*invBindPoseMtx);
            mBonePosMtxs[baseIndexPos] = ::ae::base::Vector4(
                boneMtx.v[::ae::base::Mtx34::Index00], 
                boneMtx.v[::ae::base::Mtx34::Index01], 
                boneMtx.v[::ae::base::Mtx34::Index02], 
                boneMtx.v[::ae::base::Mtx34::Index03]
                );
            mBonePosMtxs[baseIndexPos + 1] = ::ae::base::Vector4(
                boneMtx.v[::ae::base::Mtx34::Index10],
                boneMtx.v[::ae::base::Mtx34::Index11],
                boneMtx.v[::ae::base::Mtx34::Index12],
                boneMtx.v[::ae::base::Mtx34::Index13]
                );
            mBonePosMtxs[baseIndexPos + 2] = ::ae::base::Vector4(
                boneMtx.v[::ae::base::Mtx34::Index20],
                boneMtx.v[::ae::base::Mtx34::Index21],
                boneMtx.v[::ae::base::Mtx34::Index22],
                boneMtx.v[::ae::base::Mtx34::Index23]
                );

            const int baseIndexNrm = i * fBoneNrmMtxVecCount;
            const ::ae::base::Mtx34 boneMtxIt = boneMtx.invert().transpose();
            mBoneNrmMtxs[baseIndexNrm] = ::ae::base::Vector4(
                boneMtxIt.v[::ae::base::Mtx34::Index00],
                boneMtxIt.v[::ae::base::Mtx34::Index01],
                boneMtxIt.v[::ae::base::Mtx34::Index02],
                0.0f
            );
            mBoneNrmMtxs[baseIndexNrm + 1] = ::ae::base::Vector4(
                boneMtxIt.v[::ae::base::Mtx34::Index10],
                boneMtxIt.v[::ae::base::Mtx34::Index11],
                boneMtxIt.v[::ae::base::Mtx34::Index12],
                0.0f
            );
            mBoneNrmMtxs[baseIndexNrm + 2] = ::ae::base::Vector4(
                boneMtxIt.v[::ae::base::Mtx34::Index20],
                boneMtxIt.v[::ae::base::Mtx34::Index21],
                boneMtxIt.v[::ae::base::Mtx34::Index22],
                0.0f
            );
        }
    }
}

//------------------------------------------------------------------------------
const ::ae::base::Mtx34 StateMdlTransform::worldMtx(const int aNodeIndex)const
{
    return mWorldMtxs[aNodeIndex];
}

//------------------------------------------------------------------------------
const ::ae::base::Vec4* StateMdlTransform::bonePosMtxData()const
{
    return &mBonePosMtxs[0];
}

//------------------------------------------------------------------------------
const ::ae::base::Vec4* StateMdlTransform::boneNrmMtxData()const
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

}} // namespace
// EOF
