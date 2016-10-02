// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_SDKHEADER_HPP)
#else
#define XG3D_INCLUDED_SDKHEADER_HPP

#include <XBase/OS.hpp>
#include <XBase/SDKHeader.hpp>
#include <XG3D/Engine.hpp>

#if defined(XG3D_ENGINE_GLSERIES)
    #if defined(XBASE_OS_WINDOWS)
        #include <XG3D/GLee.h>
        #include <gl/glu.h>
        #pragma comment(lib,"kernel32.lib")
        #pragma comment(lib,"user32.lib")
        #pragma comment(lib,"gdi32.lib")
        #pragma comment(lib,"opengl32.lib")
        #pragma comment(lib,"glu32.lib")
    #elif defined(XBASE_OS_MACOSX)
        #include <OpenGL/OpenGL.h>
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
    #elif defined(XBASE_OS_IOS)
        #include <OpenGLES/ES2/gl.h>
        #include <OpenGLES/ES2/glext.h>
    #endif
#else
    #error "Not supported engine."
#endif

#endif
// EOF
