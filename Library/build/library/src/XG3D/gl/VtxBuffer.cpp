/**
 * @file
 * @brief VtxBuffer.hppの実装を記述する。
 * @author akino
 */
#include <XG3D/VtxBuffer.hpp>

//------------------------------------------------------------
#include <XBase/EnumCheck.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/Renderer.hpp>
#include "GLCMD.hpp"
#include "ShaderConstant.hpp"

//------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------
VtxBuffer::VtxBuffer(
    const uint aMeshCountMax 
    , const uint aVertexCountMax 
    , ::XBase::IAllocator& aAllocator
    )
: mVertexArray( aVertexCountMax , aAllocator )
, mIndexArray( ( aVertexCountMax * 3 ) / 2 , aAllocator ) // 矩形描画をカバーできるようにindex数を1.5倍に。
, mMeshArray( aMeshCountMax , aAllocator )
, mEXT()
, mWorldMtx()
, mNormal()
, mTexCoord()
, mColor()
, mIsMeshActive( false )
, mIsFlushed( false )
{
    reset();
}

//------------------------------------------------------------
VtxBuffer::~VtxBuffer()
{
}

//------------------------------------------------------------
void VtxBuffer::reset()
{
    // チェック
    if ( mIsMeshActive )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }

    clear();
    mWorldMtx  = ::XBase::Matrix34::Identity();
    mNormal    = ::XBase::Vector3::Zero();
    mTexCoord  = ::XBase::Vector2::Zero();
    mColor     = ::XBase::Color4::One();
}

//------------------------------------------------------------
void VtxBuffer::clear()
{
    // チェック
    if ( mIsMeshActive )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }

    mVertexArray.clear();
    mIndexArray.clear();
    mMeshArray.clear();
    mIsFlushed    = false;
}

//------------------------------------------------------------
void VtxBuffer::worldMtx( const ::XBase::Matrix34POD& aMtx )
{
    mWorldMtx = aMtx;
}

//------------------------------------------------------------
void VtxBuffer::begin( const PrimitiveKind aKind )
{
    // チェック
    if ( mIsFlushed )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    if ( mMeshArray.isFull() )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    if ( XBASE_ENUM_IS_INVALID( PrimitiveKind , aKind ) )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }

    // メッシュ追加
    Mesh mesh = {};
    mesh.worldMtx = mWorldMtx;
    mesh.beginIndex   = mVertexArray.count();
    mesh.count  = 0;
    mesh.kind = aKind;
    mMeshArray.add( mesh );

    // フラグオン
    mIsMeshActive = true;
}

//------------------------------------------------------------
void VtxBuffer::end()
{
    // チェック
    if ( !mIsMeshActive )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }

    // メッシュの種類ごとの処理
    Mesh& mesh = mMeshArray.last();
    XBASE_ENUM_ASSERT( PrimitiveKind , mesh.kind );
    switch ( mesh.kind )
    {
    case PrimitiveKind_Triangles:
        {// 連続三角形
            // チェック
            const uint vertexCountPerPrimitive = 3;
            if ( ( mesh.count % vertexCountPerPrimitive ) != 0 )
            {
                XBASE_INVALID_VALUE_ERROR( mesh.count );
                return;
            }
            // index生成
            const uint elemBeginIndex = mIndexArray.count();
            for ( uint i = 0; i < mesh.count; ++i )
            {
                mIndexArray.add( Index( mesh.beginIndex + i ) );
            }
            // 情報修正
            mesh.beginIndex = elemBeginIndex;
        }
        break;

    case PrimitiveKind_Quads:
        {// 連続矩形
            // チェック
            const uint vertexCountPerPrimitive = 4;
            if ( ( mesh.count % vertexCountPerPrimitive ) != 0 )
            {
                XBASE_INVALID_VALUE_ERROR( mesh.count );
                return;
            }
            // index生成
            const uint elemBeginIndex = mIndexArray.count();
            const uint vtxBeginIndex = mesh.beginIndex;
            const uint primitiveCount = mesh.count / vertexCountPerPrimitive;
            for ( uint i = 0; i < primitiveCount; ++i )
            {
                const uint vtxBaseIndex = vtxBeginIndex + i * vertexCountPerPrimitive;
                
                // trianglesに変換
                const Index lt = Index( vtxBaseIndex );
                const Index rt = Index( vtxBaseIndex + 1 );
                const Index rb = Index( vtxBaseIndex + 2 );
                const Index lb = Index( vtxBaseIndex + 3 );
                mIndexArray.add( lt );
                mIndexArray.add( rt );
                mIndexArray.add( rb );                
                mIndexArray.add( rb );
                mIndexArray.add( lb );
                mIndexArray.add( lt );
            }
            // 情報修正
            mesh.beginIndex = elemBeginIndex;
            mesh.count = 6 * primitiveCount; // trianglesでの個数。
        }
        break;

    default:
        XBASE_INVALID_VALUE_ERROR( int( mesh.kind ) );
        return;
    }

    // フラグオフ
    mIsMeshActive = false;
}

//------------------------------------------------------------
void VtxBuffer::normal( const f32 aX , const f32 aY , const f32 aZ )
{
    normal( ::XBase::Vector3( aX , aY , aZ ) );
}

//------------------------------------------------------------
void VtxBuffer::normal( const ::XBase::Vector3POD& aXYZ )
{
    // チェック
    if ( !mIsMeshActive )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    mNormal = aXYZ;
}

//------------------------------------------------------------
void VtxBuffer::texCoord( const f32 aS , const f32 aT )
{
    texCoord( ::XBase::Vector2( aS , aT ) );
}

//------------------------------------------------------------
void VtxBuffer::texCoord( const ::XBase::Vector2POD& aST )
{
    // チェック
    if ( !mIsMeshActive )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    mTexCoord = aST;
}

//------------------------------------------------------------
void VtxBuffer::color( const f32 aR , const f32 aG , const f32 aB )
{
    color( aR , aG , aB , 1.0f );
}

//------------------------------------------------------------
void VtxBuffer::color( const f32 aR , const f32 aG , const f32 aB , const f32 aA )
{
    color( ::XBase::Color4( aR , aG , aB , aA ) );
}

//------------------------------------------------------------
void VtxBuffer::color( const ::XBase::Color4POD& aRGBA )
{
    // チェック
    if ( !mIsMeshActive )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    mColor = aRGBA;
}

//------------------------------------------------------------
void VtxBuffer::vertex( const f32 aX , const f32 aY )
{
    vertex( aX , aY , 0 );
}

//------------------------------------------------------------
void VtxBuffer::vertex( const f32 aX , const f32 aY , const f32 aZ )
{
    vertex( ::XBase::Vector3( aX , aY , aZ ) );
}

//------------------------------------------------------------
void VtxBuffer::vertex( const ::XBase::Vector2POD& aXY )
{
    vertex( aXY.toXY0() );
}

//------------------------------------------------------------
void VtxBuffer::vertex( const ::XBase::Vector3POD& aXYZ )
{
    // チェック
    if ( !mIsMeshActive )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    if ( mVertexArray.isFull() )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }

    // 頂点追加
    Vertex vtx = {};
    vtx.position = aXYZ;
    vtx.normal   = mNormal;
    vtx.texCoord = mTexCoord;
    vtx.color    = mColor;
    mVertexArray.add( vtx );
    ++mMeshArray.last().count;
}

//------------------------------------------------------------
void VtxBuffer::flush()
{
    // チェック
    if ( mIsFlushed )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }

    // フラグオン
    mIsFlushed = true;

    // 描画するものがなければバッファは作成しない
    if ( mMeshArray.isEmpty() 
        || mVertexArray.isEmpty()
        )
    {
        return;
    }
    
    // バッファ作成
    {
        XG3D_GLCMD( glBindBuffer( GL_ARRAY_BUFFER , mEXT.vtxBuffer ) );
        XG3D_GLCMD( glBufferData( GL_ARRAY_BUFFER , sizeof( Vertex ) * mVertexArray.count() , &mVertexArray[0] , GL_STATIC_DRAW ) );
        XG3D_GLCMD( glBindBuffer( GL_ARRAY_BUFFER , 0 ));
    }
    {
        XG3D_GLCMD( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , mEXT.idxBuffer ) );
        XG3D_GLCMD( glBufferData( GL_ELEMENT_ARRAY_BUFFER , sizeof( Index ) * mIndexArray.count() , &mIndexArray[0] , GL_STATIC_DRAW ) );
        XG3D_GLCMD( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ) );
    }
}

//------------------------------------------------------------
void VtxBuffer::draw()
{
    // チェック
    if ( !mIsFlushed )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }

    // メッシュがなければ何もしない
    if ( mMeshArray.isEmpty() )
    {
        return;
    }

    // 頂点がなければ何もしない
    if ( mVertexArray.isEmpty() )
    {
        return;
    }
    
    // 頂点の設定
    XG3D_GLCMD( glBindBuffer( GL_ARRAY_BUFFER , mEXT.vtxBuffer ) );
    XG3D_GLCMD( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , mEXT.idxBuffer ) );
    XG3D_GLCMD( glVertexAttribPointer( ShaderConstant::Attribute_Position , 3 , GL_FLOAT , GL_FALSE , sizeof( Vertex ) , reinterpret_cast< const void* >( offsetof( Vertex , position ) ) ) );
    XG3D_GLCMD( glVertexAttribPointer( ShaderConstant::Attribute_Normal   , 3 , GL_FLOAT , GL_TRUE  , sizeof( Vertex ) , reinterpret_cast< const void* >( offsetof( Vertex , normal ) ) ) );
    XG3D_GLCMD( glVertexAttribPointer( ShaderConstant::Attribute_TexCoord , 2 , GL_FLOAT , GL_FALSE , sizeof( Vertex ) , reinterpret_cast< const void* >( offsetof( Vertex , texCoord ) ) ) );
    XG3D_GLCMD( glVertexAttribPointer( ShaderConstant::Attribute_Color    , 4 , GL_FLOAT , GL_TRUE  , sizeof( Vertex ) , reinterpret_cast< const void* >( offsetof( Vertex , color ) ) ) );
    XG3D_GLCMD( glEnableVertexAttribArray( ShaderConstant::Attribute_Position ) );
    XG3D_GLCMD( glEnableVertexAttribArray( ShaderConstant::Attribute_Normal ) );
    XG3D_GLCMD( glEnableVertexAttribArray( ShaderConstant::Attribute_TexCoord ) );
    XG3D_GLCMD( glEnableVertexAttribArray( ShaderConstant::Attribute_Color ) );
    
    // 各メッシュの描画
    for ( uint i = 0; i < mMeshArray.count(); ++i )
    {
        // 取得
        const Mesh& mesh = mMeshArray[i];

        // 行列設定
        Renderer::Instance().sdSetMtxWorld( mesh.worldMtx );

        // 描画
        XG3D_GLCMD( glDrawElements( GL_TRIANGLES , mesh.count , GL_UNSIGNED_SHORT , reinterpret_cast< const void* >( sizeof( Index ) * mesh.beginIndex  ) ) );
    }

    // 後始末
    XG3D_GLCMD( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ) );
    XG3D_GLCMD( glBindBuffer( GL_ARRAY_BUFFER , 0 ) );
}

//------------------------------------------------------------
VtxBuffer_EXT::VtxBuffer_EXT()
: vtxBuffer()
, idxBuffer()
{
    XG3D_GLCMD( glGenBuffers( 1 , &vtxBuffer ) );
    XG3D_GLCMD( glGenBuffers( 1 , &idxBuffer ) );
}

//------------------------------------------------------------
VtxBuffer_EXT::~VtxBuffer_EXT()
{
    XG3D_GLCMD( glDeleteBuffers( 1 , &idxBuffer ) );
    idxBuffer = 0;

    XG3D_GLCMD( glDeleteBuffers( 1 , &vtxBuffer ));
    vtxBuffer = 0;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
