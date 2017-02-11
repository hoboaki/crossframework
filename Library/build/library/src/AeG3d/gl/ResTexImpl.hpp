// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESTEXIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESTEXIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/Placement.hpp>
#include <ae/g3d/ResTexFormat.hpp>
#include <ae/g3d/TexBuffer.hpp>
#include "BinResTex.hpp"
#include "XdataPlus.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResTexとResTexの間にかますクラス。
class ResTexImpl : public ::ae::base::NonCopyable
{
public:
    const XdataPlus     xdata;
    const BinResTex*    binPtr;
    const TexBuffer*    texBufferPtr;

    // ResTexはワーク領域不要

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResTexImpl(const ::ae::xdata::Xdata& aXdata, const BinResTex* aBinPtr, ::ae::base::IAllocator& aAllocator);
    ~ResTexImpl();

    //============================================================
    void setup();
    ResTexFormat::EnumType format()const;
    const byte_t* pixels()const;

private:
    ::ae::base::Placement< TexBuffer > mTexBuffer;
};

}} // namespace
#endif
// EOF
