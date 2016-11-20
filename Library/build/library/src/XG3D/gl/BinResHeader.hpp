// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_BINRESHEADER_HPP)
#else
#define XG3D_INCLUDED_BINRESHEADER_HPP

#include <XG3D/BuiltInTypes.hpp>
#include <XData/XData.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

/// バイナリデータ：ヘッダ。
struct BinResHeader
{
    static const u8 VersionMajor = 1;
    static const u8 VersionMinor = 0;

    u8  versionMajor;
    u8  versionMinor;
    u16 targetEngine;

    ::XData::Reference matSets;
    ::XData::Reference mdls;
    ::XData::Reference texs;

    bool isValid()const;
    bool checkInvalid()const; // Invalidならエラー処理をしてtrueを返す。
};

} // namespace
#endif
// EOF
