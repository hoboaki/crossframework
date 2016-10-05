// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_TEXSETTING_GL_HPP)
#else
#define XG3D_INCLUDED_TEXSETTING_GL_HPP

#include <XG3D/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

// TexSettingの拡張。
class TexSetting_EXT
{
public:
    GLuint texId;

    //============================================================
    TexSetting_EXT();
    ~TexSetting_EXT();
};

} // namespace
#endif
// EOF
