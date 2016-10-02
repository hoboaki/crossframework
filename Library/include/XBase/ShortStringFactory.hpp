// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_SHORTSTRINGFACTORY)
#else
#define XBASE_INCLUDED_SHORTSTRINGFACTORY

#include <XBase/BuiltInTypes.hpp>
#include <XBase/OS.hpp>
#include <XBase/ShortString.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace XBase {

// ShortStringを作る関数群。
class ShortStringFactory
{
public:
    // 特殊化された関数達。
    static const ::XBase::ShortString Create(bool aVal);
    static const ::XBase::ShortString Create(int aVal);
    static const ::XBase::ShortString Create(uint aVal);
    static const ::XBase::ShortString Create(f32 aVal);
    static const ::XBase::ShortString Create(f64 aVal);
    static const ::XBase::ShortString Create(s8 aVal);
    static const ::XBase::ShortString Create(s16 aVal);
    static const ::XBase::ShortString Create(s64 aVal);
    static const ::XBase::ShortString Create(u8 aVal);
    static const ::XBase::ShortString Create(u16 aVal);
    static const ::XBase::ShortString Create(u64 aVal);
#if !defined(XBASE_OS_WINDOWS)
    static const ::XBase::ShortString Create(pword_t aVal);
#endif
    static const ::XBase::ShortString Create(ptr_t aVal);
    static const ::XBase::ShortString Create(const_ptr_t aVal);
    static const ::XBase::ShortString Create(anyptr_t aVal);
    static const ::XBase::ShortString Create(const_anyptr_t aVal);
    static const ::XBase::ShortString Create(const char* aVal);

    // デフォルトの実装。toShortString関数を使う。
    template< typename T, class Cond = void >
    class Impl
    {
    public:
        static const ::XBase::ShortString Create(const T& aObj)
        {
            return aObj.toShortString();
        }
    };

    // 特殊化できなかったものは、Implに委譲。
    template< typename T >
    static const ::XBase::ShortString Create(const T& aObj)
    {
        return Impl< T >::Create(aObj);
    };
};


} // namespace
#endif
// EOF
