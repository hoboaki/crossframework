// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLNODEIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLNODEIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include "BinResMdlNode.hpp"
#include "XdataPlus.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMdlNodeとResMdlNodeの間にかますクラス。
class ResMdlNodeImpl : public ::ae::base::NonCopyable
{
public:
    const XdataPlus         xdata;
    const BinResMdlNode*    binPtr;
    const ::ae::base::Mtx34*   bindPoseMtxPtr;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMdlNodeImpl(const ::ae::xdata::Xdata& aXdata, const BinResMdlNode* aBinPtr, ::ae::base::IAllocator& aAllocator);
    ~ResMdlNodeImpl();
};

}} // namespace
#endif
// EOF
