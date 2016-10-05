// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_ENUM_HPP)
#else
#define XBASE_INCLUDED_ENUM_HPP

#include <XBase/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Types
//@{
    /// @brief EnumTmpl のPod版。
template< typename ENUM_TYPE, typename DATA_TYPE >
struct EnumPodTmpl
{
    //============================================================
    // private
    DATA_TYPE val_;

    //============================================================
    // public

    /// @name typedef
    //@{
    typedef ENUM_TYPE EnumType;
    typedef DATA_TYPE DataType;
    //@}

    /// @name operator実装
    //@{
    /// @brief enum値代入。
    /// @details
    /// これを定義することで下記のコードが実行できるようになります。
    /// @code
    /// enum Color
    /// {
    /// Color_Red,
    /// Color_Green,
    /// Color_Blue,
    /// // term
    /// Color_TERMINATE
    /// };
    /// EnumPodTmpl< Color , int > color;
    /// color = Color_Red; // 代入できる
    /// @endcode
    EnumPodTmpl< ENUM_TYPE, DATA_TYPE >& operator=(const ENUM_TYPE aVal)
    {
        val_ = DataType(aVal);
        return *this;
    }

    /// @brief enum値取得。
    /// @details
    /// これを定義することで下記のコードが実行できるようになります。
    /// @code
    /// void func( const EnumPodTmpl< Color , int >& aColor )
    /// {
    ///     Color var = aColor; // enumの値を取得できるのでこのように代入できる
    /// }
    /// @endcode
    operator ENUM_TYPE()const
    {
        return ENUM_TYPE(val_);
    }
    //@}
};

/// @brief 組み込み型を指定したenum値。
/// @details
/// enumの変数サイズは環境によって変わります。 @n
/// それをを防ぎたいときにこのテンプレート構造体を使います。 @n
/// DATA_TYPEに指定した組み込み型を指定します。@n
/// データとしては0以外の値が入っていたらtrueと扱います。@n
template< typename ENUM_TYPE, typename DATA_TYPE >
class EnumTmpl : public EnumPodTmpl< ENUM_TYPE, DATA_TYPE >
{
public:
    /// @name コンストラクタ
    //@{
    /// 0として作成。
    EnumTmpl()
    {
        EnumPodTmpl< ENUM_TYPE, DATA_TYPE >::val_ = 0;
    }

    /// 値を指定して作成。
    EnumTmpl(const ENUM_TYPE aVal)
    {
        EnumPodTmpl< ENUM_TYPE, DATA_TYPE >::val_ = DataType(aVal);
    }
    //@}
};

/// @name EnumTmpl EnumPodTmpl をラップする型。
//@{
template< typename ENUM_TYPE > class Enum8 : public EnumTmpl< ENUM_TYPE, s8  > { public: Enum8() {};  Enum8(const ENUM_TYPE aVal) { EnumTmpl< ENUM_TYPE, s8   >::val_ = s8(aVal); } };  ///< 8bitクラス版。
template< typename ENUM_TYPE > class Enum16 : public EnumTmpl< ENUM_TYPE, s16 > { public: Enum16() {}; Enum16(const ENUM_TYPE aVal) { EnumTmpl< ENUM_TYPE, s16  >::val_ = s16(aVal); } };  ///< 16bitクラス版。
template< typename ENUM_TYPE > class Enum32 : public EnumTmpl< ENUM_TYPE, s32 > { public: Enum32() {}; Enum32(const ENUM_TYPE aVal) { EnumTmpl< ENUM_TYPE, s32  >::val_ = s32(aVal); } }; ///< 32bitクラス版。
template< typename ENUM_TYPE > class Enum64 : public EnumTmpl< ENUM_TYPE, s64 > { public: Enum64() {}; Enum64(const ENUM_TYPE aVal) { EnumTmpl< ENUM_TYPE, s64  >::val_ = s64(aVal); } }; ///< 64bitクラス版。

template< typename ENUM_TYPE > class Enum : public Enum8< ENUM_TYPE > { public: Enum(const ENUM_TYPE aVal) { Enum8< ENUM_TYPE >::val_ = aVal; } }; ///< 標準のクラス版(8bit)。
//@}

//@}

} // namespace
#endif
// EOF
