/**
 * @file
 * @brief Vector2.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Vector2.hpp>

//------------------------------------------------------------
#include <XBase/DivideCheck.hpp>
#include <XBase/Infinity.hpp>
#include <XBase/Math.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/ScalerTypes.hpp>
#include <XBase/Vector3.hpp>
#include <XBase/Vector4.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
const Vector2POD Vector2POD::Zero()
{
    Vector2POD obj = {};
    return obj;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::One()
{
    Vector2POD obj = { 1 , 1 };
    return obj;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::Min()
{
    Vector2POD obj = { -XBASE_INFINITY , -XBASE_INFINITY };
    return obj;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::Max()
{
    Vector2POD obj = { XBASE_INFINITY , XBASE_INFINITY };
    return obj;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::UnitX()
{
    Vector2POD obj = { 1 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::UnitY()
{
    Vector2POD obj = { 0 , 1 };
    return obj;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::NegUnitX()
{
    Vector2POD obj = { -1 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::NegUnitY()
{
    Vector2POD obj = { 0 , -1 };
    return obj;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::toX0()const
{
    return Vector2( x , 0 );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::toXX()const
{
    return Vector2( x , x );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::toYX()const
{
    return Vector2( y , x );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::toYY()const
{
    return Vector2( y , y );
}

//------------------------------------------------------------
const Vector3POD Vector2POD::toXY0()const
{
    return Vector3( x , y , 0 );
}

//------------------------------------------------------------
const Vector3POD Vector2POD::toXXX()const
{
    return Vector3( x , x , x );
}

//------------------------------------------------------------
const Vector3POD Vector2POD::toYYY()const
{
    return Vector3( y , y , y );
}

//------------------------------------------------------------
const Vector4POD Vector2POD::toXY00()const
{
    return Vector4( x , y , 0 , 0 );
}

//------------------------------------------------------------
const Vector4POD Vector2POD::toXXXX()const
{
    return Vector4( x , x , x , x );
}

//------------------------------------------------------------
const Vector4POD Vector2POD::toYYYY()const
{
    return Vector4( y , y , y , y );
}

//------------------------------------------------------------
bool Vector2POD::equals( const Vector2POD& aVec )const
{
    return Math::IsEqualsF32( x , aVec.x )
        && Math::IsEqualsF32( y , aVec.y );
}

//------------------------------------------------------------
bool Vector2POD::equalsStrict( const Vector2POD& aVec )const
{
    return x == aVec.x && y == aVec.y;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::add( const float aVal )const
{
    Vector2 vec( *this );
    vec.addAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::sub( const float aVal )const
{
    Vector2 vec( *this );
    vec.subAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::mul( const float aVal )const
{
    Vector2 vec( *this );
    vec.mulAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::div( const float aVal )const
{
    Vector2 vec( *this );
    vec.divAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::add( const Vector2POD& aVal )const
{
    Vector2 vec( *this );
    vec.addAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::sub( const Vector2POD& aVal )const
{
    Vector2 vec( *this );
    vec.subAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::mul( const Vector2POD& aVal )const
{
    Vector2 vec( *this );
    vec.mulAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::div( const Vector2POD& aVal )const
{
    Vector2 vec( *this );
    vec.divAssign( aVal );
    return vec;
}

//------------------------------------------------------------
void Vector2POD::addAssign( const float aVal )
{
    x += aVal;
    y += aVal;
}

//------------------------------------------------------------
void Vector2POD::subAssign( const float aVal )
{
    x -= aVal;
    y -= aVal;
}

//------------------------------------------------------------
void Vector2POD::mulAssign( const float aVal )
{
    x *= aVal;
    y *= aVal;
}

//------------------------------------------------------------
void Vector2POD::divAssign( const float aVal )
{
    if ( aVal == 0 )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    mulAssign( 1.0f / aVal );
}

//------------------------------------------------------------
void Vector2POD::addAssign( const Vector2POD& aVal )
{
    x += aVal.x;
    y += aVal.y;
}

//------------------------------------------------------------
void Vector2POD::subAssign( const Vector2POD& aVal )
{
    x -= aVal.x;
    y -= aVal.y;
}

//------------------------------------------------------------
void Vector2POD::mulAssign( const Vector2POD& aVal )
{
    x *= aVal.x;
    y *= aVal.y;
}

//------------------------------------------------------------
void Vector2POD::divAssign( const Vector2POD& aVal )
{
    XBASE_DIV_ASSIGN( x , aVal.x );
    XBASE_DIV_ASSIGN( y , aVal.y );
}

//------------------------------------------------------------
Vector2POD& Vector2POD::operator+=( const float aVal )
{
    addAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector2POD& Vector2POD::operator-=( const float aVal )
{
    subAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector2POD& Vector2POD::operator*=( const float aVal )
{
    mulAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector2POD& Vector2POD::operator/=( const float aVal )
{
    divAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector2POD& Vector2POD::operator+=( const Vector2POD& aVal )
{
    addAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector2POD& Vector2POD::operator-=( const Vector2POD& aVal )
{
    subAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector2POD& Vector2POD::operator*=( const Vector2POD& aVal )
{
    mulAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector2POD& Vector2POD::operator/=( const Vector2POD& aVal )
{
    divAssign( aVal );
    return *this;
}

//------------------------------------------------------------
const Vector2POD Vector2POD::operator+( const float aVal )const
{
    return add( aVal );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::operator-( const float aVal )const
{
    return sub( aVal );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::operator*( const float aVal )const
{
    return mul( aVal );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::operator/( const float aVal )const
{
    return div( aVal );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::operator+( const Vector2POD& aVal )const
{
    return add( aVal );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::operator-( const Vector2POD& aVal )const
{
    return sub( aVal );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::operator*( const Vector2POD& aVal )const
{
    return mul( aVal );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::operator/( const Vector2POD& aVal )const
{
    return div( aVal );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::operator-()const
{
    return neg();
}

//------------------------------------------------------------
const Vector2POD Vector2POD::min( const Vector2POD& aVal )const
{
    return Vector2(
        Math::Min( x , aVal.x )
        , Math::Min( y , aVal.y )
        );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::max( const Vector2POD& aVal )const
{
    return Vector2(
        Math::Max( x , aVal.x )
        , Math::Max( y , aVal.y )
        );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::clamp(
    const Vector2POD& aMin
    , const Vector2POD& aMax
    )const
{
    return max( aMin ).min( aMax );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::clampPositive()const
{
    return max( Zero() );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::clampNegative()const
{
    return min( Zero() );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::abs()const
{
    return Vector2(
        Math::AbsF32( x )
        , Math::AbsF32( y )
        );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::neg()const
{
    Vector2 vec( *this );
    vec.mulAssign( -1.0f );
    return vec;
}

//------------------------------------------------------------
f32 Vector2POD::squareLength()const
{
    return x * x + y * y;
}

//------------------------------------------------------------
f32 Vector2POD::length()const
{
    return Math::SqrtF32( squareLength() );
}

//------------------------------------------------------------
f32 Vector2POD::distance( const Vector2POD& aVal )const
{
    return sub( aVal ).length();
}

//------------------------------------------------------------
bool Vector2POD::isZero()const
{
    return Math::IsZeroF32( length() );
}

//------------------------------------------------------------
bool Vector2POD::isZeroStrict()const
{
    return x == 0 && y == 0;
}

//------------------------------------------------------------
bool Vector2POD::isUnit()const
{
    return Math::IsEqualsF32( length() , 1.0f );
}

//------------------------------------------------------------
const Vector2POD Vector2POD::unit()const
{
    Vector2 vec( *this );
    vec.unitAssign();
    return vec;
}

//------------------------------------------------------------
void Vector2POD::unitAssign()
{
    if ( isZeroStrict() )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    mulAssign( 1.0f / length() );
}

//------------------------------------------------------------
f32 Vector2POD::dot( const Vector2POD& aVec )const
{
    return x * aVec.x + y * aVec.y;
}

//------------------------------------------------------------
f32 Vector2POD::cross( const Vector2POD& aVec )const
{	
    return x * aVec.y - aVec.y * x;
}

//------------------------------------------------------------
const ::XBase::ShortString Vector2POD::toShortString()const
{
    return ::XBase::ShortString::FromFormat(
        "%s,%s"
        , F32( x ).toShortString().readPtr()
        , F32( y ).toShortString().readPtr()
        );
}

//------------------------------------------------------------
Vector2::Vector2()
    : Vector2POD( Zero() )
{
}

//------------------------------------------------------------
Vector2::Vector2( const Vector2POD& aVec )
    : Vector2POD( aVec )
{
}

//------------------------------------------------------------
Vector2::Vector2( const float aV )
{
    x = aV;
    y = aV;
}

//------------------------------------------------------------
Vector2::Vector2( const float aX , const float aY )
{
    x = aX;
    y = aY;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
