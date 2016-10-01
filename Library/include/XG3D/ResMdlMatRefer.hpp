/*
 * @file
 * @brief ResMdlMatRefer型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_RESMDLMATREFER_HPP)
#else
#define XG3D_INCLUDED_RESMDLMATREFER_HPP

//------------------------------------------------------------
#include <XBase/Pointer.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XG3D {
    class ResMdlMatReferImpl;
}

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Res
//@{
    /**
     * @brief XMDLのマテリアル参照データのアクセサ。
     * @details
     * ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
     */
    class ResMdlMatRefer
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        /// 無効なオブジェクトを作成。
        ResMdlMatRefer();

        /// 有効なオブジェクトを作成。
        ResMdlMatRefer( const ResMdlMatReferImpl& aImpl );
        //@}
        
        /// @name 全般
        //@{        
        bool isValid()const; ///< 有効なデータか。
        bool equals( const ResMdlMatRefer& aRHS )const; ///< 同じデータを指しているか。
        bool operator==( const ResMdlMatRefer& aRHS )const; ///< equals() のエイリアス。
        //@}

        /// @name プロパティの取得( isValid() なときしかアクセスできません)
        //@{
        uint        index()const;   ///< 自身のインデックス番号。
        const char* name()const;    ///< 参照するマテリアルの名前。
        //@}

    private:
        ::XBase::Pointer< const ResMdlMatReferImpl > mPtr;
        //------------------------------------------------------------
        bool checkInvalid()const;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
