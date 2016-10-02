// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLMATREFERIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMDLMATREFERIMPL_HPP

#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include "BinResMdlMatRefer.hpp"
#include "XDataPlus.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

    // BinResMdlMatReferとResMdlMatReferの間にかますクラス。
    class ResMdlMatReferImpl : public ::XBase::NonCopyable
    {
    public:
        const XDataPlus             xdata;
        const BinResMdlMatRefer*    binPtr;
        
        //============================================================
        // バイナリデータの先頭アドレスを指定して作成。
        ResMdlMatReferImpl( const ::XData::XData& aXData , const BinResMdlMatRefer* aBinPtr , ::XBase::IAllocator& aAllocator );
        ~ResMdlMatReferImpl();
    };

} // namespace
#endif
// EOF
