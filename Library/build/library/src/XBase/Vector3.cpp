// 文字コード：UTF-8
#include <XBase/Vector3.hpp>

//------------------------------------------------------------------------------
#include <XBase/DivideCheck.hpp>
#include <XBase/Infinity.hpp>
#include <XBase/Math.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/ScalerTypes.hpp>
#include <XBase/Vector2.hpp>
#include <XBase/Vector4.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::Zero()
{
    Vector3POD obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::One()
{
    Vector3POD obj = {1, 1, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::Min()
{
    Vector3POD obj = {-XBASE_INFINITY, -XBASE_INFINITY, -XBASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::Max()
{
    Vector3POD obj = {XBASE_INFINITY, XBASE_INFINITY, XBASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::UnitX()
{
    Vector3POD obj = {1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::UnitY()
{
    Vector3POD obj = {0, 1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::UnitZ()
{
    Vector3POD obj = {0, 0, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::NegUnitX()
{
    Vector3POD obj = {-1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::NegUnitY()
{
    Vector3POD obj = {0, -1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::NegUnitZ()
{
    Vector3POD obj = {0, 0, -1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2POD Vector3POD::toXY()const
{
    return Vector2(x, y);
}

//------------------------------------------------------------------------------
const Vector2POD Vector3POD::toXX()const
{
    return Vector2(x, x);
}

//------------------------------------------------------------------------------
const Vector2POD Vector3POD::toYY()const
{
    return Vector2(y, y);
}

//------------------------------------------------------------------------------
const Vector2POD Vector3POD::toZZ()const
{
    return Vector2(z, z);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::toX00()const
{
    return Vector3(x, 0, 0);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::toXY0()const
{
    return Vector3(x, y, 0);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::to0Y0()const
{
    return Vector3(0, y, 0);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::to0YZ()const
{
    return Vector3(0, y, z);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::to00Z()const
{
    return Vector3(0, 0, z);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::toXXX()const
{
    return Vector3(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::toYYY()const
{
    return Vector3(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::toZZZ()const
{
    return Vector3(z, z, z);
}

//------------------------------------------------------------------------------
const Vector4POD Vector3POD::toXYZ0()const
{
    return Vector4(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4POD Vector3POD::toXXXX()const
{
    return Vector4(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4POD Vector3POD::toYYYY()const
{
    return Vector4(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4POD Vector3POD::toZZZZ()const
{
    return Vector4(z, z, z, z);
}

//------------------------------------------------------------------------------
bool Vector3POD::equals(const Vector3POD& aVec)const
{
    return Math::IsEqualsF32(x, aVec.x)
        && Math::IsEqualsF32(y, aVec.y)
        && Math::IsEqualsF32(z, aVec.z);
}

//------------------------------------------------------------------------------
bool Vector3POD::equalsStrict(const Vector3POD& aVec)const
{
    return x == aVec.x && y == aVec.y && z == aVec.z;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::add(const float aVal)const
{
    Vector3 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::sub(const float aVal)const
{
    Vector3 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::mul(const float aVal)const
{
    Vector3 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::div(const float aVal)const
{
    Vector3 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::add(const Vector3POD& aVal)const
{
    Vector3 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::sub(const Vector3POD& aVal)const
{
    Vector3 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::mul(const Vector3POD& aVal)const
{
    Vector3 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::div(const Vector3POD& aVal)const
{
    Vector3 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector3POD::addAssign(const float aVal)
{
    x += aVal;
    y += aVal;
    z += aVal;
}

//------------------------------------------------------------------------------
void Vector3POD::subAssign(const float aVal)
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
}

//------------------------------------------------------------------------------
void Vector3POD::mulAssign(const float aVal)
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
}

//------------------------------------------------------------------------------
void Vector3POD::divAssign(const float aVal)
{
    if (aVal == 0)
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    mulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Vector3POD::addAssign(const Vector3POD& aVal)
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
}

//------------------------------------------------------------------------------
void Vector3POD::subAssign(const Vector3POD& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
}

//------------------------------------------------------------------------------
void Vector3POD::mulAssign(const Vector3POD& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
}

//------------------------------------------------------------------------------
void Vector3POD::divAssign(const Vector3POD& aVal)
{
    XBASE_DIV_ASSIGN(x, aVal.x);
    XBASE_DIV_ASSIGN(y, aVal.y);
    XBASE_DIV_ASSIGN(z, aVal.z);
}

//------------------------------------------------------------------------------
Vector3POD& Vector3POD::operator+=(const float aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3POD& Vector3POD::operator-=(const float aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3POD& Vector3POD::operator*=(const float aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3POD& Vector3POD::operator/=(const float aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3POD& Vector3POD::operator+=(const Vector3POD& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3POD& Vector3POD::operator-=(const Vector3POD& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3POD& Vector3POD::operator*=(const Vector3POD& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector3POD& Vector3POD::operator/=(const Vector3POD& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::operator+(const float aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::operator-(const float aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::operator*(const float aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::operator/(const float aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::operator+(const Vector3POD& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::operator-(const Vector3POD& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::operator*(const Vector3POD& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::operator/(const Vector3POD& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::operator-()const
{
    return neg();
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::min(const Vector3POD& aVal)const
{
    return Vector3(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y),
        Math::Min(z, aVal.z)
        );
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::max(const Vector3POD& aVal)const
{
    return Vector3(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y),
        Math::Max(z, aVal.z)
        );
}


//------------------------------------------------------------------------------
const Vector3POD Vector3POD::clamp(
    const Vector3POD& aMin,
    const Vector3POD& aMax
)const
{
    return max(aMin).min(aMax);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::clampPositive()const
{
    return max(Zero());
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::clampNegative()const
{
    return min(Zero());
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::abs()const
{
    return Vector3(
        Math::AbsF32(x),
        Math::AbsF32(y),
        Math::AbsF32(z)
        );
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::neg()const
{
    Vector3 vec(*this);
    vec.mulAssign(-1.0f);
    return vec;
}

//------------------------------------------------------------------------------
f32 Vector3POD::squareLength()const
{
    return x * x + y * y + z * z;
}

//------------------------------------------------------------------------------
f32 Vector3POD::length()const
{
    return Math::SqrtF32(squareLength());
}

//------------------------------------------------------------------------------
f32 Vector3POD::distance(const Vector3POD& aVal)const
{
    return sub(aVal).length();
}

//------------------------------------------------------------------------------
bool Vector3POD::isZero()const
{
    return Math::IsZeroF32(length());
}

//------------------------------------------------------------------------------
bool Vector3POD::isZeroStrict()const
{
    return x == 0 && y == 0 && z == 0;
}

//------------------------------------------------------------------------------
bool Vector3POD::isUnit()const
{
    return Math::IsEqualsF32(length(), 1.0f);
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::unit()const
{
    Vector3 vec(*this);
    vec.unitAssign();
    return vec;
}

//------------------------------------------------------------------------------
void Vector3POD::unitAssign()
{
    if (isZeroStrict())
    {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    mulAssign(1.0f / length());
}

//------------------------------------------------------------------------------
f32 Vector3POD::dot(const Vector3POD& aVec)const
{
    return x * aVec.x + y * aVec.y + z * aVec.z;
}

//------------------------------------------------------------------------------
const Vector3POD Vector3POD::cross(const Vector3POD& aVec)const
{
    return Vector3(
        y * aVec.z - z * aVec.y,
        z * aVec.x - x * aVec.z,
        x * aVec.y - y * aVec.x
        );
}

//------------------------------------------------------------------------------
const ::XBase::ShortString Vector3POD::toShortString()const
{
    return ::XBase::ShortString::FromFormat(
        "%s,%s,%s",
        F32(x).toShortString().readPtr(),
        F32(y).toShortString().readPtr(),
        F32(z).toShortString().readPtr()
        );
}

//------------------------------------------------------------------------------
Vector3::Vector3()
: Vector3POD(Zero())
{
}

//------------------------------------------------------------------------------
Vector3::Vector3(const Vector3POD& aVec)
: Vector3POD(aVec)
{
}

//------------------------------------------------------------------------------
Vector3::Vector3(const float aV)
{
    x = aV;
    y = aV;
    z = aV;
}

//------------------------------------------------------------------------------
Vector3::Vector3(const Vector2POD& aXY, const float aZ)
{
    x = aXY.x;
    y = aXY.y;
    z = aZ;
}

//------------------------------------------------------------------------------
Vector3::Vector3(const float aX, const float aY, const float aZ)
{
    x = aX;
    y = aY;
    z = aZ;
}

} // namespace
// EOF
