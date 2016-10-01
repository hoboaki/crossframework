/**
 * @file
 * @brief TypeTraits型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_TYPETRAITS_HPP)
#else
#define XBASE_INCLUDED_TYPETRAITS_HPP

//------------------------------------------------------------
#include <XBase/Compiler.hpp>

// type_traitsのインクルード
#if defined(XBASE_COMPILER_MSVC)
    #include <type_traits>
#endif

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Types
//@{
    /// 型特性。
    struct TypeTraits
    {
#if defined(XBASE_COMPILER_MSVC)
        template< typename T > 
        struct IsPOD { enum { Value = ::std::tr1::is_pod< T >::value }; };

        template< typename T >
        struct IsScaler { enum { Value = ::std::tr1::is_scaler< T >::value }; };
#else
        // サポートしていないコンパイラでは常にtrueを返す。
        /// POD型。
        template< typename T > struct IsPOD { enum { Value = true }; };
        /// スカラー型か。
        template< typename T > struct IsScaler { enum { Value = true }; };
#endif
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
