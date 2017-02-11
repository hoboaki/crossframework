// 文字コード：UTF-8
#include "BinResHeader.hpp"

#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/Engine.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
bool BinResHeader::isValid()const
{
    if (versionMajor != VersionMajor
        || versionMinor != VersionMinor
        || targetEngine != AE_G3D_TARGET_ENGINE
        )
    {
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
bool BinResHeader::checkInvalid()const
{
    if (!isValid()) {
        AE_BASE_ASSERT_NOT_REACHED();
        return true;
    }
    return false;
}

}} // namespace
// EOF
