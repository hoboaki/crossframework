// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_XG3DUIOPENGLVIEW_H)
#else
#define XG3D_INCLUDED_XG3DUIOPENGLVIEW_H

//------------------------------------------------------------------------------
struct XBaseUIWindow;
struct XG3DUIOpenGLView;

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    extern struct XG3DUIOpenGLView* XG3DUIOpenGLView_Setup( struct XBaseUIWindow* );
    void XG3DUIOpenGLView_FlushBuffer( struct XG3DUIOpenGLView* );
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
#endif
// EOF
