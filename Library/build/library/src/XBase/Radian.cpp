// 文字コード：UTF-8
#include <XBase/Radian.hpp>

//------------------------------------------------------------------------------
#include <XBase/Angle.hpp>
#include <XBase/Degree.hpp>
#include <XBase/PI.hpp>

//------------------------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------------------------
namespace {
const float tToDegreeRate = 180.0f / XBASE_PI;
}
//------------------------------------------------------------------------------
const Angle RadianPOD::toAngle()const
{
    return Angle(*this);
}

//------------------------------------------------------------------------------
const DegreePOD RadianPOD::toDegree()const
{
    return Degree(value * tToDegreeRate);
}

//------------------------------------------------------------------------------
Radian::Radian()
    : RadianPOD()
{
    value = 0;
}

//------------------------------------------------------------------------------
Radian::Radian(const float aRadian)
    : RadianPOD()
{
    value = aRadian;
}

//------------------------------------------------------------------------------
Radian::Radian(const RadianPOD& aVal)
    : RadianPOD(aVal)
{
}

} // namespace
// EOF
