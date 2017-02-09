// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDL_HPP)
#else
#define AE_G3D_INCLUDED_RESMDL_HPP

#include <ae/base/Pointer.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/ResMdlMatRefer.hpp>
#include <ae/g3d/ResMdlMesh.hpp>
#include <ae/g3d/ResMdlNode.hpp>
#include <ae/g3d/ResMdlShape.hpp>

namespace ae {
namespace g3d {
class ResMdlImpl;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
    /// @brief XMDLデータのアクセサ。
    /// @details
/// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
class ResMdl
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 無効なオブジェクトを作成。
    ResMdl();

    /// 有効なオブジェクトを作成。
    ResMdl(const ResMdlImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResMdl& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResMdl& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    int            index()const;                   ///< 自身のインデックス番号。
    const char*     name()const;                    ///< 名前。
    int            matReferCount()const;           ///< マテリアル参照の総数。
    ResMdlMatRefer  matRefer(int aIndex)const;   ///< 指定番目のマテリアル参照を取得。
    int            meshCount()const;               ///< メッシュリソースの総数。
    ResMdlMesh      mesh(int aIndex)const;       ///< 指定番目のメッシュリソースの取得。
    ResMdlMesh      mesh(const char* aName)const; ///< 指定の名前のメッシュリソースの取得。
    int            nodeCount()const;               ///< ノードリソースの総数。
    ResMdlNode      node(int aIndex)const;       ///< 指定番目のノードリソースの取得。
    ResMdlNode      node(const char* aName)const; ///< 指定の名前のノードリソースの取得。
    int            shapeCount()const;              ///< シェイプリソースの総数。
    ResMdlShape     shape(int aIndex)const;      ///< 指定番目のシェイプリソースの取得。
    ResMdlShape     shape(const char* aName)const;///< 指定の名前のシェイプリソースの取得。
    //@}

private:
    ::ae::base::Pointer< const ResMdlImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
