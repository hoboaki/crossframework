// 文字コード：UTF-8
#include "ResMdlShapeImpl.hpp"

#include <ae/base/ArrayLength.hpp>
#include <ae/base/Ref.hpp>
#include "GlCmd.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {
//------------------------------------------------------------------------------
namespace {

struct tInputTypeData
{
    int  dataType;
    int size;
};
const tInputTypeData tINPUT_TYPE_DATA_TABLE[] =
{
    {GL_FLOAT, sizeof(GLfloat)},
    {GL_BYTE, sizeof(GLbyte)},
    {GL_SHORT, sizeof(GLshort)},
    {GL_INT, sizeof(GLint)},
    {GL_UNSIGNED_BYTE, sizeof(GLubyte)},
    {GL_UNSIGNED_SHORT, sizeof(GLushort)},
    {GL_UNSIGNED_INT, sizeof(GLuint)}
};
AE_BASE_ARRAY_LENGTH_CHECK(tINPUT_TYPE_DATA_TABLE, ResMdlShapeInputType::TERM);
}
//------------------------------------------------------------------------------
ResMdlShapeImpl::ResMdlShapeImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMdlShape* aBinPtr,
    ::ae::base::IAllocator&
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
, vtxAttrs()
, idxBuffer(0)
, vtxAttrBuffer(0)
, idxGLDataType(tINPUT_TYPE_DATA_TABLE[aBinPtr->indexArrayDataType].dataType)
{
    // 初期化
    {
        VtxAttr obj = {};
        for (int i = 0; i < ResMdlShapeInputKind::TERM; ++i) {
            vtxAttrs[i] = obj;
        }
    }

    if (0 < binPtr->vtxAttrInfoCount) {
        const BinResMdlShape::VtxAttrInfo* infos = xdata.ref< BinResMdlShape::VtxAttrInfo>(binPtr->vtxAttrInfosRef);
        for (int i = 0; i < binPtr->vtxAttrInfoCount; ++i) {
            VtxAttr& dst = vtxAttrs[infos[i].inputKind];
            dst.glDataType = u16(tINPUT_TYPE_DATA_TABLE[infos[i].dataType].dataType);
            dst.glNormalize = GL_FALSE;
            dst.info = &infos[i];
        }
    }
}

//------------------------------------------------------------------------------
ResMdlShapeImpl::~ResMdlShapeImpl()
{
    release();
}

//------------------------------------------------------------------------------
void ResMdlShapeImpl::setup()
{
    // セットアップ済みなら何もしない
    if (idxBuffer != 0) {
        return;
    }

    // バッファ作成
    AE_BASE_ASSERT_EQUALS(uint(idxBuffer), 0);
    AE_BASE_ASSERT_EQUALS(uint(vtxAttrBuffer), 0);
    AE_G3D_GLCMD(glGenBuffers(1, &idxBuffer));
    AE_G3D_GLCMD(glGenBuffers(1, &vtxAttrBuffer));

    // idx
    AE_G3D_GLCMD(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBuffer));
    AE_G3D_GLCMD(glBufferData(GL_ELEMENT_ARRAY_BUFFER, tINPUT_TYPE_DATA_TABLE[binPtr->indexArrayDataType].size * binPtr->indexArrayDataCount, xdata.ref< GLubyte >(binPtr->indexArrayDataRef), GL_STATIC_DRAW));
    AE_G3D_GLCMD(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    // vtx
    AE_G3D_GLCMD(glBindBuffer(GL_ARRAY_BUFFER, vtxAttrBuffer));
    AE_G3D_GLCMD(glBufferData(GL_ARRAY_BUFFER, binPtr->vtxAttrDataSize, xdata.ref< GLubyte >(binPtr->vtxAttrDataRef), GL_STATIC_DRAW));
    AE_G3D_GLCMD(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

//------------------------------------------------------------------------------
void ResMdlShapeImpl::release()
{
    if (vtxAttrBuffer != 0) {
        AE_G3D_GLCMD(glDeleteBuffers(1, &vtxAttrBuffer));
        vtxAttrBuffer = 0;
    }
    if (idxBuffer != 0) {
        AE_G3D_GLCMD(glDeleteBuffers(1, &idxBuffer));
        idxBuffer = 0;
    }
}

}} // namespace
// EOF
