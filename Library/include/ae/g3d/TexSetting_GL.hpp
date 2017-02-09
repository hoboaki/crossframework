// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_TEXSETTING_GL_HPP)
#else
#define AE_G3D_INCLUDED_TEXSETTING_GL_HPP

#include <ae/g3d/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

// TexSettingの拡張。
class TexSetting_EXT
{
public:
    GLuint texId;

    //============================================================
    TexSetting_EXT();
    ~TexSetting_EXT();
};

}} // namespace
#endif
// EOF
