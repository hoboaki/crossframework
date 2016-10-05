// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_PodINHERITCLASS_HPP)
#else
#define XBASE_INCLUDED_PodINHERITCLASS_HPP

#include <XBase/StaticAssert.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Types
//@{
    /// @brief Pod型を継承するクラス用のテンプレートクラス。
    /// @details ゼロクリアコンストラクタとコピーコンストラクタを自動で作成します。
template< typename Pod_TYPE >
class PodInheritClass : public Pod_TYPE
{
public:
    /// Pod型。
    typedef Pod_TYPE PodType;

    /// 0クリアの状態で作成する。
    PodInheritClass()
    {
        PodType obj = {};
        static_cast<PodType&>(*this) = obj;
    }

    /// 引数の値をコピーして作成する。
    PodInheritClass(const PodType& aObj)
        : PodType(aObj)
    {
    }

private:
    XBASE_STATIC_ASSERT(TypeTraits::IsPod< PodType >::Value);
};

//@}

} // namespace
#endif
// EOF
