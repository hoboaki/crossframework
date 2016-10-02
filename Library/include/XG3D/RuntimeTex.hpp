// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RUNTIMETEX_HPP)
#else
#define XG3D_INCLUDED_RUNTIMETEX_HPP

#include <XBase/AutoMemBlock.hpp>
#include <XBase/Color4.hpp>
#include <XBase/Color4b.hpp>
#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/RuntimeTexContext.hpp>
#include <XG3D/TexResData.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Util
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
    : public ::XBase::NonCopyable
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
        , ::XBase::IAllocator& aAllocator = ::XBase::IAllocator::Default()
    );

/// デストラクタ。
    ~RuntimeTex();
    //@}

    /// @name 取得
    //@{
    const RuntimeTexContext context()const; ///< 作成時に使用したコンテキスト。
    const ::XBase::MemBlock data()const;    ///< イメージデータ。
    const TexResData texResData()const;     ///< TexBufferに渡すデータ。
    //@}

    /// @name 編集
    //@{
    void beginEdit(); ///< 編集開始前に必ず呼ぶべき関数。
    void endEdit();   ///< 編集終了後に必ず呼ぶべき関数。
    void setPixel(int aX, int aY, const ::XBase::Color4POD&);  ///< 指定の座標のピクセルを設定。
    void setPixel(int aX, int aY, const ::XBase::Color4bPOD&); ///< 指定の座標のピクセルを設定。
    //@}

private:
    const RuntimeTexContext mContext;
    ::XBase::AutoMemBlock mData;
};
//@}

} // namespace
#endif
// EOF
