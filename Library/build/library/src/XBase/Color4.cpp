// 文字コード：UTF-8
#include <XBase/Color4.hpp>

//------------------------------------------------------------------------------
#include <XBase/Color4b.hpp>
#include <XBase/DivideCheck.hpp>
#include <XBase/Math.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/ScalerTypes.hpp>
#include <XBase/Vector4.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
const Color4POD Color4POD::Zero()
{
    return Color4(0, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::One()
{
    return Color4(1, 1, 1, 1);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::UnitR()
{
    return Color4(1, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::UnitG()
{
    return Color4(0, 1, 0, 0);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::UnitB()
{
    return Color4(0, 0, 1, 0);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::UnitA()
{
    return Color4(0, 0, 0, 1);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::toRRRR()const
{
    return Color4(r, r, r, r);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::toGGGG()const
{
    return Color4(g, g, g, g);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::toBBBB()const
{
    return Color4(b, b, b, b);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::toAAAA()const
{
    return Color4(a, a, a, a);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4POD::toRGBAb()const
{
    const Color4 tmp = toVector4().clamp(Vector4::Zero(), Vector4::One()) * 255.0f;
    return Color4b(
        static_cast<u8>(tmp.r),
        static_cast<u8>(tmp.g),
        static_cast<u8>(tmp.b),
        static_cast<u8>(tmp.a)
        );
}

//------------------------------------------------------------------------------
const Vector4POD Color4POD::toVector4()const
{
    return Vector4(r, g, b, a);
}

//------------------------------------------------------------------------------
bool Color4POD::equals(const Color4POD& aRHS)const
{
    return Math::IsEqualsF32(r, aRHS.r)
        && Math::IsEqualsF32(g, aRHS.g)
        && Math::IsEqualsF32(b, aRHS.b)
        && Math::IsEqualsF32(a, aRHS.a);
}

//------------------------------------------------------------------------------
bool Color4POD::equalsStrict(const Color4POD& aRHS)const
{
    return r == aRHS.r
        && g == aRHS.g
        && b == aRHS.b
        && a == aRHS.a;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::add(const float aVal)const
{
    Color4 col(*this);
    col.addAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::sub(const float aVal)const
{
    Color4 col(*this);
    col.subAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::mul(const float aVal)const
{
    Color4 col(*this);
    col.mulAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::div(const float aVal)const
{
    Color4 col(*this);
    col.divAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::add(const Color4POD& aVal)const
{
    Color4 col(*this);
    col.addAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::sub(const Color4POD& aVal)const
{
    Color4 col(*this);
    col.subAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::mul(const Color4POD& aVal)const
{
    Color4 col(*this);
    col.mulAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::div(const Color4POD& aVal)const
{
    Color4 col(*this);
    col.divAssign(aVal);
    return col;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::neg()const
{
    Color4 col(*this);
    col.mulAssign(-1.0f);
    return col;
}

//------------------------------------------------------------------------------
void Color4POD::addAssign(const float aVal)
{
    r += aVal;
    g += aVal;
    b += aVal;
    a += aVal;
}

//------------------------------------------------------------------------------
void Color4POD::subAssign(const float aVal)
{
    r -= aVal;
    g -= aVal;
    b -= aVal;
    a -= aVal;
}

//------------------------------------------------------------------------------
void Color4POD::mulAssign(const float aVal)
{
    r *= aVal;
    g *= aVal;
    b *= aVal;
    a *= aVal;
}

//------------------------------------------------------------------------------
void Color4POD::divAssign(const float aVal)
{
    if (aVal == 0) {
        XBASE_NOT_REACH_ASSERT();
        return;
    }
    mulAssign(1.0f / aVal);
}

//------------------------------------------------------------------------------
void Color4POD::addAssign(const Color4POD& aVal)
{
    r += aVal.r;
    g += aVal.g;
    b += aVal.b;
    a += aVal.a;
}

//------------------------------------------------------------------------------
void Color4POD::subAssign(const Color4POD& aVal)
{
    r -= aVal.r;
    g -= aVal.g;
    b -= aVal.b;
    a -= aVal.a;
}

//------------------------------------------------------------------------------
void Color4POD::mulAssign(const Color4POD& aVal)
{
    r *= aVal.r;
    g *= aVal.g;
    b *= aVal.b;
    a *= aVal.a;
}

//------------------------------------------------------------------------------
void Color4POD::divAssign(const Color4POD& aVal)
{
    XBASE_DIV_ASSIGN(r, aVal.r);
    XBASE_DIV_ASSIGN(g, aVal.g);
    XBASE_DIV_ASSIGN(b, aVal.b);
    XBASE_DIV_ASSIGN(a, aVal.a);
}

//------------------------------------------------------------------------------
Color4POD& Color4POD::operator+=(const float aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4POD& Color4POD::operator-=(const float aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4POD& Color4POD::operator*=(const float aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4POD& Color4POD::operator/=(const float aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4POD& Color4POD::operator+=(const Color4POD& aVal)
{
    addAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4POD& Color4POD::operator-=(const Color4POD& aVal)
{
    subAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4POD& Color4POD::operator*=(const Color4POD& aVal)
{
    mulAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
Color4POD& Color4POD::operator/=(const Color4POD& aVal)
{
    divAssign(aVal);
    return *this;
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::operator+(const float aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::operator-(const float aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::operator*(const float aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::operator/(const float aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::operator+(const Color4POD& aVal)const
{
    return add(aVal);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::operator-(const Color4POD& aVal)const
{
    return sub(aVal);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::operator*(const Color4POD& aVal)const
{
    return mul(aVal);
}

//------------------------------------------------------------------------------
const Color4POD Color4POD::operator/(const Color4POD& aVal)const
{
    return div(aVal);
}

//------------------------------------------------------------------------------
const ::XBase::ShortString Color4POD::toShortString()const
{
    return ::XBase::ShortString::FromFormat(
        "%s,%s,%s,%s",
        F32(r).toShortString().readPtr(),
        F32(g).toShortString().readPtr(),
        F32(b).toShortString().readPtr(),
        F32(a).toShortString().readPtr()
        );
}

//------------------------------------------------------------------------------
Color4::Color4()
: Color4POD(Zero())
{
}

//------------------------------------------------------------------------------
Color4::Color4(const Color4POD& aCol)
: Color4POD(aCol)
{
}

//------------------------------------------------------------------------------
Color4::Color4(const float aR, const float aG, const float aB, const float aA)
{
    r = aR;
    g = aG;
    b = aB;
    a = aA;
}

//------------------------------------------------------------------------------
Color4::Color4(const Vector4POD& aVec)
{
    r = aVec.x;
    g = aVec.y;
    b = aVec.z;
    a = aVec.w;
}

} // namespace
// EOF
