// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_RADIAN_HPP)
#else
#define XBASE_INCLUDED_RADIAN_HPP

#include <XBase/BuiltInTypes.hpp>

namespace XBase {
class  Angle;
struct DegreePOD;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Math
//@{
/// ラジアンを扱う構造体。
struct RadianPOD
{
    f32 value; ///< ラジアン。

    /// @name 変換
    //@{
    const Angle     toAngle()const;  ///< 角度に変換。
    const DegreePOD toDegree()const; ///< 度に変換。
    //@}
};

/// RadianPOD のクラス版。
class Radian : public RadianPOD
{
public:
    /// @name コンストラクタ
    //@{
    Radian(); ///< 0度を作成。
    Radian(float aRadian); ///< 値を指定して作成。
    Radian(const RadianPOD& aVal); ///< コピーして作成。
    //@}
};
//@}

} // namespace
#endif
// EOF
