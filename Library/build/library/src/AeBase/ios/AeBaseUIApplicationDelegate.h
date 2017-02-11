// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_UIAPPLICATIONDELEGATE_H)
#else
#define XBASE_INCLUDED_UIAPPLICATIONDELEGATE_H

#include <UIKit/UIKit.h>

//------------------------------------------------------------------------------
@interface XBaseUIApplicationDelegate : NSObject <UIApplicationDelegate> 
{
}
@property (nonatomic, retain) id displayLink;

- (void)onUpdate:(id)sender;
@end

#endif
// EOF
