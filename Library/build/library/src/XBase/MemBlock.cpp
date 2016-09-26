/**
 * @file
 * @brief MemBlock.hppの実装を記述する。
 * @author akino
 */
#include <XBase/MemBlock.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
MemBlock::MemBlock()
: mAddr( 0 )
, mSize( 0 )
{
}

//------------------------------------------------------------
MemBlock::MemBlock( const ptr_t aAddr , const pword_t aSize )
: mAddr( aAddr )
, mSize( aSize )
{
}

//------------------------------------------------------------
bool MemBlock::isNull()const
{
    return mAddr == 0;
}

//------------------------------------------------------------
ptr_t MemBlock::head()const
{
    return mAddr;
}

//------------------------------------------------------------
ptr_t MemBlock::tail()const
{
    return mAddr + mSize;
}

//------------------------------------------------------------
pword_t MemBlock::size()const
{
    return mSize;
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
