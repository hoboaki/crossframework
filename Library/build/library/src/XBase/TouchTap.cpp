// 文字コード：UTF-8
#include <XBase/TouchTap.hpp>

//------------------------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------------------------
TouchTap::TouchTap()
: mData()
, mPrevData()
{
}

//------------------------------------------------------------------------------
TouchTap::~TouchTap()
{
}

//------------------------------------------------------------------------------
void TouchTap::update( const TouchTapUpdateData& aData )
{
    mPrevData = mData;
    mData     = aData;
}

//------------------------------------------------------------------------------
const TouchTapUpdateData TouchTap::lastUpdateData()const
{
    return mData;
}

//------------------------------------------------------------------------------
uint TouchTap::tapCount()const
{
    return mData.tapCount;
}

//------------------------------------------------------------------------------
const ScreenPosPOD TouchTap::pos()const
{
    return mData.pos;
}

//------------------------------------------------------------------------------
bool TouchTap::isHold()const
{
    return 0 < mData.tapCount;
}

//------------------------------------------------------------------------------
bool TouchTap::isTrigger()const
{
    return mData.tapCount != 0 && mPrevData.tapCount == 0;
}

//------------------------------------------------------------------------------
bool TouchTap::isRelease()const
{
    return mData.tapCount == 0 && mPrevData.tapCount != 0;
}

} // namespace
// EOF
