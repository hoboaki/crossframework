// 文字コード：UTF-8
#include <XG3D/StateMdlTransform.hpp>

//------------------------------------------------------------------------------
#include <XG3D/MdlLocalMtx.hpp>
#include <XG3D/ResConstant.hpp>
#include <XG3D/ResMdl.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------------------------
StateMdlTransform::StateMdlTransform(
    const ResMdl& aResMdl 
    , ::XBase::IAllocator& aAllocator
    )
: mResMdl( aResMdl )
, mLocalMtxs( aResMdl.nodeCount() , aAllocator )
, mWorldMtxs( aResMdl.nodeCount() , aAllocator )
{
    resetLocalMtx();
}

//------------------------------------------------------------------------------
StateMdlTransform::~StateMdlTransform()
{
}

//------------------------------------------------------------------------------
void StateMdlTransform::updateWorldMtx( const ::XBase::Mtx34& aMdlMtx )
{
    for ( uint i = 0; i < mLocalMtxs.count(); ++i )
    {
        ResMdlNode node = mResMdl.node(i);
        MdlLocalMtx& localMtx = mLocalMtxs[i];
        
        // 自身の行列を作成
        ::XBase::Mtx34 mtx;
        mtx.setX( localMtx.rtMtx.x() * localMtx.scale.x );
        mtx.setY( localMtx.rtMtx.y() * localMtx.scale.y );
        mtx.setZ( localMtx.rtMtx.z() * localMtx.scale.z );
        mtx.setW( localMtx.rtMtx.w() );

        if ( node.parentNodeIndex() == ResConstant::INVALID_MDL_NODE_INDEX )
        {// ルートノード
            mWorldMtxs[i] = aMdlMtx * mtx;
        }
        else
        {// ぶらさがっているノード
            mWorldMtxs[i] = mWorldMtxs[ node.parentNodeIndex() ] * mtx;
        }
    }
}

//------------------------------------------------------------------------------
const ::XBase::Mtx34 StateMdlTransform::worldMtx( const uint aNodeIndex )const
{
    return mWorldMtxs[ aNodeIndex ];
}

//------------------------------------------------------------------------------
void StateMdlTransform::resetLocalMtx()
{
    for ( uint i = 0; i < mLocalMtxs.count(); ++i )
    {
        ResMdlNode node = mResMdl.node(i);
        MdlLocalMtx& localMtx = mLocalMtxs[i];
        localMtx.rtMtx = node.rtMtx();
        localMtx.scale = node.scale();
    }
}

} // namespace
// EOF
