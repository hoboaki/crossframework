// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RENDERER_GL_HPP)
#else
#define XG3D_INCLUDED_RENDERER_GL_HPP

#include <XBase/Bool.hpp>
#include <XBase/Matrix34.hpp>
#include <XBase/Matrix44.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Vector4.hpp>
#include <XG3D/ResMat.hpp>
#include <XG3D/SdkHeader.hpp>

namespace XBase {
class Display;
}

//------------------------------------------------------------------------------
namespace XG3D {

// Rendererの拡張。
class Renderer_Ext
{
public:
    enum { UNIFORM_COUNT = 6 };
    GLuint demoShaderProgram;
    GLint  demoUniformLocations[UNIFORM_COUNT];
    GLuint sharedVertexArray;
    ::XBase::Bool32 colorUpdate;
    ::XBase::Bool32 depthUpdate;
    ::XG3D::ResMat currentMaterial;
    ::XBase::Matrix44 mtxProj;
    ::XBase::Matrix34 mtxView;
    ::XBase::Matrix34 mtxWorld;
    ::XBase::Pointer<const ::XBase::Vec4> mtxBonePosArray;
    ::XBase::Pointer<const ::XBase::Vec4> mtxBoneNrmArray;

    //============================================================
    Renderer_Ext();

    //============================================================
    void setup(::XBase::Display&);
    void updateMtxProj();
    void updateMtxView();
    void updateMtxWorld();
    void updateMtxBones();
};

} // namespace
#endif
// EOF
