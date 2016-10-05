// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_XBASEAPPEVENT_H)
#else
#define XBASE_INCLUDED_XBASEAPPEVENT_H

//------------------------------------------------------------------------------
// C言語版AppEvent。
typedef enum XBaseAppEvent::
{
    XBaseAppEvent::Quit
    , XBaseAppEvent::Update
    // term
    , XBaseAppEvent::INVALID
} XBaseAppEvent;

#endif
// EOF
