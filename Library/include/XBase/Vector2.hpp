/**
 * @file
 * @brief Vector2,Vector2POD(Vec2)型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_VECTOR2_HPP)
#else
#define XBASE_INCLUDED_VECTOR2_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/ShortString.hpp>

//------------------------------------------------------------
namespace XBase {
    struct Vector2POD;
    struct Vector3POD;
    struct Vector4POD;
}

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /// Vector2PODのエイリアス。
    typedef Vector2POD Vec2;

    /**
     * @brief 浮動小数型2次元ベクトル構造体。
     * @details 
     * 使用頻度のことを考えて Vec2 という名前でもアクセスできます。
     * メモリ配置は32bit浮動小数が先頭からx,yの順番に並んでいます。
     */
    struct Vector2POD
    {
        //============================================================
        /// @name 定数取得
        //@{
        static const Vector2POD Zero();     ///< 0ベクトル。
        static const Vector2POD One();      ///< X,Yが全て1のベクトル。
        static const Vector2POD Min();      ///< 最小値のベクトル。
        static const Vector2POD Max();      ///< 最大値のベクトル。
        static const Vector2POD UnitX();    ///< X単位ベクトル。
        static const Vector2POD UnitY();    ///< Y単位ベクトル。
        static const Vector2POD NegUnitX(); ///< -X単位ベクトル。
        static const Vector2POD NegUnitY(); ///< -Y単位ベクトル。
        //@}

        //============================================================
        /// @name 変数
        //@{
        f32 x; ///< x。
        f32 y; ///< y。
        //@}
        
        //============================================================
        /// @name 変換
        //@{
        const Vector2POD toX0()const;
        const Vector2POD to0Y()const;
        const Vector2POD toXX()const;
        const Vector2POD toYX()const;
        const Vector2POD toYY()const;
        const Vector3POD toXY0()const;
        const Vector3POD toXXX()const;
        const Vector3POD toYYY()const;
        const Vector4POD toXY00()const;
        const Vector4POD toXXXX()const;
        const Vector4POD toYYYY()const;
        //@}

        //============================================================
        /// @name 等価比較
        //@{
        bool equals( const Vector2POD& )const;       ///< 許容誤差を考慮した等価比較。
        bool equalsStrict( const Vector2POD& )const; ///< 許容誤差を許容しない等価比較。
        //@}

        //============================================================
        /// @name 四則演算
        //@{
        const Vector2POD add( f32 )const; ///< 各要素に値を加算した結果を取得する。
        const Vector2POD sub( f32 )const; ///< 各要素から値を減算した結果を取得する。
        const Vector2POD mul( f32 )const; ///< 各要素に値をかけた結果を取得する。
        const Vector2POD div( f32 )const; ///< 各要素から値をわった結果を取得する。
        const Vector2POD add( const Vector2POD& )const; ///< 対応する値同士を加算した結果を取得する。
        const Vector2POD sub( const Vector2POD& )const; ///< 対応する値に対して減算した結果を取得する。
        const Vector2POD mul( const Vector2POD& )const; ///< 対応する値同士をかけた結果を取得する。
        const Vector2POD div( const Vector2POD& )const; ///< 対応する値に対して割り算をした結果を取得する。
        void addAssign( f32 ); ///< 各要素に値を加算する。
        void subAssign( f32 ); ///< 各要素から値を減算する。
        void mulAssign( f32 ); ///< 各要素に値をかける。
        void divAssign( f32 ); ///< 各要素から値をわる。
        void addAssign( const Vector2POD& ); ///< 対応する値同士を加算する。
        void subAssign( const Vector2POD& ); ///< 対応する値に対して減算する。
        void mulAssign( const Vector2POD& ); ///< 対応する値同士をかける。
        void divAssign( const Vector2POD& ); ///< 対応する値に対して割り算をする。       
        //@}
        
        //============================================================
        /// @name 演算子オーバーロード
        //@{
        const Vector2POD operator+( f32 )const; ///< add()。
        const Vector2POD operator-( f32 )const; ///< sub()。
        const Vector2POD operator*( f32 )const; ///< mul()。
        const Vector2POD operator/( f32 )const; ///< div()。
        const Vector2POD operator+( const Vector2POD& )const; ///< add()。
        const Vector2POD operator-( const Vector2POD& )const; ///< sub()。
        const Vector2POD operator*( const Vector2POD& )const; ///< mul()。
        const Vector2POD operator/( const Vector2POD& )const; ///< div()。
        const Vector2POD operator-()const; ///< neg()。
        Vector2POD& operator+=( f32 ); ///< addAssign()。
        Vector2POD& operator-=( f32 ); ///< subAssign()。
        Vector2POD& operator*=( f32 ); ///< mulAssign()。
        Vector2POD& operator/=( f32 ); ///< divAssign()。
        Vector2POD& operator+=( const Vector2POD& ); ///< addAssign()。
        Vector2POD& operator-=( const Vector2POD& ); ///< subAssign()。
        Vector2POD& operator*=( const Vector2POD& ); ///< mulAssign()。
        Vector2POD& operator/=( const Vector2POD& ); ///< divAssign()。
        //@}
        
        //============================================================
        /// @name 選択
        //@{
        const Vector2POD min( const Vector2POD& )const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
        const Vector2POD max( const Vector2POD& )const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
        //@}
        
        //============================================================
        /// @name クランプ
        //@{
        const Vector2POD clamp( const Vector2POD& aMin , const Vector2POD& aMax )const; ///< aMin以上aMax以下になるようにクランプする。
        const Vector2POD clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
        const Vector2POD clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
        //@}

        //============================================================
        /// @name 符号操作
        //@{
        const Vector2POD abs()const; ///< 各要素を正に置き換えたベクトルを取得。
        const Vector2POD neg()const; ///< 符号を反転させた結果を取得する。
        //@}

        //============================================================
        /// @name 長さ＆正規化
        //@{
        f32  squareLength()const;                ///< 長さの2乗を取得する。
        f32  length()const;                      ///< 長さを取得する。
        f32  distance( const Vector2POD& )const; ///< あるベクトルとの距離を取得する。
        bool isZero()const;                      ///< 長さが0か。許容誤差を許す。
        bool isZeroStrict()const;                ///< 長さが0か。許容誤差を許さない。
        bool isUnit()const;                      ///< 正規化済みか。許容誤差を許す。
        const Vector2POD unit()const;            ///< @brief 正規化したベクトルを取得する。 @details 長さ0のベクトルで正規化するとエラーになります。
        void unitAssign();                       ///< @brief 正規化する。 @details 長さ0のベクトルで正規化するとエラーになります。
        //@}

        //============================================================
        /// @name 内積・外積
        //@{
        f32 dot( const Vector2POD& )const;     ///< あるベクトルとの内積(cosθ)を取得する。
        f32 cross( const Vector2POD& )const;   ///< あるベクトルとの外積(sinθ)を取得とる。
        //@}

        //============================================================
        /// @name ユーティリティ
        //@{
        /// x,y形式の文字列に変換。
        const ShortString toShortString()const;
        //@}
    };

    /// Vector2POD のクラス版。
    class Vector2 : public Vector2POD
    {
    public:
        //============================================================
        /// @name コンストラクタ
        //@{
        Vector2(); ///< Zero() で作成。
        Vector2( const Vector2POD& aXY ); ///< コピーして作成。
        Vector2( f32 aV ); ///< 全要素同じ値で作成。
        Vector2( f32 aX , f32 aY ); ///< XYを指定して作成。
        //@}
    };
    
    /// Vector2POD のエイリアス。
    typedef Vector2POD Vec2;

    /// Vector2POD のエイリアス。
    typedef Vector2POD Vector2fPOD;
    
    /// Vec2 のエイリアス。
    typedef Vec2 Vec2f;
    
    /// Vector2 のエイリアス。
    typedef Vector2 Vector2f;
//@}
}
//------------------------------------------------------------
#endif
// EOF
