// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_BINRESHEADER_HPP)
#else
#define AE_G3D_INCLUDED_BINRESHEADER_HPP

#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/xdata/Xdata.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// バイナリデータ：ヘッダ。
struct BinResHeader
{
    static const u8 VersionMajor = 1;
    static const u8 VersionMinor = 0;

    u8  versionMajor;
    u8  versionMinor;
    u16 targetEngine;

    ::ae::xdata::Reference matSets;
    ::ae::xdata::Reference mdls;
    ::ae::xdata::Reference texs;

    bool isValid()const;
    bool checkInvalid()const; // Invalidならエラー処理をしてtrueを返す。
};

}} // namespace
#endif
// EOF
