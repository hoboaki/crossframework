// 文字コード：UTF-8
#include <XG3D/RuntimeTex.hpp>

#include <XBase/RuntimeAssert.hpp>
#include <XBase/Unused.hpp>
#include <XG3D/TexResData.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
namespace {

int tBytePerPixel(const ::XG3D::ResTexFormat::EnumType aFormat)
{
    int bytePerPix = 0;
    switch (aFormat) {
        case ResTexFormat::RGBA8:
            bytePerPix = 4;
            break;

        case ResTexFormat::RGB8:
            bytePerPix = 3;
            break;

        case ResTexFormat::RGB5A1:
        case ResTexFormat::RGBA4:
        case ResTexFormat::RGB565:
        case ResTexFormat::RG8:
            bytePerPix = 2;
            break;

        case ResTexFormat::R8:
            bytePerPix = 1;
            break;

        default:
            XBASE_ERROR_INVALID_ENUM(aFormat);
            break;
    }
    return bytePerPix;
}

} // namespace

//------------------------------------------------------------------------------
pword_t RuntimeTex::CalcDataSize(
    const RuntimeTexContext& aContext
    )
{
    return tBytePerPixel(aContext.format()) * aContext.width() * aContext.height();
}

//------------------------------------------------------------------------------
pword_t RuntimeTex::RequireAlignment()
{
    return ::XBase::IAllocator::DefaultAlignment;
}

//------------------------------------------------------------------------------
RuntimeTex::RuntimeTex(
    const RuntimeTexContext& aContext,
    ::XBase::IAllocator& aAllocator
    )
: mContext(aContext)
, mData(CalcDataSize(aContext), aAllocator, RequireAlignment())
{
    // 0初期化
    for (int i = 0; i < mData->size(); ++i) {
        mData->head()[i] = 0;
    }
}

//------------------------------------------------------------------------------
RuntimeTex::~RuntimeTex()
{
}

//------------------------------------------------------------------------------
const RuntimeTexContext RuntimeTex::context()const
{
    return mContext;
}

//------------------------------------------------------------------------------
const ::XBase::MemBlock RuntimeTex::data()const
{
    return mData.ref();
}

//------------------------------------------------------------------------------
const TexResData RuntimeTex::texResData()const
{
    // 変数用意
    TexResData data = {};

    // データを返す
    data.format = mContext.format();
    data.width = mContext.width();
    data.height = mContext.height();
    data.pixels = mData->head();
    return data;
}

//------------------------------------------------------------------------------
void RuntimeTex::beginEdit()
{
}

//------------------------------------------------------------------------------
void RuntimeTex::endEdit()
{
}

//------------------------------------------------------------------------------
void RuntimeTex::setPixel(
    const int aX,
    const int aY,
    const ::XBase::Color4Pod& aVal
    )
{
    setPixel(aX, aY, aVal.toRGBAb());
}

//------------------------------------------------------------------------------
void RuntimeTex::setPixel(
    const int aX,
    const int aY,
    const ::XBase::Color4bPod& aVal
    )
{
    // アドレス計算
    XBASE_ASSERT_LESS(aX, mContext.width());
    XBASE_ASSERT_LESS(aY, mContext.height());
    const int pixelPos = aX + aY * mContext.width();
    const int bytePos = pixelPos * tBytePerPixel(mContext.format());
    byte_t* addr = &mData->head()[bytePos];

    // フォーマットごとに代入
    switch (mContext.format()) {
        case ResTexFormat::RGBA8:
            *reinterpret_cast< ::XBase::Color4bPod* >(addr) = aVal;
            break;

        case ResTexFormat::RGB8:
            addr[0] = aVal.r;
            addr[1] = aVal.g;
            addr[2] = aVal.b;
            break;

        case ResTexFormat::RGB5A1:
            *reinterpret_cast<u16*>(addr) = u16(
                (u16(aVal.r & 0xF8) << 8)
                | (u16(aVal.g & 0xF8) << 3)
                | (u16(aVal.b & 0xF8) >> 2)
                | (u16(aVal.a & 0x80) >> 7)
                );
            break;

        case ResTexFormat::RGBA4:
            *reinterpret_cast<u16*>(addr) = u16(
                (u16(aVal.r & 0xF0) << 8)
                | (u16(aVal.g & 0xF0) << 4)
                | (u16(aVal.b & 0xF0))
                | (u16(aVal.a & 0xF0) >> 4)
                );
            break;

        case ResTexFormat::RGB565:
            *reinterpret_cast<u16*>(addr) = u16(
                (u16(aVal.r & 0xF0) << 8)
                | (u16(aVal.g & 0xF0) << 3)
                | (u16(aVal.b & 0xF0) >> 3)
                );
            break;

        case ResTexFormat::RG8:
            addr[0] = aVal.r;
            addr[1] = aVal.g;
            break;

        case ResTexFormat::R8:
            addr[0] = aVal.r;
            break;

        default:
            XBASE_ERROR_INVALID_ENUM(mContext.format());
            break;
    }
}

} // namespace
// EOF
