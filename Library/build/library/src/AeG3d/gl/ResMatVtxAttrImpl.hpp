// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMATVTXATTRIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMATVTXATTRIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/g3d/SdkHeader.hpp>
#include "BinResMatVtxAttr.hpp"
#include "XdataPlus.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMatVtxAttrとResMatVtxAttrの間にかますクラス。
class ResMatVtxAttrImpl : public ::ae::base::NonCopyable
{
public:
    const XdataPlus  xdata;
    const BinResMatVtxAttr* binPtr;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMatVtxAttrImpl(const ::ae::xdata::Xdata& aXdata, const BinResMatVtxAttr* aBinPtr, ::ae::base::IAllocator& aAllocator);
    ~ResMatVtxAttrImpl();
};

}} // namespace
#endif
// EOF
