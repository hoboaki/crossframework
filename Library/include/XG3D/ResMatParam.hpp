/*
 * @file
 * @brief ResMatParam型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_RESMATPARAM_HPP)
#else
#define XG3D_INCLUDED_RESMATPARAM_HPP

//------------------------------------------------------------------------------
#include <XBase/Pointer.hpp>
#include <XG3D/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XG3D {
    class ResMatParamImpl;
}

//------------------------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Res
//@{
    /// @brief XMATSETのマテリアルパラメータデータのアクセサ。
    /// @details
    /// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
    class ResMatParam
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        /// 無効なオブジェクトを作成。
        ResMatParam();

        /// 有効なオブジェクトを作成。
        ResMatParam( const ResMatParamImpl& aImpl );
        //@}
        
        /// @name 全般
        //@{        
        bool isValid()const; ///< 有効なデータか。
        bool equals( const ResMatParam& aRHS )const; ///< 同じデータを指しているか。
        bool operator==( const ResMatParam& aRHS )const; ///< equals() のエイリアス。
        //@}

        /// @name プロパティの取得( isValid() なときしかアクセスできません)
        //@{
        uint        index()const; ///< 自身のインデックス番号。
        const char* name()const; ///< パラメータ名。
        //@}

    private:
        ::XBase::Pointer< const ResMatParamImpl > mPtr;
        //------------------------------------------------------------------------------
        bool checkInvalid()const;
    };
//@}

} // namespace
#endif
// EOF
