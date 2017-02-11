// 文字コード：UTF-8
#include <ae/g3d/StateMaterial.hpp>

#include <ae/g3d/MatParam.hpp>
#include <ae/g3d/ResMat.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

//------------------------------------------------------------------------------
StateMaterial::StateMaterial(
    const ResMat& aResMat,
    ::ae::base::IAllocator& aAllocator
    )
: mResMat(aResMat)
, mParams(aResMat.paramCount(), aAllocator)
{
}

//------------------------------------------------------------------------------
StateMaterial::~StateMaterial()
{
}

//------------------------------------------------------------------------------
ResMat StateMaterial::resMat()const
{
    return mResMat;
}

}} // namespace
// EOF
