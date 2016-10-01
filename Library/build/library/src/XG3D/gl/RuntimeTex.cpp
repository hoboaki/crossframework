// 文字コード：UTF-8
#include <XG3D/RuntimeTex.hpp>

//------------------------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>
#include <XBase/Unused.hpp>
#include <XG3D/TexResData.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------------------------
namespace {
    int tBytePerPixel( const ::XG3D::ResTexFormat aFormat )
    {
        int bytePerPix = 0;
        switch( aFormat )
        {
        case ResTexFormat_RGBA8:
            bytePerPix = 4;
            break;

        case ResTexFormat_RGB8:
            bytePerPix = 3;
            break;

        case ResTexFormat_RGB5A1:
        case ResTexFormat_RGBA4:
        case ResTexFormat_RGB565:
        case ResTexFormat_LA8:
            bytePerPix = 2;
            break;

        case ResTexFormat_A8:
        case ResTexFormat_L8:
            bytePerPix = 1;
            break;

        default:
            XBASE_INVALID_ENUM_ERROR( aFormat );
            break;
        }
        return bytePerPix;
    }
}
//------------------------------------------------------------------------------
pword_t RuntimeTex::CalcDataSize( 
    const RuntimeTexContext& aContext
    )
{
    return tBytePerPixel( aContext.format() ) * aContext.width() * aContext.height();
}

//------------------------------------------------------------------------------
pword_t RuntimeTex::RequireAlignment()
{
    return ::XBase::IAllocator::DefaultAlignment;
}

//------------------------------------------------------------------------------
RuntimeTex::RuntimeTex(
    const RuntimeTexContext& aContext
    , ::XBase::IAllocator& aAllocator
    )
: mContext( aContext )
, mData( CalcDataSize( aContext ) , aAllocator , RequireAlignment() )
{
    // 0初期化
    for ( uint i = 0; i < mData->size(); ++i )
    {
        mData->head()[ i ] = 0;
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
    data.width  = mContext.width();
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
    const uint aX 
    , const uint aY 
    , const ::XBase::Color4POD& aVal 
    )
{
    setPixel( aX , aY , aVal.toRGBAb() );
}

//------------------------------------------------------------------------------
void RuntimeTex::setPixel( 
    const uint aX 
    , const uint aY 
    , const ::XBase::Color4bPOD& aVal
    )
{
    // アドレス計算
    XBASE_RANGE_ASSERT_MAX( aX , mContext.width() );
    XBASE_RANGE_ASSERT_MAX( aY , mContext.height() );
    const uint pixelPos = aX + aY * mContext.width();
    const uint bytePos = pixelPos * tBytePerPixel( mContext.format() );
    byte_t* addr = &mData->head()[ bytePos ];

    // フォーマットごとに代入
    switch( mContext.format() )
    {
    case ResTexFormat_RGBA8:
        *reinterpret_cast< ::XBase::Color4bPOD* >( addr ) = aVal;
        break;

    case ResTexFormat_RGB8:
        addr[0] = aVal.r;
        addr[1] = aVal.g;
        addr[2] = aVal.b;
        break;

    case ResTexFormat_RGB5A1:
        *reinterpret_cast< u16* >( addr ) = u16(
            (u16(aVal.r & 0xF8) << 8)
            | (u16(aVal.g & 0xF8) << 3)
            | (u16(aVal.b & 0xF8) >> 2)
            | (u16(aVal.a & 0x80) >> 7)
            );
        break;

    case ResTexFormat_RGBA4:
        *reinterpret_cast< u16* >( addr ) = u16(
            (u16(aVal.r & 0xF0) << 8)
            | (u16(aVal.g & 0xF0) << 4)
            | (u16(aVal.b & 0xF0) )
            | (u16(aVal.a & 0xF0) >> 4)
            );
        break;

    case ResTexFormat_RGB565:
        *reinterpret_cast< u16* >( addr ) = u16(
            (u16(aVal.r & 0xF0) << 8)
            | (u16(aVal.g & 0xF0) << 3)
            | (u16(aVal.b & 0xF0) >> 3)
            );
        break;

    case ResTexFormat_LA8:
        addr[0] = aVal.r;
        addr[1] = aVal.a;
        break;

    case ResTexFormat_A8:
        addr[0] = aVal.a;
        break;

    case ResTexFormat_L8:
        addr[0] = aVal.r;
        break;

    default:
        XBASE_INVALID_ENUM_ERROR( mContext.format() );
        break;
    }
}

} // namespace
// EOF
