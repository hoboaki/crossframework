/**
 * @file
 * @brief Calendar,CalendarPOD型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_CALENDAR_HPP)
#else
#define XBASE_INCLUDED_CALENDAR_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/PODInheritClass.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-DateTime
//@{
    /**
     * @brief カレンダー情報を扱う構造体。
     * @details グレゴリアン歴を使っています。
     */
    struct CalendarPOD
    {
        /// @name 定数
        //@{
        enum 
        {
            YearMin =  0,       ///< 年の最小値。
            YearMax =  9998,    ///< 年の最大値。
            MonthMin = 0,       ///< 月の最小値。
            MonthMax = 11,      ///< 月の最大値。
            DayOfYearMin = 0,   ///< 日の最小値
            DayOfYearMax = 365, ///< 日の最大値。
            DayOfMonthMin = 0,  ///< 月の中の日の最小値。
            DayOfMonthMax = 30, ///< 月の中の日の最大値。
            DayOfWeekMin = 0,   ///< 週の中の日の最小値。
            DayOfWeekMax = 6,   ///< 週の中の日の最大値。
            HourMin = 0,        ///< 時の最小値。
            HourMax = 23,       ///< 時の最大値。
            MinuteMin = 0,      ///< 分の最小値。
            MinuteMax = 59,     ///< 分の最大値。
            SecondMin = 0,      ///< 秒の最小値。
            SecondMax = 59,     ///< 秒の最大値。
            MillisecondMin = 0,     ///< ミリ秒の最小値。
            MillisecondMax = 999,   ///< ミリ秒の最大値。
            MicrosecondMin = 0,     ///< マイクロ秒の最小値。
            MicrosecondMax = 999,   ///< マイクロ秒の最大値。
            NanosecondsMin = 0,     ///< ナノ秒の最小値。
            NanosecondsMax = 999,   ///< ナノ秒の最大値。
            FirstDayOfWeek = 1      ///< 西暦1年1月1日の曜日。
        };
        //@}

        /**
         * @brief 指定の年が閏年かどうか取得する。
         * @return 閏年ならtrue。
         * @param aYear 年。値の意味は CalendarPOD::year と同じ。
         */
        static bool IsLeapYear( uint aYear );

        /**
         * @brief 西暦1年1月1日から指定の年・月・日まで何日あるか取得する。
         * @return 日数。
         * @param aYear 年。値の意味は CalendarPOD::year と同じ。
         * @param aMonth 月。値の意味は CalendarPOD::month と同じ。
         * @param aDayOfMonth 日。値の意味は CalendarPOD::dayOfMonth と同じ。
         */
        static uint DaysToDate( uint aYear , uint aMonth , uint aDayOfMonth );

        /**
         * @brief 西暦1年1月1日から指定した日数が経過した日の0:0:0.0.0.0を取得する。
         * @return カレンダー。
         * @param aDays 日数。
         */
        static const CalendarPOD FromDays( uint aDays );

        /**
         * @brief 指定の年の総日数を取得する。
         * @return 総日数。
         * @param aYear 年。値の意味は CalendarPOD::year と同じ。
         */
        static uint  DaysInYear( uint aYear );

        /**
         * @brief 指定の年・月の総日数を取得する。
         * @return 総日数。
         * @param aYear 月が所属する年。値の意味は CalendarPOD::year と同じ。
         * @param aMonth 月。値の意味は CalendarPOD::month と同じ。
         */
        static uint  DaysInMonth( uint aYear , uint aMonth );

        u16 year;       ///< 年。 CalendarPOD::YearMin <= val <= CalendarPOD::YearMax 。0は西暦1年を示す。
        u16 month;      ///< 月。 CalendarPOD::MonthMin <= val <= CalendarPOD::MonthMax 。0は1月を示す。
        u16 dayOfYear;  ///< 日。 CalendarPOD::DayOfYearMin <= val <= CalendarPOD::DayOfYearMax 。0は1月1日を示す。
        u16 dayOfMonth; ///< 月の中の日。 CalendarPOD::DayOfMonthMin <= val <= CalendarPOD::DayOfMonthMax 。0は1日を示す。
        u16 dayOfWeek;  ///< 週の中の日。 CalendarPOD::DayOfWeekMin <= val <= CalendarPOD::DayOfWeekMax 。0は日曜日を示す。
        u16 hour;       ///< 時。 CalendarPOD::HourMin <= val <= CalendarPOD::HourMax 。
        u16 min;        ///< 分。 CalendarPOD::MinuteMin <= val <= CalendarPOD::MinuteMax 。
        u16 sec;        ///< 秒。 CalendarPOD::SecondMin <= val <= CalendarPOD::SecondMax 。
        u16 msec;       ///< ミリ秒。 CalendarPOD::MillisecondMin <= val <= CalendarPOD::MillisecondMax 。
        u16 usec;       ///< マイクロ秒。 CalendarPOD::MicrosecondMin <= val <= CalendarPOD::MicrosecondMax 。
        u16 nsec;       ///< ナノ秒。 CalendarPOD::NanosecondsMin <= val <= CalendarPOD::NanosecondsMax 。
    };

    /// CalendarPOD のクラス版。
    typedef PODInheritClass< CalendarPOD > Calendar;
//@}
}
//------------------------------------------------------------
#endif
// EOF
