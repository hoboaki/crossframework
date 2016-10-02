// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_COLOR4U8_HPP)
#else
#define XBASE_INCLUDED_COLOR4U8_HPP

#include <XBase/BuiltInTypes.hpp>
#include <XBase/ShortString.hpp>

namespace XBase {
struct Color3bPOD;
struct Color4POD;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Util
//@{
/// 8bit符号無し整数をRGBAの順に並べた色構造体。
struct Color4bPOD
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Color4bPOD Zero();     ///< 0の色。
    static const Color4bPOD One();      ///< R,G,B,Aが全て255の色。
    static const Color4bPOD UnitR();    ///< Rだけ1の色。
    static const Color4bPOD UnitG();    ///< Gだけ1の色。
    static const Color4bPOD UnitB();    ///< Bだけ1の色。
    static const Color4bPOD UnitA();    ///< Aだけ1の色。
    //@}

    //============================================================
    /// @name 変数
    //@{
    u8 r; ///< r。
    u8 g; ///< g。
    u8 b; ///< b。
    u8 a; ///< a。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Color3bPOD toRGB()const;
    const Color3bPOD toRRR()const;
    const Color3bPOD toGGG()const;
    const Color3bPOD toBBB()const;
    const Color3bPOD toAAA()const;
    const Color4bPOD toRRRR()const;
    const Color4bPOD toGGGG()const;
    const Color4bPOD toBBBB()const;
    const Color4bPOD toAAAA()const;
    const Color4POD toRGBAf()const;
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// r,g,b,a形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Color4bPOD のクラス版。
class Color4b : public Color4bPOD
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Color4b(); ///< Zero() で作成。
    Color4b(const Color4bPOD& aRGBA); ///< コピーして作成。
    Color4b(u8 aR, u8 aG, u8 aB, u8 aA); ///< RGBAを指定して作成。
    //@}
};
//@}

} // namespace
#endif
// EOF
