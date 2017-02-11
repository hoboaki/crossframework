// 文字コード：UTF-8
#include <ae/g3d/StateMdlMaterial.hpp>

#include <ae/base/Ref.hpp>
#include <ae/g3d/ResMatSet.hpp>
#include <ae/g3d/ResMdl.hpp>
#include <ae/g3d/StateMaterial.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
StateMdlMaterial::StateMdlMaterial(
    const ResMdl& aResMdl,
    const ResMatSet& aResMatSet,
    ::ae::base::IAllocator& aAllocator
    )
: mResMdl(aResMdl)
, mMaterials(aResMdl.matReferCount(), aAllocator)
{
    // 各マテリアルの作成
    for (int i = 0; i < aResMdl.matReferCount(); ++i) {
        mMaterials.add(
            aResMatSet.mat(aResMdl.matRefer(i).name()),
            ::ae::base::Ref(aAllocator)
            );
    }
}

//------------------------------------------------------------------------------
StateMdlMaterial::~StateMdlMaterial()
{
}

//------------------------------------------------------------------------------
StateMaterial& StateMdlMaterial::material(const int aMatIndex)
{
    return mMaterials[aMatIndex];
}

//------------------------------------------------------------------------------
const StateMaterial& StateMdlMaterial::material(const int aMatIndex)const
{
    return mMaterials[aMatIndex];
}

}} // namespace
// EOF
