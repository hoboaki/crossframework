// 文字コード：UTF-8
#include <XBase/ScreenPos.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
ScreenPos::ScreenPos()
{
    x = 0;
    y = 0;
}

//------------------------------------------------------------------------------
ScreenPos::ScreenPos(const sint16 aX, const sint16 aY)
{
    x = aX;
    y = aY;
}

//------------------------------------------------------------------------------
ScreenPos::ScreenPos(const ScreenPosPOD& aObj)
{
    static_cast<ScreenPosPOD&>(*this) = aObj;
}

} // namespace
// EOF
