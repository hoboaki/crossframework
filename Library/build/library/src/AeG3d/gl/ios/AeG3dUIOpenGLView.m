// 文字コード：UTF-8
#include "AeG3dUIOpenGLView.h"

#include <UIKit/UIKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <QuartzCore/QuartzCore.h>

//------------------------------------------------------------------------------
@interface AeG3dOpenGLView : UIView 
{
@private
    EAGLContext *context;
    
    // The pixel dimensions of the CAEAGLLayer
    GLint backingWidth;
    GLint backingHeight;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
    GLuint defaultFramebuffer, colorRenderbuffer, depthStencilRenderBuffer;
}
- (void)resizeFromLayer:(CAEAGLLayer *)layer;
- (void)flushBuffer;
@end

@implementation AeG3dOpenGLView

// You must implement this method
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)rect
{
    self = [super initWithFrame:rect];
    if (self)
    {
        // レイヤーセットアップ
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        
        
        // コンテキスト作成
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
        if (!context || ![EAGLContext setCurrentContext:context])
        {
            [self release];
            return nil;
        }
        
        // Create default framebuffer object. The backing will be allocated for the current layer in -resizeFromLayer
        glGenFramebuffers(1, &defaultFramebuffer);
        glGenRenderbuffers(1, &colorRenderbuffer);
        glGenRenderbuffers(1, &depthStencilRenderBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        
        // レンダーバッファの内容をレイヤーにコピーするように設定
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
    }
    
    return self;
}

- (void)layoutSubviews
{
    [self resizeFromLayer:(CAEAGLLayer*)self.layer];
    [self flushBuffer];
}

- (void)resizeFromLayer:(CAEAGLLayer *)layer
{
    // Allocate color buffer backing based on the current layer size
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);
    
    // DepthStencil Setup
    glBindRenderbuffer(GL_RENDERBUFFER, depthStencilRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, backingWidth, backingHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthStencilRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRenderBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        return;
    }
}

- (void)dealloc
{
    // Tear down GL
    if (depthStencilRenderBuffer)
    {
        glDeleteRenderbuffers(1, &depthStencilRenderBuffer);
        depthStencilRenderBuffer = 0;
    }
    
    if (colorRenderbuffer)
    {
        glDeleteRenderbuffers(1, &colorRenderbuffer);
        colorRenderbuffer = 0;
    }
    
    if (defaultFramebuffer)
    {
        glDeleteFramebuffers(1, &defaultFramebuffer);
        defaultFramebuffer = 0;
    }
   
    // Tear down context
    if ([EAGLContext currentContext] == context)
    {
        [EAGLContext setCurrentContext:nil];
    }
    
    [context release];
    context = nil;
    
    [super dealloc];
}

- (void)flushBuffer
{        
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER];
}
@end

//------------------------------------------------------------------------------
struct AeG3dUIOpenGLView* AeG3dUIOpenGLView_Setup(
    struct AeBaseUIWindow* aWindow
    )
{  
    UIWindow* window = (UIWindow*)aWindow;
    AeG3dOpenGLView* glView = [[AeG3dOpenGLView alloc]initWithFrame:[[UIScreen mainScreen]bounds]];    
    glView.multipleTouchEnabled = YES;
    [window addSubview:glView];
    
    return (struct AeG3dUIOpenGLView*)glView;
}

//------------------------------------------------------------------------------
void AeG3dUIOpenGLView_FlushBuffer( struct AeG3dUIOpenGLView* aView )
{
    AeG3dOpenGLView* glView = (AeG3dOpenGLView*)aView;;
    [glView flushBuffer];
}
                                                
// EOF
