/*
 * @file
 * @brief ResMdl型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_RESMDL_HPP)
#else
#define XG3D_INCLUDED_RESMDL_HPP

//------------------------------------------------------------------------------
#include <XBase/Pointer.hpp>
#include <XG3D/BuiltInTypes.hpp>
#include <XG3D/ResMdlMatRefer.hpp>
#include <XG3D/ResMdlMesh.hpp>
#include <XG3D/ResMdlNode.hpp>
#include <XG3D/ResMdlShape.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
    class ResMdlImpl;
}

//------------------------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Res
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
        ResMdl( const ResMdlImpl& aImpl );
        //@}
        
        /// @name 全般
        //@{        
        bool isValid()const; ///< 有効なデータか。
        bool equals( const ResMdl& aRHS )const; ///< 同じデータを指しているか。
        bool operator==( const ResMdl& aRHS )const; ///< equals() のエイリアス。
        //@}

        /// @name プロパティの取得( isValid() なときしかアクセスできません)
        //@{
        uint            index()const;                   ///< 自身のインデックス番号。
        const char*     name()const;                    ///< 名前。
        uint            matReferCount()const;           ///< マテリアル参照の総数。
        ResMdlMatRefer  matRefer( uint aIndex )const;   ///< 指定番目のマテリアル参照を取得。
        uint            meshCount()const;               ///< メッシュリソースの総数。
        ResMdlMesh      mesh( uint aIndex )const;       ///< 指定番目のメッシュリソースの取得。
        ResMdlMesh      mesh( const char* aName )const; ///< 指定の名前のメッシュリソースの取得。
        uint            nodeCount()const;               ///< ノードリソースの総数。
        ResMdlNode      node( uint aIndex )const;       ///< 指定番目のノードリソースの取得。
        ResMdlNode      node( const char* aName )const; ///< 指定の名前のノードリソースの取得。
        uint            shapeCount()const;              ///< シェイプリソースの総数。
        ResMdlShape     shape( uint aIndex )const;      ///< 指定番目のシェイプリソースの取得。
        ResMdlShape     shape( const char* aName )const;///< 指定の名前のシェイプリソースの取得。
        //@}

    private:
        ::XBase::Pointer< const ResMdlImpl > mPtr;
        //------------------------------------------------------------------------------
        bool checkInvalid()const;
    };
//@}

} // namespace
#endif
// EOF
