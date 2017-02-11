// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_AeG3dUIOPENGLVIEW_H)
#else
#define AE_G3D_INCLUDED_AeG3dUIOPENGLVIEW_H

struct AeBaseUIWindow;
struct AeG3dUIOpenGLView;

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
extern struct AeG3dUIOpenGLView* AeG3dUIOpenGLView_Setup( struct AeBaseUIWindow* );
void AeG3dUIOpenGLView_FlushBuffer( struct AeG3dUIOpenGLView* );
#ifdef __cplusplus
}
#endif

#endif
// EOF
