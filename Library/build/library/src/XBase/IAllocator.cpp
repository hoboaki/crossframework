// 文字コード：UTF-8
#include <XBase/IAllocator.hpp>

//------------------------------------------------------------------------------
#include <memory>
#include <XBase/FunctionAttribute.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/Unused.hpp>

//------------------------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------------------------
namespace {
    class tDefaultAllocatorObj
    {
    public:
        tDefaultAllocatorObj()
            : ptr( IAllocator::OperatorNewDelete() )
        {
        }
        Pointer< IAllocator > ptr;
    };
    tDefaultAllocatorObj tDefaultAllocator;
}
//------------------------------------------------------------------------------
IAllocator::~IAllocator()
{
}

//------------------------------------------------------------------------------
IAllocator& IAllocator::Default()
{
    return *tDefaultAllocator.ptr;
}

//------------------------------------------------------------------------------
void IAllocator::SetDefault( IAllocator& aAllocator )
{
    tDefaultAllocator.ptr.reset( &aAllocator );
}

//------------------------------------------------------------------------------
IAllocator& IAllocator::OperatorNewDelete()
{
    class OperatorNewDeleteAllocator : public IAllocator
    {
    public:
        XBASE_OVERRIDE( ptr_t alloc( pword_t aSize , pword_t aAlignment ) )
        {
            XBASE_UNUSED( aAlignment );
            void* ptr = ::operator new( aSize , std::nothrow_t() );
            XBASE_EQUALS_ASSERT( pword_t( ptr ) % aAlignment , 0 );
            return static_cast< ptr_t >( ptr );
        }
        XBASE_OVERRIDE( void free( ptr_t aPtr ) )
        {
            ::operator delete( aPtr , std::nothrow_t() );
        }
    };
    static OperatorNewDeleteAllocator obj;
    return obj;
}

//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
void* operator new( const std::size_t aSize , ::XBase::IAllocator& aAllocator )
{
    return aAllocator.alloc( aSize );
}

//------------------------------------------------------------------------------
void* operator new[]( const std::size_t aSize , ::XBase::IAllocator& aAllocator )
{
    return aAllocator.alloc( aSize );
}

//------------------------------------------------------------------------------
void operator delete( void* aPtr , ::XBase::IAllocator& aAllocator )
{
    aAllocator.free( ::XBase::ptr_t( aPtr ) );
}

//------------------------------------------------------------------------------
void operator delete[]( void* aPtr , ::XBase::IAllocator& aAllocator )
{
    aAllocator.free( ::XBase::ptr_t( aPtr ) );
}

//------------------------------------------------------------------------------
// EOF
