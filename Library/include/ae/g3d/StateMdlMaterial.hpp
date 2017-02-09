// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_STATEMDLMATERIAL_HPP)
#else
#define AE_G3D_INCLUDED_STATEMDLMATERIAL_HPP

#include <ae/base/NonCopyable.hpp>
#include <ae/base/RuntimeAutoArray.hpp>
#include <ae/g3d/ResMatSet.hpp>
#include <ae/g3d/ResMdl.hpp>

namespace ae {
namespace g3d {
class StateMaterial;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-State
//@{
    /// @brief モデルが必要とする全Materialに関するState。
    /// @details
/// 各関数の引数 aMatIndex はインスタンス元モデルの matRefer のインデックス値に対応します。
class StateMdlMaterial : public ::ae::base::NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief コンストラクタ。
    /// @param aResMdl インスタンス化するモデル。
    /// @param aResMatSet インスタンス化するマテリアルセット。
    /// @param aAllocator ワーク領域を確保するためのアロケータ。
    StateMdlMaterial(
        const ResMdl& aResMdl
        , const ResMatSet& aResMatSet
        , ::ae::base::IAllocator& aAllocator = ::ae::base::IAllocator::Default()
    );

/// デストラクタ。
    ~StateMdlMaterial();
    //@}

    /// @name マテリアルアクセス
    //@{
    StateMaterial& material(int aMatIndex);
    const StateMaterial& material(int aMatIndex)const;
    //@}

private:
    ResMdl mResMdl;
    ::ae::base::RuntimeAutoArray< StateMaterial > mMaterials;
};
//@}

}} // namespace
#endif
// EOF
