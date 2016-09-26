/**
 * @file
 * @brief EntryPoint_Sync.hの実装を記述する。
 * @author akino
 */
#include "EntryPoint_Sync.h"

//-----------------------------------------------------------
#import <QuartzCore/QuartzCore.h>

//-----------------------------------------------------------
void XBaseEntryPointSync_CATransactionFlush()
{
    [CATransaction flush];
}

//-----------------------------------------------------------
// EOF
