/**
 * @file
 * @brief GLCMDマクロを記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_GLCMD_HPP)
#else
#define XG3D_INCLUDED_GLCMD_HPP

//------------------------------------------------------------
#include <XBase/Config.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XG3D/SDKHeader.hpp>

//------------------------------------------------------------

// GLコマンドを実行しエラーがないかチェックする。
#if defined(XBASE_CONFIG_ENABLE_RUNTIME_ERROR)
    #if defined(XBASE_OS_IOS) || defined(XBASE_OS_MACOSX)
        #define XG3D_GLCMD( aCMD ) \
            do \
            { \
                aCMD; \
                const GLenum local_glCommandResult = glGetError(); \
                XBASE_ASSERT_MSGFMT( local_glCommandResult == GL_NO_ERROR \
                    , "GL Error: %#lx \n%s\n" \
                    , local_glCommandResult \
                    , #aCMD \
                    ); \
            } while( false )
    #else
        #define XG3D_GLCMD( aCMD ) \
            do \
            { \
                aCMD; \
                const GLenum local_glCommandResult = glGetError(); \
                XBASE_ASSERT_MSGFMT( local_glCommandResult == GL_NO_ERROR \
                    , "GL Error: %#lx (%s)\n%s\n" \
                    , local_glCommandResult \
                    , gluErrorString( local_glCommandResult )  \
                    , #aCMD \
                    ); \
            } while( false )
    #endif
#else
    #define XG3D_GLCMD( aCMD ) aCMD
#endif

//------------------------------------------------------------
#endif
// EOF
