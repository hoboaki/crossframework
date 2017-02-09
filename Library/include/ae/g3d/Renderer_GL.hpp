// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RENDERER_GL_HPP)
#else
#define AE_G3D_INCLUDED_RENDERER_GL_HPP

#include <ae/base/Bool.hpp>
#include <ae/base/Matrix34.hpp>
#include <ae/base/Matrix44.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/Vector4.hpp>
#include <ae/g3d/ResMat.hpp>
#include <ae/g3d/SdkHeader.hpp>

namespace ae {
namespace base {
class Display;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// Rendererの拡張。
class Renderer_Ext
{
public:
    enum { UNIFORM_COUNT = 6 };
    GLuint demoShaderProgram;
    GLint  demoUniformLocations[UNIFORM_COUNT];
    GLuint sharedVertexArray;
    ::ae::base::Bool32 colorUpdate;
    ::ae::base::Bool32 depthUpdate;
    ::ae::g3d::ResMat currentMaterial;
    ::ae::base::Matrix44 mtxProj;
    ::ae::base::Matrix34 mtxView;
    ::ae::base::Matrix34 mtxWorld;
    ::ae::base::Pointer<const ::ae::base::Vec4> mtxBonePosArray;
    ::ae::base::Pointer<const ::ae::base::Vec4> mtxBoneNrmArray;

    //============================================================
    Renderer_Ext();

    //============================================================
    void setup(::ae::base::Display&);
    void updateMtxProj();
    void updateMtxView();
    void updateMtxWorld();
    void updateMtxBones();
};

}} // namespace
#endif
// EOF
