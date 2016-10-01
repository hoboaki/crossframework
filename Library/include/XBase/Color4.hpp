/**
 * @file
 * @brief Color4,Color4POD型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_COLOR4_HPP)
#else
#define XBASE_INCLUDED_COLOR4_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/ShortString.hpp>

//------------------------------------------------------------
namespace XBase {
    struct Color3POD;
    struct Color4bPOD;
    struct Vector4POD;
}

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Util
//@{
    /// 32bit浮動小数をRGBAの順に並べた色構造体。
    struct Color4POD
    {
        //============================================================
        /// @name 定数取得
        //@{
        static const Color4POD Zero();     ///< 0の色。
        static const Color4POD One();      ///< R,G,B,Aが全て1の色。
        static const Color4POD UnitR();    ///< Rだけ1の色。
        static const Color4POD UnitG();    ///< Gだけ1の色。
        static const Color4POD UnitB();    ///< Bだけ1の色。
        static const Color4POD UnitA();    ///< Aだけ1の色。
        //@}

        //============================================================
        /// @name 変数
        //@{
        f32 r; ///< r。
        f32 g; ///< g。
        f32 b; ///< b。
        f32 a; ///< a。
        //@}
        
        //============================================================
        /// @name 変換
        //@{
        const Color3POD toRGB()const;
        const Color3POD toRRR()const;
        const Color3POD toGGG()const;
        const Color3POD toBBB()const;
        const Color3POD toAAA()const;
        const Color4POD toRRRR()const;
        const Color4POD toGGGG()const;
        const Color4POD toBBBB()const;
        const Color4POD toAAAA()const;
        const Color4bPOD toRGBAb()const;
        const Vector4POD toVector4()const;
        //@}

        //============================================================
        /// @name 等価比較
        //@{
        bool equals( const Color4POD& )const;       ///< 許容誤差を考慮した等価比較。。
        bool equalsStrict( const Color4POD& )const; ///< 許容誤差を許容しない等価比較。
        //@}

        //============================================================
        /// @name 四則演算
        //@{
        const Color4POD add( f32 )const; ///< 各要素に値を加算した結果を取得する。
        const Color4POD sub( f32 )const; ///< 各要素から値を減算した結果を取得する。
        const Color4POD mul( f32 )const; ///< 各要素に値をかけた結果を取得する。
        const Color4POD div( f32 )const; ///< 各要素から値をわった結果を取得する。
        const Color4POD add( const Color4POD& )const; ///< 対応する値同士を加算した結果を取得する。
        const Color4POD sub( const Color4POD& )const; ///< 対応する値に対して減算した結果を取得する。
        const Color4POD mul( const Color4POD& )const; ///< 対応する値同士をかけた結果を取得する。
        const Color4POD div( const Color4POD& )const; ///< 対応する値に対して割り算をした結果を取得する。
        const Color4POD neg()const; ///< 符号を反転させた結果を取得する。
        void addAssign( f32 ); ///< 各要素に値を加算する。
        void subAssign( f32 ); ///< 各要素から値を減算する。
        void mulAssign( f32 ); ///< 各要素に値をかける。
        void divAssign( f32 ); ///< 各要素から値をわる。
        void addAssign( const Color4POD& ); ///< 対応する値同士を加算する。
        void subAssign( const Color4POD& ); ///< 対応する値に対して減算する。
        void mulAssign( const Color4POD& ); ///< 対応する値同士をかける。
        void divAssign( const Color4POD& ); ///< 対応する値に対して割り算をする。       
        //@}
        
        //============================================================
        /// @name 演算子オーバーロード
        //@{
        const Color4POD operator+( f32 )const; ///< add()。
        const Color4POD operator-( f32 )const; ///< sub()。
        const Color4POD operator*( f32 )const; ///< mul()。
        const Color4POD operator/( f32 )const; ///< div()。
        const Color4POD operator+( const Color4POD& )const; ///< add()。
        const Color4POD operator-( const Color4POD& )const; ///< sub()。
        const Color4POD operator*( const Color4POD& )const; ///< mul()。
        const Color4POD operator/( const Color4POD& )const; ///< div()。
        const Color4POD operator-()const; ///< negate()。
        Color4POD& operator+=( f32 ); ///< addAssign()。
        Color4POD& operator-=( f32 ); ///< subAssign()。
        Color4POD& operator*=( f32 ); ///< mulAssign()。
        Color4POD& operator/=( f32 ); ///< divAssign()。
        Color4POD& operator+=( const Color4POD& ); ///< addAssign()。
        Color4POD& operator-=( const Color4POD& ); ///< subAssign()。
        Color4POD& operator*=( const Color4POD& ); ///< mulAssign()。
        Color4POD& operator/=( const Color4POD& ); ///< divAssign()。
        //@}

        //============================================================
        /// @name ユーティリティ
        //@{
        /// r,g,b,a形式の文字列に変換。
        const ShortString toShortString()const;
        //@}
    };

    /// Color4POD のクラス版。
    class Color4 : public Color4POD
    {
    public:
        //============================================================
        /// @name コンストラクタ
        //@{
        Color4(); ///< Zero() で作成。
        Color4( const Color4POD& aRGBA ); ///< コピーして作成。
        Color4( f32 aR , f32 aG , f32 aB , f32 aA ); ///< RGBAを指定して作成。
        Color4( const Vector4POD& aVec ); ///< ベクトルのXYZWをRGBAとみなして作成。
        //@}
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
