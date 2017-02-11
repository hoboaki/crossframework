// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLMATREFERIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLMATREFERIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include "BinResMdlMatRefer.hpp"
#include "XdataPlus.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMdlMatReferとResMdlMatReferの間にかますクラス。
class ResMdlMatReferImpl : public ::ae::base::NonCopyable
{
public:
    const XdataPlus             xdata;
    const BinResMdlMatRefer*    binPtr;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMdlMatReferImpl(const ::ae::xdata::Xdata& aXdata, const BinResMdlMatRefer* aBinPtr, ::ae::base::IAllocator& aAllocator);
    ~ResMdlMatReferImpl();
};

}} // namespace
#endif
// EOF
