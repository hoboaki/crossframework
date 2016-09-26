/**
 * @file
 * @brief Vector3i.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Vector3i.hpp>

//------------------------------------------------------------
#include <XBase/DivideCheck.hpp>
#include <XBase/Math.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/ScalerTypes.hpp>
#include <XBase/Vector2i.hpp>
#include <XBase/Vector3.hpp>
#include <XBase/Vector4i.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::Zero()
{
    Vector3iPOD obj = {};
    return obj;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::One()
{
    Vector3iPOD obj = { 1 , 1 , 1 };
    return obj;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::Min()
{
    Vector3iPOD obj = { std::numeric_limits< int >::min() , std::numeric_limits< int >::min() , std::numeric_limits< int >::min() };
    return obj;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::Max()
{
    Vector3iPOD obj = { std::numeric_limits< int >::max() , std::numeric_limits< int >::max() , std::numeric_limits< int >::max() };
    return obj;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::UnitX()
{
    Vector3iPOD obj = { 1 , 0 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::UnitY()
{
    Vector3iPOD obj = { 0 , 1 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::UnitZ()
{
    Vector3iPOD obj = { 0 , 0 , 1 };
    return obj;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::NegUnitX()
{
    Vector3iPOD obj = { -1 , 0 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::NegUnitY()
{
    Vector3iPOD obj = { 0 , -1 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::NegUnitZ()
{
    Vector3iPOD obj = { 0 , 0 , -1 };
    return obj;
}

//------------------------------------------------------------
const Vector2iPOD Vector3iPOD::toXY()const
{
    return Vector2i( x , y );
}

//------------------------------------------------------------
const Vector2iPOD Vector3iPOD::toXX()const
{
    return Vector2i( x , x );
}

//------------------------------------------------------------
const Vector2iPOD Vector3iPOD::toYY()const
{
    return Vector2i( y , y );
}

//------------------------------------------------------------
const Vector2iPOD Vector3iPOD::toZZ()const
{
    return Vector2i( z , z );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::toX00()const
{
    return Vector3i( x , 0 , 0 );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::toXY0()const
{
    return Vector3i( x , y , 0 );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::to0Y0()const
{
    return Vector3i( 0 , y , 0 );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::to0YZ()const
{
    return Vector3i( 0 , y , z );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::to00Z()const
{
    return Vector3i( 0 , 0 , z );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::toXXX()const
{
    return Vector3i( x , x , x );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::toYYY()const
{
    return Vector3i( y , y , y );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::toZZZ()const
{
    return Vector3i( z , z , z );
}

//------------------------------------------------------------
const Vector4iPOD Vector3iPOD::toXYZ0()const
{
    return Vector4i( x , y , z , 0 );
}

//------------------------------------------------------------
const Vector4iPOD Vector3iPOD::toXXXX()const
{
    return Vector4i( x , x , x , x );
}

//------------------------------------------------------------
const Vector4iPOD Vector3iPOD::toYYYY()const
{
    return Vector4i( y , y , y , y );
}

//------------------------------------------------------------
const Vector4iPOD Vector3iPOD::toZZZZ()const
{
    return Vector4i( z , z , z , z );
}

//------------------------------------------------------------
const Vector3POD Vector3iPOD::toXYZf()const
{
    return Vector3( f32( x ) , f32( y ) , f32( z ) );
}

//------------------------------------------------------------
bool Vector3iPOD::equals( const Vector3iPOD& aVec )const
{
    return x == aVec.x
        && y == aVec.y
        && z == aVec.z
        ;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::add( const s32 aVal )const
{
    Vector3i vec( *this );
    vec.addAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::sub( const s32 aVal )const
{
    Vector3i vec( *this );
    vec.subAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::mul( const s32 aVal )const
{
    Vector3i vec( *this );
    vec.mulAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::div( const s32 aVal )const
{
    Vector3i vec( *this );
    vec.divAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::add( const Vector3iPOD& aVal )const
{
    Vector3i vec( *this );
    vec.addAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::sub( const Vector3iPOD& aVal )const
{
    Vector3i vec( *this );
    vec.subAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::mul( const Vector3iPOD& aVal )const
{
    Vector3i vec( *this );
    vec.mulAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::div( const Vector3iPOD& aVal )const
{
    Vector3i vec( *this );
    vec.divAssign( aVal );
    return vec;
}

//------------------------------------------------------------
void Vector3iPOD::addAssign( const s32 aVal )
{
    x += aVal;
    y += aVal;
    z += aVal;
}

//------------------------------------------------------------
void Vector3iPOD::subAssign( const s32 aVal )
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
}

//------------------------------------------------------------
void Vector3iPOD::mulAssign( const s32 aVal )
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
}

//------------------------------------------------------------
void Vector3iPOD::divAssign( const s32 aVal )
{
    if ( aVal == 0 )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    x /= aVal;
    y /= aVal;
    z /= aVal;
}

//------------------------------------------------------------
void Vector3iPOD::addAssign( const Vector3iPOD& aVal )
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
}

//------------------------------------------------------------
void Vector3iPOD::subAssign( const Vector3iPOD& aVal )
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
}

//------------------------------------------------------------
void Vector3iPOD::mulAssign( const Vector3iPOD& aVal )
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
}

//------------------------------------------------------------
void Vector3iPOD::divAssign( const Vector3iPOD& aVal )
{
    XBASE_DIV_ASSIGN( x , aVal.x );
    XBASE_DIV_ASSIGN( y , aVal.y );
    XBASE_DIV_ASSIGN( z , aVal.z );
}

//------------------------------------------------------------
Vector3iPOD& Vector3iPOD::operator+=( const s32 aVal )
{
    addAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector3iPOD& Vector3iPOD::operator-=( const s32 aVal )
{
    subAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector3iPOD& Vector3iPOD::operator*=( const s32 aVal )
{
    mulAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector3iPOD& Vector3iPOD::operator/=( const s32 aVal )
{
    divAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector3iPOD& Vector3iPOD::operator+=( const Vector3iPOD& aVal )
{
    addAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector3iPOD& Vector3iPOD::operator-=( const Vector3iPOD& aVal )
{
    subAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector3iPOD& Vector3iPOD::operator*=( const Vector3iPOD& aVal )
{
    mulAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector3iPOD& Vector3iPOD::operator/=( const Vector3iPOD& aVal )
{
    divAssign( aVal );
    return *this;
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::operator+( const s32 aVal )const
{
    return add( aVal );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::operator-( const s32 aVal )const
{
    return sub( aVal );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::operator*( const s32 aVal )const
{
    return mul( aVal );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::operator/( const s32 aVal )const
{
    return div( aVal );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::operator+( const Vector3iPOD& aVal )const
{
    return add( aVal );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::operator-( const Vector3iPOD& aVal )const
{
    return sub( aVal );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::operator*( const Vector3iPOD& aVal )const
{
    return mul( aVal );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::operator/( const Vector3iPOD& aVal )const
{
    return div( aVal );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::operator-()const
{
    return neg();
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::min( const Vector3iPOD& aVal )const
{
    return Vector3i(
        Math::Min( x , aVal.x )
        , Math::Min( y , aVal.y )
        , Math::Min( z , aVal.z )
        );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::max( const Vector3iPOD& aVal )const
{
    return Vector3i(
        Math::Max( x , aVal.x )
        , Math::Max( y , aVal.y )
        , Math::Max( z , aVal.z )
        );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::clamp(
    const Vector3iPOD& aMin
    , const Vector3iPOD& aMax
    )const
{
    return max( aMin ).min( aMax );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::clampPositive()const
{
    return max( Zero() );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::clampNegative()const
{
    return min( Zero() );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::abs()const
{
    return Vector3i(
        Math::AbsS32( x )
        , Math::AbsS32( y )
        , Math::AbsS32( z )
        );
}

//------------------------------------------------------------
const Vector3iPOD Vector3iPOD::neg()const
{
    Vector3i vec( *this );
    vec.mulAssign( -1 );
    return vec;
}

//------------------------------------------------------------
bool Vector3iPOD::isPositive()const
{
    return 0 <= x
        && 0 <= y
        && 0 <= z;
}

//------------------------------------------------------------
bool Vector3iPOD::isZero()const
{
    return x == 0 && y == 0 && z == 0;
}

//------------------------------------------------------------
const ::XBase::ShortString Vector3iPOD::toShortString()const
{
    return ::XBase::ShortString::FromFormat(
        "%s,%s,%s"
        , S32( x ).toShortString().readPtr()
        , S32( y ).toShortString().readPtr()
        , S32( z ).toShortString().readPtr()
        );
}

//------------------------------------------------------------
Vector3i::Vector3i()
    : Vector3iPOD( Zero() )
{
}

//------------------------------------------------------------
Vector3i::Vector3i( const Vector3iPOD& aVec )
    : Vector3iPOD( aVec )
{
}

//------------------------------------------------------------
Vector3i::Vector3i( const s32 aV )
{
    x = aV;
    y = aV;
    z = aV;
}

//------------------------------------------------------------
Vector3i::Vector3i( const Vector2iPOD& aXY , const s32 aZ )
{
    x = aXY.x;
    y = aXY.y;
    z = aZ;
}

//------------------------------------------------------------
Vector3i::Vector3i( const s32 aX , const s32 aY , const s32 aZ )
{
    x = aX;
    y = aY;
    z = aZ;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
