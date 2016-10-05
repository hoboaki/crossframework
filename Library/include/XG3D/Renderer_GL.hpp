// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RENDERER_GL_HPP)
#else
#define XG3D_INCLUDED_RENDERER_GL_HPP

#include <XBase/Bool.hpp>
#include <XBase/Matrix34.hpp>
#include <XBase/Matrix44.hpp>
#include <XG3D/ResMat.hpp>
#include <XG3D/SdkHeader.hpp>

namespace XBase {
class Display;
}

//------------------------------------------------------------------------------
namespace XG3D {

// Rendererの拡張。
class Renderer_EXT
{
public:
    enum { UNIFORM_COUNT = 5 };
    GLuint demoShaderProgram;
    GLint  demoUniformLocations[UNIFORM_COUNT];
    ::XBase::Bool32 colorUpdate;
    ::XBase::Bool32 depthUpdate;
    ::XG3D::ResMat currentMaterial;
    ::XBase::Matrix44 mtxProj;
    ::XBase::Matrix34 mtxView;
    ::XBase::Matrix34 mtxWorld;

    //============================================================
    Renderer_EXT();

    //============================================================
    void setup(::XBase::Display&);
    void updateMtxProj();
    void updateMtxView();
    void updateMtxWorld();
};

} // namespace
#endif
// EOF
