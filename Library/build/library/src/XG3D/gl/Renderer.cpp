// 文字コード：UTF-8
#include <XG3D/Renderer.hpp>

#include <XBase/ArrayLength.hpp>
#include <XBase/Console.hpp>
#include <XBase/Display.hpp>
#include <XBase/EnumCheck.hpp>
#include <XBase/Matrix34.hpp>
#include <XBase/Matrix44.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Random.hpp>
#include <XBase/Unused.hpp>
#include <XG3D/ResMdlSubMesh.hpp>
#include <XG3D/ResMdlShape.hpp>
#include <XG3D/StateMaterial.hpp>
#include <XG3D/StateMdlMaterial.hpp>
#include <XG3D/StateMdlTransform.hpp>
#include <XG3D/TexSetting.hpp>
#include "GlCmd.hpp"
#include "ResMatImpl.hpp"
#include "ResMdlShapeImpl.hpp"
#include "ShaderConstant.hpp"

#if defined(XLIBRARY_DEBUG)
#include <stdlib.h>
#endif

//------------------------------------------------------------------------------
namespace XG3D {
//------------------------------------------------------------------------------
namespace {

    // TexAddressテーブル
const GLenum tTexAddressTable[] =
{
    GL_REPEAT,
    GL_MIRRORED_REPEAT,
    GL_CLAMP_TO_EDGE
};
XBASE_ARRAY_LENGTH_CHECK(tTexAddressTable, TexAddress::TERM);

// TexFilterテーブル
const GLenum tTexFilterTable[] =
{
    GL_NEAREST,
    GL_LINEAR
};
XBASE_ARRAY_LENGTH_CHECK(tTexFilterTable, TexFilter::TERM);

// シングルトンインスタンス
::XBase::Pointer< Renderer > tInstance;

// シェーダーソース
const GLchar tSHADER_SOURCE_VSH[] =
#if defined(XG3D_ENGINE_GL)
"#version 120\r\n"
#endif
"#ifdef GL_ES\r\n"
"    #define IN         attribute\r\n"
"    #define OUT        varying\r\n"
"    #define LOWP       lowp\r\n"
"    #define MEDIUMP    mediump\r\n"
"    precision MEDIUMP  float;\r\n"
"    precision MEDIUMP  int;\r\n"
"#else\r\n"
"    #define IN         attribute\r\n"
"    #define OUT        varying\r\n"
"    #define LOWP       \r\n"
"    #define MEDIUMP    \r\n"
"#endif\r\n"
""
"uniform mat4 _prmMtxProj;"
"uniform mat4 _prmMtxView;"
"uniform mat4 _prmMtxWorld;"
""
"IN  vec3 iVtxPosition;"
"IN  vec3 iVtxNormal;"
"IN  vec4 iVtxTexCoord;"
"IN  vec4 iVtxColor;"
"OUT vec4 vColor;"
"OUT vec4 vTexCoord;"
"    "
"void main()"
"{"
"    gl_Position = _prmMtxProj * _prmMtxView * _prmMtxWorld * vec4(iVtxPosition, 1.0);"
"    vColor = iVtxColor;"
"    vTexCoord = iVtxTexCoord;"
"}"
"";
const GLchar tSHADER_SOURCE_FSH[] =
#if defined(XG3D_ENGINE_GL)
"#version 120\r\n"
#endif
"#ifdef GL_ES\r\n"
"    #define IN         varying\r\n"
"    #define LOWP       lowp\r\n"
"    #define MEDIUMP    mediump\r\n"
"    precision MEDIUMP  float;\r\n"
"    precision MEDIUMP  int;\r\n"
"    precision LOWP     sampler2D;\r\n"
"#else\r\n"
"    #define IN         varying\r\n"
"    #define LOWP       \r\n"
"    #define MEDIUMP    \r\n"
"#endif\r\n"
""
"uniform int       uTexActive;"
"uniform sampler2D uTexSampler;"
""
"IN LOWP vec4 vColor;"
"IN LOWP vec4 vTexCoord;"
""
"void main()"
"{"
"    if ( uTexActive != 0 )" "    {"
"        gl_FragColor = vColor * texture2D( uTexSampler , vTexCoord.st );"
"    }"
"    else"
"    {"
"        gl_FragColor = vColor;"
"    }"
"}";
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
        XBASE_ASSERT_NOT_REACHED();
        XG3D_GLCMD(glDeleteShader(*aShader));
        *aShader = GLuint();
        return false;
    }
    return true;
}

bool tLinkProgram(GLuint aProgram)
{
    GLint status = GLint();
    XG3D_GLCMD(glLinkProgram(aProgram));
    XG3D_GLCMD(glGetProgramiv(aProgram, GL_LINK_STATUS, &status));
    if (status == 0) {
        XBASE_ASSERT_NOT_REACHED();
        return false;
    }
    return true;
}

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
        GLchar logBuffer[256];
        glGetProgramInfoLog(aProgram, sizeof(logBuffer), 0, logBuffer);
        XBASE_ASSERT_NOT_REACHED_MSG(logBuffer);
        return false;
    }
    return true;
}

bool tCreateShaderProgram(GLuint* aProgram)
{
    // プログラム作成
    XG3D_GLCMD(*aProgram = glCreateProgram());

    // シェーダーソースを作成
    GLuint srcVSH = GLuint();
    if (!tCreateShader(&srcVSH, GL_VERTEX_SHADER, tSHADER_SOURCE_VSH)) {
        XBASE_ASSERT_NOT_REACHED();
        XG3D_GLCMD(glDeleteProgram(*aProgram));
        return false;
    }
    GLuint srcFSH = GLuint();
    if (!tCreateShader(&srcFSH, GL_FRAGMENT_SHADER, tSHADER_SOURCE_FSH)) {
        XBASE_ASSERT_NOT_REACHED();
        XG3D_GLCMD(glDeleteShader(srcVSH));
        XG3D_GLCMD(glDeleteProgram(*aProgram));
        return false;
    }

    // アタッチ
    XG3D_GLCMD(glAttachShader(*aProgram, srcVSH));
    XG3D_GLCMD(glAttachShader(*aProgram, srcFSH));

    // 属性バインド
    XG3D_GLCMD(glBindAttribLocation(*aProgram, ShaderConstant::Attribute::Position, "iVtxPosition"));
    XG3D_GLCMD(glBindAttribLocation(*aProgram, ShaderConstant::Attribute::Normal, "iVtxNormal"));
    XG3D_GLCMD(glBindAttribLocation(*aProgram, ShaderConstant::Attribute::TexCoord, "iVtxTexCoord"));
    XG3D_GLCMD(glBindAttribLocation(*aProgram, ShaderConstant::Attribute::Color, "iVtxColor"));

    // リンク＆チェック
    if (!tLinkProgram(*aProgram)
        || !tValidateProgram(*aProgram)
        )
    {
        XG3D_GLCMD(glDeleteShader(srcFSH));
        XG3D_GLCMD(glDeleteShader(srcVSH));
        XG3D_GLCMD(glDeleteProgram(*aProgram));
    }

    // 後始末
    XG3D_GLCMD(glDeleteShader(srcFSH));
    XG3D_GLCMD(glDeleteShader(srcVSH));

    // 成功
    return true;
}
}
//------------------------------------------------------------------------------
Renderer& Renderer::Instance()
{
    return tInstance.ref();
}

//------------------------------------------------------------------------------
Renderer::Renderer(::XBase::Display& aDisplay)
: mDisplay(aDisplay)
, mExt()
{
    // セットアップ
    mExt.setup(aDisplay);

    // シェーダープログラムの作成
    if (!tCreateShaderProgram(&mExt.demoShaderProgram)) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }

    // Uniform場所の取得
    mExt.demoUniformLocations[ShaderConstant::SysUniform::MtxProj] = glGetUniformLocation(mExt.demoShaderProgram, "_prmMtxProj");
    mExt.demoUniformLocations[ShaderConstant::SysUniform::MtxView] = glGetUniformLocation(mExt.demoShaderProgram, "_prmMtxView");
    mExt.demoUniformLocations[ShaderConstant::SysUniform::MtxWorld] = glGetUniformLocation(mExt.demoShaderProgram, "_prmMtxWorld");
    mExt.demoUniformLocations[ShaderConstant::Uniform::TexActive] = glGetUniformLocation(mExt.demoShaderProgram, "uTexActive");
    mExt.demoUniformLocations[ShaderConstant::Uniform::TexSampler] = glGetUniformLocation(mExt.demoShaderProgram, "uTexSampler");

    // アルファブレンドは常に有効
    XG3D_GLCMD(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    XG3D_GLCMD(glEnable(GL_BLEND));

    // リセット
    reset();

    // インスタンス設定
    tInstance.set(*this);
}

//------------------------------------------------------------------------------
Renderer::~Renderer()
{
    // インスタンス設定解除
    tInstance.unset(*this);

    // シェーダープログラムの破棄
    XG3D_GLCMD(glUseProgram(0));
    XG3D_GLCMD(glDeleteProgram(mExt.demoShaderProgram));
    mExt.demoShaderProgram = GLuint();
}

//------------------------------------------------------------------------------
void Renderer::reset()
{
    // viewport
    fbSetViewport(0, 0, mDisplay.mainScreen().width(), mDisplay.mainScreen().height());

    // fbClearColor
    fbSetClearColor(::XBase::Color4::Zero());

    // fbClearDepth
    fbSetClearDepth(1.0F);

    // fbColorUpdate
    fbSetColorUpdate(true);

    // fbDepthUpdate
    fbSetDepthUpdate(true);

    // depthCompare
    fbSetDepthCompare(false);

    // シェーダー
    sdReset();
}

//------------------------------------------------------------------------------
void Renderer::fbSetViewport(
    const int aBaseX,
    const int aBaseY,
    const int aWidth,
    const int aHeight
    )
{
    XG3D_GLCMD(glViewport(GLint(aBaseX), GLint(aBaseY), GLint(aWidth), GLint(aHeight)));
}

//------------------------------------------------------------------------------
void Renderer::fbClear()
{
    GLbitfield bits = 0;
    if (mExt.colorUpdate) {
        bits |= GL_COLOR_BUFFER_BIT;
    }
    if (mExt.depthUpdate) {
        bits |= GL_DEPTH_BUFFER_BIT;
    }
    XG3D_GLCMD(glClear(bits));
}

//------------------------------------------------------------------------------
void Renderer::fbSetClearColor(const ::XBase::Color4Pod& aColor)
{
    XG3D_GLCMD(glClearColor(aColor.r, aColor.g, aColor.b, aColor.a));
}

//------------------------------------------------------------------------------
void Renderer::fbSetClearDepth(const float aDepth)
{
#if defined(XG3D_ENGINE_GLES)
    XG3D_GLCMD(glClearDepthf(aDepth));
#else
    XG3D_GLCMD(glClearDepth(aDepth));
#endif
}

//------------------------------------------------------------------------------
void Renderer::fbSetColorUpdate(const bool aIsEnable)
{
    const GLboolean val = aIsEnable ? GL_TRUE : GL_FALSE;
    XG3D_GLCMD(glColorMask(val, val, val, val));
    mExt.colorUpdate = aIsEnable;
}

//------------------------------------------------------------------------------
void Renderer::fbSetDepthUpdate(const bool aIsEnable)
{
    XG3D_GLCMD(glDepthMask(aIsEnable ? GL_TRUE : GL_FALSE));
    mExt.depthUpdate = aIsEnable;
}

//------------------------------------------------------------------------------
void Renderer::fbSetDepthCompare(const bool aIsEnabled)
{
    if (aIsEnabled) {
        XG3D_GLCMD(glEnable(GL_DEPTH_TEST));
        XG3D_GLCMD(glDepthFunc(aIsEnabled ? GL_LESS : GL_ALWAYS));
    }
    else {
        XG3D_GLCMD(glDisable(GL_DEPTH_TEST));
    }
}

//------------------------------------------------------------------------------
void Renderer::sdReset()
{
    // デモ確認用のマテリアルにリセット
    sdSetMaterialForDemo();

    // mtxProjection
    sdSetMtxProjection(::XBase::Matrix44::Ortho(-1, 1, 1, -1, 0, 1));

    // mtxView
    sdSetMtxView(::XBase::Matrix34::Identity());

    // mtxWorld
    sdSetMtxWorld(::XBase::Matrix34::Identity());

    // texMap
    for (int i = 0; i < TexId::TERM; ++i) {
        sdSetTex(TexId::EnumType(i), TexSetting());
    }
}

//------------------------------------------------------------------------------
void Renderer::sdSetMaterialForDemo()
{
    XG3D_GLCMD(glUseProgram(mExt.demoShaderProgram));
    mExt.currentMaterial = ::XG3D::ResMat();
    mExt.updateMtxProj();
    mExt.updateMtxView();
    mExt.updateMtxWorld();
}

//------------------------------------------------------------------------------
void Renderer::sdSetMaterial(const ResMat& aResMat)
{
    // 変更がなければ何もしない
    if (mExt.currentMaterial == aResMat) {
        return;
    }

    // 無効なマテリアルチェック
    if (!aResMat.isValid()) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }

    // 適用
    mExt.currentMaterial = aResMat;
    XG3D_GLCMD(glUseProgram(aResMat.impl_()->shaderProgram));
    mExt.updateMtxProj();
    mExt.updateMtxView();
    mExt.updateMtxWorld();
}

//------------------------------------------------------------------------------
void Renderer::sdSetMtxProjection(const ::XBase::Mtx44& aMtx)
{
    mExt.mtxProj = aMtx;
    mExt.updateMtxProj();
}

//------------------------------------------------------------------------------
void Renderer::sdSetMtxView(const ::XBase::Mtx34& aMtx)
{
    mExt.mtxView = aMtx;
    mExt.updateMtxView();
}

//------------------------------------------------------------------------------
void Renderer::sdSetMtxWorld(const ::XBase::Mtx34& aMtx)
{
    mExt.mtxWorld = aMtx;
    mExt.updateMtxWorld();
}

//------------------------------------------------------------------------------
void Renderer::sdSetTex(const TexId::EnumType aId, const TexSetting& aSetting)
{
    // チェック
    if (XBASE_ENUM_IS_INVALID(TexId, aId)) {
        XBASE_ERROR_INVALID_VALUE(int(aId));
        return;
    }
    XBASE_UNUSED(aId); // マルチテクスチャに対応するタイミングで使用する。

    XG3D_GLCMD(glUseProgram(mExt.demoShaderProgram));
    if (aSetting.isActive()) {
        // 設定準備
        XG3D_GLCMD(glActiveTexture(GL_TEXTURE0));
        XG3D_GLCMD(glBindTexture(GL_TEXTURE_2D, aSetting.ext_().texId));

        // テクスチャ有効
        XG3D_GLCMD(glUniform1i(mExt.demoUniformLocations[ShaderConstant::Uniform::TexActive], 1));
        XG3D_GLCMD(glUniform1i(mExt.demoUniformLocations[ShaderConstant::Uniform::TexSampler], 0));

        // 補間フィルタ
        XG3D_GLCMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tTexFilterTable[aSetting.minFilter()]));
        XG3D_GLCMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tTexFilterTable[aSetting.magFilter()]));

        // アドレッシングモード
        XG3D_GLCMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tTexAddressTable[aSetting.addressU()]));
        XG3D_GLCMD(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tTexAddressTable[aSetting.addressV()]));
    }
    else
    {
        // テクスチャ無効
        XG3D_GLCMD(glUniform1i(mExt.demoUniformLocations[ShaderConstant::Uniform::TexActive], 0));
    }
}

//------------------------------------------------------------------------------
void Renderer::draw(
    const ResMdlSubMesh& aSubMesh,
    const StateMdlTransform& aMdlTransform,
    const StateMdlMaterial& aMdlMaterial
    )
{
    // 前チェック
    if (!aSubMesh.isValid()) {
        XBASE_ASSERT_NOT_REACHED();
        return;
    }

    // ワールド行列設定
    sdSetMtxWorld(aMdlTransform.worldMtx(aSubMesh.nodeIndex()));

    // シェイプの描画
    draw(aSubMesh.shape(), aMdlMaterial.material(aSubMesh.matReferIndex()));
}

//------------------------------------------------------------------------------
void Renderer::draw(
    const ResMdlShape& aShape,
    const StateMaterial& aMaterial
    )
{
    // マテリアル設定
    sdSetMaterial(aMaterial.resMat());

    // 頂点属性有効化
    const ResMdlShapeImpl* shapeImpl = aShape.impl_();
    const ResMatImpl* matImpl = aMaterial.resMat().impl_();
    XG3D_GLCMD(glBindBuffer(GL_ARRAY_BUFFER, shapeImpl->vtxAttrBuffer));
    XG3D_GLCMD(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeImpl->idxBuffer));
    for (int i = 0; i < matImpl->vtxAttrs->count(); ++i) {
        const ResMatVtxAttrImpl* attrBind = &matImpl->vtxAttrs->at(i);
        const ResMdlShapeImpl::VtxAttr* attr = &shapeImpl->vtxAttrs[attrBind->binPtr->bindInputKind];
        XBASE_ASSERT_POINTER(attr->info);
        XG3D_GLCMD(glVertexAttribPointer(
            i,
            attr->info->elemCount,
            attr->glDataType,
            GLboolean(attr->glNormalize),
            shapeImpl->binPtr->vtxAttrDataStride,
            reinterpret_cast<const void*>(attr->info->offset)
        ));
        XG3D_GLCMD(glEnableVertexAttribArray(i));
    }

    // 描画
    XG3D_GLCMD(glDrawElements(
        GL_TRIANGLES,
        shapeImpl->binPtr->indexArrayDataCount,
        shapeImpl->idxGLDataType,
        0
    ));

// 頂点属性無効化
    for (int i = matImpl->vtxAttrs->count(); 0 < i; --i) {
        XG3D_GLCMD(glDisableVertexAttribArray(i - 1));
    }
    XG3D_GLCMD(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    XG3D_GLCMD(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

//------------------------------------------------------------------------------
void Renderer::waitDrawDone()
{
    XG3D_GLCMD(glFinish());
}

//------------------------------------------------------------------------------
void Renderer::copyToDisplay(::XBase::Display& aDisplay)
{
    copyToScreen(aDisplay.mainScreen());
}

//------------------------------------------------------------------------------
Renderer_EXT::Renderer_EXT()
: demoShaderProgram(0)
, demoUniformLocations()
, colorUpdate(false)
, depthUpdate(false)
, currentMaterial()
, mtxProj()
, mtxView()
, mtxWorld()
{
    XBASE_STATIC_ASSERT(UNIFORM_COUNT == ShaderConstant::Uniform::TERM);
}

//------------------------------------------------------------------------------
void Renderer_EXT::updateMtxProj()
{
    const GLint location = currentMaterial.isValid()
        ? currentMaterial.impl_()->sysUniformLocations[ShaderConstant::SysUniform::MtxProj]
        : demoUniformLocations[ShaderConstant::SysUniform::MtxProj];
    XG3D_GLCMD(glUniformMatrix4fv(
        location,
        1,
        GL_FALSE,
        mtxProj.v
    ));
}

//------------------------------------------------------------------------------
void Renderer_EXT::updateMtxView()
{
    const GLint location = currentMaterial.isValid()
        ? currentMaterial.impl_()->sysUniformLocations[ShaderConstant::SysUniform::MtxView]
        : demoUniformLocations[ShaderConstant::SysUniform::MtxView];
    XG3D_GLCMD(glUniformMatrix4fv(
        location,
        1,
        GL_FALSE,
        mtxView.toMatrix44().v
    ));
}

//------------------------------------------------------------------------------
void Renderer_EXT::updateMtxWorld()
{
    const GLint location = currentMaterial.isValid()
        ? currentMaterial.impl_()->sysUniformLocations[ShaderConstant::SysUniform::MtxWorld]
        : demoUniformLocations[ShaderConstant::SysUniform::MtxWorld];
    XG3D_GLCMD(glUniformMatrix4fv(
        location,
        1,
        GL_FALSE,
        mtxWorld.toMatrix44().v
    ));
}

} // namespace
// EOF
