// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_QUATERNION_HPP)
#else
#define XBASE_INCLUDED_QUATERNION_HPP

//------------------------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/ShortString.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    class  Angle;
    struct Matrix34POD;
    struct Vector3POD;
}

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /// @brief 32bit浮動小数のクォータニオンクラス。
    class Quaternion
    {
    public:
        //============================================================
        /// @name 変数
        //@{
        f32 x; ///< x。
        f32 y; ///< y。
        f32 z; ///< z。
        f32 w; ///< w。
        //@}

        //============================================================
        /// @name コンストラクタ
        //@{
        Quaternion(); ///< 単位クォータニオンの作成。
        Quaternion( f32 aX , f32 aY , f32 aZ , f32 aW ); ///< 各要素の値を指定して作成。
        Quaternion( const Vector3POD& aAxis , const Angle& aAngle ); ///< 任意軸回転用クォータニオンの作成。
        //@}

        //============================================================
        /// @name 計算
        //@{
        const Quaternion mul( const Quaternion& )const; ///< 乗算した結果を得る。this x rhs。
        Quaternion& mulAssign( const Quaternion& ); ///< 乗算。this x rhs。
        //@}

        //============================================================
        /// @name 変換
        //@{
        const Matrix34POD toRotateMatrix()const; ///< 回転行列に変換。
        //@}
        
        //============================================================
        /// @name 演算子オーバーロード
        //@{
        const Quaternion operator*( const Quaternion& )const; ///< mulのエイリアス。
        Quaternion& operator*=( const Quaternion& ); ///< mulAssignのエイリアス。
        //@}

        //============================================================
        /// @name ユーティリティ
        //@{
        /// x,y,z,w形式の文字列に変換。
        const ShortString toShortString()const;
        //@}
    };
//@}

} // namespace
#endif
// EOF
