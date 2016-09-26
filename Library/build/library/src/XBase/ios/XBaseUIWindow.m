/**
 * @file
 * @brief XBaseUIWindow.hの実装を記述する。
 * @author akino
 */
#include "XBaseUIWindow.h"

//-----------------------------------------------------------
#import <UIKit/UIKit.h>

//-----------------------------------------------------------
@interface XBaseUIWindowImpl : UIWindow
{
@private
    XBaseUITouchSet mTouchSet;
    XBaseUITouchSet mPrevTouchSet;
}
- (const XBaseUITouchSet*) pollTouch;
@end

//-----------------------------------------------------------
@implementation XBaseUIWindowImpl
-(const XBaseUITouchSet*)pollTouch
{
    mPrevTouchSet = mTouchSet;
    return &mTouchSet;
}

-(void)addNewTouch:(UITouch*)touch
{
    // あいているところを検索
    for ( int i = 0; i < XBASE_UITOUCHSET_TOUCH_COUNT_MAX; ++i )
    {
        if ( mTouchSet.touches[i].tapCount == 0
            && mPrevTouchSet.touches[i].tapCount == 0
            )
        {// ここに設定
            XBaseUITouch* target = &mTouchSet.touches[i];
            target->tapCount = (int)[touch tapCount];
            target->tapPosX  = [touch locationInView:nil].x;
            target->tapPosY  = [touch locationInView:nil].y;
            return;
        }
    }
    
    // あきが見つからなかった
    assert(false);
}

-(XBaseUITouch*)findTouch:(UITouch*)touch withUsePrevLocation:(BOOL)usePrevLocation
{
    // prev座標が一致するものを検索
    for ( int i = 0; i < XBASE_UITOUCHSET_TOUCH_COUNT_MAX; ++i )
    {
        // ポインタメモ
        XBaseUITouch* target = &mTouchSet.touches[i];
        
        // 一致判定
        CGPoint point = usePrevLocation 
            ? [touch previousLocationInView:nil]
            : [touch locationInView:nil];
        if ( target->tapCount == 0
            || target->tapPosX != point.x
            || target->tapPosY != point.y
            )
        {// 一致しない
            continue;
        }
        
        // 一致した
        return target;
    }
    // 一致なし
    return nil;
}

-(void)endTouch:(NSSet*)touches withEvent:(UIEvent*)event
{
    for ( UITouch* touch in touches )
    {
        // 内包判定
        CGPoint pos = [touch locationInView:nil];
        CGRect rect = [[UIScreen mainScreen] bounds];
        BOOL isContains = NO;
        if ( CGRectGetMinX( rect ) <= pos.x 
            && CGRectGetMinY( rect ) <= pos.y
            && pos.x < CGRectGetMaxX( rect )
            && pos.y < CGRectGetMaxY( rect )
            )
        {
            isContains = YES;
        }
        
        // 検索
        XBaseUITouch* target = [self findTouch:touch withUsePrevLocation:NO];
        if ( target == nil )
        {
            target = [self findTouch:touch withUsePrevLocation:YES];
        }
        
        // 処理
        if ( target == nil )
        {
            assert(false);
        }
        else
        {
            target->tapCount = 0;
        }
    }    
}

-(void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event 
{
    // あいているところに追加
    for ( UITouch* touch in touches )
    {
        [self addNewTouch:touch];
    }
}

-(void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event 
{
    for ( UITouch* touch in touches )
    {
        XBaseUITouch* target = [self findTouch:touch withUsePrevLocation:YES];
        if ( target == nil )
        {
            assert(false);
        }
        else
        {
            target->tapPosX = [touch locationInView:nil].x;
            target->tapPosY = [touch locationInView:nil].y;
        }
    }
}

-(void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event 
{
    [self endTouch:touches withEvent:event];
}

-(void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event 
{
    [self endTouch:touches withEvent:event];
}
@end

//-----------------------------------------------------------
struct XBaseUIWindow* XBaseUIWindow_Create()
{   
    // Window作成
    UIWindow* window = [[XBaseUIWindowImpl alloc] initWithFrame:[[UIScreen mainScreen]bounds]];
    
    // フレームをデバイスのスクリーンサイズにセット
    window.frame = CGRectMake(0, 0, [[UIScreen mainScreen]bounds].size.width, [[UIScreen mainScreen]bounds].size.height-20);
    
    // ダミーのViewController作成
    UIViewController* viewCtrl = [[UIViewController alloc]init];
    window.rootViewController = viewCtrl;

    // ダミーのView作成
    UIView* view = [[UIView alloc]initWithFrame:[[UIScreen mainScreen]bounds]];
    view.multipleTouchEnabled = YES;
    view.userInteractionEnabled = YES;
    view.backgroundColor = [UIColor blackColor]; // alphaが0だとタッチイベントが発生しないので色を指定
    [window addSubview:view];
     
    // 結果を返す
    return (struct XBaseUIWindow*)window;
}

//-----------------------------------------------------------
void XBaseUIWindow_Destroy( struct XBaseUIWindow* aWindow )
{
}

//-----------------------------------------------------------
void XBaseUIWindow_Show( struct XBaseUIWindow* aWindow )
{   
    UIWindow* window = (UIWindow*)aWindow;
    [window makeKeyAndVisible];
    [window layoutSubviews];
}

//-----------------------------------------------------------
const XBaseUITouchSet* XBaseUIWindow_PollTouch( struct XBaseUIWindow* aWindow )
{
    XBaseUIWindowImpl* window = (XBaseUIWindowImpl*)aWindow;
    return [window pollTouch];
}

//-----------------------------------------------------------
// EOF
