// 文字コード：UTF-8
#include <XBase/Color4b.hpp>

//------------------------------------------------------------------------------
#include <XBase/Color4.hpp>
#include <XBase/DivideCheck.hpp>
#include <XBase/Math.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/ScalerTypes.hpp>

//------------------------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::Zero()
{
    return Color4b(0, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::One()
{
    return Color4b(0xFF, 0xFF, 0xFF, 0xFF);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::UnitR()
{
    return Color4b(0xFF, 0, 0, 0);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::UnitG()
{
    return Color4b(0, 0xFF, 0, 0);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::UnitB()
{
    return Color4b(0, 0, 0xFF, 0);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::UnitA()
{
    return Color4b(0, 0, 0, 0xFF);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::toRRRR()const
{
    return Color4b(r, r, r, r);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::toGGGG()const
{
    return Color4b(g, g, g, g);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::toBBBB()const
{
    return Color4b(b, b, b, b);
}

//------------------------------------------------------------------------------
const Color4bPOD Color4bPOD::toAAAA()const
{
    return Color4b(a, a, a, a);
}

//------------------------------------------------------------------------------
const Color4POD Color4bPOD::toRGBAf()const
{
    const float rate = 1.0f / 255.0f;
    return Color4(r * rate, g * rate, b * rate, a * rate);
}

//------------------------------------------------------------------------------
const ::XBase::ShortString Color4bPOD::toShortString()const
{
    return ::XBase::ShortString::FromFormat(
        "%s,%s,%s,%s"
        , U8(r).toShortString().readPtr()
        , U8(g).toShortString().readPtr()
        , U8(b).toShortString().readPtr()
        , U8(a).toShortString().readPtr()
    );
}

//------------------------------------------------------------------------------
Color4b::Color4b()
    : Color4bPOD(Zero())
{
}

//------------------------------------------------------------------------------
Color4b::Color4b(const Color4bPOD& aCol)
    : Color4bPOD(aCol)
{
}

//------------------------------------------------------------------------------
Color4b::Color4b(const u8 aR, const u8 aG, const u8 aB, const u8 aA)
{
    r = aR;
    g = aG;
    b = aB;
    a = aA;
}

} // namespace
// EOF
