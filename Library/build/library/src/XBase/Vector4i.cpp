/**
 * @file
 * @brief Vector4i.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Vector4i.hpp>

//------------------------------------------------------------
#include <XBase/DivideCheck.hpp>
#include <XBase/Math.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/ScalerTypes.hpp>
#include <XBase/Vector2i.hpp>
#include <XBase/Vector3i.hpp>
#include <XBase/Vector4.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::Zero()
{
    Vector4iPOD obj = {};
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::One()
{
    Vector4iPOD obj = { 1 , 1 , 1 , 1 };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::Min()
{
    Vector4iPOD obj = { std::numeric_limits< int >::min() , std::numeric_limits< int >::min() , std::numeric_limits< int >::min() , std::numeric_limits< int >::min() };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::Max()
{
    Vector4iPOD obj = { std::numeric_limits< int >::max() , std::numeric_limits< int >::max() , std::numeric_limits< int >::max() , std::numeric_limits< int >::max() };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::UnitX()
{
    Vector4iPOD obj = { 1 , 0 , 0 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::UnitY()
{
    Vector4iPOD obj = { 0 , 1 , 0 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::UnitZ()
{
    Vector4iPOD obj = { 0 , 0 , 1 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::UnitW()
{
    Vector4iPOD obj = { 0 , 0 , 0 , 1 };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::NegUnitX()
{
    Vector4iPOD obj = { -1 , 0 , 0 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::NegUnitY()
{
    Vector4iPOD obj = { 0 , -1 , 0 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::NegUnitZ()
{
    Vector4iPOD obj = { 0 , 0 , -1 , 0 };
    return obj;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::NegUnitW()
{
    Vector4iPOD obj = { 0 , 0 , 0 , -1 };
    return obj;
}

//------------------------------------------------------------
const Vector2iPOD Vector4iPOD::toXY()const
{
    return Vector2i( x , y );
}

//------------------------------------------------------------
const Vector2iPOD Vector4iPOD::toXX()const
{
    return Vector2i( x , x );
}

//------------------------------------------------------------
const Vector2iPOD Vector4iPOD::toYY()const
{
    return Vector2i( y , y );
}

//------------------------------------------------------------
const Vector2iPOD Vector4iPOD::toZZ()const
{
    return Vector2i( z , z );
}

//------------------------------------------------------------
const Vector2iPOD Vector4iPOD::toWW()const
{
    return Vector2i( w , w );
}

//------------------------------------------------------------
const Vector3iPOD Vector4iPOD::toXYZ()const
{
    return Vector3i( x , y , z );
}

//------------------------------------------------------------
const Vector3iPOD Vector4iPOD::toXXX()const
{
    return Vector3i( x , x , x );
}

//------------------------------------------------------------
const Vector3iPOD Vector4iPOD::toYYY()const
{
    return Vector3i( y , y , y );
}

//------------------------------------------------------------
const Vector3iPOD Vector4iPOD::toZZZ()const
{
    return Vector3i( z , z , z );
}

//------------------------------------------------------------
const Vector3iPOD Vector4iPOD::toWWW()const
{
    return Vector3i( w , w , w );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toXYZ0()const
{
    return Vector4i( x , y , z , 0 );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toXY0W()const
{
    return Vector4i( x , y , 0 , w );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toXY00()const
{
    return Vector4i( x , y , 0 , 0 );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toX0ZW()const
{
    return Vector4i( x , 0 , z , w );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toX0Z0()const
{
    return Vector4i( x , 0 , z , 0 );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toX00W()const
{
    return Vector4i( x , 0 , 0 , w );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toX000()const
{
    return Vector4i( x , 0 , 0 , 0 );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::to0YZ0()const
{
    return Vector4i( 0 , y , z , 0 );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::to0Y0W()const
{
    return Vector4i( 0 , y , 0 , w );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::to0Y00()const
{
    return Vector4i( 0 , y , 0 , 0 );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::to00ZW()const
{
    return Vector4i( 0 , 0 , z , w );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::to00Z0()const
{
    return Vector4i( 0 , 0 , z , 0 );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::to000W()const
{
    return Vector4i( 0 , 0 , 0 , w );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toXXXX()const
{
    return Vector4i( x , x , x , x );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toYYYY()const
{
    return Vector4i( y , y , y , y );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toZZZZ()const
{
    return Vector4i( z , z , z , z );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::toWWWW()const
{
    return Vector4i( w , w , w , w );
}

//------------------------------------------------------------
const Vector4POD Vector4iPOD::toXYZWf()const
{
    return Vector4( f32( x ) , f32( y ) , f32( z ) , f32( w ) );
}

//------------------------------------------------------------
bool Vector4iPOD::equals( const Vector4iPOD& aVec )const
{
    return x == aVec.x
        && y == aVec.y
        && z == aVec.z
        && w == aVec.w
        ;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::add( const s32 aVal )const
{
    Vector4i vec( *this );
    vec.addAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::sub( const s32 aVal )const
{
    Vector4i vec( *this );
    vec.subAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::mul( const s32 aVal )const
{
    Vector4i vec( *this );
    vec.mulAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::div( const s32 aVal )const
{
    Vector4i vec( *this );
    vec.divAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::add( const Vector4iPOD& aVal )const
{
    Vector4i vec( *this );
    vec.addAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::sub( const Vector4iPOD& aVal )const
{
    Vector4i vec( *this );
    vec.subAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::mul( const Vector4iPOD& aVal )const
{
    Vector4i vec( *this );
    vec.mulAssign( aVal );
    return vec;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::div( const Vector4iPOD& aVal )const
{
    Vector4i vec( *this );
    vec.divAssign( aVal );
    return vec;
}

//------------------------------------------------------------
void Vector4iPOD::addAssign( const s32 aVal )
{
    x += aVal;
    y += aVal;
    z += aVal;
    w += aVal;
}

//------------------------------------------------------------
void Vector4iPOD::subAssign( const s32 aVal )
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
    w -= aVal;
}

//------------------------------------------------------------
void Vector4iPOD::mulAssign( const s32 aVal )
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
    w *= aVal;
}

//------------------------------------------------------------
void Vector4iPOD::divAssign( const s32 aVal )
{
    if ( aVal == 0 )
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    x /= aVal;
    y /= aVal;
    z /= aVal;
    w /= aVal;
}

//------------------------------------------------------------
void Vector4iPOD::addAssign( const Vector4iPOD& aVal )
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
    w += aVal.w;
}

//------------------------------------------------------------
void Vector4iPOD::subAssign( const Vector4iPOD& aVal )
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
    w -= aVal.w;
}

//------------------------------------------------------------
void Vector4iPOD::mulAssign( const Vector4iPOD& aVal )
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
    w *= aVal.w;
}

//------------------------------------------------------------
void Vector4iPOD::divAssign( const Vector4iPOD& aVal )
{
    XBASE_DIV_ASSIGN( x , aVal.x );
    XBASE_DIV_ASSIGN( y , aVal.y );
    XBASE_DIV_ASSIGN( z , aVal.z );
    XBASE_DIV_ASSIGN( w , aVal.w );
}

//------------------------------------------------------------
Vector4iPOD& Vector4iPOD::operator+=( const s32 aVal )
{
    addAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector4iPOD& Vector4iPOD::operator-=( const s32 aVal )
{
    subAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector4iPOD& Vector4iPOD::operator*=( const s32 aVal )
{
    mulAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector4iPOD& Vector4iPOD::operator/=( const s32 aVal )
{
    divAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector4iPOD& Vector4iPOD::operator+=( const Vector4iPOD& aVal )
{
    addAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector4iPOD& Vector4iPOD::operator-=( const Vector4iPOD& aVal )
{
    subAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector4iPOD& Vector4iPOD::operator*=( const Vector4iPOD& aVal )
{
    mulAssign( aVal );
    return *this;
}

//------------------------------------------------------------
Vector4iPOD& Vector4iPOD::operator/=( const Vector4iPOD& aVal )
{
    divAssign( aVal );
    return *this;
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::operator+( const s32 aVal )const
{
    return add( aVal );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::operator-( const s32 aVal )const
{
    return sub( aVal );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::operator*( const s32 aVal )const
{
    return mul( aVal );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::operator/( const s32 aVal )const
{
    return div( aVal );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::operator+( const Vector4iPOD& aVal )const
{
    return add( aVal );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::operator-( const Vector4iPOD& aVal )const
{
    return sub( aVal );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::operator*( const Vector4iPOD& aVal )const
{
    return mul( aVal );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::operator/( const Vector4iPOD& aVal )const
{
    return div( aVal );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::operator-()const
{
    return neg();
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::min( const Vector4iPOD& aVal )const
{
    return Vector4i(
        Math::Min( x , aVal.x )
        , Math::Min( y , aVal.y )
        , Math::Min( z , aVal.z )
        , Math::Min( w , aVal.w )
        );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::max( const Vector4iPOD& aVal )const
{
    return Vector4i(
        Math::Max( x , aVal.x )
        , Math::Max( y , aVal.y )
        , Math::Max( z , aVal.z )
        , Math::Max( w , aVal.w )
        );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::clamp(
    const Vector4iPOD& aMin
    , const Vector4iPOD& aMax
    )const
{
    return max( aMin ).min( aMax );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::clampPositive()const
{
    return max( Zero() );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::clampNegative()const
{
    return min( Zero() );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::abs()const
{
    return Vector4i(
        Math::AbsS32( x )
        , Math::AbsS32( y )
        , Math::AbsS32( z )
        , Math::AbsS32( 2 )
        );
}

//------------------------------------------------------------
const Vector4iPOD Vector4iPOD::neg()const
{
    Vector4i vec( *this );
    vec.mulAssign( -1 );
    return vec;
}

//------------------------------------------------------------
bool Vector4iPOD::isPositive()const
{
    return 0 <= x
        && 0 <= y
        && 0 <= z
        && 0 <= w;
}

//------------------------------------------------------------
bool Vector4iPOD::isZero()const
{
    return x == 0 && y == 0 && z == 0 && w == 0;
}

//------------------------------------------------------------
const ::XBase::ShortString Vector4iPOD::toShortString()const
{
    return ::XBase::ShortString::FromFormat(
        "%s,%s,%s,%s"
        , S32( x ).toShortString().readPtr()
        , S32( y ).toShortString().readPtr()
        , S32( z ).toShortString().readPtr()
        , S32( w ).toShortString().readPtr()
        );
}

//------------------------------------------------------------
Vector4i::Vector4i()
    : Vector4iPOD( Zero() )
{
}

//------------------------------------------------------------
Vector4i::Vector4i( const Vector4iPOD& aVec )
    : Vector4iPOD( aVec )
{
}

//------------------------------------------------------------
Vector4i::Vector4i( const s32 aV )
{
    x = aV;
    y = aV;
    z = aV;
    w = aV;
}

//------------------------------------------------------------
Vector4i::Vector4i( const Vector2iPOD& aXY , const s32 aZ , const s32 aW )
{
    x = aXY.x;
    y = aXY.y;
    z = aZ;
    w = aW;
}

//------------------------------------------------------------
Vector4i::Vector4i( const Vector3iPOD& aXYZ , const s32 aW )
{
    x = aXYZ.x;
    y = aXYZ.y;
    z = aXYZ.z;
    w = aW;
}

//------------------------------------------------------------
Vector4i::Vector4i( const s32 aX , const s32 aY , const s32 aZ , const s32 aW )
{
    x = aX;
    y = aY;
    z = aZ;
    w = aW;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
