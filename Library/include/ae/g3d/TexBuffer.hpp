// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_TEXBUFFER_HPP)
#else
#define AE_G3D_INCLUDED_TEXBUFFER_HPP

#include <ae/base/IAllocator.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/Engine.hpp>
#include <ae/g3d/TexResData.hpp>

#if defined(AE_G3D_ENGINE_GLSERIES)
#include <ae/g3d/TexBuffer_GL.hpp>
#endif

namespace ae {
namespace g3d {
class TexSetting;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Util
//@{
/// @brief テクスチャバッファ。
/// @details
/// テクスチャの描画用バッファの作成・保持をするクラスです。 @n
class TexBuffer : public ::ae::base::NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// コンストラクタ。
    TexBuffer(const TexResData& aData);

    /// デストラクタ。
    ~TexBuffer();
    //@}

    /// @name 大きさ
    //@{
    int imageWidth()const;  ///< イメージの横ピクセル数。
    int imageHeight()const; ///< イメージの縦ピクセル数。
    //@}

    // 内部実装用関数群。
    const TexBuffer_Ext& ext_()const;
    TexBuffer_Ext& ext_();

private:
    TexBuffer_Ext mExt;
    TexResData mResData;
};
//@}

}} // namespace
#endif
// EOF
