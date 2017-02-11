// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLMATREFER_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLMATREFER_HPP

#include <ae/base/Pointer.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

namespace ae {
namespace g3d {
class ResMdlMatReferImpl;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
/// @brief XMDLのマテリアル参照データのアクセサ。
/// @details
/// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
class ResMdlMatRefer
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 無効なオブジェクトを作成。
    ResMdlMatRefer();

    /// 有効なオブジェクトを作成。
    ResMdlMatRefer(const ResMdlMatReferImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResMdlMatRefer& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResMdlMatRefer& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    int        index()const;   ///< 自身のインデックス番号。
    const char* name()const;    ///< 参照するマテリアルの名前。
    //@}

private:
    ::ae::base::Pointer< const ResMdlMatReferImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
