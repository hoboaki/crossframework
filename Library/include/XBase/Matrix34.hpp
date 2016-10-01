// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_MATRIX34_HPP)
#else
#define XBASE_INCLUDED_MATRIX34_HPP

//------------------------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    class Angle;
    class Quaternion;
    struct Matrix44POD;
    struct Vector3POD;
    struct Vector4POD;
}

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /// @brief 3x4の32bit浮動小数行列構造体。
    /// @details 
    /// 使用頻度のことを考えて Mtx34 という名前でもアクセスできます。
    /// 配列の並びはOpenGL準拠にしてあります。
    /// @code
    ///    c0  c1   c2   c3
    /// r0 [0] [3]  [6]  [9]
    /// r1 [1] [4]  [7] [10]
    /// r2 [2] [5]  [8] [11]
    /// @endcode
    struct Matrix34POD
    {
        //============================================================
        /// @name インデックス値
        //@{
        enum
        {
            Index00 = 0, ///< [0][0]
            Index10 = 1, ///< [1][0]
            Index20 = 2, ///< [2][0]
            Index01 = 3, ///< [0][1]
            Index11 = 4, ///< [1][1]
            Index21 = 5, ///< [2][1]
            Index02 = 6, ///< [0][2]
            Index12 = 7, ///< [1][2]
            Index22 = 8, ///< [2][2]
            Index03 = 9, ///< [0][3]
            Index13 = 10, ///< [1][3]
            Index23 = 11, ///< [2][3]
            IndexXX = Index00, ///< [0][0]
            IndexXY = Index10, ///< [1][0]
            IndexXZ = Index20, ///< [2][0]
            IndexYX = Index01, ///< [0][1]
            IndexYY = Index11, ///< [1][1]
            IndexYZ = Index21, ///< [2][1]
            IndexZX = Index02, ///< [0][2]
            IndexZY = Index12, ///< [1][2]
            IndexZZ = Index22, ///< [2][2]
            IndexWX = Index03, ///< [0][3]
            IndexWY = Index13, ///< [1][3]
            IndexWZ = Index23, ///< [2][3]
        };
        //@}

        //============================================================
        /// @name 行列の作成
        //@{
        static const Matrix34POD Identity(); ///< 単位行列の作成。
        static const Matrix34POD Translate( f32 aX , f32 aY , f32 aZ );   ///< 平行移動行列の作成。
        static const Matrix34POD Translate( const Vector3POD& aVec );     ///< 平行移動行列の作成。
        static const Matrix34POD Scale( f32 aX , f32 aY , f32 aZ );   ///< 拡大縮小行列の作成。
        static const Matrix34POD Scale( const Vector3POD& aVec );     ///< 拡大縮小行列の作成。
        static const Matrix34POD Rotate( const Angle& , f32 aAxisX , f32 aAxisY , f32 aAxisZ );   ///< 回転行列の作成。
        static const Matrix34POD Rotate( const Angle& , const Vector3POD& aAxis );                 ///< 回転行列の作成。
        
        /// @brief 視野変換行列の作成。
        /// @param aEyePos 目の位置。
        /// @param aTargetPos 注視点。
        /// @param aUpVec 上方向のベクトル。isZeroなベクトルを渡してはいけない。
        /// @details aEyePos != aTargetPosである必要があります。
        static const Matrix34POD LookAt( const Vector3POD& aEyePos , const Vector3POD& aTargetPos , const Vector3POD& aUpVec );
        //@}

        //============================================================
        /// @name 変数
        //@{
        union
        {
            f32 v[12];   ///< 1次元配列。
        };
        //@}

        //============================================================
        /// @name XYZWアクセス（1列ごとにX,Y,Z,Wが割り当てられているとする）
        //@{
        const Vector3POD x()const;
        const Vector3POD y()const;
        const Vector3POD z()const;
        const Vector3POD w()const;
        void setX( const Vector3POD& );
        void setY( const Vector3POD& );
        void setZ( const Vector3POD& );
        void setW( const Vector3POD& );
        //@}

        //============================================================
        /// @name 乗算（引数が同じオブジェクトでも問題無し）
        //@{
        const Vector3POD mul( const Vector3POD& )const;   ///< @brief 乗算した結果を得る。 @details 4行目は0,0,0,1として計算する。
        const Matrix34POD mul( const Matrix34POD& )const; ///< @brief 乗算した結果を得る。 @details this x rhs。4行目は0,0,0,1として計算する。
        Matrix34POD& mulAssign( const Matrix34POD& );     ///< @brief 乗算し結果を代入する。@details  this = this x rhs。4行目は0,0,0,1として計算する。
        //@}
        
        //============================================================
        /// @name 演算子オーバーロード
        //@{
        const Vector3POD   operator*( const Vector3POD& )const; ///< mul() のエイリアス。
        const Matrix34POD  operator*( const Matrix34POD& )const; ///< mul() のエイリアス。
        Matrix34POD&       operator*=( const Matrix34POD& );    ///< mulAssign() のエイリアス。
        //@}
        
        //============================================================
        /// @name 変換
        //@{
        const Matrix34POD invert()const; ///< 逆行列を取得する。4行目は0,0,0,1として作成する。
        const Quaternion  toQuaternion()const; ///< 3x3の部分をクォータニオンに変換する。
        const Matrix44POD toMatrix44()const; ///< 4x4に変換する。4行目は0,0,0,1として作成する。
        //@}

        //============================================================
        /// @name デバッグ
        //@{
        void dump()const;
        //@}
    };

    /// Matrix34POD のクラス版。
    class Matrix34 : public Matrix34POD
    {
    public:
        //============================================================
        /// @name コンストラクタ
        //@{
        Matrix34(); ///< 単位行列で初期化。
        /// 全要素を指定して作成。
        Matrix34( f32 r0c0 , f32 r0c1 , f32 r0c2 , f32 r0c3
            , f32 r1c0 , f32 r1c1 , f32 r1c2 , f32 r1c3
            , f32 r2c0 , f32 r2c1 , f32 r2c2 , f32 r2c3
            );
        Matrix34( const Vector3POD& aX , const Vector3POD& aY , const Vector3POD& aZ , const Vector3POD& aW ); ///< X,Y,Z,Wを指定して作成。
        Matrix34( const Matrix34POD& ); ///< コピーして作成。
        //@}
    };
    
    /// Matrix34POD のエイリアス。
    typedef Matrix34POD Mtx34;
//@}

} // namespace
#endif
// EOF
