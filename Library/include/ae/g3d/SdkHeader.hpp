// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_SDKHEADER_HPP)
#else
#define AE_G3D_INCLUDED_SDKHEADER_HPP

#include <ae/base/Os.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/g3d/Engine.hpp>

#if defined(AE_G3D_ENGINE_GLSERIES)
    #if defined(AE_BASE_OS_WINDOWS)
        #include <ae/g3d/glew.h>
        #include <ae/g3d/wglew.h>
        #include <gl/glu.h>
        #pragma comment(lib,"kernel32.lib")
        #pragma comment(lib,"user32.lib")
        #pragma comment(lib,"gdi32.lib")
        #pragma comment(lib,"opengl32.lib")
        #pragma comment(lib,"glu32.lib")
    #elif defined(AE_BASE_OS_MACOSX)
        #include <OpenGL/OpenGL.h>
        #include <OpenGL/gl3.h>
        #include <OpenGL/gl3ext.h>
    #elif defined(AE_BASE_OS_IOS)
        #include <OpenGLES/ES3/gl.h>
        #include <OpenGLES/ES3/glext.h>
    #endif
#else
    #error "Not supported engine."
#endif

#endif
// EOF
