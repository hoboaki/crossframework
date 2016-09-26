/*
 * @file
 * @brief ResMdlNode型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_RESMDLNODE_HPP)
#else
#define XG3D_INCLUDED_RESMDLNODE_HPP

//------------------------------------------------------------
#include <XBase/Matrix34.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Vector3.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XG3D {
    class ResMdlNodeImpl;
}

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Res
//@{
    /**
     * @brief XMDL::nodeデータのアクセサ。
     * @details
     * ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
     */
    class ResMdlNode
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        /// 無効なオブジェクトを作成。
        ResMdlNode();

        /// 有効なオブジェクトを作成。
        ResMdlNode( const ResMdlNodeImpl& aImpl );
        //@}
        
        /// @name 全般
        //@{        
        bool isValid()const; ///< 有効なデータか。
        bool equals( const ResMdlNode& aRHS )const; ///< 同じデータを指しているか。
        bool operator==( const ResMdlNode& aRHS )const; ///< equals() のエイリアス。
        //@}

        /// @name プロパティの取得( isValid() なときしかアクセスできません)
        //@{
        uint index()const;                  ///< 自身のインデックス番号。
        const char* name()const;            ///< 名前。
        uint parentNodeIndex()const;        ///< @brief 親ノードのノードインデックス番号。 @return 親がなければ ResConstant::INVALID_MDL_NODE_INDEX を返す。
        uint firstChildNodeIndex()const;    ///< @brief 長男ノードのノードインデックス番号。 @return 子がなければ ResConstant::INVALID_MDL_NODE_INDEX を返す。
        uint nextSiblingNodeIndex()const;   ///< @brief 次の兄弟ノードのノードインデックス番号。 @return 兄弟がなければ ResConstant::INVALID_MDL_NODE_INDEX を返す。
        ::XBase::Mtx34 rtMtx()const;        ///< RotateTrans行列の初期値。
        ::XBase::Vec3  scale()const;        ///< Scale値の初期値。
        const ::XBase::Mtx34* bindPoseMtxPtr()const; ///< @brief バインドポーズ行列のポインタ。 @return ResMdlレベルでバインドポーズ行列が不要な場合は0を返す。
        //@}

    private:
        ::XBase::Pointer< const ResMdlNodeImpl > mPtr;
        //------------------------------------------------------------
        bool checkInvalid()const;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
