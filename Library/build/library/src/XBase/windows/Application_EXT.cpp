// 文字コード：UTF-8
#include <XBase/Application.hpp>

//------------------------------------------------------------------------------
#include <XBase/Display.hpp>
#include <XBase/Thread.hpp>
#include <XBase/TimeSpan.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
namespace {

u64 tCurrentUSec()
{
    LARGE_INTEGER freq;
    if (QueryPerformanceFrequency(&freq) == TRUE)
    {
        LARGE_INTEGER time;
        QueryPerformanceCounter(&time);
        return time.QuadPart / (freq.QuadPart / (1000 * 1000));
    }
    else
    {
        return Time::LocalTime().ticks() / 10;
    }
}

} // namespace

//------------------------------------------------------------------------------
void Application::quit()
{
    mEXT.doQuit = true;
}

//------------------------------------------------------------------------------
AppEvent Application::receiveEventCore()
{
    // 終了要求があったらQuit
    if (mEXT.doQuit)
    {
        return AppEvent_Quit;
    }

    // ディスプレイのイベントチェック
    if (mDisplayPtr.isValid())
    {
        mDisplayPtr->ext_().pollEvent(*this);
    }

    // 60フレ同期
    {
        u64 currentUSec = u64();
        while (true)
        {
            currentUSec = tCurrentUSec();
            if (mEXT.prevUSec <= currentUSec) // オーバーフローしていることもあるので。
            {
                if (currentUSec - mEXT.prevUSec < 16666)
                {
                    Thread::Sleep(TimeSpan::FromMilliseconds(1));
                    continue;
                }
            }
            break;
        }
        mEXT.prevUSec = currentUSec;
    }

    // 常にUpdate
    return AppEvent_Update;
}

//------------------------------------------------------------------------------
Application_EXT::Application_EXT()
: prevUSec(tCurrentUSec())
, doQuit(false)
{
}

} // namespace
// EOF
