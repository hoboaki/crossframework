// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_XG3DNSOPENGLVIEW_H)
#else
#define XG3D_INCLUDED_XG3DNSOPENGLVIEW_H

struct XBaseNSWindow;
struct XG3DNSOpenGLView;

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    extern struct XG3DNSOpenGLView* XG3DNSOpenGLView_Setup( struct XBaseNSWindow* aWindow , float aWidth , float aHeight , int aIsDoubleBuffer );
    void XG3DNSOpenGLView_FlushBuffer( struct XG3DNSOpenGLView* );
#ifdef __cplusplus
}
#endif

#endif
// EOF
