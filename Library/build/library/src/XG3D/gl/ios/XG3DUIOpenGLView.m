// 文字コード：UTF-8
#include "XG3DUIOpenGLView.h"

//------------------------------------------------------------------------------
#include <UIKit/UIKit.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <QuartzCore/QuartzCore.h>

//------------------------------------------------------------------------------
@interface XG3DOpenGLView : UIView 
{
@private
    EAGLContext *context;
    
    // The pixel dimensions of the CAEAGLLayer
    GLint backingWidth;
    GLint backingHeight;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
    GLuint defaultFramebuffer, colorRenderbuffer;
}
- (void)resizeFromLayer:(CAEAGLLayer *)layer;
- (void)flushBuffer;
@end

@implementation XG3DOpenGLView

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
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];        
        if (!context || ![EAGLContext setCurrentContext:context])
        {
            [self release];
            return nil;
        }
        
        // Create default framebuffer object. The backing will be allocated for the current layer in -resizeFromLayer
        glGenFramebuffers(1, &defaultFramebuffer);
        glGenRenderbuffers(1, &colorRenderbuffer);
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
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        return;
    }
}

- (void)dealloc
{
    // Tear down GL
    if (defaultFramebuffer)
    {
        glDeleteFramebuffers(1, &defaultFramebuffer);
        defaultFramebuffer = 0;
    }
    
    if (colorRenderbuffer)
    {
        glDeleteRenderbuffers(1, &colorRenderbuffer);
        colorRenderbuffer = 0;
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
struct XG3DUIOpenGLView* XG3DUIOpenGLView_Setup(
    struct XBaseUIWindow* aWindow                                              
    )
{  
    UIWindow* window = (UIWindow*)aWindow;
    XG3DOpenGLView* glView = [[XG3DOpenGLView alloc]initWithFrame:[[UIScreen mainScreen]bounds]];    
    glView.multipleTouchEnabled = YES;
    [window addSubview:glView];
    
    return (struct XG3DUIOpenGLView*)glView;
}

//------------------------------------------------------------------------------
void XG3DUIOpenGLView_FlushBuffer( struct XG3DUIOpenGLView* aView )
{
    XG3DOpenGLView* glView = (XG3DOpenGLView*)aView;;
    [glView flushBuffer];
}
                                                
//------------------------------------------------------------------------------
// EOF
