// 文字コード：UTF-8
#include <ae/g3d/TexSetting.hpp>

#include <ae/base/EnumCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/TexBuffer.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
TexSetting::TexSetting()
: mExt()
, mIsActive(false)
, mMinFilter(TexFilter::Nearest)
, mMagFilter(TexFilter::Nearest)
, mAddressU(TexAddress::Wrap)
, mAddressV(TexAddress::Wrap)
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
    return mExt.texId != 0;
}

//------------------------------------------------------------------------------
void TexSetting::bindBuffer(const TexBuffer& aBuffer)
{
    mExt.texId = aBuffer.ext_().texId;
}

//------------------------------------------------------------------------------
void TexSetting::unbindBuffer()
{
    mExt.texId = 0;
}

//------------------------------------------------------------------------------
TexFilter::EnumType TexSetting::minFilter()const
{
    return mMinFilter;
}

//------------------------------------------------------------------------------
void TexSetting::setMinFilter(const TexFilter::EnumType aFilter)
{
    if (AE_BASE_ENUM_IS_INVALID(TexFilter, aFilter)) {
        AE_BASE_ERROR_INVALID_ENUM(int(aFilter));
        return;
    }
    mMinFilter = aFilter;
}

//------------------------------------------------------------------------------
TexFilter::EnumType TexSetting::magFilter()const
{
    return mMagFilter;
}

//------------------------------------------------------------------------------
void TexSetting::setMagFilter(const TexFilter::EnumType aFilter)
{
    if (AE_BASE_ENUM_IS_INVALID(TexFilter, aFilter)) {
        AE_BASE_ERROR_INVALID_ENUM(int(aFilter));
        return;
    }
    mMagFilter = aFilter;
}

//------------------------------------------------------------------------------
TexAddress::EnumType TexSetting::addressU()const
{
    return mAddressU;
}

//------------------------------------------------------------------------------
void TexSetting::setAddressU(const TexAddress::EnumType aAddress)
{
    if (AE_BASE_ENUM_IS_INVALID(TexAddress, aAddress)) {
        AE_BASE_ERROR_INVALID_ENUM(int(aAddress));
        return;
    }
    mAddressU = aAddress;
}

//------------------------------------------------------------------------------
TexAddress::EnumType TexSetting::addressV()const
{
    return mAddressV;
}

//------------------------------------------------------------------------------
void TexSetting::setAddressV(const TexAddress::EnumType aAddress)
{
    if (AE_BASE_ENUM_IS_INVALID(TexAddress, aAddress)) {
        AE_BASE_ERROR_INVALID_ENUM(int(aAddress));
        return;
    }
    mAddressV = aAddress;
}

//------------------------------------------------------------------------------
TexSetting_EXT& TexSetting::ext_()
{
    return mExt;
}

//------------------------------------------------------------------------------
const TexSetting_EXT& TexSetting::ext_()const
{
    return mExt;
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

}} // namespace
// EOF
