// 文字コード：UTF-8
#include <XBase/Vector2i.hpp>

//------------------------------------------------------------------------------
#include <XBase/DivideCheck.hpp>
#include <XBase/Math.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/ScalerTypes.hpp>
#include <XBase/Vector2.hpp>
#include <XBase/Vector3i.hpp>
#include <XBase/Vector4i.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::Zero()
{
    Vector2iPOD obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::One()
{
    Vector2iPOD obj = {1, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::Min()
{
    Vector2iPOD obj = {std::numeric_limits< int >::min(), std::numeric_limits< int >::min()};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::Max()
{
    Vector2iPOD obj = {std::numeric_limits< int >::max(), std::numeric_limits< int >::max()};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::UnitX()
{
    Vector2iPOD obj = {1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::UnitY()
{
    Vector2iPOD obj = {0, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::NegUnitX()
{
    Vector2iPOD obj = {-1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::NegUnitY()
{
    Vector2iPOD obj = {0, -1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::toX0()const
{
    return Vector2i(x, 0);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::toXX()const
{
    return Vector2i(x, x);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::toYX()const
{
    return Vector2i(y, x);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::toYY()const
{
    return Vector2i(y, y);
}

//------------------------------------------------------------------------------
const Vector3iPOD Vector2iPOD::toXY0()const
{
    return Vector3i(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3iPOD Vector2iPOD::toXXX()const
{
    return Vector3i(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3iPOD Vector2iPOD::toYYY()const
{
    return Vector3i(y, y, y);
}

//------------------------------------------------------------------------------
const Vector4iPOD Vector2iPOD::toXY00()const
{
    return Vector4i(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4iPOD Vector2iPOD::toXXXX()const
{
    return Vector4i(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4iPOD Vector2iPOD::toYYYY()const
{
    return Vector4i(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector2POD Vector2iPOD::toXYf()const
{
    return Vector2(f32(x), f32(y));
}

//------------------------------------------------------------------------------
bool Vector2iPOD::equals(const Vector2iPOD& aVec)const
{
    return x == aVec.x
        && y == aVec.y;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::add(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::sub(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::mul(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::div(const s32 aVal)const
{
    Vector2i vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::add(const Vector2iPOD& aVal)const
{
    Vector2i vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::sub(const Vector2iPOD& aVal)const
{
    Vector2i vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::mul(const Vector2iPOD& aVal)const
{
    Vector2i vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::div(const Vector2iPOD& aVal)const
{
    Vector2i vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector2iPOD::addAssign(const s32 aVal)
{
    x += aVal;
    y += aVal;
}

//------------------------------------------------------------------------------
void Vector2iPOD::subAssign(const s32 aVal)
{
    x -= aVal;
    y -= aVal;
}

//------------------------------------------------------------------------------
void Vector2iPOD::mulAssign(const s32 aVal)
{
    x *= aVal;
    y *= aVal;
}

//------------------------------------------------------------------------------
void Vector2iPOD::divAssign(const s32 aVal)
{
    if (aVal == 0) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }
    x /= aVal;
    y /= aVal;
}

//------------------------------------------------------------------------------
void Vector2iPOD::addAssign(const Vector2iPOD& aVal)
{
    x += aVal.x;
    y += aVal.y;
}

//------------------------------------------------------------------------------
void Vector2iPOD::subAssign(const Vector2iPOD& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2iPOD::mulAssign(const Vector2iPOD& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
}

//------------------------------------------------------------------------------
void Vector2iPOD::divAssign(const Vector2iPOD& aVal)
{
    XBASE_DIV_ASSIGN(x, aVal.x);
    XBASE_DIV_ASSIGN(y, aVal.y);
}

//------------------------------------------------------------------------------
Vector2iPOD& Vector2iPOD::operator+=(const s32 aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPOD& Vector2iPOD::operator-=(const s32 aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPOD& Vector2iPOD::operator*=(const s32 aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPOD& Vector2iPOD::operator/=(const s32 aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPOD& Vector2iPOD::operator+=(const Vector2iPOD& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPOD& Vector2iPOD::operator-=(const Vector2iPOD& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPOD& Vector2iPOD::operator*=(const Vector2iPOD& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector2iPOD& Vector2iPOD::operator/=(const Vector2iPOD& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::operator+(const s32 aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::operator-(const s32 aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::operator*(const s32 aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::operator/(const s32 aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::operator+(const Vector2iPOD& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::operator-(const Vector2iPOD& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::operator*(const Vector2iPOD& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::operator/(const Vector2iPOD& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::operator-()const
{
    return neg();
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::min(const Vector2iPOD& aVal)const
{
    return Vector2i(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::max(const Vector2iPOD& aVal)const
{
    return Vector2i(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y)
        );
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::clamp(
    const Vector2iPOD& aMin,
    const Vector2iPOD& aMax
)const
{
    return max(aMin).min(aMax);
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::clampPositive()const
{
    return max(Zero());
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::clampNegative()const
{
    return min(Zero());
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::abs()const
{
    return Vector2i(
        Math::AbsS32(x),
        Math::AbsS32(y)
        );
}

//------------------------------------------------------------------------------
const Vector2iPOD Vector2iPOD::neg()const
{
    Vector2i vec(*this);
    vec.mulAssign(-1);
    return vec;
}

//------------------------------------------------------------------------------
bool Vector2iPOD::isPositive()const
{
    return 0 <= x
        && 0 <= y;
}

//------------------------------------------------------------------------------
bool Vector2iPOD::isZero()const
{
    return x == 0 && y == 0;
}

//------------------------------------------------------------------------------
const ::XBase::ShortString Vector2iPOD::toShortString()const
{
    return ::XBase::ShortString::FromFormat(
        "%s,%s",
        S32(x).toShortString().readPtr(),
        S32(y).toShortString().readPtr()
        );
}

//------------------------------------------------------------------------------
Vector2i::Vector2i()
: Vector2iPOD(Zero())
{
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const Vector2iPOD& aVec)
: Vector2iPOD(aVec)
{
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const s32 aV)
{
    x = aV;
    y = aV;
}

//------------------------------------------------------------------------------
Vector2i::Vector2i(const s32 aX, const s32 aY)
{
    x = aX;
    y = aY;
}

} // namespace
// EOF
