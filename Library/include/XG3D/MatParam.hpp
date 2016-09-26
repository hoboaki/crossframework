/**
 * @file
 * @brief MatParam型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_MATPARAM_HPP)
#else
#define XG3D_INCLUDED_MATPARAM_HPP

//------------------------------------------------------------
#include <XBase/Matrix34.hpp>
#include <XBase/Vector3.hpp>

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-State
//@{
    /**
     * @brief StateMaterialが持つマテリアルパラメータ。
     */
    class MatParam
    {
    public:
        MatParam() : mDummy() {}

    private:
        int mDummy;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
