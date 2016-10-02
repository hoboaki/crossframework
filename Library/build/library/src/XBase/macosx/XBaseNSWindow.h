// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_XBASENSWINDOW_H)
#else
#define XBASE_INCLUDED_XBASENSWINDOW_H

struct XBaseNSWindow;

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    typedef void (*XBaseNSWindow_CBKeyEvent)( void* aOwner , int aUnicode , int aIsDown );
    typedef void (*XBaseNSWindow_CBModKeyEvent)( void* aOwner , int aIsShift , int aIsCtrl , int aIsAlt );
    typedef void (*XBaseNSWindow_CBMouseEvent)( void* aOwner , int aPressedButtons , float aX , float aY );
    extern struct XBaseNSWindow* XBaseNSWindow_Create( float aPosX , float aPosY , float aWidth , float aHeight , void* aOwnerPtr , int* aIsClosedPtr , XBaseNSWindow_CBKeyEvent , XBaseNSWindow_CBModKeyEvent , XBaseNSWindow_CBMouseEvent );
    extern void XBaseNSWindow_Destroy( struct XBaseNSWindow* );
    extern void XBaseNSWindow_Show( struct XBaseNSWindow* );
#ifdef __cplusplus
}
#endif

#endif
// EOF
