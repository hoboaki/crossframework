// 文字コード：UTF-8
#include <XG3D/StateMdlMaterial.hpp>

//------------------------------------------------------------------------------
#include <XBase/Ref.hpp>
#include <XG3D/ResMatSet.hpp>
#include <XG3D/ResMdl.hpp>
#include <XG3D/StateMaterial.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

//------------------------------------------------------------------------------
StateMdlMaterial::StateMdlMaterial(
    const ResMdl& aResMdl,
    const ResMatSet& aResMatSet,
    ::XBase::IAllocator& aAllocator
    )
: mResMdl(aResMdl)
, mMaterials(aResMdl.matReferCount(), aAllocator)
{
    // 各マテリアルの作成
    for (int i = 0; i < aResMdl.matReferCount(); ++i) {
        mMaterials.add(
            aResMatSet.mat(aResMdl.matRefer(i).name()),
            ::XBase::Ref(aAllocator)
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

} // namespace
// EOF
