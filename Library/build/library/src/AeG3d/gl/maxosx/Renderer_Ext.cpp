// 文字コード：UTF-8
#include <ae/g3d/Renderer.hpp>

#include <ae/base/Display.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>
#include <ae/g3d/SdkHeader.hpp>
#include "AeG3dNSOpenGLView.h"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
void Renderer::copyToScreen(::ae::base::Screen& aScreen)
{
    AeG3dNSOpenGLView* view = aScreen.ext_().glView;
    if (view == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    AeG3dNSOpenGLView_FlushBuffer(view);
}

//------------------------------------------------------------------------------
void Renderer_Ext::setup(::ae::base::Display& aDisplay)
{
    // View割り当て
    AeG3dNSOpenGLView* view = AeG3dNSOpenGLView_Setup(
        aDisplay.ext_().windowPtr,
        aDisplay.context_().width(),
        aDisplay.context_().height(),
        aDisplay.context_().isScreenDoubleBuffer() ? 1 : 0
        );
    aDisplay.mainScreen().ext_().glView = view;
}

}} // namespace
// EOF
