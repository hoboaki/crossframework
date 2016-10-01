/**
 * @file
 * @brief ScalerClass型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_SCALERCLASS_HPP)
#else
#define XBASE_INCLUDED_SCALERCLASS_HPP

//------------------------------------------------------------
#include <XBase/StaticAssert.hpp>
#include <XBase/ScalerStruct.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Types
//@{
    /**
     * @brief Scaler型のラッパーテンプレートクラス。
     * @copydetails PODClass
     */
    template< typename T >
    class ScalerClass : public ScalerStruct<T>
    {
    public:
        /// @name コンストラクタ
        //@{
        /// 既定値で初期化する。
        ScalerClass() : SuperClass() {}

        /// 指定された値で初期化する。
        ScalerClass( const typename ScalerStruct<T>::ValueType aValue )
        {
            SuperClass::value_ = aValue;
        };
        //@}

    private:
        typedef ::XBase::ScalerStruct<T> SuperClass; // 親クラスのエイリアス。
        XBASE_STATIC_ASSERT( sizeof( SuperClass ) == sizeof( ValueType ) ); // サイズが同じであることを保証。        
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
