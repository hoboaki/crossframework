// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/Placement.hpp>
#include <ae/base/RuntimeAutoArray.hpp>
#include "BinResMdl.hpp"
#include "ResMdlMatReferImpl.hpp"
#include "ResMdlMeshImpl.hpp"
#include "ResMdlNodeImpl.hpp"
#include "ResMdlShapeImpl.hpp"
#include "XdataPlus.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMdlとResMdlの間にかますクラス。
class ResMdlImpl : public ::ae::base::NonCopyable
{
public:
    typedef ::ae::base::RuntimeAutoArray< ResMdlMatReferImpl > MatReferArray;
    typedef ::ae::base::RuntimeAutoArray< ResMdlMeshImpl >     MeshArray;
    typedef ::ae::base::RuntimeAutoArray< ResMdlNodeImpl >     NodeArray;
    typedef ::ae::base::RuntimeAutoArray< ResMdlShapeImpl >    ShapeArray;

    //============================================================
    const XdataPlus  xdata;
    const BinResMdl* binPtr;
    ::ae::base::Placement< ShapeArray >    shapeImpls; // Meshの参照解決で必要なため一番先に宣言
    ::ae::base::Placement< MatReferArray > matReferImpls;
    ::ae::base::Placement< MeshArray >     meshImpls;
    ::ae::base::Placement< NodeArray >     nodeImpls;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMdlImpl(const ::ae::xdata::Xdata& aXdata, const BinResMdl* aBinPtr, ::ae::base::IAllocator& aAllocator);
    ~ResMdlImpl();

    //============================================================
    void setup();
    void release();
};

}} // namespace
#endif
// EOF
