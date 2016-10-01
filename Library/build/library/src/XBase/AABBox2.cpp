/**
 * @file
 * @brief AABBox2.hppの実装を記述する。
 * @author akino
 */
#include <XBase/AABBox2.hpp>

//------------------------------------------------------------
#include <XBase/AABBox2i.hpp>
#include <XBase/Math.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
AABBox2::AABBox2()
: mMin()
, mMax()
{
}

//------------------------------------------------------------
AABBox2::AABBox2( const Vector2POD& aPos )
: mMin( aPos )
, mMax( aPos )
{
}

//------------------------------------------------------------
AABBox2::AABBox2( 
    const Vector2POD& aPos1
    , const Vector2POD& aPos2
    )
: mMin( aPos1.min( aPos2 ) )
, mMax( aPos1.max( aPos2 ) )
{
}

//------------------------------------------------------------
const Vector2POD AABBox2::min()const
{
    return mMin;
}

//------------------------------------------------------------
const Vector2POD AABBox2::max()const
{
    return mMax;
}

//------------------------------------------------------------
const Vector2POD AABBox2::center()const
{
    return ( mMin + mMax ) * 0.5f;
}

//------------------------------------------------------------
const Vector2POD AABBox2::posLB()const
{
    return Vector2( mMin.x , mMin.y );
}

//------------------------------------------------------------
const Vector2POD AABBox2::posRB()const
{
    return Vector2( mMax.x , mMin.y );
}

//------------------------------------------------------------
const Vector2POD AABBox2::posLT()const
{
    return Vector2( mMin.x , mMax.y );
}

//------------------------------------------------------------
const Vector2POD AABBox2::posRT()const
{
    return Vector2( mMax.x , mMax.y );
}

//------------------------------------------------------------
float AABBox2::left()const
{
    return mMin.x;
}

//------------------------------------------------------------
float AABBox2::right()const
{
    return mMax.x;
}

//------------------------------------------------------------
float AABBox2::bottom()const
{
    return mMin.y;
}

//------------------------------------------------------------
float AABBox2::top()const
{
    return mMax.y;
}

//------------------------------------------------------------
float AABBox2::width()const
{
    return mMax.x - mMin.x;
}

//------------------------------------------------------------
float AABBox2::height()const
{
    return mMax.y - mMin.y;
}

//------------------------------------------------------------
const Vector2POD AABBox2::size()const
{
    return Vector2( width() , height() );
}

//------------------------------------------------------------
const Vector2POD AABBox2::halfSize()const
{
    return size() * 0.5f;
}

//------------------------------------------------------------
const AABBox2 AABBox2::merge( const Vector2POD& aPos )const
{
    AABBox2 aabb = *this;
    aabb.mergeAssign( aPos );
    return aabb;
}

//------------------------------------------------------------
const AABBox2 AABBox2::merge( const AABBox2& aAABB )const
{
    AABBox2 aabb = *this;
    aabb.mergeAssign( aAABB );
    return aabb;
}

//------------------------------------------------------------
void AABBox2::mergeAssign( const Vector2POD& aPos )
{
    mMin = mMin.min( aPos );
    mMax = mMax.max( aPos );
}

//------------------------------------------------------------
void AABBox2::mergeAssign( const AABBox2& aAABB )
{
    mMin = mMin.min( aAABB.mMin );
    mMax = mMax.max( aAABB.mMax );
}

//------------------------------------------------------------
bool AABBox2::isIntersects( const AABBox2& aAABB )const
{
    return mMin.x <= aAABB.mMax.x
        && mMin.y <= aAABB.mMax.y
        && aAABB.mMin.x <= mMax.x 
        && aAABB.mMin.y <= mMax.y;
}

//------------------------------------------------------------
bool AABBox2::isContains( const Vector2POD& aPos )const
{
    return mMin.x <= aPos.x 
        && mMin.y <= aPos.y
        && aPos.x <= mMax.x
        && aPos.y <= mMax.y;
}

//------------------------------------------------------------
bool AABBox2::isContains( const AABBox2& aAABB )const
{
    return isContains( aAABB.mMin )
        && isContains( aAABB.mMax );
}

//------------------------------------------------------------
const AABBox2 AABBox2::add( const Vector2POD& aTrans )const
{
    AABBox2 aabb = *this;
    aabb += aTrans;
    return aabb;
}

//------------------------------------------------------------
const AABBox2 AABBox2::sub( const Vector2POD& aTrans )const
{
    AABBox2 aabb = *this;
    aabb -= aTrans;
    return aabb;
}

//------------------------------------------------------------
const AABBox2 AABBox2::add( const AABBox2& aAABB )const
{
    AABBox2 aabb = *this;
    aabb += aAABB;
    return aabb;
}

//------------------------------------------------------------
const AABBox2 AABBox2::sub( const AABBox2& aAABB )const
{
    AABBox2 aabb = *this;
    aabb -= aAABB;
    return aabb;
}

//------------------------------------------------------------
const AABBox2 AABBox2::mul( const float aScale )const
{
    AABBox2 aabb = *this;
    aabb *= aScale;
    return aabb;
}

//------------------------------------------------------------
void AABBox2::addAssign( const Vector2POD& aTrans )
{
    mMin += aTrans;
    mMax += aTrans;
}

//------------------------------------------------------------
void AABBox2::subAssign( const Vector2POD& aTrans )
{
    mMin -= aTrans;
    mMax -= aTrans;
}

//------------------------------------------------------------
void AABBox2::addAssign( const AABBox2& aAABB )
{
    mMin += aAABB.mMin;
    mMax += aAABB.mMax;
}

//------------------------------------------------------------
void AABBox2::subAssign( const AABBox2& aAABB )
{
    mMin -= aAABB.mMin;
    mMax -= aAABB.mMax;
}

//------------------------------------------------------------
void AABBox2::mulAssign( const float aScale )
{
    mMin *= aScale;
    mMax *= aScale;
}

//------------------------------------------------------------
const AABBox2 AABBox2::operator+( const Vector2POD& aTrans )const
{
    return add( aTrans );
}

//------------------------------------------------------------
const AABBox2 AABBox2::operator-( const Vector2POD& aTrans )const
{
    return sub( aTrans );
}

//------------------------------------------------------------
const AABBox2 AABBox2::operator+( const AABBox2& aAABB )const
{
    return add( aAABB );
}

//------------------------------------------------------------
const AABBox2 AABBox2::operator-( const AABBox2& aAABB )const
{
    return sub( aAABB );
}

//------------------------------------------------------------
const AABBox2 AABBox2::operator*( const float aScale )const
{
    return mul( aScale );
}

//------------------------------------------------------------
AABBox2& AABBox2::operator+=( const Vector2POD& aTrans )
{
    addAssign( aTrans );
    return *this;
}

//------------------------------------------------------------
AABBox2& AABBox2::operator-=( const Vector2POD& aTrans )
{
    subAssign( aTrans );
    return *this;
}

//------------------------------------------------------------
AABBox2& AABBox2::operator+=( const AABBox2& aAABB )
{
    addAssign( aAABB );
    return *this;
}

//------------------------------------------------------------
AABBox2& AABBox2::operator-=( const AABBox2& aAABB )
{
    subAssign( aAABB );
    return *this;
}

//------------------------------------------------------------
AABBox2& AABBox2::operator*=( const float aScale )
{
    mulAssign( aScale );
    return *this;
}

//------------------------------------------------------------
const AABBox2i AABBox2::toAABB2i()const
{
    const Vector2i newMin( 
        int( Math::FloorF32( mMin.x ) )
        , int( Math::FloorF32( mMin.y ) )
        );
    const Vector2i newTerm(
        int( Math::CeilF32( mMax.x ) )
        , int( Math::CeilF32( mMax.y ) )
        );
    return AABBox2i( 
        newMin 
        , uint( newTerm.x - newMin.x )
        , uint( newTerm.y - newMin.y )
        );
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
