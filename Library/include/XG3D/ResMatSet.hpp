// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMATSET_HPP)
#else
#define XG3D_INCLUDED_RESMATSET_HPP

#include <XBase/Pointer.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/ResMat.hpp>

namespace XG3D {
class ResMatSetImpl;
}

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Res
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
    uint        index()const;   ///< 自身のインデックス番号。
    const char* name()const;     ///< 名前。
    uint        matCount()const; ///< マテリアルの総数。
    ResMat      mat(uint aIndex)const; ///< 指定番目のマテリアルを取得。
    ResMat      mat(const char* aName)const; ///< 指定の名前のマテリアルを取得。
    //@}

private:
    ::XBase::Pointer< const ResMatSetImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

} // namespace
#endif
// EOF
