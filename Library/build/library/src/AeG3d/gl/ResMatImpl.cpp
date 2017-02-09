// 文字コード：UTF-8
#include "ResMatImpl.hpp"

#include <cstdlib>
#include <ae/base/ArrayLength.hpp>
#include <ae/base/Ref.hpp>
#include "GlCmd.hpp"

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {
//------------------------------------------------------------------------------
namespace {

//------------------------------------------------------------------------------
struct tEntryHeader
{
    ::ae::xdata::SInt32      count;
    ::ae::xdata::Reference  entries[1]; // 本当は無限長配列
};

//------------------------------------------------------------------------------
bool tCreateShader(
    GLuint* aShader,
    const GLenum aShaderType,
    const GLchar* aSource
    )
{
    GLint status = GLint();
    AE_G3D_GLCMD(*aShader = glCreateShader(aShaderType));
    AE_G3D_GLCMD(glShaderSource(*aShader, 1, &aSource, 0));
    AE_G3D_GLCMD(glCompileShader(*aShader));

#if defined(XLIBRARY_DEBUG)
    {
        GLint logLength;
        AE_G3D_GLCMD(glGetShaderiv(*aShader, GL_INFO_LOG_LENGTH, &logLength));
        if (logLength > 0) {
            GLchar *log = (GLchar *)malloc(logLength);
            AE_G3D_GLCMD(glGetShaderInfoLog(*aShader, logLength, &logLength, log));
            AE_BASE_COUT_LINE(log);
            free(log);
        }
    }
#endif

    AE_G3D_GLCMD(glGetShaderiv(*aShader, GL_COMPILE_STATUS, &status));
    if (status == GL_FALSE) {
        AE_G3D_GLCMD(glDeleteShader(*aShader));
        *aShader = GLuint();
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
bool tLinkProgram(GLuint aProgram)
{
    GLint status = GLint();
    AE_G3D_GLCMD(glLinkProgram(aProgram));
    AE_G3D_GLCMD(glGetProgramiv(aProgram, GL_LINK_STATUS, &status));
    if (status == 0) {
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
bool tValidateProgram(GLuint aProgram)
{
#if defined(AE_BASE_OS_MACOSX)
        // macos 10.11 環境で動作しないため即リターン。
    return true;
#endif
    GLint status = GLint();
    AE_G3D_GLCMD(glValidateProgram(aProgram));
    AE_G3D_GLCMD(glGetProgramiv(aProgram, GL_VALIDATE_STATUS, &status));
    if (status == 0) {
        return false;
    }
    return true;
}
}
//------------------------------------------------------------------------------
ResMatImpl::ResMatImpl(
    const ::ae::xdata::Xdata& aXdata,
    const BinResMat* aBinPtr,
    ::ae::base::IAllocator& aAllocator
    )
: xdata(aXdata.ptr())
, binPtr(aBinPtr)
, shaderProgram(0)
, sysUniformLocations()
, paramImpls()
, vtxAttrs()
{
    // param
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->params);
        paramImpls.init(header->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            paramImpls->add(
                ::ae::base::Ref(xdata),
                xdata.ref< BinResMatParam >(header->entries[i]),
                ::ae::base::Ref(aAllocator)
                );
        }
    }

    // vtxAttrs
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->vtxAttrs);
        vtxAttrs.init(header->count, ::ae::base::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            vtxAttrs->add(
                ::ae::base::Ref(xdata),
                xdata.ref< BinResMatVtxAttr >(header->entries[i]),
                ::ae::base::Ref(aAllocator)
                );
        }
    }
}

//------------------------------------------------------------------------------
ResMatImpl::~ResMatImpl()
{
    release();
}

//------------------------------------------------------------------------------
void ResMatImpl::setup()
{
    // セットアップ済みなら何もしない
    if (shaderProgram != 0) {
        return;
    }

    // プログラム作成
    AE_G3D_GLCMD(shaderProgram = glCreateProgram());

    // シェーダーソースを作成
    GLuint srcVSH = GLuint();
    if (!tCreateShader(&srcVSH, GL_VERTEX_SHADER, xdata.ref< GLchar >(binPtr->vshSrcText))) {
        AE_BASE_COUT(xdata.ref< GLchar >(binPtr->vshSrcText));
        AE_BASE_ASSERT_NOT_REACHED_MSG("VSH compile failed.");
        AE_G3D_GLCMD(glDeleteProgram(shaderProgram));
        shaderProgram = 0;
        return;
    }
    GLuint srcPSH = GLuint();
    if (!tCreateShader(&srcPSH, GL_FRAGMENT_SHADER, xdata.ref< GLchar >(binPtr->pshSrcText))) {
        AE_BASE_COUT(xdata.ref< GLchar >(binPtr->pshSrcText));
        AE_BASE_ASSERT_NOT_REACHED_MSG("PSH compile failed.");
        AE_G3D_GLCMD(glDeleteShader(srcVSH));
        AE_G3D_GLCMD(glDeleteProgram(shaderProgram));
        shaderProgram = 0;
        return;
    }

    // アタッチ
    AE_G3D_GLCMD(glAttachShader(shaderProgram, srcVSH));
    AE_G3D_GLCMD(glAttachShader(shaderProgram, srcPSH));

    // 属性バインド
    for (int i = 0; i < vtxAttrs->count(); ++i) {
        const ResMatVtxAttrImpl* vtxAttr = &vtxAttrs->at(i);
        AE_G3D_GLCMD(glBindAttribLocation(shaderProgram, i, vtxAttr->xdata.ref< char >(vtxAttr->binPtr->symbolName)));
    }

    // リンク＆チェック
    if (!tLinkProgram(shaderProgram)
        || !tValidateProgram(shaderProgram)
        )
    {
        AE_BASE_ASSERT_NOT_REACHED_MSG("Shader link failed.");
        AE_G3D_GLCMD(glDeleteShader(srcPSH));
        AE_G3D_GLCMD(glDeleteShader(srcVSH));
        AE_G3D_GLCMD(glDeleteProgram(shaderProgram));
        shaderProgram = 0;
        return;
    }

    // ユニフォーム取得
    {
        const char* TABLE[] =
        {
            "_prmMtxProj",
            "_prmMtxView",
            "_prmMtxWorld",
            "_prmMtxBonePosArray",
            "_prmMtxBoneNrmArray",
        };
        AE_BASE_ARRAY_LENGTH_CHECK(TABLE, ShaderConstant::SysUniform::TERM);
        for (int i = 0; i < ShaderConstant::SysUniform::TERM; ++i) {
            sysUniformLocations[i] = glGetUniformLocation(shaderProgram, TABLE[i]);
        }
    }

    // 後始末
    AE_G3D_GLCMD(glDeleteShader(srcPSH));
    AE_G3D_GLCMD(glDeleteShader(srcVSH));
}

//------------------------------------------------------------------------------
void ResMatImpl::release()
{
    // セットアップしていなければ何もしない
    if (shaderProgram == 0) {
        return;
    }

    // シェーダープログラムの破棄
    AE_G3D_GLCMD(glUseProgram(0));
    AE_G3D_GLCMD(glDeleteProgram(shaderProgram));
    shaderProgram = 0;
}

}} // namespace
// EOF
