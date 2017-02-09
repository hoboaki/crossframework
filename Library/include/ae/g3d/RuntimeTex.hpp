// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RUNTIMETEX_HPP)
#else
#define AE_G3D_INCLUDED_RUNTIMETEX_HPP

#include <ae/base/AutoMemBlock.hpp>
#include <ae/base/Color4.hpp>
#include <ae/base/Color4b.hpp>
#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/RuntimeTexContext.hpp>
#include <ae/g3d/TexResData.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Util
//@{
    /// @brief 実行時にイメージをを生成するテクスチャ。
    /// @details
    /// 普通のテクスチャと同様に左下原点の座標系です。@n
    /// @n
    /// setPixel() で渡したカラーはフォーマットによって使用する値が異なります。@n
    /// ・RGBA系 : RGBA を RGBA に代入@n
    /// ・RGB系 : RGB を RGB に代入@n
    /// ・LA系 : RA を LA に代入@n
    /// ・L系 : R を L に代入@n
/// ・A系 : A を A に代入@n
class RuntimeTex
    : public ::ae::base::NonCopyable
{
public:
    /// @name ユーティリティ
    //@{
    static pword_t CalcDataSize(const RuntimeTexContext&); ///< 必要なデータサイズを計算する。
    static pword_t RequireAlignment(); ///< データに必要なアライメント値を取得する。
    //@}

    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief コンストラクタ。
    /// @param aContext コンテキスト。
    /// @param aAllocator データ領域を確保するのに使うアロケータ。
    RuntimeTex(
        const RuntimeTexContext& aContext
        , ::ae::base::IAllocator& aAllocator = ::ae::base::IAllocator::Default()
    );

/// デストラクタ。
    ~RuntimeTex();
    //@}

    /// @name 取得
    //@{
    const RuntimeTexContext context()const; ///< 作成時に使用したコンテキスト。
    const ::ae::base::MemBlock data()const;    ///< イメージデータ。
    const TexResData texResData()const;     ///< TexBufferに渡すデータ。
    //@}

    /// @name 編集
    //@{
    void beginEdit(); ///< 編集開始前に必ず呼ぶべき関数。
    void endEdit();   ///< 編集終了後に必ず呼ぶべき関数。
    void setPixel(int aX, int aY, const ::ae::base::Color4Pod&);  ///< 指定の座標のピクセルを設定。
    void setPixel(int aX, int aY, const ::ae::base::Color4bPod&); ///< 指定の座標のピクセルを設定。
    //@}

private:
    const RuntimeTexContext mContext;
    ::ae::base::AutoMemBlock mData;
};
//@}

}} // namespace
#endif
// EOF
