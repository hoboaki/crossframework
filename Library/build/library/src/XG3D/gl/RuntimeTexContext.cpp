// 文字コード：UTF-8
#include <XG3D/RuntimeTexContext.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
const RuntimeTexContext RuntimeTexContext::Create(
    const ResTexFormat aFormat,
    const int aWidth,
    const int aHeight
    )
{
    return RuntimeTexContext(aFormat, aWidth, aHeight);
}

//------------------------------------------------------------------------------
ResTexFormat RuntimeTexContext::format()const
{
    return mFormat;
}

//------------------------------------------------------------------------------
u16 RuntimeTexContext::width()const
{
    return mWidth;
}

//------------------------------------------------------------------------------
u16 RuntimeTexContext::height()const
{
    return mHeight;
}

//------------------------------------------------------------------------------
RuntimeTexContext::RuntimeTexContext(
    const ResTexFormat aFormat,
    const int aWidth,
    const int aHeight
    )
: mFormat(aFormat)
, mWidth(u16(aWidth))
, mHeight(u16(aHeight))
{
}

} // namespace
// EOF
