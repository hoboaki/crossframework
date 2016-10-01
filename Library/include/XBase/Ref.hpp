// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_REF_HPP)
#else
#define XBASE_INCLUDED_REF_HPP

//------------------------------------------------------------------------------
#include <XBase/Reference.hpp>

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Util
//@{
    /// std::tr1::ref と同じ役割の関数。
    template< typename T >
    const Reference< T > Ref( T& aObj )
    {
        return Reference< T >( aObj );
    }
//@}

} // namespace
#endif
// EOF
