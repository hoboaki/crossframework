/*
 * @file
 * @brief ResMdlSubMesh型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_RESMDLSUBMESH_HPP)
#else
#define XG3D_INCLUDED_RESMDLSUBMESH_HPP

//------------------------------------------------------------
#include <XBase/Pointer.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/ResMdlShape.hpp>

//------------------------------------------------------------
namespace XG3D {
    class ResMdlSubMeshImpl;
}

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Res
//@{
    /**
     * @brief XMDL::sub_meshデータのアクセサ。
     * @details
     * ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
     */
    class ResMdlSubMesh
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        /// 無効なオブジェクトを作成。
        ResMdlSubMesh();

        /// 有効なオブジェクトを作成。
        ResMdlSubMesh( const ResMdlSubMeshImpl& aImpl );
        //@}
        
        /// @name 全般
        //@{        
        bool isValid()const; ///< 有効なデータか。
        bool equals( const ResMdlSubMesh& aRHS )const; ///< 同じデータを指しているか。
        bool operator==( const ResMdlSubMesh& aRHS )const; ///< equals() のエイリアス。
        //@}

        /// @name プロパティの取得( isValid() なときしかアクセスできません)
        //@{
        uint index()const;          ///< 自身のインデックス番号。
        uint nodeIndex()const;      ///< @brief ぶらさがるノードのインデックス。 @details シンプルメッシュの場合はぶらさがるノードのインデックス番号を返し、スキニングメッシュの場合は ResConstant::INVALID_MDL_NODE_INDEX を返します。
        uint matReferIndex()const;  ///< @brief 描画に使用するマテリアル参照のインデックス。 
        ResMdlShape shape()const;   ///< 描画に使用するシェイプ。
        //@}

    private:
        ::XBase::Pointer< const ResMdlSubMeshImpl > mPtr;
        //------------------------------------------------------------
        bool checkInvalid()const;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
