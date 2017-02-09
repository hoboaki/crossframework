// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_RESMDLSHAPE_HPP)
#else
#define AE_G3D_INCLUDED_RESMDLSHAPE_HPP

#include <ae/base/Pointer.hpp>
#include <ae/g3d/BuiltInTypes.hpp>

namespace ae {
namespace g3d {
class ResMdlShapeImpl;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace g3d {

/// @addtogroup AeG3d-Res
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
    ResMdlShape(const ResMdlShapeImpl& aImpl);
    //@}

    /// @name 全般
    //@{        
    bool isValid()const; ///< 有効なデータか。
    bool equals(const ResMdlShape& aRHS)const; ///< 同じデータを指しているか。
    bool operator==(const ResMdlShape& aRHS)const; ///< equals() のエイリアス。
    //@}

    /// @name プロパティの取得( isValid() なときしかアクセスできません)
    //@{
    const char* name()const; ///< 名前。
    int  index()const;      ///< 自身のインデックス番号。
    bool  isSkinning()const; ///< スキニングを使ったシェイプか。
    //@}

    //============================================================
    // 内部実装用関数群。
    const ResMdlShapeImpl* impl_()const;
private:
    ::ae::base::Pointer< const ResMdlShapeImpl > mPtr;
    //------------------------------------------------------------------------------
    bool checkInvalid()const;
};
//@}

}} // namespace
#endif
// EOF
