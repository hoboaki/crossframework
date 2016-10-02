// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RENDERER_HPP)
#else
#define XG3D_INCLUDED_RENDERER_HPP

#include <XBase/Color4.hpp>
#include <XBase/Matrix34.hpp>
#include <XBase/Matrix44.hpp>
#include <XBase/NonCopyable.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/Engine.hpp>
#include <XG3D/TexId.hpp>

#if defined(XG3D_ENGINE_GLSERIES)
#include <XG3D/Renderer_GL.hpp>
#endif

namespace XBase {
class Display;
class Screen;
}
namespace XG3D {
class ResMat;
class ResMdlShape;
class ResMdlSubMesh;
class StateMaterial;
class StateMdlMaterial;
class StateMdlTransform;
class TexSetting;
}

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-System
//@{
/// @brief レンダリングを統括するクラス。
class Renderer : public ::XBase::NonCopyable
{
public:
    /// @name シングルトンアクセス
    //@{
    static Renderer& Instance();
    //@}

    /// @name コンストラクタとデストラクタ
    //@{
    Renderer(::XBase::Display& aSampleDisplay);
    ~Renderer();
    //@}

    /// @name リセット
    //@{
    /// 初期状態に戻す。
    void reset();
    //@}

    /// @name フレームバッファ
    //@{
    void fbClear(); ///< クリアする。
    void fbSetClearColor(const ::XBase::Color4POD& aColor); ///< クリア時の色値を設定する。初期値RGBA(0,0,0,0)。
    void fbSetClearDepth(float aDepth); ///< クリア時の深度値を設定する。初期値1.0f。
    void fbSetColorUpdate(bool aIsEnable); ///< 色バッファの更新フラグを設定する。初期値true。
    void fbSetDepthUpdate(bool aIsEnable); ///< 深度バッファの更新フラグを設定する。初期値true。
    // void fbSetDepthCompare( DepthCompare );  ///< 深度比較の式を設定する。初期値 DepthCompare_Always 。
    void fbSetViewport(uint aBaseX, uint aBaseY, uint aWidth, uint aHeight); ///< ビューポートを設定する。初期値 Display::mainScreen() の全体。
    //@}

    /// @name シェーダー
    //@{
    void sdReset(); ///< シェーダーの設定を初期値に戻す。
    void sdSetMaterialForDemo(); ///< デモ確認用のマテリアルに設定。
    void sdSetMaterial(const ResMat& aResMat); ///< 指定のマテリアルに設定。
    void sdSetMtxProjection(const ::XBase::Mtx44&); ///< 射影行列の設定。初期値Ortho: l-r(-1,1) b-t(-1,1) n-f(0,1)。
    void sdSetMtxView(const ::XBase::Mtx34&);  ///< 視点座標系に変換する行列の設定。初期値は単位行列。
    void sdSetMtxWorld(const ::XBase::Mtx34&);  ///< ワールド座標系に変換する行列の設定。初期値は単位行列。
    void sdSetTex(TexId, const TexSetting&); ///< テクスチャの設定。初期値は全テクスチャが非Activeなテクスチャ。
    //@}

    /// @name 描画
    //@{
    void draw(const ResMdlSubMesh& aSubMesh, const StateMdlTransform& aMdlTransform, const StateMdlMaterial& aMdlMaterial); ///< SubMesh単位での描画発行。
    void draw(const ResMdlShape& aShape, const StateMaterial& aMaterial); ///< Shape単位での描画発行(非スキニング)。
    //@}

    /// @name 同期
    //@{
    void waitDrawDone(); ///< 描画が完了するまで待つ。
    //@}

    /// @name 転送
    //@{
    void copyToDisplay(::XBase::Display&); ///< 指定したディスプレイのメインスクリーンの描画結果を転送する。
    void copyToScreen(::XBase::Screen&);   ///< 指定したスクリーンに描画結果を転送する。
    //@}

private:
    ::XBase::Display& mDisplay;
    Renderer_EXT mEXT;
};

//@}

} // namespace
#endif
// EOF
