// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_DEGREE_HPP)
#else
#define XBASE_INCLUDED_DEGREE_HPP

#include <XBase/BuiltInTypes.hpp>

namespace XBase {
class  Angle;
struct RadianPod;
}

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Math
//@{
/// 度を扱う構造体。
struct DegreePod
{
    f32 value; ///< 度の値。

    /// @name 変換
    //@{
    const Angle     toAngle()const;  ///< 角度に変換。
    const RadianPod toRadian()const; ///< ラジアンに変換。
    //@}
};

/// DegreePod のクラス版。
class Degree : public DegreePod
{
public:
    /// @name コンストラクタ
    //@{
    Degree(); ///< 0度を作成。
    Degree(float aDegree); ///< 値を指定して作成。
    Degree(const DegreePod& aVal); ///< コピーして作成。
    //@}
};
//@}

} // namespace
#endif
// EOF
