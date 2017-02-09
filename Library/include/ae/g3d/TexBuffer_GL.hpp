// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_TEXBUFFER_GL_HPP)
#else
#define AE_G3D_INCLUDED_TEXBUFFER_GL_HPP

#include <ae/g3d/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// TexBufferの拡張。
class TexBuffer_Ext
{
public:
    GLuint texId;

    //============================================================
    TexBuffer_Ext();
    ~TexBuffer_Ext();
};

}} // namespace
#endif
// EOF
