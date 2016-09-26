/**
 * @file
 * @brief TimeSpan.hppの実装を記述する。
 * @author akino
 */
#include <XBase/TimeSpan.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::FromTicks( const s64 aTicks )
{
    TimeSpanPOD obj = { aTicks };
    return obj;
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::FromMicroseconds( const s64 aUsecs )
{
    return FromTicks( aUsecs * 10 );
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::FromMilliseconds( const s64 aMSecs )
{
    return FromMicroseconds( aMSecs * 1000 );
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::FromSeconds( const s64 aSecs )
{
    return FromMilliseconds( aSecs * 1000 );
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::FromMinnutes( const s64 aMins )
{
    return FromSeconds( aMins * 60 );
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::FromHours( const s64 aHours )
{
    return FromMinnutes( aHours * 60 );
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::FromDays( const s64 aDays )
{
    return FromHours( aDays * 24 );
}

//------------------------------------------------------------
s64 TimeSpanPOD::ticks()const
{
    return ticks_;
}

//------------------------------------------------------------
s64 TimeSpanPOD::microseconds()const
{
    return ticks_ / 10;
}

//------------------------------------------------------------
s64 TimeSpanPOD::milliseconds()const
{
    return ticks_ / ( 1000 * 10 );
}

//------------------------------------------------------------
s64 TimeSpanPOD::seconds()const
{
    return ticks_ / ( 1000 * 1000 * 10 );
}

//------------------------------------------------------------
s64 TimeSpanPOD::minutes()const
{
    return ticks_ / ( 60 * 1000 * 1000 * 10 );
}

//------------------------------------------------------------
s64 TimeSpanPOD::hours()const
{
    return ticks_ / ( s64( 60 ) * 60 * 1000 * 1000 * 10 );
}

//------------------------------------------------------------
s64 TimeSpanPOD::days()const
{
    return ticks_ / ( s64( 24 ) * 60 * 60 * 1000 * 1000 * 10 );
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::add( const TimeSpanPOD& aTimeSpan )const
{
    TimeSpanPOD obj = *this;
    obj += aTimeSpan;
    return obj;
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::operator+( const TimeSpanPOD& aTimeSpan )const
{
    return add( aTimeSpan );
}

//------------------------------------------------------------
TimeSpanPOD& TimeSpanPOD::addAssign( const TimeSpanPOD& aTimeSpan )
{
    ticks_ += aTimeSpan.ticks_;
    return *this;
}

//------------------------------------------------------------
TimeSpanPOD& TimeSpanPOD::operator+=( const TimeSpanPOD& aTimeSpan )
{
    return addAssign( aTimeSpan );
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::sub( const TimeSpanPOD& aTimeSpan )const
{
    TimeSpanPOD obj = *this;
    obj -= aTimeSpan;
    return obj;
}

//------------------------------------------------------------
const TimeSpanPOD TimeSpanPOD::operator-( const TimeSpanPOD& aTimeSpan )const
{
    return sub( aTimeSpan );
}

//------------------------------------------------------------
TimeSpanPOD& TimeSpanPOD::subAssign( const TimeSpanPOD& aTimeSpan )
{
    ticks_ -= aTimeSpan.ticks_;
    return *this;
}

//------------------------------------------------------------
TimeSpanPOD& TimeSpanPOD::operator-=( const TimeSpanPOD& aTimeSpan )
{
    return subAssign( aTimeSpan );
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
