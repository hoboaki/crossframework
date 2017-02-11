// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_AEG3DNSOPENGLVIEW_H)
#else
#define AE_G3D_INCLUDED_AEG3DNSOPENGLVIEW_H

struct AeBaseNSWindow;
struct AeG3dNSOpenGLView;

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    extern struct AeG3dNSOpenGLView* AeG3dNSOpenGLView_Setup( struct AeBaseNSWindow* aWindow , float aWidth , float aHeight , int aIsDoubleBuffer );
    void AeG3dNSOpenGLView_FlushBuffer( struct AeG3dNSOpenGLView* );
#ifdef __cplusplus
}
#endif

#endif
// EOF
