// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_VTXBUFFER_GL_HPP)
#else
#define AE_G3D_INCLUDED_VTXBUFFER_GL_HPP

#include <ae/g3d/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// VtxBufferの拡張。
class VtxBuffer_Ext
{
public:
    GLuint vtxArray;
    GLuint vtxBuffer;
    GLuint idxBuffer;

    //============================================================
    VtxBuffer_Ext();
    ~VtxBuffer_Ext();
};

}} // namespace
#endif
// EOF
