// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_MDLLOCALMTX_HPP)
#else
#define XG3D_INCLUDED_MDLLOCALMTX_HPP

//------------------------------------------------------------------------------
#include <XBase/Matrix34.hpp>
#include <XBase/Vector3.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-State
//@{
    /// @brief StateMdlTransformが持つローカル行列。
    struct MdlLocalMtx
    {
        ::XBase::Mtx34 rtMtx; ///< RotateTrans行列。
        ::XBase::Vec3  scale; ///< Scale値。
    };
//@}

} // namespace
#endif
// EOF
