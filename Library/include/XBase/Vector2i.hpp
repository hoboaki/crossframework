// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_VECTOR2I_HPP)
#else
#define XBASE_INCLUDED_VECTOR2I_HPP

//------------------------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/ShortString.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    struct Vector2POD;
    struct Vector3iPOD;
    struct Vector4iPOD;
}

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /// @brief 整数型2次元ベクトル構造体。
    /// @details 
    /// 使用頻度のことを考えて Vec2i という名前でもアクセスできます。
    /// メモリ配置は32bit符号有り整数が先頭からx,yの順番に並んでいます。
    struct Vector2iPOD
    {
        //============================================================
        /// @name 定数取得
        //@{
        static const Vector2iPOD Zero();     ///< 0ベクトル。
        static const Vector2iPOD One();      ///< X,Yが全て1のベクトル。
        static const Vector2iPOD Min();      ///< 最小値のベクトル。
        static const Vector2iPOD Max();      ///< 最大値のベクトル。
        static const Vector2iPOD UnitX();    ///< X単位ベクトル。
        static const Vector2iPOD UnitY();    ///< Y単位ベクトル。
        static const Vector2iPOD NegUnitX(); ///< -X単位ベクトル。
        static const Vector2iPOD NegUnitY(); ///< -Y単位ベクトル。
        //@}

        //============================================================
        /// @name 変数
        //@{
        s32 x; ///< x。
        s32 y; ///< y。
        //@}
        
        //============================================================
        /// @name 変換
        //@{
        const Vector2iPOD toX0()const;
        const Vector2iPOD to0Y()const;
        const Vector2iPOD toXX()const;
        const Vector2iPOD toYX()const;
        const Vector2iPOD toYY()const;
        const Vector3iPOD toXY0()const;
        const Vector3iPOD toXXX()const;
        const Vector3iPOD toYYY()const;
        const Vector4iPOD toXY00()const;
        const Vector4iPOD toXXXX()const;
        const Vector4iPOD toYYYY()const;
        const Vector2POD  toXYf()const;
        //@}

        //============================================================
        /// @name 等価比較
        //@{
        bool equals( const Vector2iPOD& )const;       ///< 等価比較。
        //@}

        //============================================================
        /// @name 四則演算
        //@{
        const Vector2iPOD add( s32 )const; ///< 各要素に値を加算した結果を取得する。
        const Vector2iPOD sub( s32 )const; ///< 各要素から値を減算した結果を取得する。
        const Vector2iPOD mul( s32 )const; ///< 各要素に値をかけた結果を取得する。
        const Vector2iPOD div( s32 )const; ///< 各要素から値をわった結果を取得する。
        const Vector2iPOD add( const Vector2iPOD& )const; ///< 対応する値同士を加算した結果を取得する。
        const Vector2iPOD sub( const Vector2iPOD& )const; ///< 対応する値に対して減算した結果を取得する。
        const Vector2iPOD mul( const Vector2iPOD& )const; ///< 対応する値同士をかけた結果を取得する。
        const Vector2iPOD div( const Vector2iPOD& )const; ///< 対応する値に対して割り算をした結果を取得する。
        void addAssign( s32 ); ///< 各要素に値を加算する。
        void subAssign( s32 ); ///< 各要素から値を減算する。
        void mulAssign( s32 ); ///< 各要素に値をかける。
        void divAssign( s32 ); ///< 各要素から値をわる。
        void addAssign( const Vector2iPOD& ); ///< 対応する値同士を加算する。
        void subAssign( const Vector2iPOD& ); ///< 対応する値に対して減算する。
        void mulAssign( const Vector2iPOD& ); ///< 対応する値同士をかける。
        void divAssign( const Vector2iPOD& ); ///< 対応する値に対して割り算をする。       
        //@}
        
        //============================================================
        /// @name 演算子オーバーロード
        //@{
        const Vector2iPOD operator+( s32 )const; ///< add()。
        const Vector2iPOD operator-( s32 )const; ///< sub()。
        const Vector2iPOD operator*( s32 )const; ///< mul()。
        const Vector2iPOD operator/( s32 )const; ///< div()。
        const Vector2iPOD operator+( const Vector2iPOD& )const; ///< add()。
        const Vector2iPOD operator-( const Vector2iPOD& )const; ///< sub()。
        const Vector2iPOD operator*( const Vector2iPOD& )const; ///< mul()。
        const Vector2iPOD operator/( const Vector2iPOD& )const; ///< div()。
        const Vector2iPOD operator-()const; ///< neg()。
        Vector2iPOD& operator+=( s32 ); ///< addAssign()。
        Vector2iPOD& operator-=( s32 ); ///< subAssign()。
        Vector2iPOD& operator*=( s32 ); ///< mulAssign()。
        Vector2iPOD& operator/=( s32 ); ///< divAssign()。
        Vector2iPOD& operator+=( const Vector2iPOD& ); ///< addAssign()。
        Vector2iPOD& operator-=( const Vector2iPOD& ); ///< subAssign()。
        Vector2iPOD& operator*=( const Vector2iPOD& ); ///< mulAssign()。
        Vector2iPOD& operator/=( const Vector2iPOD& ); ///< divAssign()。
        //@}
        
        //============================================================
        /// @name 選択
        //@{
        const Vector2iPOD min( const Vector2iPOD& )const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
        const Vector2iPOD max( const Vector2iPOD& )const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
        //@}

        //============================================================
        /// @name クランプ
        //@{
        const Vector2iPOD clamp( const Vector2iPOD& aMin , const Vector2iPOD& aMax )const; ///< aMin以上aMax以下になるようにクランプする。
        const Vector2iPOD clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
        const Vector2iPOD clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
        //@}

        //============================================================
        /// @name 符号
        //@{
        const Vector2iPOD abs()const; ///< 各要素を正に置き換えたベクトルを取得。
        const Vector2iPOD neg()const; ///< 符号を反転させた結果を取得する。
        bool isPositive()const; ///< 各要素が0以上か。
        //@}

        //============================================================
        /// @name 長さ
        //@{
        bool isZero()const;                      ///< 全てが0か。
        //@}
        
        //============================================================
        /// @name ユーティリティ
        //@{
        /// x,y形式の文字列に変換。
        const ShortString toShortString()const;
        //@}
    };

    /// Vector2iPOD のクラス版。
    class Vector2i : public Vector2iPOD
    {
    public:
        //============================================================
        /// @name コンストラクタ
        //@{
        Vector2i(); ///< Zero() で作成。
        Vector2i( const Vector2iPOD& aXY ); ///< コピーして作成。
        Vector2i( s32 aV ); ///< 全要素同じ値で作成。
        Vector2i( s32 aX , s32 aY ); ///< XYを指定して作成。
        //@}
    };
    
    /// Vector2iPOD のエイリアス。
    typedef Vector2iPOD Vec2i;
//@}

} // namespace
#endif
// EOF
