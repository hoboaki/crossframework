// 文字コード：UTF-8
#include <XG3D/Renderer.hpp>

//------------------------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/Unused.hpp>
#include <XG3D/SDKHeader.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
void Renderer::copyToScreen(::XBase::Screen& aScreen)
{
    XBASE_UNUSED(aScreen);
    SwapBuffers(wglGetCurrentDC());
}

//------------------------------------------------------------------------------
void Renderer_EXT::setup(::XBase::Display& aDisplay)
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

    // GLEE
    if (GLeeInit() == GL_FALSE) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }
}

} // namespace
// EOF
