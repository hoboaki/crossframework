﻿/**
 * @file
 * @brief Screen.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Screen.hpp>

//------------------------------------------------------------
#include <XBase/ScreenPos.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
Screen::Screen( 
    Display_EXT& aOwner 
    , const uint aWidth 
    , const uint aHeight
    )
: mOwner( aOwner )
, mEXT()
, mWidth( aWidth )
, mHeight( aHeight )
{
}

//------------------------------------------------------------
uint Screen::width()const
{
    return mWidth;
}

//------------------------------------------------------------
uint Screen::height()const
{
    return mHeight;
}

//------------------------------------------------------------
bool Screen::isContains( const ScreenPosPOD& aPos )const
{
    return 0 <= aPos.x && aPos.x < int( mWidth )
        && 0 <= aPos.y && aPos.y < int( mHeight );
}

//------------------------------------------------------------
Display_EXT& Screen::display_()
{
    return mOwner;
}

//------------------------------------------------------------
Screen_EXT& Screen::ext_()
{
    return mEXT;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
