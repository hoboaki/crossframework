/*
 * @file
 * @brief ResMdlShape型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_RESMDLSHAPE_HPP)
#else
#define XG3D_INCLUDED_RESMDLSHAPE_HPP

//------------------------------------------------------------------------------
#include <XBase/Pointer.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
    class ResMdlShapeImpl;
}

//------------------------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Res
//@{
    /// @brief XMDL::shapeデータのアクセサ。
    /// @details
    /// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
    class ResMdlShape
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        /// 無効なオブジェクトを作成。
        ResMdlShape();

        /// 有効なオブジェクトを作成。
        ResMdlShape( const ResMdlShapeImpl& aImpl );
        //@}
        
        /// @name 全般
        //@{        
        bool isValid()const; ///< 有効なデータか。
        bool equals( const ResMdlShape& aRHS )const; ///< 同じデータを指しているか。
        bool operator==( const ResMdlShape& aRHS )const; ///< equals() のエイリアス。
        //@}

        /// @name プロパティの取得( isValid() なときしかアクセスできません)
        //@{
        const char* name()const; ///< 名前。
        uint  index()const;      ///< 自身のインデックス番号。
        bool  isSkinning()const; ///< スキニングを使ったシェイプか。
        //@}
               
        //============================================================
        // 内部実装用関数群。
        const ResMdlShapeImpl* impl_()const;
    private:
        ::XBase::Pointer< const ResMdlShapeImpl > mPtr;
        //------------------------------------------------------------------------------
        bool checkInvalid()const;
    };
//@}

} // namespace
#endif
// EOF
