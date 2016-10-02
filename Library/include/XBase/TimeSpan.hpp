// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_TIMESPAN_HPP)
#else
#define XBASE_INCLUDED_TIMESPAN_HPP

#include <XBase/BuiltInTypes.hpp>
#include <XBase/PODInheritClass.hpp>

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-DateTime
//@{
    /// @brief 時間間隔を表現する構造体。
    /// @details
    /// 最小単位(1チック)は100ナノ秒です。@n
    /// 加算・減算に関してオーバーフロー対策は何もしていないためオーバーフローしてもエラーにはなりません。 @n
struct TimeSpanPOD
{
    /// @brief チック数から作成する。
    /// @return 作成された時間間隔。
    /// @param aTicks チック数。
    static const TimeSpanPOD FromTicks(s64 aTicks);

    /// @brief マイクロ秒数から作成する。
    /// @return 作成された時間間隔。
    /// @param aUsecs マイクロ秒数。
    static const TimeSpanPOD FromMicroseconds(s64 aUsecs);

    /// @brief ミリ秒数から作成する。
    /// @return 作成された時間間隔。
    /// @param aMsecs ミリ秒数。
    static const TimeSpanPOD FromMilliseconds(s64 aMsecs);

    /// @brief 秒数から作成する。
    /// @return 作成された時間間隔。
    /// @param aSecs 秒数。
    static const TimeSpanPOD FromSeconds(s64 aSecs);

    /// @brief 分数から作成する。
    /// @return 作成された時間間隔。
    /// @param aMinutes 分数。
    static const TimeSpanPOD FromMinnutes(s64 aMinutes);

    /// @brief 時数から作成する。
    /// @return 作成された時間間隔。
    /// @param aHours 時数。
    static const TimeSpanPOD FromHours(s64 aHours);

    /// @brief 日数から作成する。
    /// @return 作成された時間間隔。
    /// @param aDays 日数。
    static const TimeSpanPOD FromDays(s64 aDays);

    /// @brief チック数として取得する。
    /// @return チック数。
    s64 ticks()const;

    /// @brief マイクロ秒数として取得する。
    /// @return マイクロ秒数。小数点以下は切り捨て。
    s64 microseconds()const;

    /// @brief ミリ秒数として取得する。
    /// @return ミリ秒数。小数点以下は切り捨て。
    s64 milliseconds()const;

    /// @brief 秒数として取得する。
    /// @return 秒数。小数点以下は切り捨て。
    s64 seconds()const;

    /// @brief 分数として取得する。
    /// @return 分数。小数点以下は切り捨て。
    s64 minutes()const;

    /// @brief 時数として取得する。
    /// @return 時数。小数点以下は切り捨て。
    s64 hours()const;

    /// @brief 日数として取得する。
    /// @return 日数。小数点以下は切り捨て。
    s64 days()const;

    /// @brief 加算された時間間隔を取得する。
    /// @param aTimeSpan 加算する時間間隔。
    /// @return 求められた時間間隔。
    const TimeSpanPOD add(const TimeSpanPOD& aTimeSpan)const;
    const TimeSpanPOD operator+(const TimeSpanPOD& aTimeSpan)const; ///< @copydoc add

    /// @brief 時間間隔を加算する。
    /// @return 加算された自分自身の参照。
    /// @param aTimeSpan 加算する時間間隔。
    TimeSpanPOD& addAssign(const TimeSpanPOD& aTimeSpan);
    TimeSpanPOD& operator+=(const TimeSpanPOD& aTimeSpan); ///< @copydoc addAssign

    /// @brief 減算された時間間隔を取得する。
    /// @param aTimeSpan 減算する時間間隔。
    /// @return 求められた時間間隔。
    const TimeSpanPOD sub(const TimeSpanPOD& aTimeSpan)const;
    const TimeSpanPOD operator-(const TimeSpanPOD& aTimeSpan)const; ///< @copydoc sub

    /// @brief 時間間隔を減算する。
    /// @return 減算された自分自身の参照。
    /// @param aTimeSpan 減算する時間間隔。
    TimeSpanPOD& subAssign(const TimeSpanPOD& aTimeSpan);
    TimeSpanPOD& operator-=(const TimeSpanPOD& aTimeSpan); ///< @copydoc subAssign

    // 値。直接アクセスすることは想定していない。
    s64 ticks_;
};

/// TimeSpanPOD のクラス版。
typedef PODInheritClass< TimeSpanPOD > TimeSpan;
//@}

} // namespace
#endif
// EOF
