// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_GLCMD_HPP)
#else
#define AE_G3D_INCLUDED_GLCMD_HPP

#include <ae/base/Config.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/g3d/SdkHeader.hpp>


// GLコマンドを実行しエラーがないかチェックする。
#if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
    #if defined(AE_BASE_OS_IOS) || defined(AE_BASE_OS_MACOSX)
        #define AE_G3D_GLCMD( aCMD ) \
            do \
            { \
                aCMD; \
                const GLenum local_glCommandResult = glGetError(); \
                AE_BASE_ASSERT_MSGFMT( local_glCommandResult == GL_NO_ERROR \
                    , "GL Error: %#lx \n%s\n" \
                    , local_glCommandResult \
                    , #aCMD \
                    ); \
            } while( false )
    #else
        #define AE_G3D_GLCMD( aCMD ) \
            do \
            { \
                aCMD; \
                const GLenum local_glCommandResult = glGetError(); \
                AE_BASE_ASSERT_MSGFMT( local_glCommandResult == GL_NO_ERROR \
                    , "GL Error: %#lx (%s)\n%s\n" \
                    , local_glCommandResult \
                    , gluErrorString( local_glCommandResult )  \
                    , #aCMD \
                    ); \
            } while( false )
    #endif
#else
    #define AE_G3D_GLCMD( aCMD ) aCMD
#endif

#endif
// EOF
