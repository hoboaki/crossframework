// 文字コード：UTF-8
#include "BinResHeader.hpp"

#include <XBase/RuntimeAssert.hpp>
#include <XG3D/Engine.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
bool BinResHeader::isValid()const
{
    if (versionMajor != VersionMajor
        || versionMinor != VersionMinor
        || targetEngine != XG3D_TARGET_ENGINE
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
        XBASE_ASSERT_NOT_REACHED();
        return true;
    }
    return false;
}

} // namespace
// EOF
