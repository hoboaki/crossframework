// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLSUBMESH_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLSUBMESH_HPP

#include <ae/base/Pointer.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/ResMdlShape.hpp>

namespace ae {
namespace g3d {
class ResMdlSubMeshImpl;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
/// @brief XMDL::sub_meshデータのアクセサ。
/// @details
/// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
class ResMdlSubMesh
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 無効なオブジェクトを作成。
    ResMdlSubMesh();

    /// 有効なオブジェクトを作成。
    ResMdlSubMesh(const ResMdlSubMeshImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResMdlSubMesh& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResMdlSubMesh& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    int index()const;          ///< 自身のインデックス番号。
    int nodeIndex()const;      ///< @brief ぶらさがるノードのインデックス。 @details シンプルメッシュの場合はぶらさがるノードのインデックス番号を返し、スキニングメッシュの場合は ResConstant::INVALID_MDL_NODE_INDEX を返します。
    int matReferIndex()const;  ///< @brief 描画に使用するマテリアル参照のインデックス。 
    ResMdlShape shape()const;   ///< 描画に使用するシェイプ。
    //@}

private:
    ::ae::base::Pointer< const ResMdlSubMeshImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
