// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_ANGLE_HPP)
#else
#define XBASE_INCLUDED_ANGLE_HPP

//------------------------------------------------------------------------------
#include <XBase/BuiltinTypes.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    struct DegreePOD;
    struct RadianPOD;
}
//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /// 角度を示すクラス。
    class Angle
    {
    public:
        /// @name コンストラクタ
        //@{
        Angle(); ///< 0度で作成。
        Angle( const DegreePOD& ); ///< Degreeで作成。
        Angle( const RadianPOD& ); ///< Radianで作成。
        //@}

        /// @name 角度の取得
        //@{
        f32 rad()const; ///< radianで取得。
        f32 deg()const; ///< degreeで取得。
        //@}

    private:
        f32 mRad;
    };
//@}

} // namespace
#endif
// EOF
