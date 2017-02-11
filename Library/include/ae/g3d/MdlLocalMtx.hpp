// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_MDLLOCALMTX_HPP)
#else
#define AE_G3D_INCLUDED_MDLLOCALMTX_HPP

#include <ae/base/Matrix34.hpp>
#include <ae/base/Vector3.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-State
//@{
/// @brief StateMdlTransformが持つローカル行列。
struct MdlLocalMtx
{
    ::ae::base::Mtx34 rtMtx; ///< RotateTrans行列。
    ::ae::base::Vec3  scale; ///< Scale値。
};
//@}

}} // namespace
#endif
// EOF
