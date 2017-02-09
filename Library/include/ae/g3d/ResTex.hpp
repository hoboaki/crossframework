// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESTEX_HPP)
#else
#define AE_G3D_INCLUDED_RESTEX_HPP

#include <ae/base/Pointer.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/ResTexFormat.hpp>

namespace ae {
namespace g3d {
class ResTexImpl;
class TexBuffer;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
    /// @brief XTEXデータのアクセサ。
    /// @details
/// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
class ResTex
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 無効なオブジェクトを作成。
    ResTex();

    /// 有効なオブジェクトを作成。
    ResTex(const ResTexImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResTex& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResTex& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    int        index()const;   ///< 自身のインデックス番号。
    const char* name()const;    ///< 名前。
    u16 width()const;           ///< 横ピクセル数。
    u16 height()const;          ///< 縦ピクセル数。
    ResTexFormat::EnumType format()const; ///< フォーマット。
    const byte_t* pixels()const;///< ピクセルデータの先頭アドレス。
    const TexBuffer* texBufferPtr()const; ///< @brief バッファ。 @details ResBin::setup() 呼び出し前は0を返します。
    //@}

private:
    ::ae::base::Pointer< const ResTexImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
