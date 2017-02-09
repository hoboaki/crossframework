// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLSUBMESHIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLSUBMESHIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/g3d/ResMdlShape.hpp>
#include "BinResMdlSubMesh.hpp"
#include "XdataPlus.hpp"

namespace ae {
namespace g3d {
class ResMdl;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMdlSubMeshとResMdlSubMeshの間にかますクラス。
class ResMdlSubMeshImpl : public ::ae::base::NonCopyable
{
public:
    const XdataPlus         xdata;
    const BinResMdlSubMesh* binPtr;
    ResMdlShape             resMdlShape;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMdlSubMeshImpl(const ::ae::xdata::Xdata& aXdata, const BinResMdlSubMesh* aBinPtr, ::ae::base::IAllocator& aAllocator, const ResMdl& aResMdl);
    ~ResMdlSubMeshImpl();
};

}} // namespace
#endif
// EOF
