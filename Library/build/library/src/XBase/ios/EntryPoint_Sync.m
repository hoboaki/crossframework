// 文字コード：UTF-8
#include "EntryPoint_Sync.h"

#import <QuartzCore/QuartzCore.h>

//------------------------------------------------------------------------------
void XBaseEntryPointSync_CATransactionFlush()
{
    [CATransaction flush];
}

// EOF
