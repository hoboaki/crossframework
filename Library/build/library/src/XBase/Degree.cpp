// 文字コード：UTF-8
#include <XBase/Degree.hpp>

//------------------------------------------------------------------------------
#include <XBase/Angle.hpp>
#include <XBase/Pi.hpp>
#include <XBase/Radian.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
namespace {

const float tToRadianRate = XBASE_PI / 180.0f;

} // namespace

//------------------------------------------------------------------------------
const Angle DegreePod::toAngle()const
{
    return Angle(*this);
}

//------------------------------------------------------------------------------
const RadianPod DegreePod::toRadian()const
{
    return Radian(value * tToRadianRate);
}

//------------------------------------------------------------------------------
Degree::Degree()
: DegreePod()
{
    value = 0;
}

//------------------------------------------------------------------------------
Degree::Degree(const float aDegree)
: DegreePod()
{
    value = aDegree;
}

//------------------------------------------------------------------------------
Degree::Degree(const DegreePod& aVal)
: DegreePod(aVal)
{
}

} // namespace
// EOF
