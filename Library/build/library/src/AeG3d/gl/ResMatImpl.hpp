// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMATIMPL_HPP)
#else
#define AE_G3D_INCLUDED_RESMATIMPL_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/Placement.hpp>
#include <ae/base/RuntimeAutoArray.hpp>
#include <ae/g3d/SdkHeader.hpp>
#include "BinResMat.hpp"
#include "ResMatParamImpl.hpp"
#include "ResMatVtxAttrImpl.hpp"
#include "ShaderConstant.hpp"
#include "XdataPlus.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// BinResMatとResMatの間にかますクラス。
class ResMatImpl : public ::ae::base::NonCopyable
{
public:
    typedef ::ae::base::RuntimeAutoArray< ResMatParamImpl >     ParamArray;
    typedef ::ae::base::RuntimeAutoArray< ResMatVtxAttrImpl > VtxAttrArray;

    //============================================================
    const XdataPlus  xdata;
    const BinResMat* binPtr;
    GLuint shaderProgram;
    GLint  sysUniformLocations[ShaderConstant::SysUniform::TERM];
    ::ae::base::Placement< ParamArray >    paramImpls;
    ::ae::base::Placement< VtxAttrArray >  vtxAttrs;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMatImpl(const ::ae::xdata::Xdata& aXdata, const BinResMat* aBinPtr, ::ae::base::IAllocator& aAllocator);
    ~ResMatImpl();

    //============================================================
    void setup();
    void release();
};

}} // namespace
#endif
// EOF
