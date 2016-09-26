/**
 * @file
 * @brief Angle.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Angle.hpp>

//------------------------------------------------------------
#include <XBase/Degree.hpp>
#include <XBase/Radian.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
Angle::Angle()
: mRad( 0 )
{
}

//------------------------------------------------------------
Angle::Angle( const DegreePOD& aDegree )
: mRad( aDegree.toRadian().value )
{
}

//------------------------------------------------------------
Angle::Angle( const RadianPOD& aRadian )
: mRad( aRadian.value )
{
}

//------------------------------------------------------------
f32 Angle::rad()const
{
    return mRad;
}

//------------------------------------------------------------
f32 Angle::deg()const
{
    return Radian( mRad ).toDegree().value;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
