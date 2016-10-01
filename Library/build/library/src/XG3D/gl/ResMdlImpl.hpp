/**
 * @file
 * @brief ResMdlImpl型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_RESMDLIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMDLIMPL_HPP

//------------------------------------------------------------
#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/Placement.hpp>
#include <XBase/RuntimeAutoArray.hpp>
#include "BinResMdl.hpp"
#include "ResMdlMatReferImpl.hpp"
#include "ResMdlMeshImpl.hpp"
#include "ResMdlNodeImpl.hpp"
#include "ResMdlShapeImpl.hpp"
#include "XDataPlus.hpp"

//------------------------------------------------------------
namespace XG3D {
    // BinResMdlとResMdlの間にかますクラス。
    class ResMdlImpl : public ::XBase::NonCopyable
    {
    public:
        typedef ::XBase::RuntimeAutoArray< ResMdlMatReferImpl > MatReferArray;
        typedef ::XBase::RuntimeAutoArray< ResMdlMeshImpl >     MeshArray;
        typedef ::XBase::RuntimeAutoArray< ResMdlNodeImpl >     NodeArray;
        typedef ::XBase::RuntimeAutoArray< ResMdlShapeImpl >    ShapeArray;

        //============================================================
        const XDataPlus  xdata;
        const BinResMdl* binPtr;
        ::XBase::Placement< ShapeArray >    shapeImpls; // Meshの参照解決で必要なため一番先に宣言
        ::XBase::Placement< MatReferArray > matReferImpls;
        ::XBase::Placement< MeshArray >     meshImpls;
        ::XBase::Placement< NodeArray >     nodeImpls;

        //============================================================
        // バイナリデータの先頭アドレスを指定して作成。
        ResMdlImpl( const ::XData::XData& aXData , const BinResMdl* aBinPtr , ::XBase::IAllocator& aAllocator );
        ~ResMdlImpl();

        //============================================================
        void setup();
        void release();
    };
}
//------------------------------------------------------------
#endif
// EOF
