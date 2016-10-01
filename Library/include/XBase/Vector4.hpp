// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_VECTOR4_HPP)
#else
#define XBASE_INCLUDED_VECTOR4_HPP

//------------------------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/ShortString.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    struct Vector2POD;
    struct Vector3POD;
}

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /// @brief 浮動小数型4次元ベクトル構造体。
    /// @details 
    /// 使用頻度のことを考えて Vec4 という名前でもアクセスできます。
    /// メモリ配置は32bit浮動小数が先頭からx,y,z,wの順番に並んでいます。
    struct Vector4POD
    {
        //============================================================
        /// @name 定数取得
        //@{
        static const Vector4POD Zero();     ///< 0ベクトル。
        static const Vector4POD One();      ///< X,Y,Z,Wが全て1のベクトル。
        static const Vector4POD Min();      ///< 最小値のベクトル。
        static const Vector4POD Max();      ///< 最大値のベクトル。
        static const Vector4POD UnitX();    ///< X単位ベクトル。
        static const Vector4POD UnitY();    ///< Y単位ベクトル。
        static const Vector4POD UnitZ();    ///< Z単位ベクトル。
        static const Vector4POD UnitW();    ///< W単位ベクトル。
        static const Vector4POD NegUnitX(); ///< -X単位ベクトル。
        static const Vector4POD NegUnitY(); ///< -Y単位ベクトル。
        static const Vector4POD NegUnitZ(); ///< -Z単位ベクトル。
        static const Vector4POD NegUnitW(); ///< -W単位ベクトル。
        //@}
        //============================================================
        /// @name 変数
        //@{
        f32 x; ///< x。
        f32 y; ///< y。
        f32 z; ///< z。
        f32 w; ///< w。
        //@}
        
        //============================================================
        /// @name 変換
        //@{
        const Vector2POD toXY()const;
        const Vector2POD toXX()const;
        const Vector2POD toYY()const;
        const Vector2POD toZZ()const;
        const Vector2POD toWW()const;
        const Vector3POD toXYZ()const;
        const Vector3POD toXXX()const;
        const Vector3POD toYYY()const;
        const Vector3POD toZZZ()const;
        const Vector3POD toWWW()const;
        const Vector4POD toXYZ0()const;
        const Vector4POD toXY0W()const;
        const Vector4POD toXY00()const;
        const Vector4POD toX0ZW()const;
        const Vector4POD toX0Z0()const;
        const Vector4POD toX00W()const;
        const Vector4POD toX000()const;
        const Vector4POD to0YZ0()const;
        const Vector4POD to0Y0W()const;
        const Vector4POD to0Y00()const;
        const Vector4POD to00ZW()const;
        const Vector4POD to00Z0()const;
        const Vector4POD to000W()const;
        const Vector4POD toXXXX()const;
        const Vector4POD toYYYY()const;
        const Vector4POD toZZZZ()const;
        const Vector4POD toWWWW()const;
        //@}

        //============================================================
        /// @name 等価比較
        //@{
        bool equals( const Vector4POD& )const;       ///< 許容誤差を考慮した等価比較。
        bool equalsStrict( const Vector4POD& )const; ///< 許容誤差を許容しない等価比較。
        //@}

        //============================================================
        /// @name 四則演算
        //@{
        const Vector4POD add( f32 )const; ///< 各要素に値を加算した結果を取得する。
        const Vector4POD sub( f32 )const; ///< 各要素から値を減算した結果を取得する。
        const Vector4POD mul( f32 )const; ///< 各要素に値をかけた結果を取得する。
        const Vector4POD div( f32 )const; ///< 各要素から値をわった結果を取得する。
        const Vector4POD add( const Vector4POD& )const; ///< 対応する値同士を加算した結果を取得する。
        const Vector4POD sub( const Vector4POD& )const; ///< 対応する値に対して減算した結果を取得する。
        const Vector4POD mul( const Vector4POD& )const; ///< 対応する値同士をかけた結果を取得する。
        const Vector4POD div( const Vector4POD& )const; ///< 対応する値に対して割り算をした結果を取得する。
        void addAssign( f32 ); ///< 各要素に値を加算する。
        void subAssign( f32 ); ///< 各要素から値を減算する。
        void mulAssign( f32 ); ///< 各要素に値をかける。
        void divAssign( f32 ); ///< 各要素から値をわる。
        void addAssign( const Vector4POD& ); ///< 対応する値同士を加算する。
        void subAssign( const Vector4POD& ); ///< 対応する値に対して減算する。
        void mulAssign( const Vector4POD& ); ///< 対応する値同士をかける。
        void divAssign( const Vector4POD& ); ///< 対応する値に対して割り算をする。       
        //@}
        
        //============================================================
        /// @name 演算子オーバーロード
        //@{
        const Vector4POD operator+( f32 )const; ///< add()。
        const Vector4POD operator-( f32 )const; ///< sub()。
        const Vector4POD operator*( f32 )const; ///< mul()。
        const Vector4POD operator/( f32 )const; ///< div()。
        const Vector4POD operator+( const Vector4POD& )const; ///< add()。
        const Vector4POD operator-( const Vector4POD& )const; ///< sub()。
        const Vector4POD operator*( const Vector4POD& )const; ///< mul()。
        const Vector4POD operator/( const Vector4POD& )const; ///< div()。
        const Vector4POD operator-()const; ///< neg()。
        Vector4POD& operator+=( f32 ); ///< addAssign()。
        Vector4POD& operator-=( f32 ); ///< subAssign()。
        Vector4POD& operator*=( f32 ); ///< mulAssign()。
        Vector4POD& operator/=( f32 ); ///< divAssign()。
        Vector4POD& operator+=( const Vector4POD& ); ///< addAssign()。
        Vector4POD& operator-=( const Vector4POD& ); ///< subAssign()。
        Vector4POD& operator*=( const Vector4POD& ); ///< mulAssign()。
        Vector4POD& operator/=( const Vector4POD& ); ///< divAssign()。
        //@}
        
        //============================================================
        /// @name 選択
        //@{
        const Vector4POD min( const Vector4POD& )const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
        const Vector4POD max( const Vector4POD& )const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
        //@}
        
        //============================================================
        /// @name クランプ
        //@{
        const Vector4POD clamp( const Vector4POD& aMin , const Vector4POD& aMax )const; ///< aMin以上aMax以下になるようにクランプする。
        const Vector4POD clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
        const Vector4POD clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
        //@}

        //============================================================
        /// @name 符号操作
        //@{
        const Vector4POD abs()const; ///< 各要素を正に置き換えたベクトルを取得。
        const Vector4POD neg()const; ///< 符号を反転させた結果を取得する。
        //@}

        //============================================================
        /// @name 長さ＆正規化
        //@{
        f32  squareLength()const;                ///< 長さの2乗を取得する。
        f32  length()const;                      ///< 長さを取得する。
        f32  distance( const Vector4POD& )const; ///< あるベクトルとの距離を取得する。
        bool isZero()const;                      ///< 長さが0か。許容誤差を許す。
        bool isZeroStrict()const;                ///< 長さが0か。許容誤差を許さない。
        bool isUnit()const;                      ///< 正規化済みか。許容誤差を許す。
        const Vector4POD unit()const;            ///< @brief 正規化したベクトルを取得する。 @details 長さ0のベクトルで正規化するとエラーになります。
        void unitAssign();                       ///< @brief 正規化する。 @details 長さ0のベクトルで正規化するとエラーになります。
        //@}

        //============================================================
        /// @name 内積
        //@{
        f32 dot( const Vector4POD& )const;                ///< あるベクトルとの内積を取得する。
        //@}

        //============================================================
        /// @name ユーティリティ
        //@{
        /// x,y,z,w形式の文字列に変換。
        const ShortString toShortString()const;
        //@}
    };

    /// Vector4POD のクラス版。
    class Vector4 : public Vector4POD
    {
    public:
        //============================================================
        /// @name コンストラクタ
        //@{
        Vector4(); ///< Zero() で作成。
        Vector4( const Vector4POD& aXYZW ); ///< コピーして作成。
        Vector4( f32 aV ); ///< 全要素同じ値で作成。
        Vector4( const Vector2POD& aXY , f32 aZ , f32 aW ); ///< XYZWを指定して作成。
        Vector4( const Vector3POD& aXYZ , f32 aW ); ///< XYZWを指定して作成。
        Vector4( f32 aX , f32 aY , f32 aZ , f32 aW ); ///< XYZWを指定して作成。
        //@}
    };
    
    /// Vector4POD のエイリアス。
    typedef Vector4POD Vec4;

    /// Vector4POD のエイリアス。
    typedef Vector4POD Vector4fPOD;
    
    /// Vec4 のエイリアス。
    typedef Vec4 Vec4f;

    /// Vector4 のエイリアス。
    typedef Vector4 Vector4f;
//@}

} // namespace
#endif
// EOF
