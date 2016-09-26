/**
 * @file
 * @brief C言語版AppEventを記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_XBASEAPPEVENT_H)
#else
#define XBASE_INCLUDED_XBASEAPPEVENT_H

//-----------------------------------------------------------
// C言語版AppEvent。
typedef enum XBaseAppEvent_
{
    XBaseAppEvent_Quit
    , XBaseAppEvent_Update
    // term
    , XBaseAppEvent_INVALID
} XBaseAppEvent;

//-----------------------------------------------------------
#endif
// EOF
