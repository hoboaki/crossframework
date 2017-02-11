/*
 * @file
 * @brief ResMatParam型を記述する。
 * @author akino
 */
#if defined(AE_G3D_INCLUDED_RESMATPARAM_HPP)
#else
#define AE_G3D_INCLUDED_RESMATPARAM_HPP

#include <ae/base/Pointer.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

namespace ae {
namespace g3d {
class ResMatParamImpl;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
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
    ResMatParam(const ResMatParamImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResMatParam& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResMatParam& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    int        index()const; ///< 自身のインデックス番号。
    const char* name()const; ///< パラメータ名。
    //@}

private:
    ::ae::base::Pointer< const ResMatParamImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
