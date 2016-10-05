// 文字コード：UTF-8
#include <XBase/Display.hpp>

#include <XBase/Application.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Ref.hpp>
#include <XBase/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
Display::Display(const DisplayContext& aContext)
: mContext(aContext)
, mExt(aContext)
{
    // 登録
    Application::Instance().registerDisplay_(*this);
}

//------------------------------------------------------------------------------
Display::~Display()
{
    // 登録解除
    Application::Instance().unregisterDisplay_(*this);
}

//------------------------------------------------------------------------------
const DisplayContext Display::context_()const
{
    return mContext;
}

//------------------------------------------------------------------------------
Display_Ext& Display::ext_()
{
    return mExt;
}

} // namespace
// EOF
