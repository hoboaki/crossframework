// 文字コード：UTF-8
#include "ResTexImpl.hpp"

#include <ae/base/EnumCheck.hpp>
#include <ae/base/FunctionAttribute.hpp>
#include <ae/base/Ref.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/TexResData.hpp>
#include <ae/g3d/ResTexFormat.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
ResTexImpl::ResTexImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResTex* aBinPtr,
    ::ae::base::IAllocator&
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
, texBufferPtr(0)
, mTexBuffer()
{
}

//------------------------------------------------------------------------------
ResTexImpl::~ResTexImpl()
{
}

//------------------------------------------------------------------------------
void ResTexImpl::setup()
{
    // セットアップ済みなら何もしない
    if (texBufferPtr != 0) {
        return;
    }

    // 変数用意
    TexResData data = {};
    data.format = format();
    data.width = binPtr->width;;
    data.height = binPtr->height;
    data.pixels = pixels();

    // 作成
    mTexBuffer.init(::ae::base::Ref(data));
    texBufferPtr = mTexBuffer.ptr();
}

//------------------------------------------------------------------------------
ResTexFormat::EnumType ResTexImpl::format()const
{
    ResTexFormat::EnumType fmt = ResTexFormat::EnumType(binPtr->format);
    if (AE_BASE_ENUM_IS_INVALID(ResTexFormat, fmt)) {
        AE_BASE_ASSERT_NOT_REACHED();
        return ResTexFormat::EnumType(0);
    }
    return ResTexFormat::EnumType(fmt);
}

//------------------------------------------------------------------------------
const byte_t* ResTexImpl::pixels()const
{
    return xdata.ref< byte_t >(binPtr->pixels);
}

}} // namespace
// EOF
