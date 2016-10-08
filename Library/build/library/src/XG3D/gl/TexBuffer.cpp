// 文字コード：UTF-8
#include <XG3D/TexBuffer.hpp>

#include <XBase/RuntimeAssert.hpp>
#include <XG3D/ITexRes.hpp>
#include <XG3D/SdkHeader.hpp>
#include <XG3D/TexSetting.hpp>
#include "GlCmd.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

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

        case ResTexFormat::A8:
            internalFormat = GL_ALPHA;
            format = GL_ALPHA;
            type = GL_UNSIGNED_BYTE;
            break;

        case ResTexFormat::LA8:
            internalFormat = GL_LUMINANCE_ALPHA;
            format = GL_LUMINANCE_ALPHA;
            type = GL_UNSIGNED_BYTE;
            break;

        case ResTexFormat::L8:
            internalFormat = GL_LUMINANCE;
            format = GL_LUMINANCE;
            type = GL_UNSIGNED_BYTE;
            break;

        default:
            XBASE_ERROR_INVALID_VALUE(int(mResData.format));
            break;
    }
    XG3D_GLCMD(glBindTexture(GL_TEXTURE_2D, mExt.texId));
    XG3D_GLCMD(glTexImage2D(
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
    XG3D_GLCMD(glBindTexture(GL_TEXTURE_2D, 0));
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
TexBuffer_EXT& TexBuffer::ext_()
{
    return mExt;
}

//------------------------------------------------------------------------------
const TexBuffer_EXT& TexBuffer::ext_()const
{
    return mExt;
}

//------------------------------------------------------------------------------
TexBuffer_EXT::TexBuffer_EXT()
: texId()
{
    XG3D_GLCMD(glGenTextures(1, &texId));
}

//------------------------------------------------------------------------------
TexBuffer_EXT::~TexBuffer_EXT()
{
    XG3D_GLCMD(glDeleteTextures(1, &texId));
}

} // namespace
// EOF
