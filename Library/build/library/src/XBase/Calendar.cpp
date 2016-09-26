/**
 * @file
 * @brief Calendar.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Calendar.hpp>

//------------------------------------------------------------
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
namespace
{
    // 範囲チェックをしつつ範囲外なら最小値を返す。
    uint tYearCheck( const uint aYear )
    {
        if ( aYear < Calendar::YearMin
            || Calendar::YearMax < aYear
            )
        {
            XBASE_INVALID_VALUE_ERROR( aYear );
            return Calendar::YearMin;
        }
        return aYear;
    }
    uint tMonthCheck( const uint aMonth )
    {
        if ( aMonth < Calendar::MonthMin
            || Calendar::MonthMax < aMonth
            )
        {
            XBASE_INVALID_VALUE_ERROR( aMonth );
            return Calendar::MonthMin;
        }
        return aMonth;
    }
}

//------------------------------------------------------------
bool CalendarPOD::IsLeapYear( const uint aYear )
{
    // 閏年の定義
    // 1. 西暦年が4で割り切れる年は閏年
    // 2. ただし、西暦年が100で割り切れる年は平年
    // 3. ただし、西暦年が400で割り切れる年は閏年
    // 西暦4年は閏年と扱わなかったらしいという話もあるが
    // .Net4.0 の実装では西暦4年が閏年となっていたためそれに合わせる。
    const uint year = 1 + tYearCheck( aYear );

    if ( ( year % 4 ) != 0 // 4で割り切れないので平年
        || ( ( year % 100 ) == 0 && ( year % 400 ) != 0 ) // 100 で割り切れ 400 で割り切れない年は平年
        )
    {
        return false;
    }

    // 閏年
    return true;
}

//------------------------------------------------------------
uint CalendarPOD::DaysToDate(
    const uint aYear
    , const uint aMonth
    , const uint aDayOfMonth
    )
{
    uint days = 0;
    
    // 年
    {
        // 平年
        days += aYear * 365;
        
        // 閏年補正
        uint addDays = aYear / 4;
        addDays -= aYear / 100;
        addDays += aYear / 400;
        days += addDays;
    }

    // 月
    for ( uint i = 0; i < aMonth; ++i )
    {
        days += DaysInMonth( aYear ,  i );
    }

    // 日
    days += aDayOfMonth;

    return days;
}

//------------------------------------------------------------
const CalendarPOD CalendarPOD::FromDays( const uint aDays )
{
    Calendar calendar;
    uint days = aDays;
    {// 年
        uint year = 0;
        while ( true )
        {
            // その年の総日数を取得
            const uint totalDayOfYear = Calendar::DaysInYear( year );

            // 年を越すか計算
            if ( days < totalDayOfYear )
            {// 年は越さないので終了
                calendar.year      = u16( year );
                calendar.dayOfYear = u16( days );
                break;
            }

            // 次の年へ
            ++year;
            days -= totalDayOfYear;
        }
    }

    {// 月・曜日・日
        uint month = 0;
        while ( true )
        {
            // その月の総日数を取得
            const uint totalDayOfMonth = Calendar::DaysInMonth( calendar.year , month );

            // 月を越すか計算
            if ( days < totalDayOfMonth )
            {// 月は越さないので終了
                calendar.month      = u16( month );
                calendar.dayOfMonth = u16( days );
                calendar.dayOfWeek  = u16( ( FirstDayOfWeek + aDays ) % ( DayOfWeekMax + 1 ) );
                break;
            }

            // 次の月へ
            ++month;
            days -= totalDayOfMonth;
        }
    }

    return calendar;
}

//------------------------------------------------------------
uint CalendarPOD::DaysInYear( const uint aYear )
{
    const uint year = tYearCheck( aYear ); 
    return uint( IsLeapYear( year ) ? 366 : 365 );
}

//------------------------------------------------------------
uint CalendarPOD::DaysInMonth( 
    const uint aYear
    , const uint aMonth 
    )
{
    const uint month = tMonthCheck( aMonth );
    switch( month + 1 ) // 直感的になるように+1
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
        
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;

    case 2:
        return IsLeapYear( tYearCheck( aYear ) ) ? 29 : 28;

    default:
        XBASE_INVALID_VALUE_ERROR( month );
        return 28; // fail safe code
    }
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
