// 文字コード：UTF-8
#include "ResMatImpl.hpp"

//------------------------------------------------------------------------------
#include <cstdlib>
#include <XBase/ArrayLength.hpp>
#include <XBase/Ref.hpp>
#include "GLCMD.hpp"

//------------------------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------------------------
namespace {

//------------------------------------------------------------------------------
struct tEntryHeader
{
    ::XData::SInt32      count;
    ::XData::Reference  entries[1]; // 本当は無限長配列
};

//------------------------------------------------------------------------------
bool tCreateShader(
    GLuint* aShader,
    const GLenum aShaderType,
    const GLchar* aSource
    )
{
    GLint status = GLint();
    XG3D_GLCMD(*aShader = glCreateShader(aShaderType));
    XG3D_GLCMD(glShaderSource(*aShader, 1, &aSource, 0));
    XG3D_GLCMD(glCompileShader(*aShader));

#if defined(XLIBRARY_DEBUG)
    {
        GLint logLength;
        XG3D_GLCMD(glGetShaderiv(*aShader, GL_INFO_LOG_LENGTH, &logLength));
        if (logLength > 0) {
            GLchar *log = (GLchar *)malloc(logLength);
            XG3D_GLCMD(glGetShaderInfoLog(*aShader, logLength, &logLength, log));
            XBASE_COUT_LINE(log);
            free(log);
        }
    }
#endif

    XG3D_GLCMD(glGetShaderiv(*aShader, GL_COMPILE_STATUS, &status));
    if (status == GL_FALSE) {
        XG3D_GLCMD(glDeleteShader(*aShader));
        *aShader = GLuint();
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
bool tLinkProgram(GLuint aProgram)
{
    GLint status = GLint();
    XG3D_GLCMD(glLinkProgram(aProgram));
    XG3D_GLCMD(glGetProgramiv(aProgram, GL_LINK_STATUS, &status));
    if (status == 0) {
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
bool tValidateProgram(GLuint aProgram)
{
#if defined(XBASE_OS_MACOSX)
        // macos 10.11 環境で動作しないため即リターン。
    return true;
#endif
    GLint status = GLint();
    XG3D_GLCMD(glValidateProgram(aProgram));
    XG3D_GLCMD(glGetProgramiv(aProgram, GL_VALIDATE_STATUS, &status));
    if (status == 0) {
        return false;
    }
    return true;
}
}
//------------------------------------------------------------------------------
ResMatImpl::ResMatImpl(
    const ::XData::XData& aXData,
    const BinResMat* aBinPtr,
    ::XBase::IAllocator& aAllocator
    )
: xdata(aXData.ptr())
, binPtr(aBinPtr)
, shaderProgram(0)
, sysUniformLocations()
, paramImpls()
, vtxAttrs()
{
    // param
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->params);
        paramImpls.init(header->count, ::XBase::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            paramImpls->add(
                ::XBase::Ref(xdata),
                xdata.ref< BinResMatParam >(header->entries[i]),
                ::XBase::Ref(aAllocator)
                );
        }
    }

    // vtxAttrs
    {
        const tEntryHeader* header = xdata.ref< tEntryHeader >(binPtr->vtxAttrs);
        vtxAttrs.init(header->count, ::XBase::Ref(aAllocator));
        for (int i = 0; i < header->count; ++i) {
            vtxAttrs->add(
                ::XBase::Ref(xdata),
                xdata.ref< BinResMatVtxAttr >(header->entries[i]),
                ::XBase::Ref(aAllocator)
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
    XG3D_GLCMD(shaderProgram = glCreateProgram());

    // シェーダーソースを作成
    GLuint srcVSH = GLuint();
    if (!tCreateShader(&srcVSH, GL_VERTEX_SHADER, xdata.ref< GLchar >(binPtr->vshSrcText))) {
        XBASE_COUT(xdata.ref< GLchar >(binPtr->vshSrcText));
        XBASE_NOT_REACH_ASSERT_MSG("VSH compile failed.");
        XG3D_GLCMD(glDeleteProgram(shaderProgram));
        shaderProgram = 0;
        return;
    }
    GLuint srcPSH = GLuint();
    if (!tCreateShader(&srcPSH, GL_FRAGMENT_SHADER, xdata.ref< GLchar >(binPtr->pshSrcText))) {
        XBASE_COUT(xdata.ref< GLchar >(binPtr->pshSrcText));
        XBASE_NOT_REACH_ASSERT_MSG("PSH compile failed.");
        XG3D_GLCMD(glDeleteShader(srcVSH));
        XG3D_GLCMD(glDeleteProgram(shaderProgram));
        shaderProgram = 0;
        return;
    }

    // アタッチ
    XG3D_GLCMD(glAttachShader(shaderProgram, srcVSH));
    XG3D_GLCMD(glAttachShader(shaderProgram, srcPSH));

    // 属性バインド
    for (int i = 0; i < vtxAttrs->count(); ++i) {
        const ResMatVtxAttrImpl* vtxAttr = &vtxAttrs->at(i);
        XG3D_GLCMD(glBindAttribLocation(shaderProgram, i, vtxAttr->xdata.ref< char >(vtxAttr->binPtr->symbolName)));
    }

    // リンク＆チェック
    if (!tLinkProgram(shaderProgram)
        || !tValidateProgram(shaderProgram)
        )
    {
        XBASE_NOT_REACH_ASSERT_MSG("Shader link failed.");
        XG3D_GLCMD(glDeleteShader(srcPSH));
        XG3D_GLCMD(glDeleteShader(srcVSH));
        XG3D_GLCMD(glDeleteProgram(shaderProgram));
        shaderProgram = 0;
        return;
    }

    // ユニフォーム取得
    {
        const char* TABLE[] =
        {
            "_prmMtxProj",
            "_prmMtxView",
            "_prmMtxWorld"
        };
        XBASE_ARRAY_LENGTH_CHECK(TABLE, ShaderConstant::SysUniform_TERMINATE);
        for (int i = 0; i < ShaderConstant::SysUniform_TERMINATE; ++i) {
            sysUniformLocations[i] = glGetUniformLocation(shaderProgram, TABLE[i]);
        }
    }

    // 後始末
    XG3D_GLCMD(glDeleteShader(srcPSH));
    XG3D_GLCMD(glDeleteShader(srcVSH));
}

//------------------------------------------------------------------------------
void ResMatImpl::release()
{
    // セットアップしていなければ何もしない
    if (shaderProgram == 0) {
        return;
    }

    // シェーダープログラムの破棄
    XG3D_GLCMD(glUseProgram(0));
    XG3D_GLCMD(glDeleteProgram(shaderProgram));
    shaderProgram = 0;
}

} // namespace
// EOF
