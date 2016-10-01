/**
 * @file
 * @brief TexSetting_EXT型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_TEXSETTING_GL_HPP)
#else
#define XG3D_INCLUDED_TEXSETTING_GL_HPP

//------------------------------------------------------------
#include <XG3D/SDKHeader.hpp>

//------------------------------------------------------------
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
}
//------------------------------------------------------------
#endif
// EOF
