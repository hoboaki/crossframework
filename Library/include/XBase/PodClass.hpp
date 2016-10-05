// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_PodCLASS_HPP)
#else
#define XBASE_INCLUDED_PodCLASS_HPP

#include <XBase/PodStruct.hpp>
#include <XBase/StaticAssert.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Types
//@{    
    /// @brief Pod型のラッパーテンプレートクラス。
    /// @details
    /// boost::value_initializedのようにデフォルトコンストラクタで必ず初期化をすることで未初期化を防ぎます。
template< typename T >
class PodClass : public PodStruct<T>
{
public:
    /// Struct型のエイリアス。
    typedef ::XBase::PodStruct<T> StructType;

    PodClass() { StructType::ref() = StructType::DefaultValue(); }   ///< 規定値で初期化される。
    PodClass(const PodStruct<T>& aValue) { StructType::ref() = aValue; } ///< 値を指定して初期化。

private:
    typedef StructType SuperClass;
    XBASE_STATIC_ASSERT(TypeTraits::IsPod< StructType >::Value);
    XBASE_STATIC_ASSERT(sizeof(SuperClass) == sizeof(ValueType)); // サイズが同じであることを保証。
};
//@}

} // namespace
#endif
// EOF
