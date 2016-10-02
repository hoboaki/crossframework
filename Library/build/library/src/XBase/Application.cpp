// 文字コード：UTF-8
#include <XBase/Application.hpp>

//------------------------------------------------------------------------------
#include <XBase/Display.hpp>

//------------------------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------------------------
namespace {
Pointer< Application > tPtr;
}
//------------------------------------------------------------------------------
Application& Application::Instance()
{
    return tPtr.ref();
}

//------------------------------------------------------------------------------
XBase::Application::Application(const Argument& aArgument)
    : mArgument(aArgument)
    , mLastEvent(AppEvent_INVALID)
    , mDisplayPtr()
    , mEXT()
{
    tPtr.set(*this);
}

//------------------------------------------------------------------------------
Application::~Application()
{
    tPtr.unset();
}

//------------------------------------------------------------------------------
const Argument& Application::argument()const
{
    return mArgument;
}

//------------------------------------------------------------------------------
AppEvent Application::receiveEvent()
{
    mLastEvent = receiveEventCore();
    return mLastEvent;
}

//------------------------------------------------------------------------------
AppEvent Application::lastEvent()const
{
    return mLastEvent;
}

//------------------------------------------------------------------------------
void Application::registerDisplay_(Display& aDisplay)
{
    mDisplayPtr.set(aDisplay);
}

//------------------------------------------------------------------------------
void Application::unregisterDisplay_(Display& aDisplay)
{
    mDisplayPtr.unset(aDisplay);
}

} // namespace
// EOF
