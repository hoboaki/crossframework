// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_TEXBUFFER_HPP)
#else
#define XG3D_INCLUDED_TEXBUFFER_HPP

#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/Engine.hpp>
#include <XG3D/TexResData.hpp>

#if defined(XG3D_ENGINE_GLSERIES)
#include <XG3D/TexBuffer_GL.hpp>
#endif

namespace XG3D {
class TexSetting;
}

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Util
//@{
    /// @brief テクスチャバッファ。
    /// @details
/// テクスチャの描画用バッファの作成・保持をするクラスです。 @n
class TexBuffer : public ::XBase::NonCopyable
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
    const TexBuffer_EXT& ext_()const;
    TexBuffer_EXT& ext_();

private:
    TexBuffer_EXT mExt;
    TexResData mResData;
};
//@}

} // namespace
#endif
// EOF
