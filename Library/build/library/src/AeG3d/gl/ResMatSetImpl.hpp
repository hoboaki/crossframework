// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMATSETIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMATSETIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/Placement.hpp>
#include <ae/base/RuntimeAutoArray.hpp>
#include "BinResMatSet.hpp"
#include "ResMatImpl.hpp"
#include "XdataPlus.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMatSetとResMatSetの間にかますクラス。
class ResMatSetImpl : public ::ae::base::NonCopyable
{
public:
    typedef ::ae::base::RuntimeAutoArray< ResMatImpl > MatArray;

    //============================================================
    const XdataPlus  xdata;
    const BinResMatSet* binPtr;
    ::ae::base::Placement< MatArray > matImpls;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMatSetImpl(const ::ae::xdata::Xdata& aXdata, const BinResMatSet* aBinPtr, ::ae::base::IAllocator& aAllocator);
    ~ResMatSetImpl();

    //============================================================
    void setup();
    void release();
};

}} // namespace
#endif
// EOF
