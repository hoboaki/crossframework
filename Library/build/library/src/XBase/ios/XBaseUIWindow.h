/**
 * @file
 * @brief Mac環境のWindow実装に関する関数を定義する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_XBASEUIWindow_H)
#else
#define XBASE_INCLUDED_XBASEUIWindow_H

//-----------------------------------------------------------
struct XBaseUIWindow;
#define XBASE_UITOUCHSET_TOUCH_COUNT_MAX (4)

//-----------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    typedef struct 
    {
        int   tapCount;
        float tapPosX;
        float tapPosY;
    } XBaseUITouch;
    typedef struct
    {
        XBaseUITouch touches[XBASE_UITOUCHSET_TOUCH_COUNT_MAX];
    } XBaseUITouchSet;
    extern struct XBaseUIWindow* XBaseUIWindow_Create();
    extern void XBaseUIWindow_Destroy( struct XBaseUIWindow* );
    extern void XBaseUIWindow_Show( struct XBaseUIWindow* );
    extern const XBaseUITouchSet* XBaseUIWindow_PollTouch( struct XBaseUIWindow* );
#ifdef __cplusplus
}
#endif
//-----------------------------------------------------------
#endif
//-----------------------------------------------------------
// EOF
