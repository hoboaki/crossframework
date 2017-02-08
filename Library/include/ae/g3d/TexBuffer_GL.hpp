// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_TEXBUFFER_GL_HPP)
#else
#define XG3D_INCLUDED_TEXBUFFER_GL_HPP

#include <XG3D/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

// TexBufferの拡張。
class TexBuffer_Ext
{
public:
    GLuint texId;

    //============================================================
    TexBuffer_Ext();
    ~TexBuffer_Ext();
};

} // namespace
#endif
// EOF
