// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_STATEMATERIAL_HPP)
#else
#define XG3D_INCLUDED_STATEMATERIAL_HPP

#include <XBase/NonCopyable.hpp>
#include <XBase/RuntimeArray.hpp>
#include <XG3D/ResMat.hpp>

namespace XG3D {
class MatParam;
}

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-State
//@{
/// @brief マテリアルのState。
class StateMaterial : public ::XBase::NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief コンストラクタ。
    /// @param aResMat インスタンス化するマテリアル。
    /// @param aAllocator ワーク領域を確保するためのアロケータ。
    StateMaterial(
        const ResMat& aResMat
        , ::XBase::IAllocator& aAllocator = ::XBase::IAllocator::Default()
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
    ::XBase::RuntimeArray< MatParam > mParams;
};
//@}

} // namespace
#endif
// EOF
