// 文字コード：UTF-8
#include <XBase/Angle.hpp>

#include <XBase/Degree.hpp>
#include <XBase/Radian.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
Angle::Angle()
: mRad(0)
{
}

//------------------------------------------------------------------------------
Angle::Angle(const DegreePod& aDegree)
: mRad(aDegree.toRadian().value)
{
}

//------------------------------------------------------------------------------
Angle::Angle(const RadianPod& aRadian)
: mRad(aRadian.value)
{
}

//------------------------------------------------------------------------------
f32 Angle::rad()const
{
    return mRad;
}

//------------------------------------------------------------------------------
f32 Angle::deg()const
{
    return Radian(mRad).toDegree().value;
}

} // namespace
// EOF
