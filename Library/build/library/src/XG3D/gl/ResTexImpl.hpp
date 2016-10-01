// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESTEXIMPL_HPP)
#else
#define XG3D_INCLUDED_RESTEXIMPL_HPP

//------------------------------------------------------------------------------
#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/Placement.hpp>
#include <XG3D/ResTexFormat.hpp>
#include <XG3D/TexBuffer.hpp>
#include "BinResTex.hpp"
#include "XDataPlus.hpp"

//------------------------------------------------------------------------------
namespace XG3D {
    // BinResTexとResTexの間にかますクラス。
    class ResTexImpl : public ::XBase::NonCopyable
    {
    public:
        const XDataPlus     xdata;
        const BinResTex*    binPtr;
        const TexBuffer*    texBufferPtr;

        // ResTexはワーク領域不要

        //============================================================
        // バイナリデータの先頭アドレスを指定して作成。
        ResTexImpl( const ::XData::XData& aXData , const BinResTex* aBinPtr , ::XBase::IAllocator& aAllocator );
        ~ResTexImpl();

        //============================================================
        void setup();
        ResTexFormat format()const;
        const byte_t* pixels()const;

    private:
        ::XBase::Placement< TexBuffer > mTexBuffer;
    };

} // namespace
#endif
// EOF
