// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMATVTXATTRIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMATVTXATTRIMPL_HPP

#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XG3D/SDKHeader.hpp>
#include "BinResMatVtxAttr.hpp"
#include "XDataPlus.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

    // BinResMatVtxAttrとResMatVtxAttrの間にかますクラス。
    class ResMatVtxAttrImpl : public ::XBase::NonCopyable
    {
    public:
        const XDataPlus  xdata;
        const BinResMatVtxAttr* binPtr;

        //============================================================
        // バイナリデータの先頭アドレスを指定して作成。
        ResMatVtxAttrImpl( const ::XData::XData& aXData , const BinResMatVtxAttr* aBinPtr , ::XBase::IAllocator& aAllocator );
        ~ResMatVtxAttrImpl();
    };

} // namespace
#endif
// EOF
