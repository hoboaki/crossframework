// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLNODE_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLNODE_HPP

#include <ae/base/Matrix34.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

namespace ae {
namespace g3d {
class ResMdlNodeImpl;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
/// @brief XMDL::nodeデータのアクセサ。
/// @details
/// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
class ResMdlNode
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 無効なオブジェクトを作成。
    ResMdlNode();

    /// 有効なオブジェクトを作成。
    ResMdlNode(const ResMdlNodeImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResMdlNode& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResMdlNode& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    int index()const;                  ///< 自身のインデックス番号。
    const char* name()const;            ///< 名前。
    int parentNodeIndex()const;        ///< @brief 親ノードのノードインデックス番号。 @return 親がなければ ResConstant::INVALID_MDL_NODE_INDEX を返す。
    int firstChildNodeIndex()const;    ///< @brief 長男ノードのノードインデックス番号。 @return 子がなければ ResConstant::INVALID_MDL_NODE_INDEX を返す。
    int nextSiblingNodeIndex()const;   ///< @brief 次の兄弟ノードのノードインデックス番号。 @return 兄弟がなければ ResConstant::INVALID_MDL_NODE_INDEX を返す。
    ::ae::base::Mtx34 rtMtx()const;        ///< RotateTrans行列の初期値。
    ::ae::base::Vec3  scale()const;        ///< Scale値の初期値。
    const ::ae::base::Mtx34* bindPoseMtxPtr()const; ///< @brief バインドポーズ行列のポインタ。 @return ResMdlレベルでバインドポーズ行列が不要な場合は0を返す。
    //@}

private:
    ::ae::base::Pointer< const ResMdlNodeImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
