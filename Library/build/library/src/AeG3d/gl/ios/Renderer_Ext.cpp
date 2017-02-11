// 文字コード：UTF-8
#include <ae/g3d/Renderer.hpp>

#include <ae/base/Display.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>
#include <ae/g3d/SdkHeader.hpp>
#include "AeG3dUIOpenGLView.h"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
void Renderer::copyToScreen(::ae::base::Screen& aScreen)
{
    AeG3dUIOpenGLView* view = aScreen.ext_().glView;
    if (view == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return;
    }
    AeG3dUIOpenGLView_FlushBuffer(view);
}

//------------------------------------------------------------------------------
void Renderer_Ext::setup(::ae::base::Display& aDisplay)
{
    AeG3dUIOpenGLView* view = AeG3dUIOpenGLView_Setup(
        aDisplay.ext_().windowPtr
        );
    aDisplay.mainScreen().ext_().glView = view;
}

}} // namespace
// EOF
