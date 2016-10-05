// 文字コード：UTF-8
#include <XBase/AABBox2i.hpp>

//------------------------------------------------------------------------------
#include <XBase/AABBox2.hpp>
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
const AABBox2i AABBox2i::Largest()
{
    return AABBox2i(Vector2iPod::Min(), 0xFFFFFFFF, 0xFFFFFFFF);
}

//------------------------------------------------------------------------------
AABBox2i::AABBox2i()
: mMin(Vector2i::Zero())
, mTerm(mMin)
{
}

//------------------------------------------------------------------------------
AABBox2i::AABBox2i(const Vector2iPod& aBegin)
: mMin(aBegin)
, mTerm(mMin)
{
}

//------------------------------------------------------------------------------
AABBox2i::AABBox2i(
    const Vector2iPod& aBegin,
    const int aWidth,
    const int aHeight
    )
: mMin(aBegin)
, mTerm(
    aBegin.x + reinterpret_cast<const int&>(aWidth),
    aBegin.y + reinterpret_cast<const int&>(aHeight)
    )
{
    XBASE_ASSERT_LESS_EQUALS(mMin.x, mTerm.x);
    XBASE_ASSERT_LESS_EQUALS(mMin.y, mTerm.y);
}

//------------------------------------------------------------------------------
const Vector2iPod AABBox2i::begin()const
{
    return mMin;
}

//------------------------------------------------------------------------------
const Vector2iPod AABBox2i::end()const
{
    return mTerm;
}

//------------------------------------------------------------------------------
const Vector2iPod AABBox2i::min()const
{
    return mMin;
}

//------------------------------------------------------------------------------
const Vector2iPod AABBox2i::term()const
{
    return mTerm;
}

//------------------------------------------------------------------------------
int AABBox2i::width()const
{
    return int(mTerm.x - mMin.x);
}

//------------------------------------------------------------------------------
int AABBox2i::height()const
{
    return int(mTerm.y - mMin.y);
}

//------------------------------------------------------------------------------
bool AABBox2i::isPositive()const
{
    return 0 <= mMin.x
        && 0 <= mMin.y;
}

//------------------------------------------------------------------------------
const AABBox2i AABBox2i::toPositive()const
{
    const Vector2i newMin = mMin.max(Vector2i::Zero());
    const Vector2i newTerm = mTerm.max(Vector2i::Zero());
    const Vector2i newSize = newTerm - newMin;
    return AABBox2i(
        newMin,
        uint(newSize.x),
        uint(newSize.y)
        );
}

//------------------------------------------------------------------------------
const AABBox2i AABBox2i::merge(const AABBox2i& aAABB)const
{
    AABBox2i aabb(*this);
    aabb.mergeAssign(aAABB);
    return aabb;
}

//------------------------------------------------------------------------------
void AABBox2i::mergeAssign(const AABBox2i& aAABB)
{
    mMin = mMin.min(aAABB.mMin);
    mTerm = mTerm.max(aAABB.mTerm);
}

//------------------------------------------------------------------------------
bool AABBox2i::isIntersects(const AABBox2i& aAABB)const
{
    return mMin.x < aAABB.mTerm.x
        && mMin.y < aAABB.mTerm.y
        && aAABB.mMin.x < mTerm.x
        && aAABB.mMin.y < mTerm.y;
}

//------------------------------------------------------------------------------
bool AABBox2i::isContains(const Vector2iPod& aPos)const
{
    return mMin.x <= aPos.x
        && mMin.y <= aPos.y
        && aPos.x < mTerm.x
        && aPos.y < mTerm.y;
}

//------------------------------------------------------------------------------
bool AABBox2i::isContains(const AABBox2i& aAABB)const
{
    return mMin.x <= aAABB.mMin.x
        && mMin.y <= aAABB.mMin.y
        && aAABB.mTerm.x <= mTerm.x
        && aAABB.mTerm.y <= mTerm.y;
}

//------------------------------------------------------------------------------
const AABBox2i AABBox2i::add(const Vector2iPod& aTrans)const
{
    AABBox2i aabb = *this;
    aabb.addAssign(aTrans);
    return aabb;
}

//------------------------------------------------------------------------------
const AABBox2i AABBox2i::sub(const Vector2iPod& aTrans)const
{
    AABBox2i aabb = *this;
    aabb.subAssign(aTrans);
    return aabb;
}

//------------------------------------------------------------------------------
void AABBox2i::addAssign(const Vector2iPod& aTrans)
{
    mMin += aTrans;
    mTerm += aTrans;
}

//------------------------------------------------------------------------------
void AABBox2i::subAssign(const Vector2iPod& aTrans)
{
    mMin -= aTrans;
    mTerm -= aTrans;
}

//------------------------------------------------------------------------------
const AABBox2i AABBox2i::operator+(const Vector2iPod& aTrans)const
{
    return add(aTrans);
}

//------------------------------------------------------------------------------
const AABBox2i AABBox2i::operator-(const Vector2iPod& aTrans)const
{
    return sub(aTrans);
}

//------------------------------------------------------------------------------
AABBox2i& AABBox2i::operator+=(const Vector2iPod& aTrans)
{
    addAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
AABBox2i& AABBox2i::operator-=(const Vector2iPod& aTrans)
{
    subAssign(aTrans);
    return *this;
}

//------------------------------------------------------------------------------
const AABBox2 AABBox2i::toAABB2f()const
{
    return AABBox2(
        min().toXYf(),
        term().toXYf()
        );
}

} // namespace
// EOF
