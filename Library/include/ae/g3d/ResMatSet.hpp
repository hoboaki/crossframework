// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMATSET_HPP)
#else
#define AE_G3D_INCLUDED_RESMATSET_HPP

#include <ae/base/Pointer.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/ResMat.hpp>

namespace ae {
namespace g3d {
class ResMatSetImpl;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
/// @brief XMATSETデータのアクセサ。
/// @details
/// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
class ResMatSet
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 無効なオブジェクトを作成。
    ResMatSet();

    /// 有効なオブジェクトを作成。
    ResMatSet(const ResMatSetImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResMatSet& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResMatSet& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    int        index()const;   ///< 自身のインデックス番号。
    const char* name()const;     ///< 名前。
    int        matCount()const; ///< マテリアルの総数。
    ResMat      mat(int aIndex)const; ///< 指定番目のマテリアルを取得。
    ResMat      mat(const char* aName)const; ///< 指定の名前のマテリアルを取得。
    //@}

private:
    ::ae::base::Pointer< const ResMatSetImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
