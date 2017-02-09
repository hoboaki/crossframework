// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLMESHIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLMESHIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/Placement.hpp>
#include <ae/base/RuntimeAutoArray.hpp>
#include "BinResMdlMesh.hpp"
#include "ResMdlSubMeshImpl.hpp"
#include "XdataPlus.hpp"

namespace ae {
namespace g3d {
class ResMdl;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMdlMeshとResMdlMeshの間にかますクラス。
class ResMdlMeshImpl : public ::ae::base::NonCopyable
{
public:
    typedef ::ae::base::RuntimeAutoArray< ResMdlSubMeshImpl >  SubMeshArray;

    //============================================================
    const XdataPlus  xdata;
    const BinResMdlMesh* binPtr;
    ::ae::base::Placement< SubMeshArray > subMeshImpls;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMdlMeshImpl(const ::ae::xdata::Xdata& aXdata, const BinResMdlMesh* aBinPtr, ::ae::base::IAllocator& aAllocator, const ResMdl& aResMdl);
    ~ResMdlMeshImpl();
};

}} // namespace
#endif
// EOF
