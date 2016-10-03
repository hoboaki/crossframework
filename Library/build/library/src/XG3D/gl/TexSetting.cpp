// 文字コード：UTF-8
#include <XG3D/TexSetting.hpp>

//------------------------------------------------------------------------------
#include <XBase/EnumCheck.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/TexBuffer.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
TexSetting::TexSetting()
: mEXT()
, mIsActive(false)
, mMinFilter(TexFilter_Nearest)
, mMagFilter(TexFilter_Nearest)
, mAddressU(TexAddress_Wrap)
, mAddressV(TexAddress_Wrap)
{
}

//------------------------------------------------------------------------------
bool TexSetting::isActive()const
{
    return mIsActive;
}

//------------------------------------------------------------------------------
void TexSetting::setIsActive(const bool aIsActive)
{
    mIsActive = aIsActive;
}

//------------------------------------------------------------------------------
bool TexSetting::isBoundBuffer()const
{
    return mEXT.texId != 0;
}

//------------------------------------------------------------------------------
void TexSetting::bindBuffer(const TexBuffer& aBuffer)
{
    mEXT.texId = aBuffer.ext_().texId;
}

//------------------------------------------------------------------------------
void TexSetting::unbindBuffer()
{
    mEXT.texId = 0;
}

//------------------------------------------------------------------------------
TexFilter TexSetting::minFilter()const
{
    return mMinFilter;
}

//------------------------------------------------------------------------------
void TexSetting::setMinFilter(const TexFilter aFilter)
{
    if (XBASE_ENUM_IS_INVALID(TexFilter, aFilter)) {
        XBASE_ERROR_INVALID_ENUM(int(aFilter));
        return;
    }
    mMinFilter = aFilter;
}

//------------------------------------------------------------------------------
TexFilter TexSetting::magFilter()const
{
    return mMagFilter;
}

//------------------------------------------------------------------------------
void TexSetting::setMagFilter(const TexFilter aFilter)
{
    if (XBASE_ENUM_IS_INVALID(TexFilter, aFilter)) {
        XBASE_ERROR_INVALID_ENUM(int(aFilter));
        return;
    }
    mMagFilter = aFilter;
}

//------------------------------------------------------------------------------
TexAddress TexSetting::addressU()const
{
    return mAddressU;
}

//------------------------------------------------------------------------------
void TexSetting::setAddressU(const TexAddress aAddress)
{
    if (XBASE_ENUM_IS_INVALID(TexAddress, aAddress)) {
        XBASE_ERROR_INVALID_ENUM(int(aAddress));
        return;
    }
    mAddressU = aAddress;
}

//------------------------------------------------------------------------------
TexAddress TexSetting::addressV()const
{
    return mAddressV;
}

//------------------------------------------------------------------------------
void TexSetting::setAddressV(const TexAddress aAddress)
{
    if (XBASE_ENUM_IS_INVALID(TexAddress, aAddress)) {
        XBASE_ERROR_INVALID_ENUM(int(aAddress));
        return;
    }
    mAddressV = aAddress;
}

//------------------------------------------------------------------------------
TexSetting_EXT& TexSetting::ext_()
{
    return mEXT;
}

//------------------------------------------------------------------------------
const TexSetting_EXT& TexSetting::ext_()const
{
    return mEXT;
}

//------------------------------------------------------------------------------
TexSetting_EXT::TexSetting_EXT()
: texId(0)
{
}

//------------------------------------------------------------------------------
TexSetting_EXT::~TexSetting_EXT()
{
}

} // namespace
// EOF
