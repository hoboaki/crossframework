// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_VECTOR3I_HPP)
#else
#define XBASE_INCLUDED_VECTOR3I_HPP

//------------------------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/ShortString.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    struct Vector2iPOD;
    struct Vector3POD;
    struct Vector4iPOD;
}

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /// @brief 整数型3次元ベクトル構造体。
    /// @details 
    /// 使用頻度のことを考えて Vec3i という名前でもアクセスできます。
    /// メモリ配置は32bit符号有り整数が先頭からx,y,zの順番に並んでいます。
    struct Vector3iPOD
    {
        //============================================================
        /// @name 定数取得
        //@{
        static const Vector3iPOD Zero();     ///< 0ベクトル。
        static const Vector3iPOD One();      ///< X,Y,Zが全て1のベクトル。
        static const Vector3iPOD Min();      ///< 最小値のベクトル。
        static const Vector3iPOD Max();      ///< 最大値のベクトル。
        static const Vector3iPOD UnitX();    ///< X単位ベクトル。
        static const Vector3iPOD UnitY();    ///< Y単位ベクトル。
        static const Vector3iPOD UnitZ();    ///< Z単位ベクトル。
        static const Vector3iPOD NegUnitX(); ///< -X単位ベクトル。
        static const Vector3iPOD NegUnitY(); ///< -Y単位ベクトル。
        static const Vector3iPOD NegUnitZ(); ///< -Z単位ベクトル。
        //@}

        //============================================================
        /// @name 変数
        //@{
        s32 x; ///< x。
        s32 y; ///< y。
        s32 z; ///< z。
        //@}
        
        //============================================================
        /// @name 変換
        //@{
        const Vector2iPOD toXY()const;
        const Vector2iPOD toXX()const;
        const Vector2iPOD toYY()const;
        const Vector2iPOD toZZ()const;
        const Vector3iPOD toX00()const;
        const Vector3iPOD toXY0()const;
        const Vector3iPOD to0Y0()const;
        const Vector3iPOD to0YZ()const;
        const Vector3iPOD to00Z()const;
        const Vector3iPOD toXXX()const;
        const Vector3iPOD toYYY()const;
        const Vector3iPOD toZZZ()const;
        const Vector4iPOD toXYZ0()const;
        const Vector4iPOD toXXXX()const;
        const Vector4iPOD toYYYY()const;
        const Vector4iPOD toZZZZ()const;
        const Vector3POD  toXYZf()const;
        //@}

        //============================================================
        /// @name 等価比較
        //@{
        bool equals( const Vector3iPOD& )const;       ///< 等価比較。
        //@}

        //============================================================
        /// @name 四則演算
        //@{
        const Vector3iPOD add( s32 )const; ///< 各要素に値を加算した結果を取得する。
        const Vector3iPOD sub( s32 )const; ///< 各要素から値を減算した結果を取得する。
        const Vector3iPOD mul( s32 )const; ///< 各要素に値をかけた結果を取得する。
        const Vector3iPOD div( s32 )const; ///< 各要素から値をわった結果を取得する。
        const Vector3iPOD add( const Vector3iPOD& )const; ///< 対応する値同士を加算した結果を取得する。
        const Vector3iPOD sub( const Vector3iPOD& )const; ///< 対応する値に対して減算した結果を取得する。
        const Vector3iPOD mul( const Vector3iPOD& )const; ///< 対応する値同士をかけた結果を取得する。
        const Vector3iPOD div( const Vector3iPOD& )const; ///< 対応する値に対して割り算をした結果を取得する。
        void addAssign( s32 ); ///< 各要素に値を加算する。
        void subAssign( s32 ); ///< 各要素から値を減算する。
        void mulAssign( s32 ); ///< 各要素に値をかける。
        void divAssign( s32 ); ///< 各要素から値をわる。
        void addAssign( const Vector3iPOD& ); ///< 対応する値同士を加算する。
        void subAssign( const Vector3iPOD& ); ///< 対応する値に対して減算する。
        void mulAssign( const Vector3iPOD& ); ///< 対応する値同士をかける。
        void divAssign( const Vector3iPOD& ); ///< 対応する値に対して割り算をする。       
        //@}
        
        //============================================================
        /// @name 演算子オーバーロード
        //@{
        const Vector3iPOD operator+( s32 )const; ///< add()。
        const Vector3iPOD operator-( s32 )const; ///< sub()。
        const Vector3iPOD operator*( s32 )const; ///< mul()。
        const Vector3iPOD operator/( s32 )const; ///< div()。
        const Vector3iPOD operator+( const Vector3iPOD& )const; ///< add()。
        const Vector3iPOD operator-( const Vector3iPOD& )const; ///< sub()。
        const Vector3iPOD operator*( const Vector3iPOD& )const; ///< mul()。
        const Vector3iPOD operator/( const Vector3iPOD& )const; ///< div()。
        const Vector3iPOD operator-()const; ///< neg()。
        Vector3iPOD& operator+=( s32 ); ///< addAssign()。
        Vector3iPOD& operator-=( s32 ); ///< subAssign()。
        Vector3iPOD& operator*=( s32 ); ///< mulAssign()。
        Vector3iPOD& operator/=( s32 ); ///< divAssign()。
        Vector3iPOD& operator+=( const Vector3iPOD& ); ///< addAssign()。
        Vector3iPOD& operator-=( const Vector3iPOD& ); ///< subAssign()。
        Vector3iPOD& operator*=( const Vector3iPOD& ); ///< mulAssign()。
        Vector3iPOD& operator/=( const Vector3iPOD& ); ///< divAssign()。
        //@}
        
        //============================================================
        /// @name 選択
        //@{
        const Vector3iPOD min( const Vector3iPOD& )const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
        const Vector3iPOD max( const Vector3iPOD& )const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
        //@}

        //============================================================
        /// @name クランプ
        //@{
        const Vector3iPOD clamp( const Vector3iPOD& aMin , const Vector3iPOD& aMax )const; ///< aMin以上aMax以下になるようにクランプする。
        const Vector3iPOD clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
        const Vector3iPOD clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
        //@}

        //============================================================
        /// @name 符号
        //@{
        const Vector3iPOD abs()const; ///< 各要素を正に置き換えたベクトルを取得。
        const Vector3iPOD neg()const; ///< 符号を反転させた結果を取得する。
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
        /// x,y,z形式の文字列に変換。
        const ShortString toShortString()const;
        //@}
    };

    /// Vector3iPOD のクラス版。
    class Vector3i : public Vector3iPOD
    {
    public:
        //============================================================
        /// @name コンストラクタ
        //@{
        Vector3i(); ///< Zero() で作成。
        Vector3i( const Vector3iPOD& aXYZ ); ///< コピーして作成。
        Vector3i( s32 aV ); ///< 全要素同じ値で作成。
        Vector3i( const Vector2iPOD& aXY , s32 aZ ); ///< XYZを指定して作成。
        Vector3i( s32 aX , s32 aY , s32 aZ ); ///< XYZを指定して作成。
        //@}
    };
    
    /// Vector3iPOD のエイリアス。
    typedef Vector3iPOD Vec3i;
//@}

} // namespace
#endif
// EOF
