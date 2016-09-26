/**
 * @file
 * @brief Display.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Display.hpp>

//------------------------------------------------------------
#include <XBase/Application.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Ref.hpp>
#include <XBase/SDKHeader.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
Display::Display( const DisplayContext& aContext )
: mContext( aContext )
, mEXT( aContext )
{
    // 登録
    Application::Instance().registerDisplay_( *this );
}

//------------------------------------------------------------
Display::~Display()
{
    // 登録解除
    Application::Instance().unregisterDisplay_( *this );
}

//------------------------------------------------------------
const DisplayContext Display::context_()const
{
    return mContext;
}

//------------------------------------------------------------
Display_EXT& Display::ext_()
{
    return mEXT;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
