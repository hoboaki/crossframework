// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMATPARAMIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMATPARAMIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/g3d/SdkHeader.hpp>
#include "BinResMatParam.hpp"
#include "XdataPlus.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMatParamとResMatParamの間にかますクラス。
class ResMatParamImpl : public ::ae::base::NonCopyable
{
public:
    const XdataPlus  xdata;
    const BinResMatParam* binPtr;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMatParamImpl(const ::ae::xdata::Xdata& aXdata, const BinResMatParam* aBinPtr, ::ae::base::IAllocator& aAllocator);
    ~ResMatParamImpl();
};

}} // namespace
#endif
// EOF
