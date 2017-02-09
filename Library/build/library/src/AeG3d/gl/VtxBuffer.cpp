// 文字コード：UTF-8
#include <ae/g3d/VtxBuffer.hpp>

#include <ae/base/EnumCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/Renderer.hpp>
#include "GlCmd.hpp"
#include "ShaderConstant.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
VtxBuffer::VtxBuffer(
    const int aMeshCountMax,
    const int aVertexCountMax,
    ::ae::base::IAllocator& aAllocator
    )
: mVertexArray(aVertexCountMax, aAllocator)
, mIndexArray((aVertexCountMax * 3) / 2, aAllocator) // 矩形描画をカバーできるようにindex数を1.5倍に。
, mMeshArray(aMeshCountMax, aAllocator)
, mExt()
, mWorldMtx()
, mNormal()
, mTexCoord()
, mColor()
, mIsMeshActive(false)
, mIsFlushed(false)
{
    reset();
}

//------------------------------------------------------------------------------
VtxBuffer::~VtxBuffer()
{
}

//------------------------------------------------------------------------------
void VtxBuffer::reset()
{
    // チェック
    if (mIsMeshActive) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }

    clear();
    mWorldMtx = ::ae::base::Matrix34::Identity();
    mNormal = ::ae::base::Vector3::Zero();
    mTexCoord = ::ae::base::Vector2::Zero();
    mColor = ::ae::base::Color4::One();
}

//------------------------------------------------------------------------------
void VtxBuffer::clear()
{
    // チェック
    if (mIsMeshActive) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }

    mVertexArray.clear();
    mIndexArray.clear();
    mMeshArray.clear();
    mIsFlushed = false;
}

//------------------------------------------------------------------------------
void VtxBuffer::worldMtx(const ::ae::base::Matrix34Pod& aMtx)
{
    mWorldMtx = aMtx;
}

//------------------------------------------------------------------------------
void VtxBuffer::begin(const PrimitiveKind::EnumType aKind)
{
    // チェック
    if (mIsFlushed) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    if (mMeshArray.isFull()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    if (AE_BASE_ENUM_IS_INVALID(PrimitiveKind, aKind)) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }

    // メッシュ追加
    Mesh mesh = {};
    mesh.worldMtx = mWorldMtx;
    mesh.beginIndex = mVertexArray.count();
    mesh.count = 0;
    mesh.kind = aKind;
    mMeshArray.add(mesh);

    // フラグオン
    mIsMeshActive = true;
}

//------------------------------------------------------------------------------
void VtxBuffer::end()
{
    // チェック
    if (!mIsMeshActive) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }

    // メッシュの種類ごとの処理
    Mesh& mesh = mMeshArray.last();
    AE_BASE_ASSERT_ENUM(PrimitiveKind, mesh.kind);
    switch (mesh.kind) {
        case PrimitiveKind::Triangles:
        {// 連続三角形
            // チェック
            const int vertexCountPerPrimitive = 3;
            if ((mesh.count % vertexCountPerPrimitive) != 0) {
                AE_BASE_ERROR_INVALID_VALUE(mesh.count);
                return;
            }
            // index生成
            const int elemBeginIndex = mIndexArray.count();
            for (int i = 0; i < mesh.count; ++i) {
                mIndexArray.add(Index(mesh.beginIndex + i));
            }
            // 情報修正
            mesh.beginIndex = elemBeginIndex;
        }
        break;

        case PrimitiveKind::Quads:
        {// 連続矩形
            // チェック
            const int vertexCountPerPrimitive = 4;
            if ((mesh.count % vertexCountPerPrimitive) != 0) {
                AE_BASE_ERROR_INVALID_VALUE(mesh.count);
                return;
            }
            // index生成
            const int elemBeginIndex = mIndexArray.count();
            const int vtxBeginIndex = mesh.beginIndex;
            const int primitiveCount = mesh.count / vertexCountPerPrimitive;
            for (int i = 0; i < primitiveCount; ++i) {
                const int vtxBaseIndex = vtxBeginIndex + i * vertexCountPerPrimitive;

                // trianglesに変換
                const Index lt = Index(vtxBaseIndex);
                const Index rt = Index(vtxBaseIndex + 1);
                const Index rb = Index(vtxBaseIndex + 2);
                const Index lb = Index(vtxBaseIndex + 3);
                mIndexArray.add(lt);
                mIndexArray.add(rt);
                mIndexArray.add(rb);
                mIndexArray.add(rb);
                mIndexArray.add(lb);
                mIndexArray.add(lt);
            }
            // 情報修正
            mesh.beginIndex = elemBeginIndex;
            mesh.count = 6 * primitiveCount; // trianglesでの個数。
        }
        break;

        default:
            AE_BASE_ERROR_INVALID_VALUE(int(mesh.kind));
            return;
    }

    // フラグオフ
    mIsMeshActive = false;
}

//------------------------------------------------------------------------------
void VtxBuffer::normal(const f32 aX, const f32 aY, const f32 aZ)
{
    normal(::ae::base::Vector3(aX, aY, aZ));
}

//------------------------------------------------------------------------------
void VtxBuffer::normal(const ::ae::base::Vector3Pod& aXYZ)
{
    // チェック
    if (!mIsMeshActive) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mNormal = aXYZ;
}

//------------------------------------------------------------------------------
void VtxBuffer::texCoord(const f32 aS, const f32 aT)
{
    texCoord(::ae::base::Vector2(aS, aT));
}

//------------------------------------------------------------------------------
void VtxBuffer::texCoord(const ::ae::base::Vector2Pod& aST)
{
    // チェック
    if (!mIsMeshActive) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mTexCoord = aST;
}

//------------------------------------------------------------------------------
void VtxBuffer::color(const f32 aR, const f32 aG, const f32 aB)
{
    color(aR, aG, aB, 1.0f);
}

//------------------------------------------------------------------------------
void VtxBuffer::color(const f32 aR, const f32 aG, const f32 aB, const f32 aA)
{
    color(::ae::base::Color4(aR, aG, aB, aA));
}

//------------------------------------------------------------------------------
void VtxBuffer::color(const ::ae::base::Color4Pod& aRGBA)
{
    // チェック
    if (!mIsMeshActive) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    mColor = aRGBA;
}

//------------------------------------------------------------------------------
void VtxBuffer::vertex(const f32 aX, const f32 aY)
{
    vertex(aX, aY, 0);
}

//------------------------------------------------------------------------------
void VtxBuffer::vertex(const f32 aX, const f32 aY, const f32 aZ)
{
    vertex(::ae::base::Vector3(aX, aY, aZ));
}

//------------------------------------------------------------------------------
void VtxBuffer::vertex(const ::ae::base::Vector2Pod& aXY)
{
    vertex(aXY.toXY0());
}

//------------------------------------------------------------------------------
void VtxBuffer::vertex(const ::ae::base::Vector3Pod& aXYZ)
{
    // チェック
    if (!mIsMeshActive) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    if (mVertexArray.isFull()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }

    // 頂点追加
    Vertex vtx = {};
    vtx.position = aXYZ;
    vtx.normal = mNormal;
    vtx.texCoord = mTexCoord;
    vtx.color = mColor;
    mVertexArray.add(vtx);
    ++mMeshArray.last().count;
}

//------------------------------------------------------------------------------
void VtxBuffer::flush()
{
    // チェック
    if (mIsFlushed) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }

    // フラグオン
    mIsFlushed = true;

    // 描画するものがなければバッファは作成しない
    if (mMeshArray.isEmpty()
        || mVertexArray.isEmpty()
        )
    {
        return;
    }

    // バッファ作成
    {
        AE_G3D_GLCMD(glBindBuffer(GL_ARRAY_BUFFER, mExt.vtxBuffer));
        AE_G3D_GLCMD(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertexArray.count(), &mVertexArray[0], GL_STATIC_DRAW));
        AE_G3D_GLCMD(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    {
        AE_G3D_GLCMD(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mExt.idxBuffer));
        AE_G3D_GLCMD(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * mIndexArray.count(), &mIndexArray[0], GL_STATIC_DRAW));
        AE_G3D_GLCMD(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    // データ指定
    AE_G3D_GLCMD(glBindVertexArray(mExt.vtxArray));
    AE_G3D_GLCMD(glBindBuffer(GL_ARRAY_BUFFER, mExt.vtxBuffer));
    AE_G3D_GLCMD(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mExt.idxBuffer));
    AE_G3D_GLCMD(glVertexAttribPointer(ShaderConstant::Attribute::Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, position))));
    AE_G3D_GLCMD(glVertexAttribPointer(ShaderConstant::Attribute::Normal, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, normal))));
    AE_G3D_GLCMD(glVertexAttribPointer(ShaderConstant::Attribute::TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, texCoord))));
    AE_G3D_GLCMD(glVertexAttribPointer(ShaderConstant::Attribute::Color, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, color))));
    AE_G3D_GLCMD(glEnableVertexAttribArray(ShaderConstant::Attribute::Position));
    AE_G3D_GLCMD(glEnableVertexAttribArray(ShaderConstant::Attribute::Normal));
    AE_G3D_GLCMD(glEnableVertexAttribArray(ShaderConstant::Attribute::TexCoord));
    AE_G3D_GLCMD(glEnableVertexAttribArray(ShaderConstant::Attribute::Color));
    AE_G3D_GLCMD(glBindVertexArray(0));
}

//------------------------------------------------------------------------------
void VtxBuffer::draw()
{
    // チェック
    if (!mIsFlushed) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }

    // メッシュがなければ何もしない
    if (mMeshArray.isEmpty()) {
        return;
    }

    // 頂点がなければ何もしない
    if (mVertexArray.isEmpty()) {
        return;
    }

    // セットアップ
    AE_G3D_GLCMD(glBindVertexArray(mExt.vtxArray));

    // 各メッシュの描画
    for (int i = 0; i < mMeshArray.count(); ++i) {
        // 取得
        const Mesh& mesh = mMeshArray[i];

        // 行列設定
        Renderer::Instance().sdSetMtxWorld(mesh.worldMtx);

        // 描画
        AE_G3D_GLCMD(glDrawElements(GL_TRIANGLES, mesh.count, GL_UNSIGNED_SHORT, reinterpret_cast<const void*>(sizeof(Index) * mesh.beginIndex)));
    }

    // クリーンアップ
    AE_G3D_GLCMD(glBindVertexArray(0));
}

//------------------------------------------------------------------------------
VtxBuffer_Ext::VtxBuffer_Ext()
: vtxArray()
, vtxBuffer()
, idxBuffer()
{
    AE_G3D_GLCMD(glGenVertexArrays(1, &vtxArray));
    AE_G3D_GLCMD(glGenBuffers(1, &vtxBuffer));
    AE_G3D_GLCMD(glGenBuffers(1, &idxBuffer));
}

//------------------------------------------------------------------------------
VtxBuffer_Ext::~VtxBuffer_Ext()
{
    AE_G3D_GLCMD(glDeleteBuffers(1, &idxBuffer));
    idxBuffer = 0;

    AE_G3D_GLCMD(glDeleteBuffers(1, &vtxBuffer));
    vtxBuffer = 0;

    AE_G3D_GLCMD(glDeleteVertexArrays(1, &vtxArray));
    vtxArray = 0;
}

}} // namespace
// EOF
