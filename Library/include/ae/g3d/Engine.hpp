// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_ENGINE_HPP)
#else
#define AE_G3D_INCLUDED_ENGINE_HPP

#include <ae/base/Os.hpp>

/// @addtogroup AeG3d-Env
//@{

/// 使用するエンジンがOpenGLのときに定義されるプリプロセッサ。
#define AE_G3D_ENGINE_GL
#undef  AE_G3D_ENGINE_GL

/// 使用するエンジンがOpenGLESのときに定義されるプリプロセッサ。
#define AE_G3D_ENGINE_GLES
#undef  AE_G3D_ENGINE_GLES

/// 使用するエンジンがOpenGLもしくはOpenGLESのときに定義されるプリプロセッサ。
#define AE_G3D_ENGINE_GLSERIES
#undef  AE_G3D_ENGINE_GLSERIES

// 選択
#if defined(AE_BASE_OS_WINDOWS)
    #define AE_G3D_ENGINE_GL
#elif defined(AE_BASE_OS_MACOSX)
    #define AE_G3D_ENGINE_GL
#elif defined(AE_BASE_OS_IOS)
    #define AE_G3D_ENGINE_GLES
#else
    #error "Not supported OS."
#endif

// 選択後の定義
#if defined(AE_G3D_ENGINE_GL)
    #define AE_G3D_TARGET_ENGINE (::ae::g3d::Engine::GL)
    #define AE_G3D_ENGINE_GLSERIES
#elif defined(AE_G3D_ENGINE_GLES)
    #define AE_G3D_TARGET_ENGINE (::ae::g3d::Engine::GLES)
    #define AE_G3D_ENGINE_GLSERIES
#endif

//@}
//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// エンジンの種類。
struct Engine
{
    enum EnumType
    {
        GL,
        GLES,

        TERM,
    };
};

}} // namespace
#endif
// EOF
