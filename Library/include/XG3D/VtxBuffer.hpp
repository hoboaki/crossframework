// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_VTXBUFFER_HPP)
#else
#define XG3D_INCLUDED_VTXBUFFER_HPP

#include <XBase/Color4.hpp>
#include <XBase/IAllocator.hpp>
#include <XBase/Matrix34.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/RuntimeMArray.hpp>
#include <XBase/Vector2.hpp>
#include <XBase/Vector3.hpp>
#include <XBase/Vector4.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/Engine.hpp>
#include <XG3D/PrimitiveKind.hpp>

#if defined(XG3D_ENGINE_GLSERIES)
    #include <XG3D/VtxBuffer_GL.hpp>
#endif

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Util
//@{
    /// @brief 頂点バッファ。
    /// @details
    /// 頂点配列のバッファの作成・保持・描画をするクラスです。 @n
/// プログラムコードで何かを簡易に描画する用に作られています。 @n
class VtxBuffer : public ::XBase::NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief コンストラクタ。
    /// @param aMeshCountMax 最大メッシュ数。
    /// @param aVertexCountMax 最大頂点数。
    /// @param aAllocator 頂点・メッシュ情報を配置するためのアロケータ。
    VtxBuffer(
        int aMeshCountMax,
        int aVertexCountMax,
        ::XBase::IAllocator& aAllocator = ::XBase::IAllocator::Default()
        );

/// デストラクタ。
    ~VtxBuffer();
    //@}

    /// @name リセット
    //@{
    void reset(); ///< コンストラクトした直後の状態に戻す。
    void clear(); ///< 構築したメッシュを破棄する。
    //@}

    /// @name メッシュの構築準備
    //@{
    /// @brief 次回のメッシュ構築の際に使用するワールド行列を指定する。
    /// @param aMtx XBase::Matrix34Pod::Translate() などで作られたワールド行列。
    /// @details
    /// 初期値は単位行列です。@n
    /// 引数の行列の値はコピーされます。 @n
    /// beginの前に呼ぶようにしてください。
    void worldMtx(const ::XBase::Matrix34Pod& aMtx);
    //@}

    /// @name メッシュの構築の開始と終わり
    //@{
    /// メッシュの構築を始めるタイミングで呼ぶ。
    void begin(PrimitiveKind aKind);

    /// １つのメッシュの構築が終わったタイミングで呼ぶ。
    void end();
    //@}

    /// @name メッシュの頂点構築
    //@{
    void normal(f32 aX, f32 aY, f32 aZ);        ///< 次に追加する頂点の法線を指定する。
    void normal(const ::XBase::Vector3Pod& aXYZ); ///< @copydoc normal()
    void texCoord(f32 aS, f32 aT);                   ///< 次に追加する頂点のテクスチャ座標を指定する。
    void texCoord(const ::XBase::Vector2Pod& aST);    ///< @copydoc texCoord()
    void color(f32 aR, f32 aG, f32 aB);             ///< 次に追加する頂点の色を指定する。
    void color(f32 aR, f32 aG, f32 aB, f32 aA);    ///< @copydoc color()
    void color(const ::XBase::Color4Pod& aRGBA);      ///< @copydoc color()
    void vertex(f32 aX, f32 aY);                 ///< 頂点の位置を決定し今回の頂点を頂点バッファに追加する。
    void vertex(f32 aX, f32 aY, f32 aZ);        ///< @copydoc vertex()
    void vertex(const ::XBase::Vector2Pod& aXY);  ///< @copydoc vertex()
    void vertex(const ::XBase::Vector3Pod& aXYZ); ///< @copydoc vertex()
    //@}

    /// @name バッファの構築と描画
    //@{

    /// @brief 構築された全メッシュをバッファに落とし込む。
    /// @details
    /// この関数を呼ぶと reset() もしくは clear() を呼ぶまでメッシュの構築ができなくなります。
    void flush();

    /// @brief 構築されたバッファを使って描画する。
    /// @details
    /// この関数が呼ばれる前に flush() が呼ばれている必要があります。@n
    void draw();

    //@}

private:
    struct Vertex
    {
        ::XBase::Vector3Pod position;
        ::XBase::Vector3Pod normal;
        ::XBase::Vector2Pod texCoord;
        ::XBase::Color4Pod  color;
    };
    struct Mesh
    {
        ::XBase::Matrix34 worldMtx;
        int beginIndex; // 頂点追加中は頂点の開始index。終了後はelementの開始index。
        int count; // 頂点追加中は頂点の個数。終了後はelementの個数。
        PrimitiveKind kind;
    };
    typedef u16 Index;
    //------------------------------------------------------------------------------
    ::XBase::RuntimeMArray< Vertex > mVertexArray;
    ::XBase::RuntimeMArray< Index >  mIndexArray;
    ::XBase::RuntimeMArray< Mesh >   mMeshArray;
    VtxBuffer_EXT  mEXT;
    ::XBase::Matrix34 mWorldMtx;
    ::XBase::Vector3  mNormal;
    ::XBase::Vector2  mTexCoord;
    ::XBase::Color4   mColor;
    ::XBase::Bool32 mIsMeshActive;
    ::XBase::Bool32 mIsFlushed;
};
//@}

} // namespace
#endif
// EOF
