// 文字コード：UTF-8
#include <XBase/DisplayContext.hpp>

//------------------------------------------------------------------------------
#include <XBase/SDKHeader.hpp>

#if defined(XBASE_OS_MACOSX)
    #include "XBaseNSScreen.h"
#endif

//------------------------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------------------------
#if defined(XBASE_OSTYPE_WINDOWSYSTEM)
//------------------------------------------------------------------------------
namespace {
    enum
    {
        tDefaultWidth  = 960
        , tDefaultHeight = 640
    };
}
//------------------------------------------------------------------------------
DisplayContext::DisplayContext()
: mLocationX( 0 )
, mLocationY( 0 )
, mWidth( tDefaultWidth )
, mHeight( tDefaultHeight )
, mIsScreenDoubleBuffer( true )
{
    // センタリング
    setLocationToCenter();
}

//------------------------------------------------------------------------------
void DisplayContext::setLocationToCenter()
{
#if defined(XBASE_OS_WINDOWS)
    // 情報取得
    HWND hwnd = GetDesktopWindow();
    HDC hdc   = GetDC( hwnd );
    const int dispWidth  = GetDeviceCaps( hdc , HORZRES );
    const int dispHeight = GetDeviceCaps( hdc , VERTRES );
    ReleaseDC( hwnd, hdc );
        
    // 位置設定
    if ( mWidth < uint( dispWidth ) )
    {
        mLocationX = ( dispWidth - mWidth  ) / 2;
    }
    if ( mHeight < uint( dispHeight ) )
    {
        mLocationY = ( dispHeight - mHeight  ) / 2;
    }
#elif defined(XBASE_OS_MACOSX)
    // 情報取得
    XBaseNSRect rect = {};
    XBaseNSScreen_GetMainScreenVisibleFrame( &rect );
    
    // 位置設定
    if ( mWidth < rect.sizeW )
    {
        mLocationX = uint( rect.originX + ( rect.sizeW - mWidth ) / 2 );
    }
    if ( mHeight < rect.sizeH )
    {
        mLocationY = uint( rect.originY + ( rect.sizeH - mHeight ) / 2 );
    }
#endif
}

//------------------------------------------------------------------------------
uint DisplayContext::locationX()const
{
    return mLocationX;
}

//------------------------------------------------------------------------------
uint DisplayContext::locationY()const
{
    return mLocationY;
}

//------------------------------------------------------------------------------
uint DisplayContext::width()const
{
    return mWidth;
}

//------------------------------------------------------------------------------
uint DisplayContext::height()const
{
    return mHeight;
}

//------------------------------------------------------------------------------
bool DisplayContext::isScreenDoubleBuffer()const
{
    return true;
}

//------------------------------------------------------------------------------
#else // end of WindowSystem
//------------------------------------------------------------------------------
DisplayContext::DisplayContext()
{
}

//------------------------------------------------------------------------------
#endif // end of other OS
} // namespace
// EOF
