// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMAT_HPP)
#else
#define AE_G3D_INCLUDED_RESMAT_HPP

#include <ae/base/Pointer.hpp>
#include <ae/g3d/BuiltInTypes.hpp>
#include <ae/g3d/ResMatParam.hpp>

namespace ae {
namespace g3d {
class ResMatImpl;
}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
//@{
/// @brief XMATSET::matデータのアクセサ。
/// @details
/// ただのアクセサなのでコピーして使って構いません。メモリのアロケーションも走りません。
class ResMat
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// 無効なオブジェクトを作成。
    ResMat();

    /// 有効なオブジェクトを作成。
    ResMat(const ResMatImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResMat& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResMat& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    int        index()const;                       ///< 自身のインデックス番号。
    const char* name()const;                        ///< 名前。
    int        paramCount()const;                  ///< パラメータリソースの総数。
    ResMatParam param(int aIndex)const;          ///< 指定番目のパラメータリソースの取得。
    ResMatParam param(const char* aName)const;    ///< 指定の名前のパラメータリソースの取得。
    //@}

    //============================================================
    // 内部実装用関数群。
    const ResMatImpl* impl_()const;
private:
    ::ae::base::Pointer< const ResMatImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
