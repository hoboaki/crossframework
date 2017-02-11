// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RENDERER_HPP)
#else
#define AE_G3D_INCLUDED_RENDERER_HPP

#include <ae/base/Color4.hpp>
#include <ae/base/Matrix34.hpp>
#include <ae/base/Matrix44.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/Engine.hpp>
#include <ae/g3d/TexId.hpp>

#if defined(AE_G3D_ENGINE_GLSERIES)
#include <ae/g3d/Renderer_GL.hpp>
#endif

namespace ae {
namespace base {
class Display;
class Screen;
}}
namespace ae {
namespace g3d {
class ResMat;
class ResMdlShape;
class ResMdlSubMesh;
class StateMaterial;
class StateMdlMaterial;
class StateMdlTransform;
class TexSetting;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-System
//@{
/// @brief レンダリングを統括するクラス。
class Renderer : public ::ae::base::NonCopyable
{
public:
    /// @name シングルトンアクセス
    //@{
    static Renderer& Instance();
    //@}

    /// @name コンストラクタとデストラクタ
    //@{
    Renderer(::ae::base::Display& aSampleDisplay);
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
    void fbSetClearColor(const ::ae::base::Color4Pod& aColor); ///< クリア時の色値を設定する。初期値RGBA(0,0,0,0)。
    void fbSetClearDepth(float aDepth); ///< クリア時の深度値を設定する。初期値1.0f。
    void fbSetColorUpdate(bool aIsEnable); ///< 色バッファの更新フラグを設定する。初期値true。
    void fbSetDepthUpdate(bool aIsEnable); ///< 深度バッファの更新フラグを設定する。初期値true。
    // void fbSetDepthCompare( DepthCompare );  ///< 深度比較の式を設定する。初期値 DepthCompare_Always 。
    void fbSetDepthCompare(bool aIsEnable); ///< 深度比較を設定する。初期値false。(将来的に引数はEnumになります）
    void fbSetViewport(int aBaseX, int aBaseY, int aWidth, int aHeight); ///< ビューポートを設定する。初期値 Display::mainScreen() の全体。
    //@}

    /// @name シェーダー
    //@{
    void sdReset(); ///< シェーダーの設定を初期値に戻す。
    void sdSetMaterialForDemo(); ///< デモ確認用のマテリアルに設定。
    void sdSetMaterial(const ResMat& aResMat); ///< 指定のマテリアルに設定。
    void sdSetMtxProjection(const ::ae::base::Mtx44&); ///< 射影行列の設定。初期値Ortho: l-r(-1,1) b-t(-1,1) n-f(0,1)。
    void sdSetMtxView(const ::ae::base::Mtx34&);  ///< 視点座標系に変換する行列の設定。初期値は単位行列。
    void sdSetMtxWorld(const ::ae::base::Mtx34&);  ///< ワールド座標系に変換する行列の設定。初期値は単位行列。
    void sdSetMtxBones(const ::ae::base::Vec4* aMtxBonePosArray, const ::ae::base::Vec4* aMtxBoneNrmArray);  ///< スキニング位置変換行列（Vec4x3で1セット）と法線変換行列（Vec4x3で1セット）の設定。初期値は不定値。
    void sdSetTex(TexId::EnumType, const TexSetting&); ///< テクスチャの設定。初期値は全テクスチャが非Activeなテクスチャ。
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
    void copyToDisplay(::ae::base::Display&); ///< 指定したディスプレイのメインスクリーンの描画結果を転送する。
    void copyToScreen(::ae::base::Screen&);   ///< 指定したスクリーンに描画結果を転送する。
    //@}

private:
    ::ae::base::Display& mDisplay;
    Renderer_Ext mExt;
};

//@}

}} // namespace
#endif
// EOF
