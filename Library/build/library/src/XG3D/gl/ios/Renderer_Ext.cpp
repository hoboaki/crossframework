// 文字コード：UTF-8
#include <XG3D/Renderer.hpp>

#include <XBase/Display.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/Unused.hpp>
#include <XG3D/SdkHeader.hpp>
#include "XG3DUIOpenGLView.h"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
void Renderer::copyToScreen(::XBase::Screen& aScreen)
{
    XG3DUIOpenGLView* view = aScreen.ext_().glView;
    if (view == 0) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }
    XG3DUIOpenGLView_FlushBuffer(view);
}

//------------------------------------------------------------------------------
void Renderer_Ext::setup(::XBase::Display& aDisplay)
{
    XG3DUIOpenGLView* view = XG3DUIOpenGLView_Setup(
        aDisplay.ext_().windowPtr
        );
    aDisplay.mainScreen().ext_().glView = view;
}

} // namespace
// EOF
