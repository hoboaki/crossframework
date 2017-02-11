// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_TEXSETTING_HPP)
#else
#define AE_G3D_INCLUDED_TEXSETTING_HPP

#include <ae/base/Bool.hpp>
#include <ae/base/Enum.hpp>
#include <ae/g3d/Engine.hpp>
#include <ae/g3d/TexAddress.hpp>
#include <ae/g3d/TexFilter.hpp>

#if defined(AE_G3D_ENGINE_GLSERIES)
#include <ae/g3d/TexSetting_GL.hpp>
#endif

namespace ae {
namespace g3d {
class TexBuffer;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Util
//@{
/// テクスチャの設定。
class TexSetting
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// デフォルトの設定で作成。
    TexSetting();
    //@}

    /// @name 設定
    //@{
    /// @brief アクティブ状態の取得。
    /// @details
    /// 初期値は非アクティブです。@n
    /// 非アクティブ状態だとテクスチャ処理されません。
    bool isActive()const;
    void setIsActive(bool aIsActive);  ///< @brief アクティブ状態の設定。 @see isActive()        

    /// @brief バッファのバインド状態の取得。
    /// @details
    /// 初期値は false 状態です。
    bool isBoundBuffer()const;
    void bindBuffer(const TexBuffer&); ///< @brief 使用するバッファを設定。 @see isBoundBuffer() @details バインド済み状態でバインドした場合、設定が上書きされます。
    void unbindBuffer();  ///< @brief バッファがバインドされていない状態にする。 @see isBoundBuffer() @details バインドされていない状態でこれを呼んだ場合。何もしません。

    /// @brief 縮小補間方法の取得。
    /// @details
    /// 初期値は TexIntpKind::Nearest です。@n
    TexFilter::EnumType minFilter()const;
    void setMinFilter(TexFilter::EnumType); ///< @brief 縮小補間方法の設定。 @see minFilter()

    /// @brief 拡大補間方法の取得。
    /// @details
    /// 初期値は TexIntpKind::Nearest です。@n
    TexFilter::EnumType magFilter()const;
    void setMagFilter(TexFilter::EnumType); ///< @brief 拡大補間方法の設定。 @see magFilter()

    /// @brief U座標のアドレッシングモードの取得。
    /// @details
    /// 初期値は TexAddress::Wrap です。@n
    TexAddress::EnumType addressU()const;
    void setAddressU(TexAddress::EnumType); ///< @brief U座標のアドレッシングモードの設定。 @see addressU()

    /// @brief V座標のアドレッシングモードの取得。
    /// @details
    /// 初期値は TexAddress::Wrap です。@n
    TexAddress::EnumType addressV()const;
    void setAddressV(TexAddress::EnumType); ///< @brief V座標のアドレッシングモードの設定。 @see addressV()
    //@}

    // 内部実装用関数群。
    const TexSetting_EXT& ext_()const;
    TexSetting_EXT& ext_();

private:
    TexSetting_EXT  mExt;
    ::ae::base::Bool32 mIsActive;
    ::ae::base::Enum8< TexFilter::EnumType > mMinFilter;
    ::ae::base::Enum8< TexFilter::EnumType > mMagFilter;
    ::ae::base::Enum8< TexAddress::EnumType > mAddressU;
    ::ae::base::Enum8< TexAddress::EnumType > mAddressV;
};
//@}

}} // namespace
#endif
// EOF
