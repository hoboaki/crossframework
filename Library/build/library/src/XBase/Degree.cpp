/**
 * @file
 * @brief Degree.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Degree.hpp>

//------------------------------------------------------------
#include <XBase/Angle.hpp>
#include <XBase/PI.hpp>
#include <XBase/Radian.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
namespace {
    const float tToRadianRate = XBASE_PI / 180.0f;
}
//------------------------------------------------------------
const Angle DegreePOD::toAngle()const
{
    return Angle( *this );
}

//------------------------------------------------------------
const RadianPOD DegreePOD::toRadian()const
{
    return Radian( value * tToRadianRate );
}

//------------------------------------------------------------
Degree::Degree() 
    : DegreePOD()
{
    value = 0;
}

//------------------------------------------------------------
Degree::Degree( const float aDegree ) 
    : DegreePOD()
{
    value = aDegree;
}

//------------------------------------------------------------
Degree::Degree( const DegreePOD& aVal )
    : DegreePOD( aVal )
{
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
