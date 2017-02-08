// 文字コード：UTF-8
#include <XBase/Radian.hpp>

#include <XBase/Angle.hpp>
#include <XBase/Degree.hpp>
#include <XBase/Pi.hpp>

//------------------------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------------------------
namespace {

const float tToDegreeRate = 180.0f / XBASE_PI;
}
//------------------------------------------------------------------------------
const Angle RadianPod::toAngle()const
{
    return Angle(*this);
}

//------------------------------------------------------------------------------
const DegreePod RadianPod::toDegree()const
{
    return Degree(value * tToDegreeRate);
}

//------------------------------------------------------------------------------
Radian::Radian()
: RadianPod()
{
    value = 0;
}

//------------------------------------------------------------------------------
Radian::Radian(const float aRadian)
: RadianPod()
{
    value = aRadian;
}

//------------------------------------------------------------------------------
Radian::Radian(const RadianPod& aVal)
: RadianPod(aVal)
{
}

} // namespace
// EOF
