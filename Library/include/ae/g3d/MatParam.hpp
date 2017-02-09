// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_MATPARAM_HPP)
#else
#define AE_G3D_INCLUDED_MATPARAM_HPP

#include <ae/base/Matrix34.hpp>
#include <ae/base/Vector3.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-State
//@{
/// @brief StateMaterialが持つマテリアルパラメータ。
class MatParam
{
public:
    MatParam() : mDummy() {}

private:
    int mDummy;
};
//@}

}} // namespace
#endif
// EOF
