// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_REFERENCE_HPP)
#else
#define XBASE_INCLUDED_REFERENCE_HPP

//------------------------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Util
//@{
    /// @brief Ref() 用の参照のラッパークラス。
    /// @details
    /// 通常は Ref() 関数を使うのでこのクラスを意識することはないはずです。
    template< typename T >
    class Reference
    {
    public:
        Reference( T& aRef ) 
            : mPtr( &aRef )
        {
        }

        operator T& ()const
        {
            XBASE_POINTER_ASSERT( mPtr );
            return *mPtr; 
        }

    private:
        T* mPtr;
    };
//@}

} // namespace
#endif
// EOF
