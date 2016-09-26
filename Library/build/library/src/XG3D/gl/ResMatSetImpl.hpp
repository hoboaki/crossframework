/**
 * @file
 * @brief ResMatSetImpl型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_RESMATSETIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMATSETIMPL_HPP

//------------------------------------------------------------
#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/Placement.hpp>
#include <XBase/RuntimeAutoArray.hpp>
#include "BinResMatSet.hpp"
#include "ResMatImpl.hpp"
#include "XDataPlus.hpp"

//------------------------------------------------------------
namespace XG3D {
    // BinResMatSetとResMatSetの間にかますクラス。
    class ResMatSetImpl : public ::XBase::NonCopyable
    {
    public:
        typedef ::XBase::RuntimeAutoArray< ResMatImpl > MatArray;

        //============================================================
        const XDataPlus  xdata;
        const BinResMatSet* binPtr;
        ::XBase::Placement< MatArray > matImpls;

        //============================================================
        // バイナリデータの先頭アドレスを指定して作成。
        ResMatSetImpl( const ::XData::XData& aXData , const BinResMatSet* aBinPtr , ::XBase::IAllocator& aAllocator );
        ~ResMatSetImpl();

        //============================================================
        void setup();
        void release();
    };
}
//------------------------------------------------------------
#endif
// EOF
