// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMATIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMATIMPL_HPP

#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/Placement.hpp>
#include <XBase/RuntimeAutoArray.hpp>
#include <XG3D/SdkHeader.hpp>
#include "BinResMat.hpp"
#include "ResMatParamImpl.hpp"
#include "ResMatVtxAttrImpl.hpp"
#include "ShaderConstant.hpp"
#include "XDataPlus.hpp"

//------------------------------------------------------------------------------
namespace XG3D {

// BinResMatとResMatの間にかますクラス。
class ResMatImpl : public ::XBase::NonCopyable
{
public:
    typedef ::XBase::RuntimeAutoArray< ResMatParamImpl >     ParamArray;
    typedef ::XBase::RuntimeAutoArray< ResMatVtxAttrImpl > VtxAttrArray;

    //============================================================
    const XDataPlus  xdata;
    const BinResMat* binPtr;
    GLuint shaderProgram;
    GLint  sysUniformLocations[ShaderConstant::SysUniform::TERM];
    ::XBase::Placement< ParamArray >    paramImpls;
    ::XBase::Placement< VtxAttrArray >  vtxAttrs;

    //============================================================
    // バイナリデータの先頭アドレスを指定して作成。
    ResMatImpl(const ::XData::XData& aXData, const BinResMat* aBinPtr, ::XBase::IAllocator& aAllocator);
    ~ResMatImpl();

    //============================================================
    void setup();
    void release();
};

} // namespace
#endif
// EOF
