// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_STATEMATERIAL_HPP)
#else
#define AE_G3D_INCLUDED_STATEMATERIAL_HPP

#include <ae/base/NonCopyable.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/g3d/ResMat.hpp>

namespace ae {
namespace g3d {
class MatParam;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-State
//@{
/// @brief マテリアルのState。
class StateMaterial : public ::ae::base::NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief コンストラクタ。
    /// @param aResMat インスタンス化するマテリアル。
    /// @param aAllocator ワーク領域を確保するためのアロケータ。
    StateMaterial(
        const ResMat& aResMat
        , ::ae::base::IAllocator& aAllocator = ::ae::base::IAllocator::Default()
    );

/// デストラクタ。
    ~StateMaterial();
    //@}

    /// @name 全般
    //@{
    ResMat resMat()const; ///< インスタンス元となるリソース。
    //@}

private:
    ResMat mResMat;
    ::ae::base::RuntimeArray< MatParam > mParams;
};
//@}

}} // namespace
#endif
// EOF
