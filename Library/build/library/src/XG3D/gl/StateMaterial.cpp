/**
 * @file
 * @brief StateMaterial.hppの実装を記述する。
 * @author akino
 */
#include <XG3D/StateMaterial.hpp>

//------------------------------------------------------------
#include <XG3D/MatParam.hpp>
#include <XG3D/ResMat.hpp>

//------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------
StateMaterial::StateMaterial(
    const ResMat& aResMat 
    , ::XBase::IAllocator& aAllocator
    )
: mResMat( aResMat )
, mParams( aResMat.paramCount() , aAllocator )
{
}

//------------------------------------------------------------
StateMaterial::~StateMaterial()
{
}

//------------------------------------------------------------
ResMat StateMaterial::resMat()const
{
    return mResMat;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
