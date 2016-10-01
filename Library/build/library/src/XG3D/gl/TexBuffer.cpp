/**
 * @file
 * @brief TexBuffer.hppの実装を記述する。
 * @author akino
 */
#include <XG3D/TexBuffer.hpp>

//------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/ITexRes.hpp>
#include <XG3D/SDKHeader.hpp>
#include <XG3D/TexSetting.hpp>
#include "GLCMD.hpp"

//------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------
TexBuffer::TexBuffer(
    const TexResData& aData
    )
: mEXT()
, mResData( aData )
{
    // テクスチャ作成
    GLenum internalFormat = GLenum();
    GLenum format = GLenum();
    GLenum type = GLenum();
    switch ( mResData.format )
    {
    case ResTexFormat_RGBA8:
        internalFormat = GL_RGBA;
        format = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
        break;
        
    case ResTexFormat_RGB8:
        internalFormat = GL_RGB;
        format = GL_RGB;
        type = GL_UNSIGNED_BYTE;
        break;

    case ResTexFormat_RGB5A1:
        internalFormat = GL_RGBA;
        format = GL_RGBA;
        type = GL_UNSIGNED_SHORT_5_5_5_1;
        break;
        
    case ResTexFormat_RGBA4:
        internalFormat = GL_RGBA;
        format = GL_RGBA;
        type = GL_UNSIGNED_SHORT_4_4_4_4;
        break;
        
    case ResTexFormat_RGB565:
        internalFormat = GL_RGB;
        format = GL_RGB;
        type = GL_UNSIGNED_SHORT_5_6_5;
        break;

    case ResTexFormat_A8:
        internalFormat = GL_ALPHA;
        format = GL_ALPHA;
        type = GL_UNSIGNED_BYTE;
        break;

    case ResTexFormat_LA8:
        internalFormat = GL_LUMINANCE_ALPHA;
        format = GL_LUMINANCE_ALPHA;
        type = GL_UNSIGNED_BYTE;
        break;
        
    case ResTexFormat_L8:
        internalFormat = GL_LUMINANCE;
        format = GL_LUMINANCE;
        type = GL_UNSIGNED_BYTE;
        break;

    default:
        XBASE_INVALID_VALUE_ERROR( int( mResData.format ) );
        break;
    }
    XG3D_GLCMD( glBindTexture( GL_TEXTURE_2D , mEXT.texId ) );
    XG3D_GLCMD( glTexImage2D(
        GL_TEXTURE_2D
        , 0
        , internalFormat
        , mResData.width
        , mResData.height
        , 0
        , format
        , type
        , mResData.pixels
        ));
    XG3D_GLCMD( glBindTexture( GL_TEXTURE_2D , 0 ) );
}

//------------------------------------------------------------
TexBuffer::~TexBuffer()
{
}

//------------------------------------------------------------
uint TexBuffer::imageWidth()const
{
    return mResData.width;
}

//------------------------------------------------------------
uint TexBuffer::imageHeight()const
{
    return mResData.height;
}

//------------------------------------------------------------
TexBuffer_EXT& TexBuffer::ext_()
{
    return mEXT;
}

//------------------------------------------------------------
const TexBuffer_EXT& TexBuffer::ext_()const
{
    return mEXT;
}

//------------------------------------------------------------
TexBuffer_EXT::TexBuffer_EXT()
: texId()
{
    XG3D_GLCMD( glGenTextures( 1 , &texId ) );
}

//------------------------------------------------------------
TexBuffer_EXT::~TexBuffer_EXT()
{
    XG3D_GLCMD( glDeleteTextures( 1 , &texId ) );
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
