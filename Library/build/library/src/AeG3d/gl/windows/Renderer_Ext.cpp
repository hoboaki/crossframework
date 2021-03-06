// 文字コード：UTF-8
#include <ae/g3d/Renderer.hpp>

#include <ae/base/Display.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>
#include <ae/g3d/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
void Renderer::copyToScreen(::ae::base::Screen& aScreen)
{
    AE_BASE_UNUSED(aScreen);
    SwapBuffers(wglGetCurrentDC());
}

//------------------------------------------------------------------------------
void Renderer_Ext::setup(::ae::base::Display& aDisplay)
{
    // デバイスコンテキスト取得
    HDC dc = GetDC(aDisplay.ext_().window);

    // デスクリプタ作成
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    if (aDisplay.context_().isScreenDoubleBuffer()) {
        pfd.dwFlags |= PFD_DOUBLEBUFFER;
    }

    // ピクセルフォーマット選択
    const int pixelFormat = ChoosePixelFormat(dc, &pfd);
    if (pixelFormat == 0) {
        return;
    }

    // ピクセルフォーマット設定
    BOOL result = SetPixelFormat(dc, pixelFormat, &pfd);
    if (result == FALSE) {
        return;
    }

    // コンテキスト設定
    HGLRC tempContext = wglCreateContext(dc);
    wglMakeCurrent(dc, tempContext);

    // GLEW
    if (glewInit() != GLEW_OK) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }

    // コアプロファイルの有効化
    if (true) {
        // 使用する OpenGL のバージョンとプロファイルの指定
        static const int  att[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_FLAGS_ARB, 0,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0,
        };

        // 作成済みのContextを無効化
        wglMakeCurrent(dc, NULL);
        wglDeleteContext(tempContext);

        // コアプロファイルで有効化
        tempContext = wglCreateContextAttribsARB(dc, NULL, att);
        wglMakeCurrent(dc, tempContext);
    }
    //std::printf("Version: %s\n", glGetString(GL_VERSION));
}

}} // namespace
// EOF
