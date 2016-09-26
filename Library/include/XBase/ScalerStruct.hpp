/**
 * @file
 * @brief ScalerStruct型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_SCALERSTRUCT_HPP)
#else
#define XBASE_INCLUDED_SCALERSTRUCT_HPP

//------------------------------------------------------------
#include <limits>
#include <XBase/PODStruct.hpp>
#include <XBase/ShortString.hpp>
#include <XBase/ShortStringFactory.hpp>
#include <XBase/StaticAssert.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Types
//@{
    /// Scaler型のPODラッパーテンプレート構造体。
    template< typename T >
    struct ScalerStruct : public PODStruct<T>
    {
        static typename PODStruct<T>::ValueType MaxValue() { return std::numeric_limits< typename PODStruct<T>::ValueType >::max(); } ///< 最大値を取得する。 @return 最大値。
        static typename PODStruct<T>::ValueType MinValue(){ return std::numeric_limits< typename PODStruct<T>::ValueType >::min(); } ///< 最小値を取得する。 @return 最小値。

        /// ShortStringに変換する。@return 変換された文字列。
        const ShortString toShortString()const { return ::XBase::ShortStringFactory::Create( PODStruct<T>::readRef() ); }

    private:
        typedef ::XBase::PODStruct< T > SuperStruct; // 親クラスのエイリアス。
        XBASE_STATIC_ASSERT( TypeTraits::IsPOD< SuperStruct >::Value ); // POD型のチェック。
        XBASE_STATIC_ASSERT( sizeof( SuperStruct ) == sizeof( ValueType ) ); // サイズが同じであることを保証。        
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
