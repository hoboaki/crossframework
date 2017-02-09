// 文字コード：UTF-8
#include <ae/g3d/TexBuffer.hpp>

#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/ITexRes.hpp>
#include <ae/g3d/SdkHeader.hpp>
#include <ae/g3d/TexSetting.hpp>
#include "GlCmd.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
TexBuffer::TexBuffer(
    const TexResData& aData
    )
: mExt()
, mResData(aData)
{
    // テクスチャ作成
    GLenum internalFormat = GLenum();
    GLenum format = GLenum();
    GLenum type = GLenum();
    switch (mResData.format) {
        case ResTexFormat::RGBA8:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            break;

        case ResTexFormat::RGB8:
            internalFormat = GL_RGB;
            format = GL_RGB;
            type = GL_UNSIGNED_BYTE;
            break;

        case ResTexFormat::RGB5A1:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            type = GL_UNSIGNED_SHORT_5_5_5_1;
            break;

        case ResTexFormat::RGBA4:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            type = GL_UNSIGNED_SHORT_4_4_4_4;
            break;

        case ResTexFormat::RGB565:
            internalFormat = GL_RGB;
            format = GL_RGB;
            type = GL_UNSIGNED_SHORT_5_6_5;
            break;

        case ResTexFormat::RG8:
            internalFormat = GL_RG;
            format = GL_RG;
            type = GL_UNSIGNED_BYTE;
            break;

        case ResTexFormat::R8:
            internalFormat = GL_RED;
            format = GL_RED;
            type = GL_UNSIGNED_BYTE;
            break;

        default:
            AE_BASE_ERROR_INVALID_VALUE(int(mResData.format));
            break;
    }
    AE_G3D_GLCMD(glBindTexture(GL_TEXTURE_2D, mExt.texId));
    AE_G3D_GLCMD(glTexImage2D(
        GL_TEXTURE_2D,
        0,
        internalFormat,
        mResData.width,
        mResData.height,
        0,
        format,
        type,
        mResData.pixels
    ));
    AE_G3D_GLCMD(glBindTexture(GL_TEXTURE_2D, 0));
}

//------------------------------------------------------------------------------
TexBuffer::~TexBuffer()
{
}

//------------------------------------------------------------------------------
int TexBuffer::imageWidth()const
{
    return mResData.width;
}

//------------------------------------------------------------------------------
int TexBuffer::imageHeight()const
{
    return mResData.height;
}

//------------------------------------------------------------------------------
TexBuffer_Ext& TexBuffer::ext_()
{
    return mExt;
}

//------------------------------------------------------------------------------
const TexBuffer_Ext& TexBuffer::ext_()const
{
    return mExt;
}

//------------------------------------------------------------------------------
TexBuffer_Ext::TexBuffer_Ext()
: texId()
{
    AE_G3D_GLCMD(glGenTextures(1, &texId));
}

//------------------------------------------------------------------------------
TexBuffer_Ext::~TexBuffer_Ext()
{
    AE_G3D_GLCMD(glDeleteTextures(1, &texId));
}

}} // namespace
// EOF
