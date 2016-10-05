// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_VTXBUFFER_GL_HPP)
#else
#define XG3D_INCLUDED_VTXBUFFER_GL_HPP

#include <XG3D/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

// VtxBufferの拡張。
class VtxBuffer_EXT
{
public:
    GLuint vtxBuffer;
    GLuint idxBuffer;

    //============================================================
    VtxBuffer_EXT();
    ~VtxBuffer_EXT();
};

} // namespace
#endif
// EOF
