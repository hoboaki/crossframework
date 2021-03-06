// 文字コード：UTF-8
#include "AeG3dNSOpenGLView.h"

#include <Cocoa/Cocoa.h>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
#include <OpenCL/OpenCL.h>

//------------------------------------------------------------------------------
@interface AeG3dOpenGLView : NSOpenGLView 
{
}
@end

@implementation AeG3dOpenGLView

@end

//------------------------------------------------------------------------------
struct AeG3dNSOpenGLView* AeG3dNSOpenGLView_Setup(
    struct AeBaseNSWindow* aWindow
    , const float aWidth 
    , const float aHeight 
    , const int aIsDoubleBuffer                                                
    )
{
    // メモリリーク対策
    NSAutoreleasePool* pool=[[NSAutoreleasePool alloc] init];
    
    // 属性
	NSOpenGLPixelFormatAttribute formatAttrib[]=
	{
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFAColorSize,	24,
        NSOpenGLPFAAlphaSize,	8,
        NSOpenGLPFADepthSize,	24,
        NSOpenGLPFAStencilSize,	8,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
		0
	};
    
    // ピクセルフォーマット
	NSOpenGLPixelFormat* format= [[[NSOpenGLPixelFormat alloc] initWithAttributes: formatAttrib] autorelease];
	
    // view作成
	NSRect contRect = NSMakeRect( 0 , 0 , aWidth , aHeight );    
	AeG3dOpenGLView* view = [[AeG3dOpenGLView alloc]
        initWithFrame:contRect
        pixelFormat:format
        ];
    assert(view != nil);
    
    // ウィンドウに設定
    NSWindow* window = (NSWindow*)aWindow;
	[window setContentView:view];
	[window makeFirstResponder:view];
    
    // 以下のコードを実行することでglコードを使えるようにする
	[window makeKeyAndOrderFront:nil];
	[window makeMainWindow];
    [window orderOut:nil];
    [[view openGLContext] makeCurrentContext];
#if defined(XLIBRARY_DEBUG)
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));
    printf("GL_VENDOR: %s\n", glGetString(GL_RENDERER));
    printf("GL_SHADING_LANGUAGE_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif
    
    // 結果を返す
    [pool release];
    return (struct AeG3dNSOpenGLView*)view;    
}

//------------------------------------------------------------------------------
void AeG3dNSOpenGLView_FlushBuffer( struct AeG3dNSOpenGLView* aView )
{
    NSOpenGLView* view = (NSOpenGLView*)aView;
    [[view openGLContext] flushBuffer];
}
                                                
// EOF
