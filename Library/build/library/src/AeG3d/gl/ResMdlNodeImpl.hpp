// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLNODEIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMDLNODEIMPL_HPP

#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include "BinResMdlNode.hpp"
#include "XDataPlus.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

// BinResMdlNodeとResMdlNodeの間にかますクラス。
class ResMdlNodeImpl : public ::XBase::NonCopyable
{
public:
    const XDataPlus         xdata;
    const BinResMdlNode*    binPtr;
    const ::XBase::Mtx34*   bindPoseMtxPtr;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMdlNodeImpl(const ::XData::XData& aXData, const BinResMdlNode* aBinPtr, ::XBase::IAllocator& aAllocator);
    ~ResMdlNodeImpl();
};

} // namespace
#endif
// EOF
