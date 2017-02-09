// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLMESH_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLMESH_HPP

#include <ae/base/Pointer.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/ResMdlSubMesh.hpp>

namespace ae {
namespace g3d {
class ResMdlMeshImpl;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
    /// @brief XMDL::meshデータのアクセサ。
    /// @details
/// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
class ResMdlMesh
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 無効なオブジェクトを作成。
    ResMdlMesh();

    /// 有効なオブジェクトを作成。
    ResMdlMesh(const ResMdlMeshImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResMdlMesh& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResMdlMesh& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    int            index()const;                   ///< 自身のインデックス番号。
    const char*     name()const;                    ///< 名前。
    int            subMeshCount()const;            ///< サブメッシュリソースの総数。
    ResMdlSubMesh   subMesh(int aIndex)const;    ///< 指定番目のサブメッシュリソースの取得。
    //@}

private:
    ::ae::base::Pointer< const ResMdlMeshImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
