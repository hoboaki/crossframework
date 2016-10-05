// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_SCALERSTRUCT_HPP)
#else
#define XBASE_INCLUDED_SCALERSTRUCT_HPP

#include <limits>
#include <XBase/PodStruct.hpp>
#include <XBase/ShortString.hpp>
#include <XBase/ShortStringFactory.hpp>
#include <XBase/StaticAssert.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Types
//@{
    /// Scaler型のPodラッパーテンプレート構造体。
template< typename T >
struct ScalerStruct : public PodStruct<T>
{
    static typename PodStruct<T>::ValueType MaxValue() { return std::numeric_limits< typename PodStruct<T>::ValueType >::max(); } ///< 最大値を取得する。 @return 最大値。
    static typename PodStruct<T>::ValueType MinValue() { return std::numeric_limits< typename PodStruct<T>::ValueType >::min(); } ///< 最小値を取得する。 @return 最小値。

    /// ShortStringに変換する。@return 変換された文字列。
    const ShortString toShortString()const { return ::XBase::ShortStringFactory::Create(PodStruct<T>::readRef()); }

private:
    typedef ::XBase::PodStruct< T > SuperStruct; // 親クラスのエイリアス。
    XBASE_STATIC_ASSERT(TypeTraits::IsPod< SuperStruct >::Value); // Pod型のチェック。
    XBASE_STATIC_ASSERT(sizeof(SuperStruct) == sizeof(ValueType)); // サイズが同じであることを保証。        
};
//@}

} // namespace
#endif
// EOF
