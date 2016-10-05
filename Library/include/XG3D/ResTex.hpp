// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESTEX_HPP)
#else
#define XG3D_INCLUDED_RESTEX_HPP

#include <XBase/Pointer.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/ResTexFormat.hpp>

namespace XG3D {
class ResTexImpl;
class TexBuffer;
}

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Res
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
    ::XBase::Pointer< const ResTexImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

} // namespace
#endif
// EOF
