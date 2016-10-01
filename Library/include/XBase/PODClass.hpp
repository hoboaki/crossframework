/**
 * @file
 * @brief PODClass型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_PODCLASS_HPP)
#else
#define XBASE_INCLUDED_PODCLASS_HPP

//------------------------------------------------------------
#include <XBase/PODStruct.hpp>
#include <XBase/StaticAssert.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Types
//@{    
    /**
     * @brief POD型のラッパーテンプレートクラス。
     * @details
     * boost::value_initializedのようにデフォルトコンストラクタで必ず初期化をすることで未初期化を防ぎます。
     */
    template< typename T >
    class PODClass : public PODStruct<T>
    {        
    public:
        /// Struct型のエイリアス。
        typedef ::XBase::PODStruct<T> StructType;
                
        PODClass()    { StructType::ref() = StructType::DefaultValue(); }   ///< 規定値で初期化される。
        PODClass( const PODStruct<T>& aValue ) { StructType::ref() = aValue; } ///< 値を指定して初期化。
                
    private:
        typedef StructType SuperClass;
        XBASE_STATIC_ASSERT( TypeTraits::IsPOD< StructType >::Value );
        XBASE_STATIC_ASSERT( sizeof(SuperClass) == sizeof( ValueType ) ); // サイズが同じであることを保証。
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
