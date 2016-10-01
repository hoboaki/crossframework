// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_MATRIX44_HPP)
#else
#define XBASE_INCLUDED_MATRIX44_HPP

//------------------------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    class Angle;
    struct Vector3POD;
    struct Vector4POD;
}

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /// @brief 4x4の32bit浮動小数行列構造体。
    /// @details
    /// 使用頻度のことを考えて Mtx44 という名前でもアクセスできます。
    /// 配列の並びはOpenGL準拠にしてあります。
    /// @code
    ///    c0  c1   c2   c3
    /// r0 [0] [4]  [8] [12]
    /// r1 [1] [5]  [9] [13]
    /// r2 [2] [6] [10] [14]
    /// r3 [3] [7] [11] [15]
    /// @endcode
    /// 
    /// DirectXの並びは行ベースになりますが演算上はどちらでも変わりません。
    /// (例：Translateのx,y,z値はどちらも12,13,14番にくる。)
    struct Matrix44POD
    {
        //============================================================
        /// @name インデックス値
        //@{
        enum
        {
            Index00 = 0, ///< [0][0]
            Index10 = 1, ///< [1][0]
            Index20 = 2, ///< [2][0]
            Index30 = 3, ///< [3][0]
            Index01 = 4, ///< [0][1]
            Index11 = 5, ///< [1][1]
            Index21 = 6, ///< [2][1]
            Index31 = 7, ///< [3][1]
            Index02 = 8, ///< [0][2]
            Index12 = 9, ///< [1][2]
            Index22 = 10, ///< [2][2]
            Index32 = 11, ///< [3][2]
            Index03 = 12, ///< [0][3]
            Index13 = 13, ///< [1][3]
            Index23 = 14, ///< [2][3]
            Index33 = 15, ///< [3][3]
            IndexXX = Index00, ///< [0][0]
            IndexXY = Index10, ///< [1][0]
            IndexXZ = Index20, ///< [2][0]
            IndexXW = Index30, ///< [3][0]
            IndexYX = Index01, ///< [0][1]
            IndexYY = Index11, ///< [1][1]
            IndexYZ = Index21, ///< [2][1]
            IndexYW = Index31, ///< [3][1]
            IndexZX = Index02, ///< [0][2]
            IndexZY = Index12, ///< [1][2]
            IndexZZ = Index22, ///< [2][2]
            IndexZW = Index32, ///< [3][2]
            IndexWX = Index03, ///< [0][3]
            IndexWY = Index13, ///< [1][3]
            IndexWZ = Index23, ///< [2][3]
            IndexWW = Index33, ///< [3][3]
        };
        //@}

        //============================================================
        /// @name 行列の作成
        //@{
        static const Matrix44POD Identity(); ///< 単位行列の作成。
        static const Matrix44POD Translate( f32 aX , f32 aY , f32 aZ );   ///< 平行移動行列の作成。
        static const Matrix44POD Translate( const Vector3POD& aVec );     ///< 平行移動行列の作成。
        static const Matrix44POD Scale( f32 aX , f32 aY , f32 aZ );   ///< 拡大縮小行列の作成。
        static const Matrix44POD Scale( const Vector3POD& aVec );     ///< 拡大縮小行列の作成。
        static const Matrix44POD Rotate( const Angle& , f32 aAxisX , f32 aAxisY , f32 aAxisZ );   ///< 回転行列の作成。
        static const Matrix44POD Rotate( const Angle& , const Vector3POD& aAxis );                 ///< 回転行列の作成。
        
        /// 正射影行列の作成。
        static const Matrix44POD Ortho( f32 aLeft , f32 aTop , f32 aRight , f32 aBottom , f32 aNear , f32 aFar );

        /// 透視射影行列(Frustum)の作成。
        static const Matrix44POD Frustum( f32 aLeft ,f32 aRight ,f32 aBottom , f32 aTop , f32 aNear , f32 aFar );
        
        /// @brief 透視射影行列(Perspective)の作成。
        /// @param aFOVY   Y方向の画角。0 < aFOVY。
        /// @param aAspect 横/縦のアスペクト比。4:3なら1.333。0 < aAspect。
        /// @param aNear   Near値。
        /// @param aFar    Far値。
        static const Matrix44POD Perspective( const Angle& aFOVY , f32 aAspect , f32 aNear , f32 aFar );

        /// @brief 視野変換行列の作成。
        /// @param aEyePos 目の位置。
        /// @param aTargetPos 注視点。
        /// @param aUpVec 上方向のベクトル。isZeroなベクトルを渡してはいけない。
        /// @param aEyePos != aTargetPosである必要がある。
        static const Matrix44POD LookAt( const Vector3POD& aEyePos , const Vector3POD& aTargetPos , const Vector3POD& aUpVec );
        //@}

        //============================================================
        /// @name 変数
        //@{
        union
        {
            f32 v[16];   ///< 1次元配列。
            f32 m[4][4]; ///< 2次元配列。
        };
        //@}

        //============================================================
        /// @name XYZWアクセス（1列ごとにX,Y,Z,Wが割り当てられているとする）
        //@{
        const Vector4POD x()const;
        const Vector4POD y()const;
        const Vector4POD z()const;
        const Vector4POD w()const;
        void setX( const Vector4POD& );
        void setY( const Vector4POD& );
        void setZ( const Vector4POD& );
        void setW( const Vector4POD& );
        //@}

        //============================================================
        /// @name 乗算（引数が同じオブジェクトでも問題無し）
        //@{
        const Matrix44POD mul( const Matrix44POD& )const; ///< 乗算した結果を得る。this x rhs。
        Matrix44POD& mulAssign( const Matrix44POD& );     ///< 乗算し結果を代入する。this = this x rhs。
        //@}
        
        //============================================================
        /// @name 演算子オーバーロード
        //@{
        const Matrix44POD  operator*( const Matrix44POD& )const; ///< mul()。
        Matrix44POD&       operator*=( const Matrix44POD& );    ///< mulAssign()。
        //@}
        
        //============================================================
        /// @name 変換
        //@{
        const Matrix44POD invert()const; ///< 逆行列を取得する。
        const Matrix44POD transpose()const; ///< 転置行列を取得する。
        //@}

        //============================================================
        /// @name デバッグ
        //@{
        void dump()const;
        //@}
    };

    /// Matrix44POD のクラス版。
    class Matrix44 : public Matrix44POD
    {
    public:
        //============================================================
        /// @name コンストラクタ
        //@{
        Matrix44(); ///< 単位行列で初期化。
        /// 全要素を指定して作成。
        Matrix44( f32 r0c0 , f32 r0c1 , f32 r0c2 , f32 r0c3
            , f32 r1c0 , f32 r1c1 , f32 r1c2 , f32 r1c3
            , f32 r2c0 , f32 r2c1 , f32 r2c2 , f32 r2c3
            , f32 r3c0 , f32 r3c1 , f32 r3c2 , f32 r3c3
            );
        Matrix44( const Vector4POD& aX , const Vector4POD& aY , const Vector4POD& aZ , const Vector4POD& aW ); ///< X,Y,Z,Wを指定して作成。
        Matrix44( const Matrix44POD& ); ///< コピーして作成。
        //@}
    };
    
    /// Matrix44POD のエイリアス。
    typedef Matrix44POD Mtx44;
//@}

} // namespace
#endif
// EOF
