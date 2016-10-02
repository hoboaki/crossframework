// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_VECTOR3_HPP)
#else
#define XBASE_INCLUDED_VECTOR3_HPP

#include <XBase/BuiltInTypes.hpp>
#include <XBase/ShortString.hpp>

namespace XBase {
struct Vector2POD;
struct Vector4POD;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Math
//@{
    /// @brief 浮動小数型3次元ベクトル構造体。
    /// @details 
    /// 使用頻度のことを考えて Vec3 という名前でもアクセスできます。
    /// メモリ配置は32bit浮動小数が先頭からx,y,zの順番に並んでいます。
struct Vector3POD
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Vector3POD Zero();     ///< 0ベクトル。
    static const Vector3POD One();      ///< X,Y,Zが全て1のベクトル。
    static const Vector3POD Min();      ///< 最小値のベクトル。
    static const Vector3POD Max();      ///< 最大値のベクトル。
    static const Vector3POD UnitX();    ///< X単位ベクトル。
    static const Vector3POD UnitY();    ///< Y単位ベクトル。
    static const Vector3POD UnitZ();    ///< Z単位ベクトル。
    static const Vector3POD NegUnitX(); ///< -X単位ベクトル。
    static const Vector3POD NegUnitY(); ///< -Y単位ベクトル。
    static const Vector3POD NegUnitZ(); ///< -Z単位ベクトル。
    //@}

    //============================================================
    /// @name 変数
    //@{
    f32 x; ///< x。
    f32 y; ///< y。
    f32 z; ///< z。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Vector2POD toXY()const;
    const Vector2POD toXX()const;
    const Vector2POD toYY()const;
    const Vector2POD toZZ()const;
    const Vector3POD toX00()const;
    const Vector3POD toXY0()const;
    const Vector3POD to0Y0()const;
    const Vector3POD to0YZ()const;
    const Vector3POD to00Z()const;
    const Vector3POD toXXX()const;
    const Vector3POD toYYY()const;
    const Vector3POD toZZZ()const;
    const Vector4POD toXYZ0()const;
    const Vector4POD toXXXX()const;
    const Vector4POD toYYYY()const;
    const Vector4POD toZZZZ()const;
    //@}

    //============================================================
    /// @name 等価比較
    //@{
    bool equals(const Vector3POD&)const;       ///< 許容誤差を考慮した等価比較。
    bool equalsStrict(const Vector3POD&)const; ///< 許容誤差を許容しない等価比較。
    //@}

    //============================================================
    /// @name 四則演算
    //@{
    const Vector3POD add(f32)const; ///< 各要素に値を加算した結果を取得する。
    const Vector3POD sub(f32)const; ///< 各要素から値を減算した結果を取得する。
    const Vector3POD mul(f32)const; ///< 各要素に値をかけた結果を取得する。
    const Vector3POD div(f32)const; ///< 各要素から値をわった結果を取得する。
    const Vector3POD add(const Vector3POD&)const; ///< 対応する値同士を加算した結果を取得する。
    const Vector3POD sub(const Vector3POD&)const; ///< 対応する値に対して減算した結果を取得する。
    const Vector3POD mul(const Vector3POD&)const; ///< 対応する値同士をかけた結果を取得する。
    const Vector3POD div(const Vector3POD&)const; ///< 対応する値に対して割り算をした結果を取得する。
    void addAssign(f32); ///< 各要素に値を加算する。
    void subAssign(f32); ///< 各要素から値を減算する。
    void mulAssign(f32); ///< 各要素に値をかける。
    void divAssign(f32); ///< 各要素から値をわる。
    void addAssign(const Vector3POD&); ///< 対応する値同士を加算する。
    void subAssign(const Vector3POD&); ///< 対応する値に対して減算する。
    void mulAssign(const Vector3POD&); ///< 対応する値同士をかける。
    void divAssign(const Vector3POD&); ///< 対応する値に対して割り算をする。       
    //@}

    //============================================================
    /// @name 演算子オーバーロード
    //@{
    const Vector3POD operator+(f32)const; ///< add()。
    const Vector3POD operator-(f32)const; ///< sub()。
    const Vector3POD operator*(f32)const; ///< mul()。
    const Vector3POD operator/(f32)const; ///< div()。
    const Vector3POD operator+(const Vector3POD&)const; ///< add()。
    const Vector3POD operator-(const Vector3POD&)const; ///< sub()。
    const Vector3POD operator*(const Vector3POD&)const; ///< mul()。
    const Vector3POD operator/(const Vector3POD&)const; ///< div()。
    const Vector3POD operator-()const; ///< neg()。
    Vector3POD& operator+=(f32); ///< addAssign()。
    Vector3POD& operator-=(f32); ///< subAssign()。
    Vector3POD& operator*=(f32); ///< mulAssign()。
    Vector3POD& operator/=(f32); ///< divAssign()。
    Vector3POD& operator+=(const Vector3POD&); ///< addAssign()。
    Vector3POD& operator-=(const Vector3POD&); ///< subAssign()。
    Vector3POD& operator*=(const Vector3POD&); ///< mulAssign()。
    Vector3POD& operator/=(const Vector3POD&); ///< divAssign()。
    //@}

    //============================================================
    /// @name 選択
    //@{
    const Vector3POD min(const Vector3POD&)const; ///< 指定のベクトルとの各要素の最小値を選択したベクトルを取得する。
    const Vector3POD max(const Vector3POD&)const; ///< 指定のベクトルとの各要素の最大値を選択したベクトルを取得する。
    //@}

    //============================================================
    /// @name クランプ
    //@{
    const Vector3POD clamp(const Vector3POD& aMin, const Vector3POD& aMax)const; ///< aMin以上aMax以下になるようにクランプする。
    const Vector3POD clampPositive()const; ///< clamp( Zero() , Max() ) を取得する。
    const Vector3POD clampNegative()const; ///< clamp( Min() , Zero() ) を取得する。
    //@}

    //============================================================
    /// @name 符号操作
    //@{
    const Vector3POD abs()const; ///< 各要素を正に置き換えたベクトルを取得。
    const Vector3POD neg()const; ///< 符号を反転させた結果を取得する。
    //@}

    //============================================================
    /// @name 長さ＆正規化
    //@{
    f32  squareLength()const;                ///< 長さの2乗を取得する。
    f32  length()const;                      ///< 長さを取得する。
    f32  distance(const Vector3POD&)const; ///< あるベクトルとの距離を取得する。
    bool isZero()const;                      ///< 長さが0か。許容誤差を許す。
    bool isZeroStrict()const;                ///< 長さが0か。許容誤差を許さない。
    bool isUnit()const;                      ///< 正規化済みか。許容誤差を許す。
    const Vector3POD unit()const;            ///< @brief 正規化したベクトルを取得する。 @details 長さ0のベクトルで正規化するとエラーになります。
    void unitAssign();                       ///< @brief 正規化する。 @details 長さ0のベクトルで正規化するとエラーになります。
    //@}

    //============================================================
    /// @name 内積・外積
    //@{
    f32 dot(const Vector3POD&)const;                ///< あるベクトルとの内積を取得する。
    const Vector3POD cross(const Vector3POD&)const; ///< あるベクトルとの外積を取得とる。
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// x,y,z形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Vector3POD のクラス版。
class Vector3 : public Vector3POD
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Vector3(); ///< Zero() で作成。
    Vector3(const Vector3POD& aXYZ); ///< コピーして作成。
    Vector3(f32 aV); ///< 全要素同じ値で作成。
    Vector3(const Vector2POD& aXY, f32 aZ); ///< XYZを指定して作成。
    Vector3(f32 aX, f32 aY, f32 aZ); ///< XYZを指定して作成。
    //@}
};

/// Vector3POD のエイリアス。
typedef Vector3POD Vec3;

/// Vector3POD のエイリアス。
typedef Vector3POD Vector3fPOD;

/// Vec3 のエイリアス。
typedef Vec3 Vec3f;

/// Vector3 のエイリアス。
typedef Vector3 Vector3f;
//@}

} // namespace
#endif
// EOF
