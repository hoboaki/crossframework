// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_ENGINE_HPP)
#else
#define XG3D_INCLUDED_ENGINE_HPP

#include <XBase/Os.hpp>

/// @addtogroup XG3D-Env
//@{

/// 使用するエンジンがOpenGLのときに定義されるプリプロセッサ。
#define XG3D_ENGINE_GL
#undef  XG3D_ENGINE_GL

/// 使用するエンジンがOpenGLESのときに定義されるプリプロセッサ。
#define XG3D_ENGINE_GLES
#undef  XG3D_ENGINE_GLES

/// 使用するエンジンがOpenGLもしくはOpenGLESのときに定義されるプリプロセッサ。
#define XG3D_ENGINE_GLSERIES
#undef  XG3D_ENGINE_GLSERIES

// 選択
#if defined(XBASE_OS_WINDOWS)
    #define XG3D_ENGINE_GL
#elif defined(XBASE_OS_MACOSX)
    #define XG3D_ENGINE_GL
#elif defined(XBASE_OS_IOS)
    #define XG3D_ENGINE_GLES
#else
    #error "Not supported OS."
#endif

// 選択後の定義
#if defined(XG3D_ENGINE_GL)
    #define XG3D_TARGET_ENGINE (::XG3D::Engine::GL)
    #define XG3D_ENGINE_GLSERIES
#elif defined(XG3D_ENGINE_GLES)
    #define XG3D_TARGET_ENGINE (::XG3D::Engine::GLES)
    #define XG3D_ENGINE_GLSERIES
#endif

//@}
//------------------------------------------------------------------------------
namespace XG3D {

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

} // namespace
#endif
// EOF
