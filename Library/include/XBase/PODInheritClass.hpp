// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_PODINHERITCLASS_HPP)
#else
#define XBASE_INCLUDED_PODINHERITCLASS_HPP

#include <XBase/StaticAssert.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Types
//@{
    /// @brief POD型を継承するクラス用のテンプレートクラス。
    /// @details ゼロクリアコンストラクタとコピーコンストラクタを自動で作成します。
template< typename POD_TYPE >
class PODInheritClass : public POD_TYPE
{
public:
    /// POD型。
    typedef POD_TYPE PODType;

    /// 0クリアの状態で作成する。
    PODInheritClass()
    {
        PODType obj = {};
        static_cast<PODType&>(*this) = obj;
    }

    /// 引数の値をコピーして作成する。
    PODInheritClass(const PODType& aObj)
        : PODType(aObj)
    {
    }

private:
    XBASE_STATIC_ASSERT(TypeTraits::IsPOD< PODType >::Value);
};

//@}

} // namespace
#endif
// EOF
