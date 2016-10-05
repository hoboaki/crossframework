// 文字コード：UTF-8
#include <XBase/Vector4.hpp>

//------------------------------------------------------------------------------
#include <XBase/DivideCheck.hpp>
#include <XBase/Infinity.hpp>
#include <XBase/Math.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/ScalerTypes.hpp>
#include <XBase/Vector2.hpp>
#include <XBase/Vector3.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Zero()
{
    Vector4Pod obj = {};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::One()
{
    Vector4Pod obj = {1, 1, 1, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Min()
{
    Vector4Pod obj = {-XBASE_INFINITY, -XBASE_INFINITY, -XBASE_INFINITY, -XBASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::Max()
{
    Vector4Pod obj = {XBASE_INFINITY, XBASE_INFINITY, XBASE_INFINITY, XBASE_INFINITY};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitX()
{
    Vector4Pod obj = {1, 0, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitY()
{
    Vector4Pod obj = {0, 1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitZ()
{
    Vector4Pod obj = {0, 0, 1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::UnitW()
{
    Vector4Pod obj = {0, 0, 0, 1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitX()
{
    Vector4Pod obj = {-1, 0, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitY()
{
    Vector4Pod obj = {0, -1, 0, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitZ()
{
    Vector4Pod obj = {0, 0, -1, 0};
    return obj;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::NegUnitW()
{
    Vector4Pod obj = {0, 0, 0, -1};
    return obj;
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::toXY()const
{
    return Vector2(x, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::toXX()const
{
    return Vector2(x, x);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::toYY()const
{
    return Vector2(y, y);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::toZZ()const
{
    return Vector2(z, z);
}

//------------------------------------------------------------------------------
const Vector2Pod Vector4Pod::toWW()const
{
    return Vector2(w, w);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toXYZ()const
{
    return Vector3(x, y, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toXXX()const
{
    return Vector3(x, x, x);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toYYY()const
{
    return Vector3(y, y, y);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toZZZ()const
{
    return Vector3(z, z, z);
}

//------------------------------------------------------------------------------
const Vector3Pod Vector4Pod::toWWW()const
{
    return Vector3(w, w, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toXYZ0()const
{
    return Vector4(x, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toXY0W()const
{
    return Vector4(x, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toXY00()const
{
    return Vector4(x, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toX0ZW()const
{
    return Vector4(x, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toX0Z0()const
{
    return Vector4(x, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toX00W()const
{
    return Vector4(x, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toX000()const
{
    return Vector4(x, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to0YZ0()const
{
    return Vector4(0, y, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to0Y0W()const
{
    return Vector4(0, y, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to0Y00()const
{
    return Vector4(0, y, 0, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to00ZW()const
{
    return Vector4(0, 0, z, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to00Z0()const
{
    return Vector4(0, 0, z, 0);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::to000W()const
{
    return Vector4(0, 0, 0, w);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toXXXX()const
{
    return Vector4(x, x, x, x);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toYYYY()const
{
    return Vector4(y, y, y, y);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toZZZZ()const
{
    return Vector4(z, z, z, z);
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::toWWWW()const
{
    return Vector4(w, w, w, w);
}

//------------------------------------------------------------------------------
bool Vector4Pod::equals(const Vector4Pod& aVec)const
{
    return Math::IsEqualsF32(x, aVec.x)
        && Math::IsEqualsF32(y, aVec.y)
        && Math::IsEqualsF32(z, aVec.z)
        && Math::IsEqualsF32(w, aVec.w);
}

//------------------------------------------------------------------------------
bool Vector4Pod::equalsStrict(const Vector4Pod& aVec)const
{
    return x == aVec.x && y == aVec.y && z == aVec.z && w == aVec.w;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::add(const float aVal)const
{
    Vector4 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4Pod Vector4Pod::sub(const float aVal)const
{
    Vector4 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::mul(const float aVal)const
{
    Vector4 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::div(const float aVal)const
{
    Vector4 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::add(const Vector4POD& aVal)const
{
    Vector4 vec(*this);
    vec.addAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::sub(const Vector4POD& aVal)const
{
    Vector4 vec(*this);
    vec.subAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::mul(const Vector4POD& aVal)const
{
    Vector4 vec(*this);
    vec.mulAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::div(const Vector4POD& aVal)const
{
    Vector4 vec(*this);
    vec.divAssign(aVal);
    return vec;
}

//------------------------------------------------------------------------------
void Vector4POD::addAssign(const float aVal)
{
    x += aVal;
    y += aVal;
    z += aVal;
    w += aVal;
}

//------------------------------------------------------------------------------
void Vector4POD::subAssign(const float aVal)
{
    x -= aVal;
    y -= aVal;
    z -= aVal;
    w -= aVal;
}

//------------------------------------------------------------------------------
void Vector4POD::mulAssign(const float aVal)
{
    x *= aVal;
    y *= aVal;
    z *= aVal;
    w *= aVal;
}

//------------------------------------------------------------------------------
void Vector4POD::divAssign(const float aVal)
{
    if (aVal == 0) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }
    mulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Vector4POD::addAssign(const Vector4POD& aVal)
{
    x += aVal.x;
    y += aVal.y;
    z += aVal.z;
    w += aVal.w;
}

//------------------------------------------------------------------------------
void Vector4POD::subAssign(const Vector4POD& aVal)
{
    x -= aVal.x;
    y -= aVal.y;
    z -= aVal.z;
    w -= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4POD::mulAssign(const Vector4POD& aVal)
{
    x *= aVal.x;
    y *= aVal.y;
    z *= aVal.z;
    w *= aVal.w;
}

//------------------------------------------------------------------------------
void Vector4POD::divAssign(const Vector4POD& aVal)
{
    XBASE_DIV_ASSIGN(x, aVal.x);
    XBASE_DIV_ASSIGN(y, aVal.y);
    XBASE_DIV_ASSIGN(z, aVal.z);
    XBASE_DIV_ASSIGN(w, aVal.w);
}

//------------------------------------------------------------------------------
Vector4POD& Vector4POD::operator+=(const float aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4POD& Vector4POD::operator-=(const float aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4POD& Vector4POD::operator*=(const float aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4POD& Vector4POD::operator/=(const float aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4POD& Vector4POD::operator+=(const Vector4POD& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4POD& Vector4POD::operator-=(const Vector4POD& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4POD& Vector4POD::operator*=(const Vector4POD& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Vector4POD& Vector4POD::operator/=(const Vector4POD& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::operator+(const float aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::operator-(const float aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::operator*(const float aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::operator/(const float aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::operator+(const Vector4POD& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::operator-(const Vector4POD& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::operator*(const Vector4POD& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::operator/(const Vector4POD& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::operator-()const
{
    return neg();
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::min(const Vector4POD& aVal)const
{
    return Vector4(
        Math::Min(x, aVal.x),
        Math::Min(y, aVal.y),
        Math::Min(z, aVal.z),
        Math::Min(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::max(const Vector4POD& aVal)const
{
    return Vector4(
        Math::Max(x, aVal.x),
        Math::Max(y, aVal.y),
        Math::Max(z, aVal.z),
        Math::Max(w, aVal.w)
        );
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::clamp(
    const Vector4POD& aMin,
    const Vector4POD& aMax
)const
{
    return max(aMin).min(aMax);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::clampPositive()const
{
    return max(Zero());
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::clampNegative()const
{
    return min(Zero());
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::abs()const
{
    return Vector4(
        Math::AbsF32(x),
        Math::AbsF32(y),
        Math::AbsF32(z),
        Math::AbsF32(w)
        );
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::neg()const
{
    Vector4 vec(*this);
    vec.mulAssign(-1.0f);
    return vec;
}

//------------------------------------------------------------------------------
f32 Vector4POD::squareLength()const
{
    return x * x + y * y + z * z + w * w;
}

//------------------------------------------------------------------------------
f32 Vector4POD::length()const
{
    return Math::SqrtF32(squareLength());
}

//------------------------------------------------------------------------------
f32 Vector4POD::distance(const Vector4POD& aVal)const
{
    return sub(aVal).length();
}

//------------------------------------------------------------------------------
bool Vector4POD::isZero()const
{
    return Math::IsZeroF32(length());
}

//------------------------------------------------------------------------------
bool Vector4POD::isZeroStrict()const
{
    return x == 0 && y == 0 && z == 0 && w == 0;
}

//------------------------------------------------------------------------------
bool Vector4POD::isUnit()const
{
    return Math::IsEqualsF32(length(), 1.0f);
}

//------------------------------------------------------------------------------
const Vector4POD Vector4POD::unit()const
{
    Vector4 vec(*this);
    vec.unitAssign();
    return vec;
}

//------------------------------------------------------------------------------
void Vector4POD::unitAssign()
{
    if (isZeroStrict()) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }
    mulAssign(1.0f / length());
}

//------------------------------------------------------------------------------
f32 Vector4POD::dot(const Vector4POD& aVec)const
{
    return x * aVec.x + y * aVec.y + z * aVec.z + w * aVec.w;
}

//------------------------------------------------------------------------------
const ::XBase::ShortString Vector4POD::toShortString()const
{
    return ::XBase::ShortString::FromFormat(
        "%s,%s,%s,%s",
        F32(x).toShortString().readPtr(),
        F32(y).toShortString().readPtr(),
        F32(z).toShortString().readPtr(),
        F32(w).toShortString().readPtr()
        );
}

//------------------------------------------------------------------------------
Vector4::Vector4()
: Vector4POD(Zero())
{
}

//------------------------------------------------------------------------------
Vector4::Vector4(const Vector4POD& aVec)
: Vector4POD(aVec)
{
}

//------------------------------------------------------------------------------
Vector4::Vector4(const float aV)
{
    x = aV;
    y = aV;
    z = aV;
    w = aV;
}

//------------------------------------------------------------------------------
Vector4::Vector4(const Vector2POD& aXY, const float aZ, const float aW)
{
    x = aXY.x;
    y = aXY.y;
    z = aZ;
    w = aW;
}

//------------------------------------------------------------------------------
Vector4::Vector4(const Vector3POD& aXYZ, const float aW)
{
    x = aXYZ.x;
    y = aXYZ.y;
    z = aXYZ.z;
    w = aW;
}

//------------------------------------------------------------------------------
Vector4::Vector4(const float aX, const float aY, const float aZ, const float aW)
{
    x = aX;
    y = aY;
    z = aZ;
    w = aW;
}

} // namespace
// EOF
