/**
 * @file
 * @brief TexBuffer_EXT型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_TEXBUFFER_GL_HPP)
#else
#define XG3D_INCLUDED_TEXBUFFER_GL_HPP

//------------------------------------------------------------
#include <XG3D/SDKHeader.hpp>

//------------------------------------------------------------
namespace XG3D {
    // TexBufferの拡張。
    class TexBuffer_EXT
    {
    public:
        GLuint texId;

        //============================================================
        TexBuffer_EXT();
        ~TexBuffer_EXT();
    };
}
//------------------------------------------------------------
#endif
// EOF
