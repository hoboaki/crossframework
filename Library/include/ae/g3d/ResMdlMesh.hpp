// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_RESMDLMESH_HPP)
#else
#define XG3D_INCLUDED_RESMDLMESH_HPP

#include <XBase/Pointer.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/ResMdlSubMesh.hpp>

namespace XG3D {
class ResMdlMeshImpl;
}

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-Res
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
    ::XBase::Pointer< const ResMdlMeshImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

} // namespace
#endif
// EOF
