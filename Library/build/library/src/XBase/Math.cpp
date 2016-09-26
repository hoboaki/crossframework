/**
 * @file
 * @brief Math.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Math.hpp>

//------------------------------------------------------------
#include <cmath>
#include <XBase/Angle.hpp>
#include <XBase/DivideCheck.hpp>
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
namespace {
    const float tEPSILON = 0.000001f;
}
//------------------------------------------------------------
f32 Math::ClampF32( 
     const f32 aMin
    , const f32 aValue
    , const f32 aMax
    )
{
    XBASE_RANGE_ASSERT_EMIN( aMin , aMax );
    if ( aValue < aMin )
    {
        return aMin;
    }
    if ( aMax < aValue )
    {
        return aMax;
    }
    return aValue;
}

//------------------------------------------------------------
bool Math::IsInRangeF32(
    const f32 aMin
    , const f32 aValue
    , const f32 aMax
    )
{
    return ( aMin - tEPSILON ) <= aValue
        && aValue <= ( aMax + tEPSILON );
}

//------------------------------------------------------------
bool Math::IsEqualsF32( const f32 aVal1 , const f32 aVal2 )
{
    return IsInRangeF32( aVal2 , aVal1 , aVal2 );
}

//------------------------------------------------------------
bool Math::IsLessEqualsF32( const f32 aLhs , const f32 aRhs )
{
    return aLhs <= ( aRhs  + tEPSILON );
}

//------------------------------------------------------------
bool Math::IsLessF32( const f32 aLhs , const f32 aRhs )
{
    return aLhs < ( aRhs - tEPSILON );
}

//------------------------------------------------------------
bool Math::IsZeroF32( const f32 aVal )
{
    return IsEqualsF32( aVal , 0 );
}

//------------------------------------------------------------
f32 Math::SinF32( const Angle& aAngle )
{
    using namespace std;
    return f32( sinf( aAngle.rad() ) );
}

//------------------------------------------------------------
f32 Math::CosF32( const Angle& aAngle )
{
    using namespace std;
    return f32( cosf( aAngle.rad() ) );
}

//------------------------------------------------------------
f32 Math::TanF32( const Angle& aAngle )
{
    using namespace std;
    return f32( tanf( aAngle.rad() ) );
}

//------------------------------------------------------------
f32 Math::CecF32( const Angle& aAngle )
{
    return XBASE_DIV( 1 , SinF32( aAngle ) );
}

//------------------------------------------------------------
f32 Math::SecF32( const Angle& aAngle )
{
    return XBASE_DIV( 1 , CosF32( aAngle ) );
}

//------------------------------------------------------------
f32 Math::CotF32( const Angle& aAngle )
{
    return XBASE_DIV( 1 , TanF32( aAngle ) );
}

//------------------------------------------------------------
f32 Math::SqrtF32( const f32 aVal )
{
    using namespace std;
    return f32( sqrtf( aVal ) );
}

//------------------------------------------------------------
f32 Math::CeilF32( const f32 aVal )
{
    using namespace std;
    return f32( ceil( aVal ) );
}

//------------------------------------------------------------
f32 Math::FloorF32( const f32 aVal )
{
    using namespace std;
    return f32( floor( aVal ) );
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
