/**
 * @file
 * @brief Vector4i,Vector4iPOD(Vec4i)型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_VECTOR4I_HPP)
#else
#define XBASE_INCLUDED_VECTOR4I_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/ShortString.hpp>

//------------------------------------------------------------
namespace XBase {
    struct Vector2iPOD;
    struct Vector3iPOD;
    struct Vector4POD;
}

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /**
     * @brief 整数型4次元ベクトル構造体。
     * @details 
     * 使用頻度のことを考えて Vec4i という名前でもアクセスできます。
     * メモリ配置は32bit符号有り整数が先頭からx,y,z,wの順番に並んでいます。
     */
    struct Vector4iPOD
    {
        //============================================================
        /// @name 定数取得
        //@{
        static const Vector4iPOD Zero();     ///< 0ベクトル。
        static const Vector4iPOD One();      ///< X,Y,Z,Wが全て1のベクトル。
        static const Vector4iPOD Min();      ///< 最小値のベクトル。
        static const Vector4iPOD Max();      ///< 最大値のベクトル。
        static const Vector4iPOD UnitX();    ///< X単位ベクトル。
        static const Vector4iPOD UnitY();    ///< Y単位ベクトル。
        static const Vector4iPOD UnitZ();    ///< Z単位ベクトル。
        static const Vector4iPOD UnitW();    ///< W単位ベクトル。
        static const Vector4iPOD NegUnitX(); ///< -X単位ベクトル。
        static const Vector4iPOD NegUnitY(); ///< -Y単位ベクトル。
        static const Vector4iPOD NegUnitZ(); ///< -Z単位ベクトル。
        static const Vector4iPOD NegUnitW(); ///< -W単位ベクトル。
        //@}

        //============================================================
        /// @name 変数
        //@{
        s32 x; ///< x。
        s32 y; ///< y。
        s32 z; ///< z。
        s32 w; ///< z。
        //@}
        
        //============================================================
        /// @name 変換
        //@{
        const Vector2iPOD toXY()const;
        const Vector2iPOD toXX()const;
        const Vector2iPOD toYY()const;
        const Vector2iPOD toZZ()const;
        const Vector2iPOD toWW()const;
        const Vector3iPOD toXYZ()const;
        const Vector3iPOD toXXX()const;
        const Vector3iPOD toYYY()const;
        const Vector3iPOD toZZZ()const;
        const Vector3iPOD toWWW()const;
        const Vector4iPOD toXYZ0()const;
        const Vector4iPOD toXY0W()const;
        const Vector4iPOD toXY00()const;
        const Vector4iPOD toX0ZW()const;
        const Vector4iPOD toX0Z0()const;
        const Vector4iPOD toX00W()const;
        const Vector4iPOD toX000()const;
        const Vector4iPOD to0YZ0()const;
        const Vector4iPOD to0Y0W()const;
        const Vector4iPOD to0Y00()const;
        const Vector4iPOD to00ZW()const;
        const Vector4iPOD to00Z0()const;
        const Vector4iPOD to000W()const;
        const Vector4iPOD toXXXX()const;
        const Vector4iPOD toYYYY()const;
        const Vector4iPOD toZZZZ()const;
        const Vector4iPOD toWWWW()const;
        const Vector4POD  toXYZWf()const;
        //@}

        //============================================================
        /// @name 等価比較
        //@{
        bool equals( const Vector4iPOD& )const;       ///< 等価比較。
        //@}

        //============================================================
        /// @name 四則演算
        //@{
        const Vector4iPOD add( s32 )const; ///< 各要素に値を加算した結果を取得する。
        const Vector4iPOD sub( s32 )const; ///< 各要素から値を減算した結果を取得する。
        const Vector4iPOD mul( s32 )const; ///< 各要素に値をかけた結果を取得する。
        const Vector4iPOD div( s32 )const; ///< 各要素から値をわった結果を取得する。
        const Vector4iPOD add( const Vector4iPOD& )const; ///< 対応する値同士を加算した結果を取得する。
        const Vector4iPOD sub( const Vector4iPOD& )const; ///< 対応する値に対して減算した結果を取得する。
        const Vector4iPOD mul( const Vector4iPOD& )const; ///< 対応する値同士をかけた結果を取得する。
        const Vector4iPOD div( const Vector4iPOD& )const; ///< 対応する値に対して割り算をした結果を取得する。
        void addAssign( s32 ); ///< 各要素に値を加算する。
        void subAssign( s32 ); ///< 各要素から値を減算する。
        void mulAssign( s32 ); ///< 各要素に値をかける。
        void divAssign( s32 ); ///< 各要素から値をわる。
        void addAssign( const Vector4iPOD& ); ///< 対応する値同士を加算する。
        void subAssign( const Vector4iPOD& ); ///< 対応する値に対して減算する。
        void mulAssign( const Vector4iPOD& ); ///< 対応する値同士をかける。
        void divAssign( const Vector4iPOD& ); ///< 対応する値に対して割り算をする。       
        //@}
        
        //============================================================
        /// @name 演算子オーバーロード
        //@{
        const Vector4iPOD operator+( s32 )const; ///< add()。
        const Vector4iPOD operator-( s32 )const; ///< sub()。
        const Vector4iPOD operator*( s32 )const; ///< mul()。
        const Vector4iPOD operator/( s32 )const; ///< div()。
        const Vector4iPOD operator+( const Vector4iPOD& )const; ///< add()。
        const Vector4iPOD operator-( const Vector4iPOD& )const; ///< sub()。
        const Vector4iPOD operator*( const Vector4iPOD& )const; ///< mul()。
        const Vector4iPOD operator/( const Vector4iPOD& )const; ///< div()。
        const Vector4iPOD operator-()const; ///< neg()。
        Vector4iPOD& operator+=( s32 ); ///< addAssign()。
        Vector4iPOD& operator-=( s32 ); ///< subAssign()。
        Vector4iPOD& operator*=( s32 ); ///< mulAssign()。
        Vector4iPOD& operator/=( s32 ); ///< divAssign()。
        Vector4iPOD& operator+=( const Vector4iPOD& ); ///< addAssign()。
        Vector4iPOD& operator-=( const Vector4iPOD& ); ///< subAssign()。
        Vector4iPOD& operator*=( const Vector4iPOD& ); ///< mulAssign()。
        Vector4iPOD& operator/=( const Vector4iPOD& ); ///< divAssign()。
        //@}
        
        //============================================================
        /// @name 選択
        //@{
        const Vector4iPOD min( const Vector4iPOD& )const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
        const Vector4iPOD max( const Vector4iPOD& )const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
        //@}

        //============================================================
        /// @name クランプ
        //@{
        const Vector4iPOD clamp( const Vector4iPOD& aMin , const Vector4iPOD& aMax )const; ///< aMin以上aMax以下になるようにクランプする。
        const Vector4iPOD clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
        const Vector4iPOD clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
        //@}

        //============================================================
        /// @name 符号
        //@{
        const Vector4iPOD abs()const; ///< 各要素を正に置き換えたベクトルを取得。
        const Vector4iPOD neg()const; ///< 符号を反転させた結果を取得する。
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
        /// x,y,z,w形式の文字列に変換。
        const ShortString toShortString()const;
        //@}
    };

    /// Vector4iPOD のクラス版。
    class Vector4i : public Vector4iPOD
    {
    public:
        //============================================================
        /// @name コンストラクタ
        //@{
        Vector4i(); ///< Zero() で作成。
        Vector4i( const Vector4iPOD& aXYZW ); ///< コピーして作成。
        Vector4i( s32 aV ); ///< 全要素同じ値で作成。
        Vector4i( const Vector2iPOD& aXY , s32 aZ , s32 aW ); ///< XYZWを指定して作成。
        Vector4i( const Vector3iPOD& aXYZ , s32 aW ); ///< XYZWを指定して作成。
        Vector4i( s32 aX , s32 aY , s32 aZ , s32 aW ); ///< XYZWを指定して作成。
        //@}
    };
    
    /// Vector4iPOD のエイリアス。
    typedef Vector4iPOD Vec4i;
//@}
}
//------------------------------------------------------------
#endif
// EOF
