// 文字コード：UTF-8
#include <XG3D/Renderer.hpp>

#include <XBase/Display.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/Unused.hpp>
#include <XG3D/SdkHeader.hpp>
#include "XG3DNSOpenGLView.h"

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
void Renderer::copyToScreen(::XBase::Screen& aScreen)
{
    XG3DNSOpenGLView* view = aScreen.ext_().glView;
    if (view == 0) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }
    XG3DNSOpenGLView_FlushBuffer(view);
}

//------------------------------------------------------------------------------
void Renderer_Ext::setup(::XBase::Display& aDisplay)
{
    // View割り当て
    XG3DNSOpenGLView* view = XG3DNSOpenGLView_Setup(
        aDisplay.ext_().windowPtr,
        aDisplay.context_().width(),
        aDisplay.context_().height(),
        aDisplay.context_().isScreenDoubleBuffer() ? 1 : 0
        );
    aDisplay.mainScreen().ext_().glView = view;
}

} // namespace
// EOF
